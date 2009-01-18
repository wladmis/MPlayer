#include <assert.h>
#include <string.h>
#include <stdio.h>

#include <polyp/polypaudio.h>

#include "config.h"
#include "libaf/af_format.h"
#include "mp_msg.h"
#include "audio_out.h"
#include "audio_out_internal.h"

#define POLYP_CLIENT_NAME "MPlayer"

//#define POLYP_DEBUG

/** General driver info */
static ao_info_t info = {
    "Polypaudio audio output",
    "polyp",
    "Lennart Poettering",
    ""
};

/** The sink to connect to */
static char *sink = NULL;

/** Polypaudio playback stream object */
static struct pa_stream *stream = NULL;

/** Polypaudio connection context */
static struct pa_context *context = NULL;

/** Main event loop object */
static struct pa_threaded_mainloop *mainloop = NULL;

/** A temporary variable to store the current volume */
static pa_cvolume volume;
static int volume_initialized = 0;

/** Some special libao macro magic */
LIBAO_EXTERN(polyp)

#define CHECK_DEAD_GOTO(label) do { \
if (!context || pa_context_get_state(context) != PA_CONTEXT_READY || \
    !stream || pa_stream_get_state(stream) != PA_STREAM_READY) { \
        mp_msg(MSGT_AO, MSGL_ERR, "AO: [polyp] Connection died: %s\n", context ? pa_strerror(pa_context_errno(context)) : "NULL"); \
        goto label; \
    }  \
} while(0);

static void context_state_cb(pa_context *c, void *userdata) {
    assert(c);

    switch (pa_context_get_state(c)) {
        case PA_CONTEXT_READY:
        case PA_CONTEXT_TERMINATED:
        case PA_CONTEXT_FAILED:
            pa_threaded_mainloop_signal(mainloop, 0);
            break;

        case PA_CONTEXT_UNCONNECTED:
        case PA_CONTEXT_CONNECTING:
        case PA_CONTEXT_AUTHORIZING:
        case PA_CONTEXT_SETTING_NAME:
            break;
    }
}

static void stream_state_cb(pa_stream *s, void * userdata) {
    assert(s);

    switch (pa_stream_get_state(s)) {

        case PA_STREAM_READY:
        case PA_STREAM_FAILED:
        case PA_STREAM_TERMINATED:
            pa_threaded_mainloop_signal(mainloop, 0);
            break;

        case PA_STREAM_UNCONNECTED:
        case PA_STREAM_CREATING:
            break;
    }
}

static void stream_request_cb(pa_stream *s, size_t length, void *userdata) {
    assert(s);
    
    pa_threaded_mainloop_signal(mainloop, 0);
}

static void stream_latency_update_cb(pa_stream *s, void *userdata) {
    assert(s);
    
    pa_threaded_mainloop_signal(mainloop, 0);
}

static void success_cb(pa_stream *s, int success, void *userdata) {
    assert(s);

    if (userdata)
        *(int*) userdata = success;
    pa_threaded_mainloop_signal(mainloop, 0);
}

/** libao initialization function, arguments are sampling frequency,
 * number of channels, sample type and some flags */
