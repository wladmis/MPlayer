/*
 * Copyright (C) 2001 Rich Wareham <richwareham@users.sourceforge.net>
 *
 * This file is part of libdvdnav, a DVD navigation library.
 *
 * libdvdnav is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * libdvdnav is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA
 *
 * $Id: dvdnav.h,v 1.31 2003/06/09 15:17:44 mroi Exp $
 *
 */

#ifndef __STREAM_DVDNAV_H_

#ifdef USE_MPDVDNAV		// enable dvdnav support?

#define __STREAM_DVDNAV_H_

#ifdef USE_DVDREAD

#ifdef USE_MPDVDKIT
#if (USE_MPDVDKIT == 2)
#include "libmpdvdkit2/dvd_input.h"
#include "libmpdvdkit2/dvd_reader.h"
#include "libmpdvdkit2/ifo_types.h"
#include "libmpdvdkit2/ifo_read.h"
#include "libmpdvdkit2/nav_read.h"
#else
#include "libmpdvdkit/dvd_input.h"
#include "libmpdvdkit/dvd_reader.h"
#include "libmpdvdkit/ifo_types.h"
#include "libmpdvdkit/ifo_read.h"
#include "libmpdvdkit/nav_read.h"
#endif
#else
#include <dvdread/dvd_input.h>
#include <dvdread/dvd_reader.h>
#include <dvdread/ifo_types.h>
#include <dvdread/ifo_read.h>
#include <dvdread/nav_read.h>
#endif

#include "libmpdvdnav/dvdnav.h"

#if 0
extern int dvd_nav_skip_opening;
extern int dvd_nav_still;
extern int dvdnav_menutype;		/* dvdnav menu type: 0-SPU, 1-BOX, 2-SPU&BOX */
extern int dvdnav_continue_play;
extern int dvdnav_go_title;		/* dvdnav_title_play */
extern int dvdnav_go_part;		/* dvdnav_part_play */
extern int dvdnav_go_menu;		/* call main menu */
extern int dvdnav_go_menu_force;	/* call force main menu with skip intro*/
extern int dvdnav_go_audio;		/* dvdnav set new audio stream */
extern int dvdnav_go_spu;		/* dbdnav set new spu stream */
extern int dvdnav_force_menu;		/* force display menu with simple box */
extern int dvdnav_skipintro;		/* skip intro before dvd menu */
extern int dvdnav_color_spu;		/* enable color spu buttons */
extern int dvdnav_still_repeat;		/* still pgc repeat count */
#ifdef USE_MPDVDNAV_TRACE
extern int dvdnav_trace;		/* print trace messages (only devel)*/
#endif
extern char* dvdmenu_lang;		/* nav menu language */

#ifdef HAVE_NEW_GUI
extern int	dvdnav_window_width;
extern int	dvdnav_window_height;
extern int	dvdnav_window_orig_width;
extern int	dvdnav_window_orig_height;
extern int	dvdnav_mouse_x;
extern int	dvdnav_mouse_y;
extern int	dvdnav_mouse_button;
extern int	dvdnav_mouse_set;
#endif

// dvdnav menu button types
#define DVDNAV_MENUTYPE_SPU	0
#define DVDNAV_MENUTYPE_BOX	1
#define DVDNAV_MENUTYPE_SPU_BOX	2
#endif

#define DVDNAV_MAX_STILL_FRAME	5

#undef max
#define max(x,y) ((x) > (y) ? (x) : (y))
#undef min
#define min(x,y) ((x) < (y) ? (x) : (y))

typedef struct {
  int event;             /* event number fromd dvdnav_events.h */
  void * details;        /* event details */
  int len;               /* bytes in details */
} dvdnav_event_t;


typedef struct stream_dvdnav_event_flg_st {
    unsigned int nop : 1;			// 1
    unsigned int still_frame : 1;		// 2
    unsigned int spu_stream_change : 1;		// 3
    unsigned int audio_stream_change : 1;	// 4
    unsigned int vts_change : 1;		// 5
    unsigned int cell_change : 1;		// 6
    unsigned int nav_packet : 1;		// 7
    unsigned int stop : 1;			// 8
    unsigned int highlight : 1;			// 9
    unsigned int spu_clut_change : 1;		// 10
    unsigned int none1 : 1;
    unsigned int hop_channel : 1;		// 12
    unsigned int wait : 1;			// 13
    unsigned int none2 : 2;
    unsigned int isevent : 1;
} stream_dvdnav_event_flg_t;


typedef struct stream_dvdnav_event_st {
stream_dvdnav_event_flg_t eventflag;
off_t			eventid;
// store dvdnav event parameters
// DVDNAV_STILL_FRAME
int 			still_length;
// DVDNAV_SPU_STREAM_CHANGE
int 			spu_physical_wide;
int 			spu_physical_letterbox;
int 			spu_physical_pan_scan;
// DVDNAV_AUDIO_STREAM_CHANGE
int 			audio_physical;
int 			audio_logical;
// DVDNAV_VTS_CHANGE
int 			vts_old_vtsN;
dvd_read_domain_t 	vts_old_domain;
int 			vts_new_vtsN;
dvd_read_domain_t 	vts_new_domain;
// DVDNAV_CELL_CHANGE
int 			cell_cellN;
int 			cell_pgN;
int64_t 		cell_cell_length;
int64_t 		cell_pg_length;
int64_t 		cell_pgc_length;
int64_t 		cell_cell_start;
int64_t 		cell_pg_start;
int			cell_really_change;
// DVDNAV_HIGHLIGHT
int			hl_display;
uint32_t		hl_palette;
uint16_t		hl_sx,hl_sy,hl_ex,hl_ey;
uint32_t		hl_pts;
uint32_t		hl_buttonN;
// DVDNAV_SPU_CLUT_CHANGE
uint32_t 		spu_clut[16];
uint32_t		spu_palette;
} stream_dvdnav_event_t;



