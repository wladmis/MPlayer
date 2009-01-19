#include "config.h"

#include <stdio.h>
#ifdef HAVE_MALLOC_H
#include <malloc.h>
#endif
#include <stdlib.h>
#include <unistd.h>

#include "mp_msg.h"
#include "help_mp.h"

#include "osdep/timer.h"
#include "osdep/shmem.h"

#include "stream.h"
#include "demuxer.h"
#include "parse_es.h"

#include "codec-cfg.h"

#include "libvo/video_out.h"

#include "stheader.h"
#include "vd.h"
#include "vf.h"

#include "dec_video.h"

#ifdef DYNAMIC_PLUGINS
#include <dlfcn.h>
#endif

#ifdef USE_MPDVDNAV_TRACE
extern int dvdnav_trace;
#endif

#include "libvo/fastmemcpy.h"
mp_image_t *smpi=NULL;
int mp_preserve=0;
#define	MP_STORED_IMAGE_NOSET	-1
#define MP_STORED_IMAGE_OFF	0
#define MP_STORED_IMAGE_ON	1
int mp_stored_image=MP_STORED_IMAGE_NOSET;


extern double video_time_usage;
extern double vout_time_usage;

extern vd_functions_t* mpvdec; // FIXME!

#include "cpudetect.h"

void clearsmpi(void) {smpi=NULL; mp_stored_image=MP_STORED_IMAGE_NOSET;}

int vd_mpeg2_reset(sh_video_t *sh_video, int full_reset)
{
if (!mpvdec) return 0;
if (mp_stored_image==MP_STORED_IMAGE_NOSET) return 0;
if (mp_stored_image==MP_STORED_IMAGE_OFF) return 1;
if (!sh_video->enable_mpeg2_reset) return 0;
mpvdec->control(sh_video, VDCTRL_RESET, &full_reset);
return 1;
}

inline static void copy_mpi(mp_image_t *dmpi, mp_image_t *mpi) {
  if(mpi->flags&MP_IMGFLAG_PLANAR){
    memcpy_pic(dmpi->planes[0],mpi->planes[0], mpi->w, mpi->h,
	       dmpi->stride[0],mpi->stride[0]);
    memcpy_pic(dmpi->planes[1],mpi->planes[1], mpi->chroma_width, mpi->chroma_height,
	       dmpi->stride[1],mpi->stride[1]);
    memcpy_pic(dmpi->planes[2], mpi->planes[2], mpi->chroma_width, mpi->chroma_height,
	       dmpi->stride[2],mpi->stride[2]);
  } else {
    memcpy_pic(dmpi->planes[0],mpi->planes[0], 
	       mpi->w*(dmpi->bpp/8), mpi->h,
	       dmpi->stride[0],mpi->stride[0]);
  }
}


int vd_decode_mp_preserve(void) {return mp_preserve;}

int decode_video_still(sh_video_t *sh_video,unsigned char *start,
    int in_size,int drop_frame, double pts, int enable_still){
vf_instance_t* vf;
mp_image_t *mpi=NULL;
unsigned int t=GetTimer();
unsigned int t2;
double tt;
int ret;

if (in_size>=0 || !enable_still)
    //if(!(sh_video->ds->flags&1) || sh_video->ds->pack_no<5)
    mpi=mpvdec->decode(sh_video, start, in_size, drop_frame);
//------------------------ frame decoded. --------------------

#ifdef ARCH_X86
	// some codecs are broken, and doesn't restore MMX state :(
	// it happens usually with broken/damaged files.
    if(gCpuCaps.has3DNow){
	__asm __volatile ("femms\n\t":::"memory");
    }
    else if(gCpuCaps.hasMMX){
	__asm __volatile ("emms\n\t":::"memory");
    }
#endif

if (mp_stored_image==MP_STORED_IMAGE_NOSET && mpvdec && enable_still)
  {
  if (mpvdec->control(sh_video, VDCTRL_STORED_IMAGE, NULL)==CONTROL_TRUE)
    mp_stored_image=MP_STORED_IMAGE_ON;
    else
    mp_stored_image=MP_STORED_IMAGE_OFF;
  }
mp_preserve=0;
if (in_size>=0 && mpi && enable_still && mp_stored_image==MP_STORED_IMAGE_ON)
  {
  smpi=mpi;		/* It will use copy_mpi() or other solution? */
  if (mpi) mp_preserve=mpi->flags & MP_IMGFLAG_PRESERVE;
  }
if (in_size<0 && enable_still && smpi && mp_stored_image!=MP_STORED_IMAGE_NOSET)
  {
  mpi=smpi;
  }


t2=GetTimer();t=t2-t;
tt = t*0.000001f;
video_time_usage+=tt;

if(!mpi || (drop_frame && !(enable_still && in_size<0))) return 0; // error / skipped frame
//vo_draw_image(video_out,mpi);
vf=sh_video->vfilter;
ret = vf->put_image(vf,mpi, pts); // apply video filters and call the leaf vo/ve
if (in_size>=0 && mpi && enable_still && mp_stored_image==MP_STORED_IMAGE_OFF)
  {
  smpi=mpcodecs_get_image(sh_video, 
	(sh_video->codec->outflags[sh_video->outfmtidx] & CODECS_FLAG_STATIC) ?
	MP_IMGTYPE_STATIC : MP_IMGTYPE_TEMP, MP_IMGFLAG_ACCEPT_WIDTH, 
	sh_video->disp_w, sh_video->disp_h);
  if (smpi) copy_mpi(smpi,mpi);
  }
if(ret>0) vf->control(vf,VFCTRL_DRAW_OSD,NULL);

    t2=GetTimer()-t2;
    tt=t2*0.000001f;
    vout_time_usage+=tt;

return ret;
}