static int init(int rate_hz, int channels, int format, int flags) {
    struct pa_sample_spec ss;
    char hn[128];
    char *host = NULL;

    assert(!context);
    assert(!stream);
    assert(!mainloop);

    if (ao_subdevice) {
        int i = strcspn(ao_subdevice, ":");
        if ((size_t) i >= sizeof(hn))
            i = sizeof(hn)-1;

        if (i > 0) {
            strncpy(host = hn, ao_subdevice, i);
            hn[i] = 0;
        }

        if (ao_subdevice[i] == ':')
            sink = ao_subdevice+i+1;
    }

    ss.channels = channels;
    ss.rate = rate_hz;

    ao_data.samplerate = rate_hz;
    ao_data.format = format;
    ao_data.channels = channels;

    switch (format) {
        case AF_FORMAT_U8:
            ss.format = PA_SAMPLE_U8;
            break;
        case AF_FORMAT_S16_LE:
            ss.format = PA_SAMPLE_S16LE;
            break;
        case AF_FORMAT_S16_BE:
            ss.format = PA_SAMPLE_S16BE;
            break;
        case AF_FORMAT_FLOAT_LE:
            ss.format = PA_SAMPLE_FLOAT32LE;
            break;
        case AF_FORMAT_FLOAT_BE:
            ss.format = PA_SAMPLE_FLOAT32BE;
            break;
        case AF_FORMAT_MU_LAW:
            ss.format = PA_SAMPLE_ULAW;
            break;
        case AF_FORMAT_A_LAW:
            ss.format = PA_SAMPLE_ALAW;
            break;
        default:
            mp_msg(MSGT_AO, MSGL_ERR, "AO: [polyp] Unsupported sample spec\n");
            goto fail;
    }

    if (!pa_sample_spec_valid(&ss)) {
        mp_msg(MSGT_AO, MSGL_ERR, "AO: [polyp] Invalid sample spec\n");
        goto fail;
    }

    ao_data.bps = pa_bytes_per_second(&ss);

    if (!volume_initialized || ss.channels != volume.channels) {
        pa_cvolume_reset(&volume, ss.channels);
        volume_initialized = 1;
    }
    
    if (!(mainloop = pa_threaded_mainloop_new())) {
        mp_msg(MSGT_AO, MSGL_ERR, "AO: [polyp] Failed to allocate main loop\n");
        goto fail;
    }

    if (!(context = pa_context_new(pa_threaded_mainloop_get_api(mainloop), POLYP_CLIENT_NAME))) {
        mp_msg(MSGT_AO, MSGL_ERR, "AO: [polyp] Failed to allocate context\n");
        goto fail;
    }

    pa_context_set_state_callback(context, context_state_cb, NULL);

    if (pa_context_connect(context, host, 0, NULL) < 0) {
        mp_msg(MSGT_AO, MSGL_ERR, "AO: [polyp] Failed to connect to server: %s\n", pa_strerror(pa_context_errno(context)));
        goto fail;
    }

    pa_threaded_mainloop_lock(mainloop);
    
    if (pa_threaded_mainloop_start(mainloop) < 0) {
        mp_msg(MSGT_AO, MSGL_ERR, "AO: [polyp] Failed to start main loop\n");
        goto unlock_and_fail;
    }

    /* Wait until the context is ready */
    pa_threaded_mainloop_wait(mainloop);

    if (pa_context_get_state(context) != PA_CONTEXT_READY) {
        mp_msg(MSGT_AO, MSGL_ERR, "AO: [polyp] Failed to connect to server: %s\n", pa_strerror(pa_context_errno(context)));
        goto unlock_and_fail;
    }

    if (!(stream = pa_stream_new(context, "audio stream", &ss, NULL))) {
        mp_msg(MSGT_AO, MSGL_ERR, "AO: [polyp] Failed to create stream: %s\n", pa_strerror(pa_context_errno(context)));
        goto unlock_and_fail;
    }

    pa_stream_set_state_callback(stream, stream_state_cb, NULL);
    pa_stream_set_write_callback(stream, stream_request_cb, NULL);
    pa_stream_set_latency_update_callback(stream, stream_latency_update_cb, NULL);

    if (pa_stream_connect_playback(stream, sink, NULL, PA_STREAM_INTERPOLATE_TIMING|PA_STREAM_AUTO_TIMING_UPDATE, &volume, NULL) < 0) {
        mp_msg(MSGT_AO, MSGL_ERR, "AO: [polyp] Failed to connect stream: %s\n", pa_strerror(pa_context_errno(context)));
        goto unlock_and_fail;
    }

    /* Wait until the stream is ready */
    pa_threaded_mainloop_wait(mainloop);

    if (pa_stream_get_state(stream) != PA_STREAM_READY) {
        mp_msg(MSGT_AO, MSGL_ERR, "AO: [polyp] Failed to connect to server: %s\n", pa_strerror(pa_context_errno(context)));
        goto unlock_and_fail;
    }

    pa_threaded_mainloop_unlock(mainloop);
    
    return 1;

unlock_and_fail:

    if (mainloop)
        pa_threaded_mainloop_unlock(mainloop);
    
fail:
    
    uninit(1);
    return 0;
}

/** Destroy libao driver */
static void uninit(int immed) {
#ifdef POLYP_DEBUG
    fprintf(stderr, "uninit(%i) ***\n", immed); 
#endif

    if (stream) {
        if (!immed) {
            pa_operation *o;

            pa_threaded_mainloop_lock(mainloop);

            if ((o = pa_stream_drain(stream, success_cb, NULL))) {

                while (pa_operation_get_state(o) != PA_OPERATION_DONE) {
                    CHECK_DEAD_GOTO(fail);
                    pa_threaded_mainloop_wait(mainloop);
                }

            fail:
                
                pa_operation_unref(o);
            }

            pa_threaded_mainloop_unlock(mainloop);
        }
    }

    if (mainloop)
        pa_threaded_mainloop_stop(mainloop);
    
    if (stream) {
        pa_stream_disconnect(stream);
        pa_stream_unref(stream);
        stream = NULL;
    }

    if (context) {
        pa_context_disconnect(context);
        pa_context_unref(context);
        context = NULL;
    }

    if (mainloop) {
        pa_threaded_mainloop_free(mainloop);
        mainloop = NULL;
    }
}