typedef struct {
 int id; // 0 - 31 mpeg; 128 - 159 ac3; 160 - 191 pcm
 int language;
 int type;
 int channels;
} nstream_language_t;

typedef struct {
    dvdnav_t			*dvdnav;		/* libdvdnav handle */
    char			*filename;
    int				started;		/* libdvdnav start */
    int				stopflg;		/* libdvdnav stop event */
    int 			vts_domain;		/* is vts domain flag */
    int		   		old_vts_domain;		/* old vts domain flag */
    uint32_t			tpos;			/* title pos */
    uint32_t			tlen;			/* title length */
    float			final_pts;		/* playback time */

    int32_t 			title;			/* current title number */
    int32_t 			part;			/* current chapter number */
    int32_t			lasttitle;		/* last title number */
    int32_t			lastpart;		/* last chapter number */

    uint8_t  			alang;			/* current audio language */
    uint8_t  			slang;			/* current spu language */
    uint8_t			menu_sid;		/* current menu spu stream id */
    uint8_t 			aspect;			/* current video aspect */
    uint8_t			lastaspect;		/* last aspect */
    uint32_t			titles_nr;		/* number of titles */
    uint32_t			chapters_nr;		/* number of chapters in actual title */
    int 			nr_of_channels;		/* number of audio channels */
    nstream_language_t 		audio_streams[32]; 	/* audio properties */
    int				nr_of_subtitles;	/* number of subtitles */
    nstream_language_t 		subtitles[32];		/* subtitles properties */
    stream_dvdnav_event_t	event;			/* dvdnav event storage st/ructure */
    int				stillflg;		/* still frame mode */
    int				stillcounter;
    int				waitcounter;
    int				lockstillcounter;
    int				lockseek;		/* disable seek sector */
    int				stillok;
    unsigned int		cell_timer;		/* pgc cell timer */
    unsigned int		one_cell_timer;		/* pgc only one cell timer */
    int				back_from_timer;	/* if back from timer then nav_demux_seek required */

    int				cell_cellN;		/* last cellN */
    int				cell_pgN;		/* last pgN */
    int				cell_pgcN;		/* last pgcN */
    int				lock_pgN;		/* lock pgN */
    int				lock_pgcN;		/* lock pgcN */
} dvdnav_priv_t;

// open new dvdnav stream
dvdnav_priv_t * new_dvdnav_stream(char * filename, uint32_t titlenum);
// read dvdnav block or event
int dvdnav_stream_read(dvdnav_priv_t * dvdnav_priv, unsigned char *buf, 
    int *len,stream_dvdnav_event_t *event);
// clear all stored event
void dvdnav_event_clear(dvdnav_priv_t * dvdnav_priv);
// close and free dvdnav
void free_dvdnav_stream(dvdnav_priv_t * dvdnav_priv);
// get palette
unsigned int * dvdnav_stream_get_palette(dvdnav_priv_t * dvdnav_priv);
// call menu action UP,DOWN,LEFT,RIGHT,ACTIVATE & MENU
int dvdnav_menu_action(dvdnav_priv_t * dvdnav_priv, int action);
// go main menu with skip intro
int dvdnav_menu_force(dvdnav_priv_t * dvdnav_priv);
void dvdnav_stream_fullstart(dvdnav_priv_t *dvdnav_priv);
// is dvdnav stop event?
int dvdnav_reallyeof(dvdnav_priv_t * dvdnav_priv);
// set languages
void dvdnav_set_language(dvdnav_priv_t *dvdnav_priv, char* alang, 
    char *slang, char *mlang);
// get lang sid
int dvdnav_lang_from_sid(dvdnav_priv_t * dvdnav_priv, int id);
// get lang sid
int dvdnav_sid_from_lang(dvdnav_priv_t * dvdnav_priv, unsigned char* lang);
// get audio sid
int dvdnav_aid_from_lang(dvdnav_priv_t * dvdnav_priv, unsigned char* lang);
// get subtitles number
int dvdnav_number_of_subs(dvdnav_priv_t * dvdnav_priv);
// get highlight properties
void dvdnav_get_highlight(dvdnav_priv_t *dvdnav_priv,
    dvdnav_highlight_event_t *highlight_event,
    int display_mode);
// show menu button (dvdnav-trace)
void dvdnav_print_buttons(dvdnav_priv_t *dvdnav_priv,char* txt);
// get current button palette
void dvdnav_get_button_palette(dvdnav_priv_t *dvdnav_priv,uint32_t *palette);
#ifdef HAVE_NEW_GUI
// hadler gmplayer mouse
void dvdnav_mouse(dvdnav_priv_t * dvdnav_priv);
#endif // HAVE_NEW_GUI
#endif // USE_DVDREAD

#endif // USE_MPDVDNAV
#endif // __STREAM_DVDNAV_H_
