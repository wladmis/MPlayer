#ifndef __VD_VIDEOSTILL_H_
#define __VD_VIDEOSTILL_H_

extern void clearsmpi(void);
extern int vd_mpeg2_reset(sh_video_t *sh_video, int force_reset);
extern int decode_video_still(sh_video_t *sh_video,unsigned char *start,int in_size,int drop_frame, double pts,int enable_still);
extern int vd_decode_mp_preserve(void);
#endif