/** Play the specified data to the polypaudio server */
static int play(void* data, int len, int flags) {
    int r = -1;
    pa_operation *o = NULL;
    
    assert(stream);
    assert(context);

#ifdef POLYP_DEBUG
    fprintf(stderr, "playing %lu ***\n", len); 
#endif
    
    pa_threaded_mainloop_lock(mainloop);

    CHECK_DEAD_GOTO(fail);

    if (len) {

        if (pa_stream_write(stream, data, len, NULL, 0, PA_SEEK_RELATIVE) < 0) {
            mp_msg(MSGT_AO, MSGL_ERR, "AO: [polyp] pa_stream_write() failed: %s\n", pa_strerror(pa_context_errno(context)));
            goto fail;
        }
        
    } else {

        if (!(o = pa_stream_trigger(stream, NULL, NULL))) {
            mp_msg(MSGT_AO, MSGL_ERR, "AO: [polyp] pa_stream_trigger() failed: %s\n", pa_strerror(pa_context_errno(context)));
            goto fail;
        }

        /* We don't wait for this operation to complete */
    }

    r = len;
    
fail:
    if (o)
        pa_operation_unref(o);

    pa_threaded_mainloop_unlock(mainloop);
    
    return r;
}

static void cork(int b) {
    pa_operation *o = NULL;
    int success = 0;
    
    assert(stream);
    assert(context);

#ifdef POLYP_DEBUG
    fprintf(stderr, "cork(%i) ***\n", b); 
#endif
    
    pa_threaded_mainloop_lock(mainloop);

    CHECK_DEAD_GOTO(fail);
    
    if (!(o = pa_stream_cork(stream, b, success_cb, &success))) {
        mp_msg(MSGT_AO, MSGL_ERR, "AO: [polyp] pa_stream_cork() failed: %s\n", pa_strerror(pa_context_errno(context)));
        goto fail;
    }
    
    while (pa_operation_get_state(o) != PA_OPERATION_DONE) {
        CHECK_DEAD_GOTO(fail);
        pa_threaded_mainloop_wait(mainloop);
    }

    if (!success) 
        mp_msg(MSGT_AO, MSGL_ERR, "AO: [polyp] pa_stream_cork() failed: %s\n", pa_strerror(pa_context_errno(context)));
    
    pa_operation_unref(o);

fail:
    pa_threaded_mainloop_unlock(mainloop);
}

/** Pause the audio stream by corking it on the server */
static void audio_pause(void) {
    cork(1);
 }

/** Resume the audio stream by uncorking it on the server */
static void audio_resume(void) {
    cork(0);
}

/** Reset the audio stream, i.e. flush the playback buffer on the server side */
static void reset(void) {
    pa_operation *o = NULL;
    int success = 0;
    
    assert(stream);
    assert(context);

#ifdef POLYP_DEBUG
    fprintf(stderr, "reset() ***\n"); 
#endif
    
    pa_threaded_mainloop_lock(mainloop);

    CHECK_DEAD_GOTO(fail);
    
    if (!(o = pa_stream_flush(stream, success_cb, &success))) {
        mp_msg(MSGT_AO, MSGL_ERR, "AO: [polyp] pa_stream_flush() failed: %s\n", pa_strerror(pa_context_errno(context)));
        goto fail;
    }
    
    while (pa_operation_get_state(o) != PA_OPERATION_DONE) {
        CHECK_DEAD_GOTO(fail);
        pa_threaded_mainloop_wait(mainloop);
    }

    if (!success) 
        mp_msg(MSGT_AO, MSGL_ERR, "AO: [polyp] pa_stream_flush() failed: %s\n", pa_strerror(pa_context_errno(context)));
    
    pa_operation_unref(o);

fail:
    pa_threaded_mainloop_unlock(mainloop);
}

/** Return number of bytes that may be written to the server without blocking */
static int get_space(void) {
    size_t l = (size_t) -1;

    pa_threaded_mainloop_lock(mainloop);

    CHECK_DEAD_GOTO(fail);

    l = pa_stream_writable_size(stream);

#ifdef POLYP_DEBUG
    fprintf(stderr, "\nspace = %lu\n", l); 
#endif

fail:
    
    pa_threaded_mainloop_unlock(mainloop);

    return l == (size_t) -1 ? -1 : (int) l;
}

/** Return the current latency in seconds */
static float get_delay(void) {
    pa_usec_t latency = (pa_usec_t) -1;

    pa_threaded_mainloop_lock(mainloop);

    for (;;) {
        CHECK_DEAD_GOTO(fail);

        if (pa_stream_get_latency(stream, &latency, NULL) >= 0)
            break;

        if (pa_context_errno(context) != PA_ERR_NODATA) {
            mp_msg(MSGT_AO, MSGL_ERR, "AO: [polyp] pa_stream_get_latency() failed: %s\n", pa_strerror(pa_context_errno(context)));
            goto fail;
        }
        
        /* Wait until latency data is available again */
        pa_threaded_mainloop_wait(mainloop);
    }

#ifdef POLYP_DEBUG
    fprintf(stderr, "latency=%0.3f sec\n", (double) latency / 1000000); 
#endif

fail:
    pa_threaded_mainloop_unlock(mainloop);

    return (latency == (pa_usec_t) -1) ? 0 : ((float) latency / 1000000.0);
}

/** A callback function that is called when the
 * pa_context_get_sink_input_info() operation completes. Saves the
 * volume field of the specified structure to the global variable volume. */
static void info_func(struct pa_context *c, const struct pa_sink_input_info *i, int is_last, void *userdata) {
    if (is_last < 0) {
        mp_msg(MSGT_AO, MSGL_ERR, "AO: [polyp] Failed to get sink input info: %s\n", pa_strerror(pa_context_errno(context)));
        return;
    }

    if (!i)
        return;

    volume = i->volume;
    volume_initialized = 1;
    
    pa_threaded_mainloop_signal(mainloop, 0);
}

/** Issue special libao controls on the device */
static int control(int cmd, void *arg) {
    
    if (!context || !stream)
        return CONTROL_ERROR;
    
    switch (cmd) {
        
        case AOCONTROL_GET_VOLUME: {
            /* Return the current volume of the playback stream */
            ao_control_vol_t *vol = (ao_control_vol_t*) arg;
            pa_operation *o;

            if (!(o = pa_context_get_sink_input_info(context, pa_stream_get_index(stream), info_func, NULL))) {
                mp_msg(MSGT_AO, MSGL_ERR, "AO: [polyp] pa_stream_get_sink_input_info() failed: %s\n", pa_strerror(pa_context_errno(context)));
                return CONTROL_ERROR;
            }
    
            while (pa_operation_get_state(o) != PA_OPERATION_DONE) {
                CHECK_DEAD_GOTO(fail);
                pa_threaded_mainloop_wait(mainloop);
            }

        fail:
            pa_operation_unref(o);

            if (!volume_initialized) {
                mp_msg(MSGT_AO, MSGL_ERR, "AO: [polyp] pa_stream_get_sink_input_info() failed: %s\n", pa_strerror(pa_context_errno(context)));
                return CONTROL_ERROR;
            }
            
            if (volume.channels != 2)
                vol->left = vol->right = (int) ((pa_cvolume_avg(&volume)*100)/PA_VOLUME_NORM);
            else {
                vol->left = (int) (volume.values[0]*100)/PA_VOLUME_NORM;
                vol->right = (int) (volume.values[1]*100)/PA_VOLUME_NORM;
            }
                
            return CONTROL_OK;
        }
            
        case AOCONTROL_SET_VOLUME: {
            /* Set the playback volume of the stream */
            const ao_control_vol_t *vol = (ao_control_vol_t*) arg;
            pa_operation *o;

            if (!volume_initialized) {
                pa_cvolume_reset(&volume, 2);
                volume_initialized = 1;
            }
            
            if (volume.channels != 2)
                pa_cvolume_set(&volume, volume.channels, ((pa_volume_t) vol->left*PA_VOLUME_NORM)/100);
            else {
                volume.values[0] = ((pa_volume_t) vol->left*PA_VOLUME_NORM)/100;
                volume.values[1] = ((pa_volume_t) vol->right*PA_VOLUME_NORM)/100;
            }

            if (!(o = pa_context_set_sink_input_volume(context, pa_stream_get_index(stream), &volume, NULL, NULL))) {
                mp_msg(MSGT_AO, MSGL_ERR, "AO: [polyp] pa_context_set_sink_input_volume() failed: %s\n", pa_strerror(pa_context_errno(context)));
                return CONTROL_ERROR;
            }

            pa_operation_unref(o);

            /* We don't wait for completion here */
            
            return CONTROL_OK;
        }
            
        default:
            /* Unknown CONTROL command */
            return CONTROL_UNKNOWN;
    }
}
