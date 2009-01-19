/*
 * Copyright (C) 2000 Rich Wareham <richwareham@users.sourceforge.net>
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
 * $Id: dvdnav.c,v 1.63 2004/01/31 17:12:58 jcdutton Exp $
 *
 */

/*
 * Ötvös Attila (Attila, Otvos) created it with the libdvdnav-0.1.10.
 * Useful links:
 * SourceForge.net: DVD tools for Linux
 * http://sourceforge.net/projects/dvd/
 */

#include "config.h"

#ifdef USE_MPDVDNAV		// enable dvdnav support?
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "mp_msg.h"
#include "../libmpdemux/stream.h"
#include "help_mp.h"
#include "osdep/timer.h"
#include "input/input.h"
#include "stream.h"
#include "stream_dvdnav.h"
#include "libvo/video_out.h"
#include "spudec.h"
#include "m_option.h"
#include "m_struct.h"
#include "libmpdvdnav/dvdnav_internal.h"

#define TRACE	// enable trace messages print, usage: -dvdnav-trace options
//#define LOG_DEBUG

int dvd_nav_skip_opening = 0;
int dvd_nav_still = 0;
int dvdnav_menutype = 0;
int dvdnav_continue_play = 0;
int dvdnav_go_title = 0;
int dvdnav_go_part = 0;
int dvdnav_go_menu = 0;
int dvdnav_go_menu_force = 0;
int dvdnav_go_audio = 0;
int dvdnav_go_spu = 0;
int dvdnav_trace = 0;
int dvdnav_force_menu = 0;
int dvdnav_skipintro = 0;
int dvdnav_color_spu = 1;
int dvdnav_still_repeat = DVDNAV_MAX_STILL_FRAME;
char* dvdmenu_lang = NULL;

extern char* dvd_device;
extern int audio_id;
extern int dvdsub_id;
extern char* audio_lang;
extern char* dvdsub_lang;

#ifdef HAVE_NEW_GUI
int	dvdnav_window_width=0;
int	dvdnav_window_height=0;
int	dvdnav_window_orig_width=0;
int	dvdnav_window_orig_height=0;
int	dvdnav_mouse_x=0;
int	dvdnav_mouse_y=0;
int	dvdnav_mouse_orig_x=0;
int	dvdnav_mouse_orig_y=0;
int	dvdnav_mouse_button=0;
int	dvdnav_mouse_set=0;
#endif

off_t	eventnum=0;

int cellxx=0;

static struct stream_priv_s {
  int track;
  char* device;
} stream_priv_dflts = {
  1,
  NULL
};

#define ST_OFF(f) M_ST_OFF(struct stream_priv_s,f)
/// URL definition
static m_option_t stream_opts_fields[] = {
  { NULL, NULL, 0, 0, 0, 0,  NULL }
};
static struct m_struct_st stream_opts = {
  "dvd",
  sizeof(struct stream_priv_s),
  &stream_priv_dflts,
  stream_opts_fields
};


#ifndef _MSC_VER
#include <sys/param.h>
#include <sys/fcntl.h>
#else
#ifndef MAXPATHLEN
#define MAXPATHLEN 255
#endif
#endif /* _MSC_VER */

int dvdnav_seek(dvdnav_priv_t * dvdnav_priv, off_t newpos,stream_t *s)
{
if (dvdnav_priv->lockseek) return 0;
if (dvdnav_sector_search(dvdnav_priv->dvdnav, newpos, SEEK_SET)!=
	DVDNAV_STATUS_OK) {
  if (!newpos) mp_msg(MSGT_CPLAYER,MSGL_ERR,
	MSGTR_MPDVDNAV_ErrorSeek,dvdnav_err_to_string(dvdnav_priv->dvdnav),
	newpos );
  return 0;
  }
return 1;
}

static int seek(stream_t *s, off_t newpos)
{
off_t seekpos;

mp_msg(MSGT_CPLAYER,MSGL_DBG2,"DVDNAV seek pos: %llx\n",newpos);
dvdnav_priv_t* dvdnav_priv=s->priv;
int domain_vts=dvdnav_priv->vts_domain;
if(newpos!=s->pos) {
  if (!domain_vts)
    mp_msg(MSGT_CPLAYER,MSGL_V,"Cannot seek in DVDNAV streams yet!\n");
    else {
    seekpos=newpos/2048;
    if (dvdnav_seek((dvdnav_priv_t*)s->priv,seekpos,s)) s->pos=newpos; }
    }
if (newpos==0) {
  ((dvdnav_priv_t*)(s->priv))->stillcounter=0;
  ((dvdnav_priv_t*)(s->priv))->waitcounter=0;
  ((dvdnav_priv_t*)(s->priv))->lockstillcounter=0;}
return 1;
}

unsigned int * dvdnav_stream_get_palette(dvdnav_priv_t * dvdnav_priv)
{
if (!dvdnav_priv) {
  mp_msg(MSGT_CPLAYER,MSGL_INFO,
	"%s: NULL dvdnav_priv\n",
	__FUNCTION__);
  return NULL;
  }
if (!dvdnav_priv->dvdnav) {
  mp_msg(MSGT_CPLAYER,MSGL_INFO,
	"%s: NULL dvdnav_priv->dvdnav\n",
	__FUNCTION__);
  return NULL;
  }
if (!dvdnav_priv->dvdnav->vm) {
  mp_msg(MSGT_CPLAYER,MSGL_INFO,
	"%s: NULL dvdnav_priv->dvdnav->vm\n",
	__FUNCTION__);
  return NULL;
  }
if (!dvdnav_priv->dvdnav->vm->state.pgc) {
  mp_msg(MSGT_CPLAYER,MSGL_INFO,
	"%s: NULL dvdnav_priv->dvdnav->vm->state.pgc\n",
	__FUNCTION__);
  return NULL;
  }
return dvdnav_priv->dvdnav->vm->state.pgc->palette;
}

int dvdnav_menu_action(dvdnav_priv_t * dvdnav_priv, int action)
{
pci_t* pnavpci;
dsi_t* pnavdsi;
uint32_t buttonN;
pnavpci = dvdnav_get_current_nav_pci( dvdnav_priv->dvdnav );
pnavdsi = dvdnav_get_current_nav_dsi( dvdnav_priv->dvdnav );
dvdnav_status_t nav_status;
if (!dvdnav_priv) return 0;
switch (action) {
  case MP_CMD_DVDNAV_UP:
    nav_status = dvdnav_upper_button_select(dvdnav_priv->dvdnav, pnavpci);
#ifdef USE_MPDVDNAV_TRACE
    dvdnav_print_buttons(dvdnav_priv,"dvdnav cmd up");
#endif
    break;
  case MP_CMD_DVDNAV_DOWN:
    nav_status = dvdnav_lower_button_select(dvdnav_priv->dvdnav, pnavpci);
#ifdef USE_MPDVDNAV_TRACE
    dvdnav_print_buttons(dvdnav_priv,"dvdnav cmd down");
#endif
    break;
  case MP_CMD_DVDNAV_LEFT:
    nav_status = dvdnav_left_button_select(dvdnav_priv->dvdnav, pnavpci);
#ifdef USE_MPDVDNAV_TRACE
    dvdnav_print_buttons(dvdnav_priv,"dvdnav cmd left");
#endif
    break;
  case MP_CMD_DVDNAV_RIGHT:
    nav_status = dvdnav_right_button_select(dvdnav_priv->dvdnav, pnavpci);
#ifdef USE_MPDVDNAV_TRACE
    dvdnav_print_buttons(dvdnav_priv,"dvdnav cmd right");
#endif
    break;
  case MP_CMD_DVDNAV_MENU:
    dvdnav_wait_still_clear(dvdnav_priv->dvdnav);
    dvdnav_priv->cell_timer=0;
    dvdnav_priv->one_cell_timer=0;
    dvdnav_priv->stillflg=0;
#ifdef USE_MPDVDNAV_TRACE
    if (dvdnav_trace) mp_msg(MSGT_CPLAYER,MSGL_INFO,
	    "dvdnav: menu action: Menu Root\n");
#endif
    dvdnav_button_select_auto_action( dvdnav_priv->dvdnav, 0);
    nav_status = dvdnav_menu_call(dvdnav_priv->dvdnav,DVD_MENU_Root);
    break;
  case MP_CMD_DVDNAV_SELECT:
    dvdnav_wait_still_clear(dvdnav_priv->dvdnav);
    dvdnav_priv->cell_timer=0;
    dvdnav_priv->one_cell_timer=0;
    dvdnav_priv->stillflg=0;
#ifdef USE_MPDVDNAV_TRACE
    if (dvdnav_trace) mp_msg(MSGT_CPLAYER,MSGL_INFO,
	    "dvdnav: menu action: Menu Select\n");
#endif
    dvdnav_button_select_auto_action( dvdnav_priv->dvdnav, 0);
    nav_status = dvdnav_button_activate(dvdnav_priv->dvdnav, pnavpci);
    break;
  default:
    return 0;
  }
if (nav_status == DVDNAV_STATUS_ERR) {mp_msg(MSGT_CPLAYER, MSGL_WARN,
	MSGTR_MPDVDNAV_ErrorNav,
	dvdnav_err_to_string(dvdnav_priv->dvdnav));
    return 0;}
return 1;
}

int dvdnav_menu_force(dvdnav_priv_t * dvdnav_priv)
{
return 1;
}

void dvdnav_stream_fullstart(dvdnav_priv_t * dvdnav_priv)
{
if (dvdnav_priv && !dvdnav_priv->started) {
//    dvdnav_stream_reset(dvdnav_priv);
  dvdnav_priv->started=1; }
dvdnav_event_clear(dvdnav_priv);
dvdnav_priv->stillcounter=0;
dvdnav_priv->waitcounter=0;
dvdnav_priv->lockstillcounter=0;
}

int dvdnav_reallyeof(dvdnav_priv_t * dvdnav_priv)
{
if (!dvdnav_priv) return 1;
return dvdnav_priv->stopflg;
}

void dvdnav_set_language(dvdnav_priv_t *dvdnav_priv, char *alang,
    char *slang, char *mlang)	/* set nav languages */
{
if (slang) {
  if (dvdnav_spu_language_select(dvdnav_priv->dvdnav, slang ) !=
      DVDNAV_STATUS_OK)	/* FIXME: don't work! */
    mp_msg(MSGT_FIXME, MSGL_FIXME, "Error on setting spu languages: %s\n",
      dvdnav_err_to_string(dvdnav_priv->dvdnav)); }
if (alang) {
  if (dvdnav_audio_language_select(dvdnav_priv->dvdnav, alang ) !=
      DVDNAV_STATUS_OK)	/* FIXME: don't work! */
    mp_msg(MSGT_FIXME, MSGL_FIXME, "Error on setting audio languages: %s\n",
      dvdnav_err_to_string(dvdnav_priv->dvdnav)); }
if (mlang) {
  if (dvdnav_menu_language_select(dvdnav_priv->dvdnav, dvdmenu_lang ) !=
    DVDNAV_STATUS_OK)
  mp_msg(MSGT_FIXME, MSGL_FIXME, "Error on setting menu languages: %s\n",
    dvdnav_err_to_string(dvdnav_priv->dvdnav)); }
return;
}

int dvdnav_lang_from_sid(dvdnav_priv_t *dvdnav_priv, int id)
{
if (!dvdnav_priv) return 0;
if (id >= dvdnav_priv->nr_of_subtitles) return 0;
return dvdnav_priv->subtitles[id].language;
}

int dvdnav_sid_from_lang(dvdnav_priv_t *dvdnav_priv, unsigned char* lang)
{
if (!dvdnav_priv) return 0;
int code,i;
while(lang && strlen(lang)>=2) {
  code=lang[1]|(lang[0]<<8);
  for(i=0;i<dvdnav_priv->nr_of_subtitles;i++) {
    if(dvdnav_priv->subtitles[i].language==code) {
      mp_msg(MSGT_OPEN,MSGL_V,MSGTR_DVDsubtitleChannel, i, lang[0],lang[1]);
      return i;}
    }
  lang+=2; 
  while (lang[0]==',' || lang[0]==' ') ++lang;
  }
mp_msg(MSGT_OPEN,MSGL_WARN,MSGTR_DVDnoMatchingSubtitle);
return -1;
}

int dvdnav_aid_from_lang(dvdnav_priv_t *dvdnav_priv, unsigned char* lang)
{
if (!dvdnav_priv) return 0;
int code,i;
while(lang && strlen(lang)>=2) {
  code=lang[1]|(lang[0]<<8);
  for(i=0;i<dvdnav_priv->nr_of_channels;i++) {
    if(dvdnav_priv->audio_streams[i].language==code) {
      mp_msg(MSGT_OPEN,MSGL_V,MSGTR_DVDaudioChannel,
	    dvdnav_priv->audio_streams[i].id, lang[0],lang[1]);
      return dvdnav_priv->audio_streams[i].id;}
    }
  lang+=2; 
  while (lang[0]==',' || lang[0]==' ') ++lang;
  }
mp_msg(MSGT_OPEN,MSGL_WARN,MSGTR_DVDnoMatchingAudio);
return -1;
}

int dvdnav_number_of_subs(dvdnav_priv_t *dvdnav_priv)
{
if (!dvdnav_priv) return -1;
return dvdnav_priv->nr_of_subtitles;
}

static void stream_dvdnav_close(stream_t *s)
{
free_dvdnav_stream((dvdnav_priv_t*)s->priv);
}

void dvdnav_event_clear(dvdnav_priv_t * dvdnav_priv)
{
memset(&(dvdnav_priv->event),0,sizeof(stream_dvdnav_event_t));
return;
}

void dvdnav_get_highlight(dvdnav_priv_t *dvdnav_priv,
    dvdnav_highlight_event_t *highlight_event,
    int display_mode)
{
pci_t* pnavpci;
int button_number = -1;
int b_mode = 0;
if (!dvdnav_priv) return;
if (!dvdnav_priv->dvdnav) return;
if (!highlight_event) return;
if (NULL==(pnavpci = dvdnav_get_current_nav_pci( dvdnav_priv->dvdnav ))) return;
dvdnav_get_current_highlight(dvdnav_priv->dvdnav, &(highlight_event->buttonN));
highlight_event->display=display_mode; /* show */
if (highlight_event->display==2) b_mode=1;	/* activate */
if (highlight_event->buttonN > 0 && pnavpci->hli.hl_gi.btn_ns > 0 &&
	highlight_event->display) {
    for (button_number = 0; button_number < pnavpci->hli.hl_gi.btn_ns;
	    button_number++) {
        btni_t *btni = &(pnavpci->hli.btnit[button_number]);
        if(highlight_event->buttonN==button_number+1) {
	    highlight_event->sx=min(btni->x_start,btni->x_end);
	    highlight_event->ex=max(btni->x_start,btni->x_end);
	    highlight_event->sy=min(btni->y_start,btni->y_end);
	    highlight_event->ey=max(btni->y_start,btni->y_end);
	    if (btni->btn_coln==0) highlight_event->palette=0;
		else
		highlight_event->palette=
		    pnavpci->hli.btn_colit.btn_coli[btni->btn_coln-1][b_mode];
	    }
	}
#ifdef USE_MPDVDNAV_TRACE
    if (dvdnav_trace) mp_msg(MSGT_CPLAYER,MSGL_DBG2,
	"dvdnav: get highlight (%i:%i-%i:%i #%i)\n",
	highlight_event->sx,
	highlight_event->sy,
	highlight_event->ex,
	highlight_event->ey,
	highlight_event->buttonN);
#endif
    } else {	/* hide button or none button */
#ifdef USE_MPDVDNAV_TRACE
    if (dvdnav_trace) mp_msg(MSGT_CPLAYER,MSGL_DBG2,
	"dvdnav: get highlight hide\n");
#endif
    highlight_event->sx=0;
    highlight_event->ex=0;
    highlight_event->sy=0;
    highlight_event->ey=0;
    highlight_event->palette=0;
    highlight_event->buttonN=0; }
#ifdef USE_MPDVDNAV_TRACE
    dvdnav_print_buttons(dvdnav_priv,"dvdnav_get_highlight");
#endif
return;
}

void dvdnav_get_button_palette(dvdnav_priv_t *dvdnav_priv,uint32_t *palette)	/* get button palette */
{
pci_t* pnavpci;
int button_number;
int buttonN;
int b_mode = 0;
if (!dvdnav_priv) return;
if (!dvdnav_priv->dvdnav) return;
if (!palette) return;
if (NULL==(pnavpci = dvdnav_get_current_nav_pci( dvdnav_priv->dvdnav )))
  return;
dvdnav_get_current_highlight(dvdnav_priv->dvdnav, &buttonN);	/* get current button ID */
if (pnavpci->hli.hl_gi.btn_ns) {	/* is buttons */
    for (button_number = 0; button_number < pnavpci->hli.hl_gi.btn_ns;
	    button_number++) {
        btni_t *btni = &(pnavpci->hli.btnit[button_number]);
        if(buttonN==button_number+1) {					/* current button? */
	    if (btni->btn_coln==0) *palette=0;
		else *palette=
		    pnavpci->hli.btn_colit.btn_coli[btni->btn_coln-1][b_mode];
	    }
	}
    }
if (*palette==0)	/* if none current button? */
    {
    btni_t *btni = &(pnavpci->hli.btnit[0]);
    if (btni->btn_coln==0) *palette=0;
	else *palette=
	    pnavpci->hli.btn_colit.btn_coli[btni->btn_coln-1][b_mode];
    }
return;
}

void dvdnav_print_buttons(dvdnav_priv_t *dvdnav_priv, char* txt)
{
#ifdef USE_MPDVDNAV_TRACE
if( !mp_msg_test(MSGT_CPLAYER,MSGL_DBG2) ) return; 
pci_t* pnavpci;
int button_number;
int buttonN;
int b_mode = 0;
if (!dvdnav_priv) return;
if (!dvdnav_priv->dvdnav) return;
if (NULL==(pnavpci = dvdnav_get_current_nav_pci( dvdnav_priv->dvdnav )))
  return;
dvdnav_get_current_highlight(dvdnav_priv->dvdnav, &buttonN);	/* get current button ID */
if (pnavpci->hli.hl_gi.btn_ns) {	/* is buttons */
  if (dvdnav_trace) mp_msg(MSGT_CPLAYER,MSGL_INFO,
	"dvdnav: buttons number: %d (%s)\n",
	pnavpci->hli.hl_gi.btn_ns,
	txt);
  for (button_number = 0; button_number < pnavpci->hli.hl_gi.btn_ns;
	    button_number++) {
    btni_t *btni = &(pnavpci->hli.btnit[button_number]);
    if(buttonN==button_number+1) {					/* current button? */
      if (dvdnav_trace) mp_msg(MSGT_CPLAYER,MSGL_INFO,
	"dvdnav: *buttons: #%d (%d:%d,%d:%d)\n",
	button_number,
	btni->x_start,
	btni->y_start,
	btni->x_end,
	btni->y_end);
    } else {
      if (dvdnav_trace) mp_msg(MSGT_CPLAYER,MSGL_INFO,
	"dvdnav:  buttons: #%d (%d:%d,%d:%d)\n",
	button_number,
	btni->x_start,
	btni->y_start,
	btni->x_end,
	btni->y_end);
	}
    }
  } else {
  if (dvdnav_trace) mp_msg(MSGT_CPLAYER,MSGL_INFO,
	"dvdnav: buttons number: no buttons (%s)\n",
	txt);
  }
#endif
return;
}


#ifdef HAVE_NEW_GUI
void dvdnav_mouse(dvdnav_priv_t * dvdnav_priv)
{
pci_t* pnavpci;
if (dvdnav_mouse_set!=1) return;
dvdnav_mouse_set=2;		// Lock mouse event
if (NULL==(pnavpci = dvdnav_get_current_nav_pci( dvdnav_priv->dvdnav )))
  return;
if (dvdnav_window_orig_width>0 &&
    dvdnav_window_orig_height>0 &&
    dvdnav_window_width>0 &&
    dvdnav_window_height>0) {
    // Calculate original mouse position (if scaled window)
  dvdnav_mouse_orig_x=
	dvdnav_mouse_x*dvdnav_window_orig_width/dvdnav_window_width;
  dvdnav_mouse_orig_y=
	dvdnav_mouse_y*dvdnav_window_orig_height/dvdnav_window_height;
  } else {
  dvdnav_mouse_orig_x=dvdnav_mouse_x;
  dvdnav_mouse_orig_y=dvdnav_mouse_y; }
if (pnavpci->hli.hl_gi.btn_ns) {	/* is buttons */
    dvdnav_mouse_select(dvdnav_priv->dvdnav, pnavpci,
	dvdnav_mouse_orig_x,
	dvdnav_mouse_orig_y); /* mouse position select */
#ifdef USE_MPDVDNAV_TRACE
    if (dvdnav_mouse_button) dvdnav_print_buttons(dvdnav_priv,
	"dvdnav_mouse");
#endif
  if (dvdnav_mouse_button) dvdnav_menu_action(dvdnav_priv,
	MP_CMD_DVDNAV_SELECT); }	/* mouse button event */
dvdnav_mouse_set=0;
dvdnav_mouse_button=0;
return;
}
#endif

#define FIRST_AC3_AID 128
#define FIRST_DTS_AID 136
#define FIRST_MPG_AID 0
#define FIRST_PCM_AID 160

int dvdnav_stream_read(dvdnav_priv_t * dvdnav_priv, unsigned char *buf,
    int *len,stream_dvdnav_event_t *event)
{
int eventid = DVDNAV_NOP;

if (!len) return -1;
*len=-1;
if (!dvdnav_priv) return -1;
if (!buf) return -1;
if (dvdnav_priv->stopflg) return -1;

if (dvd_nav_still) {
  mp_msg(MSGT_CPLAYER,MSGL_DBG2,
  MSGTR_MPDVDNAV_ReadInStillActive,
  __FUNCTION__);
  *len=0;
  return -1;
  }
if (dvdnav_get_next_block(dvdnav_priv->dvdnav,buf,&eventid,len)!=
    DVDNAV_STATUS_OK) {
  mp_msg(MSGT_CPLAYER,MSGL_ERR,
	MSGTR_MPDVDNAV_ErrorGetNextBlock,
	dvdnav_err_to_string(dvdnav_priv->dvdnav) );
  *len=-1;
  }
  else if (eventid!=DVDNAV_BLOCK_OK) {
    switch (eventid) {
#if 0
      case DVDNAV_NOP : {
	event->eventflag.nop=1;
	event->eventflag.isevent=1;
	break; }
#endif
      case DVDNAV_STILL_FRAME: {
	event->eventflag.still_frame=1;
	event->eventflag.isevent=1;
	dvdnav_priv->stillflg=1;
	dvdnav_priv->stillok=0;
	dvdnav_still_event_t *still_event = (dvdnav_still_event_t*)(buf);
	event->still_length=still_event->length;
	unsigned int end_time=0;
#ifdef USE_MPDVDNAV_TRACE
	if (dvdnav_trace) mp_msg(MSGT_CPLAYER,MSGL_INFO,
	    "dvdnav: still frame (%x)\n",
	    event->still_length);
#endif
	if (still_event->length==0x01)		// FIXME: TIME HACK
	  {
	  pci_t* pnavpci = dvdnav_get_current_nav_pci( dvdnav_priv->dvdnav );
	  end_time=(pnavpci->pci_gi.e_eltm.hour*3600+
	    pnavpci->pci_gi.e_eltm.minute*60+
	    pnavpci->pci_gi.e_eltm.second)*1000000;
#ifdef USE_MPDVDNAV_TRACE
	  if (dvdnav_trace) {
	    float et=end_time;
	    et=et/1000000;
	    mp_msg(MSGT_CPLAYER,MSGL_INFO,
		    "dvdnav: still wait time %8.3f sec (form pci_t) hack:(\n",
		    et);
	    }
#endif
	  }
	if (event->still_length==0xff) {
	  if (dvdnav_priv->stillcounter<dvdnav_still_repeat)
	    dvdnav_still_back(dvdnav_priv->dvdnav);
	    else
	    dvdnav_priv->stillok=1;
	  } else {
	  if (end_time==0) end_time=still_event->length*1000000;
	  if (!dvdnav_priv->cell_timer) {
	    dvdnav_priv->cell_timer = GetTimer();
	    dvdnav_priv->one_cell_timer = dvdnav_priv->cell_timer;
	    }
	  unsigned int now = GetTimer();
#ifdef USE_MPDVDNAV_TRACE
	  if (dvdnav_trace) {
	    float pt=now-dvdnav_priv->cell_timer;
	    pt=pt/1000000;
	    float et=end_time;
	    et=et/1000000;
	    mp_msg(MSGT_CPLAYER,MSGL_INFO,
		"dvdnav: remains time %8.3f sec\n",
		et-pt);
	    }
#endif
	  if (now-dvdnav_priv->cell_timer<end_time) {	// cell play time end?
	    dvdnav_button_select_auto_action( dvdnav_priv->dvdnav, 1);
	  if (dvdnav_priv->stillcounter<dvdnav_still_repeat)
	    dvdnav_still_back(dvdnav_priv->dvdnav);
	    else
	    dvdnav_priv->stillok=1; // don't let dvdnav stall on this image
	  } else {
	  dvdnav_still_skip(dvdnav_priv->dvdnav);
	  dvdnav_priv->cell_timer=0;
	  dvdnav_priv->one_cell_timer=0;}
	  }
	break; }
      case DVDNAV_SPU_STREAM_CHANGE : {
	event->eventflag.spu_stream_change=1;
	event->eventflag.isevent=1;
	dvdnav_spu_stream_change_event_t *spu_stream_change_event =
	    (dvdnav_spu_stream_change_event_t*)(buf);
	event->spu_physical_wide=
	    spu_stream_change_event->physical_wide;
	event->spu_physical_letterbox=
	    spu_stream_change_event->physical_letterbox;
	event->spu_physical_pan_scan=
	    spu_stream_change_event->physical_pan_scan;
#ifdef USE_MPDVDNAV_TRACE
	if (dvdnav_trace) mp_msg(MSGT_CPLAYER,MSGL_INFO,
	    "dvdnav: spu stream change\n");
#endif
	break; }
      case DVDNAV_AUDIO_STREAM_CHANGE : {
	event->eventflag.audio_stream_change=1;
	event->eventflag.isevent=1;
	dvdnav_audio_stream_change_event_t *audio_stream_change_event =
	    (dvdnav_audio_stream_change_event_t*)(buf);
	event->audio_physical=
	    audio_stream_change_event->physical;
	event->audio_logical=
	    audio_stream_change_event->logical;
#ifdef USE_MPDVDNAV_TRACE
	if (dvdnav_trace) mp_msg(MSGT_CPLAYER,MSGL_INFO,
	    "dvdnav: audio stream change\n");
#endif
	break; }
      case DVDNAV_VTS_CHANGE : {
#ifdef USE_MPDVDNAV_TRACE
	if (dvdnav_trace) mp_msg(MSGT_CPLAYER,MSGL_INFO,
	    "dvdnav: vts change\n");
#endif
	event->eventflag.vts_change=1;
	event->eventflag.isevent=1;
	dvdnav_vts_change_event_t *vts_change_event =
	    (dvdnav_vts_change_event_t*)(buf);
	event->vts_old_vtsN=vts_change_event->old_vtsN;
	event->vts_old_domain=vts_change_event->old_domain;
	event->vts_new_vtsN=vts_change_event->new_vtsN;
	event->vts_new_domain=vts_change_event->new_domain;
	dvdnav_get_position(dvdnav_priv->dvdnav,
	    &(dvdnav_priv->tpos),
	    &(dvdnav_priv->tlen));
	if (!dvdnav_priv->vts_domain)
	  dvdnav_priv->cell_timer=GetTimer();
	  else
	  dvdnav_priv->cell_timer=0;
	event->cell_really_change=1;
	dvdnav_priv->one_cell_timer=dvdnav_priv->cell_timer;
	dvdnav_priv->stillok=0;
	dvdnav_priv->stillflg=0;
	dvdnav_priv->stillcounter=0;
	dvdnav_priv->waitcounter=0;
	dvdnav_priv->lockstillcounter=0;
	break; }
      case DVDNAV_CELL_CHANGE : {
	event->eventflag.cell_change=1;
	event->eventflag.isevent=1;
	dvdnav_cell_change_event_t *cell_change_event =
	    (dvdnav_cell_change_event_t*)(buf);
	event->cell_cellN=cell_change_event->cellN;
	event->cell_pgN=cell_change_event->pgN;
	event->cell_cell_length=cell_change_event->cell_length;
	event->cell_pg_length=cell_change_event->pg_length;
	event->cell_pgc_length=cell_change_event->pgc_length;
	event->cell_cell_start=cell_change_event->cell_start;
	event->cell_pg_start=cell_change_event->pg_start;
	int pgcN = 0;
	dvdnav_get_pgc(dvdnav_priv->dvdnav, &pgcN);
// get dvdnav audio setting
	uint8_t alang=dvdnav_get_active_audio_stream(dvdnav_priv->dvdnav);
	dvdnav_priv->alang=
	    128+dvdnav_get_active_audio_stream(dvdnav_priv->dvdnav);
// get dvdnav spu settings
	dvdnav_priv->slang=dvdnav_get_active_spu_stream(dvdnav_priv->dvdnav);
// get dvdnav aspect settings
	dvdnav_priv->aspect=dvdnav_get_video_aspect(dvdnav_priv->dvdnav);
// setting dvdnav info
	dvdnav_priv->vts_domain=dvdnav_is_domain_vts(dvdnav_priv->dvdnav);
	dvdnav_get_position(dvdnav_priv->dvdnav,
	    &(dvdnav_priv->tpos),
	    &(dvdnav_priv->tlen));
	dvdnav_get_number_of_titles(dvdnav_priv->dvdnav,
	    &(dvdnav_priv->titles_nr));
	dvdnav_priv->part=0;
	dvdnav_priv->title=0;
	event->cell_really_change=0;
	if (dvdnav_priv->cell_cellN!=event->cell_cellN ||
		dvdnav_priv->cell_pgN!=event->cell_pgN ||
		dvdnav_priv->cell_pgcN!=pgcN)	// really cell change?
	  {
	  event->cell_really_change=1;
	  dvdnav_priv->stillcounter=0;
	  dvdnav_priv->waitcounter=0;
	  dvdnav_priv->lockstillcounter=0;
	  }
	if (event->cell_really_change)
	  {
	  dvdnav_priv->stillok=0;
	  dvdnav_priv->cell_timer=GetTimer();
	  dvdnav_priv->one_cell_timer=dvdnav_priv->cell_timer;
	  dvdnav_priv->stillflg=0;
	  dvdnav_priv->stillcounter=0;
	  dvdnav_priv->waitcounter=0;
	  dvdnav_priv->lockstillcounter=0;
	  }
	if (!(dvdnav_priv->vts_domain)) {
	  dvdnav_priv->chapters_nr=0;
	  dvdnav_priv->menu_sid=
		dvdnav_get_active_spu_stream(dvdnav_priv->dvdnav);
	  dvdnav_priv->final_pts=0.0;
	  } else {
	  dvdnav_priv->final_pts = cell_change_event->cell_length;
	  dvdnav_priv->final_pts = dvdnav_priv->final_pts / 90000;
	  dvdnav_current_title_info(dvdnav_priv->dvdnav,
		&dvdnav_priv->title,
		&dvdnav_priv->part);
	  dvdnav_get_number_of_parts(dvdnav_priv->dvdnav,
		dvdnav_priv->title,
		&dvdnav_priv->chapters_nr);
	  event->cell_really_change=1;

	  uint32_t audio_id;
	  audio_attr_t audio_attr;
	  dvdnav_priv->nr_of_channels=0;
	  int language;
	  int i;
	  for( i=0; i<8; i++) {
	    if (-1!=(audio_id=audio_id=
		dvdnav_get_audio_logical_stream(dvdnav_priv->dvdnav, i))) {
	      dvdnav_get_audio_attr(dvdnav_priv->dvdnav, i, &audio_attr);
	      language=0;
	      if(audio_attr.lang_type==1)
	        language=audio_attr.lang_code;
	      dvdnav_priv->audio_streams[dvdnav_priv->nr_of_channels].language=
		    language;
	      dvdnav_priv->audio_streams[dvdnav_priv->nr_of_channels].id=
		    audio_id;
	      switch (audio_attr.audio_format) {
		case 0: // ac3
		  dvdnav_priv->audio_streams[dvdnav_priv->nr_of_channels].id+=
			FIRST_AC3_AID;
		break;
		case 6: // dts
		  dvdnav_priv->audio_streams[dvdnav_priv->nr_of_channels].id+=
			FIRST_DTS_AID;
		break;
		case 2: // mpeg layer 1/2/3
		case 3: // mpeg2 ext
		  dvdnav_priv->audio_streams[dvdnav_priv->nr_of_channels].id+=
			FIRST_MPG_AID;
		break;
		case 4: // lpcm
		  dvdnav_priv->audio_streams[dvdnav_priv->nr_of_channels].id+=
			FIRST_PCM_AID;
		break;
		}
	      dvdnav_priv->audio_streams[dvdnav_priv->nr_of_channels].type=
		    audio_attr.audio_format;
	      dvdnav_priv->audio_streams[dvdnav_priv->nr_of_channels].channels=
		    audio_attr.channels;
	      if (alang==i) dvdnav_priv->alang=
		    dvdnav_priv->audio_streams[dvdnav_priv->nr_of_channels].id;
	      dvdnav_priv->nr_of_channels++;
	      }
	    }
	  dvdnav_priv->nr_of_subtitles=0;
	  uint32_t sub_id;
	  subp_attr_t subp_attr;
	  for( i=0; i<32; i++)
	    {
	    if (-1!=(sub_id=dvdnav_get_spu_logical_stream(dvdnav_priv->dvdnav,
		i))) {
	      dvdnav_get_spu_attr(dvdnav_priv->dvdnav, i, &subp_attr);
	      language=0;
	      if(subp_attr.type==1) language=subp_attr.lang_code;
	      dvdnav_priv->subtitles[dvdnav_priv->nr_of_subtitles].language=
		    language;
	      dvdnav_priv->subtitles[dvdnav_priv->nr_of_subtitles].id=
		    sub_id;
	      dvdnav_priv->nr_of_subtitles++;
	      }
	    }
	  }
	dvdnav_priv->cell_cellN=cell_change_event->cellN;
	dvdnav_priv->cell_pgN=cell_change_event->pgN;
	dvdnav_priv->cell_pgcN=pgcN;
#ifdef USE_MPDVDNAV_TRACE
	if (dvdnav_trace) mp_msg(MSGT_CPLAYER,MSGL_INFO,
	    "dvdnav: cell change\n");
#endif
	break; }
      case DVDNAV_NAV_PACKET : {
	event->eventflag.nav_packet=1;
	event->eventflag.isevent=1;
	pci_t* pnavpci = dvdnav_get_current_nav_pci( dvdnav_priv->dvdnav );
	int buttonN;
	if (pnavpci && pnavpci->hli.hl_gi.btn_ns) {
	  dvdnav_get_current_highlight(dvdnav_priv->dvdnav, &buttonN);	/* get current button ID */
	  if (buttonN==0 || buttonN > pnavpci->hli.hl_gi.btn_ns)
	    {
	    dvdnav_button_select( dvdnav_priv->dvdnav , pnavpci, 1);
#ifdef USE_MPDVDNAV_TRACE
	    if (dvdnav_trace) mp_msg(MSGT_CPLAYER,MSGL_INFO,
		"dvdnav: reset menu button number\n");
#endif
	    }
	  }
#ifdef USE_MPDVDNAV_TRACE
	if (dvdnav_trace) mp_msg(MSGT_CPLAYER,MSGL_INFO,
	    "dvdnav: nav packet\n");
#endif
#ifdef USE_MPDVDNAV_TRACE
	dvdnav_print_buttons(dvdnav_priv,"highlight event");
#endif
	break; }
      case DVDNAV_STOP: {
        event->eventflag.stop=1;
	event->eventflag.isevent=1;
	dvdnav_priv->stopflg=1;
#ifdef USE_MPDVDNAV_TRACE
	if (dvdnav_trace) mp_msg(MSGT_CPLAYER,MSGL_INFO,
	    "dvdnav: stop\n");
#endif
	break; }
      case DVDNAV_HIGHLIGHT : {
	event->eventflag.highlight=1;
	event->eventflag.isevent=1;
	dvdnav_highlight_event_t *highlight_event =
	    (dvdnav_highlight_event_t*)(buf);
	event->hl_display=highlight_event->display;
	/* libdvdnav v0.1.10: these fields are currently not set!! */
	dvdnav_get_highlight(dvdnav_priv,highlight_event,1);
	event->hl_palette=highlight_event->palette;
	event->hl_sx=highlight_event->sx;
	event->hl_sy=highlight_event->sy;
	event->hl_ex=highlight_event->ex;
	event->hl_ey=highlight_event->ey;
	event->hl_pts=highlight_event->pts;
	event->hl_buttonN=highlight_event->buttonN;
#ifdef USE_MPDVDNAV_TRACE
	if (dvdnav_trace) mp_msg(MSGT_CPLAYER,MSGL_INFO,
	    "dvdnav: highlight (%i:%i-%i:%i #%i)\n",
	    event->hl_sx,
	    event->hl_sy,
	    event->hl_ex,
	    event->hl_ey,
	    event->hl_buttonN);
#endif
#ifdef USE_MPDVDNAV_TRACE
	dvdnav_print_buttons(dvdnav_priv,"highlight event");
#endif
	break; }
      case DVDNAV_SPU_CLUT_CHANGE: {
	event->eventflag.spu_clut_change=1;
	event->eventflag.isevent=1;
	memcpy(event->spu_clut,buf,16*sizeof(uint32_t));
	dvdnav_get_button_palette(dvdnav_priv,&(event->spu_palette));
#ifdef USE_MPDVDNAV_TRACE
	if (dvdnav_trace) mp_msg(MSGT_CPLAYER,MSGL_INFO,
	    "dvdnav: spu clut change\n");
#endif
        break; }
      case DVDNAV_HOP_CHANNEL : {
	event->eventflag.hop_channel=1;
	event->eventflag.isevent=1;
#ifdef USE_MPDVDNAV_TRACE
	if (dvdnav_trace) mp_msg(MSGT_CPLAYER,MSGL_INFO,
	    "dvdnav: hop channel\n");
#endif
	break; }
      case DVDNAV_WAIT: {
#ifdef USE_MPDVDNAV_TRACE
	if (dvdnav_trace) mp_msg(MSGT_CPLAYER,MSGL_INFO,
	    "dvdnav: wait\n");
#endif
        event->eventflag.wait=1;
        event->eventflag.isevent=1;
        int flag=0;
        dvdnav_is_still_cell( dvdnav_priv->dvdnav , &flag);
        if (!flag && dvdnav_priv->lockseek) {
	  dvdnav_wait_back(dvdnav_priv->dvdnav);
	  break; }
	if (!dvdnav_priv->vts_domain && dvdnav_priv->cell_timer && !flag) {
	pci_t* pnavpci = dvdnav_get_current_nav_pci( dvdnav_priv->dvdnav );
	unsigned int end_time=(pnavpci->pci_gi.e_eltm.hour*3600+
		pnavpci->pci_gi.e_eltm.minute*60+
		pnavpci->pci_gi.e_eltm.second)*1000000;
	unsigned int now = GetTimer();
	float t;
	t=now-dvdnav_priv->one_cell_timer;
	dvdnav_priv->one_cell_timer=now;
	t=t/1000000;
	float rt=end_time-(now-dvdnav_priv->cell_timer);
	rt=rt/1000000;
	float et=end_time;
	et=et/1000000;
#ifdef USE_MPDVDNAV_TRACE
	if (dvdnav_trace) mp_msg(MSGT_CPLAYER,MSGL_INFO,
	    "dvdnav: remains time %8.3f sec (%8.3f/%8.3f sec)\n",
	    rt,et,t);
#endif
	if (t<2.00 && et>4.00) {				// correct cell play time?
	  if (now-dvdnav_priv->cell_timer<end_time) {	// cell play time end?
	    if (dvdnav_priv->waitcounter<dvdnav_still_repeat)
	      {
	      dvdnav_wait_back(dvdnav_priv->dvdnav);
	      dvdnav_priv->waitcounter++;
	      }
	    } else {
	    dvdnav_priv->waitcounter=0;
	    dvdnav_priv->cell_timer=0;
	    dvdnav_priv->one_cell_timer=0;
	    dvdnav_priv->back_from_timer=1;
	    dvdnav_wait_still_clear(dvdnav_priv->dvdnav);
	    }
	  } else {
	  dvdnav_wait_skip(dvdnav_priv->dvdnav);
	  dvdnav_priv->waitcounter=0;
	  dvdnav_priv->cell_timer=0;
	  dvdnav_priv->one_cell_timer=0;
	  }
	} else {
	dvdnav_wait_skip(dvdnav_priv->dvdnav);
	if (!flag) {
	  dvdnav_priv->cell_timer=0;
	  dvdnav_priv->one_cell_timer=0;
	  dvdnav_priv->waitcounter=0;
	  }
	}
      break;
      }
    }
  *len=0;
  }
return eventid;
}


static int fill_buffer(stream_t *s, char *but, int len)
{
int event;
dvdnav_priv_t* dvdnav_priv=s->priv;
len=0;
while (len==0) /* grab all event until DVDNAV_BLOCK_OK (len=2048), DVDNAV_STOP or DVDNAV_STILL_FRAME */
  {
  if (-1==(event=dvdnav_stream_read(dvdnav_priv, s->buffer, &len,
	    &(dvdnav_priv->event))) ||
	len==-1)
    {
    mp_msg(MSGT_CPLAYER,MSGL_ERR,
	"DVDNAV stream read error!\n");
    return 0;
    }
  switch (event) {
    case DVDNAV_STOP: return len; break; /* return eof */
    case DVDNAV_STILL_FRAME: {
      if (!dvdnav_priv->stillok) dvdnav_priv->stillcounter++;
      dvdnav_priv->lockstillcounter++;
      return len;
      break; }/* return eof */
    case DVDNAV_WAIT: {
      if (dvdnav_priv->waitcounter>=dvdnav_still_repeat) return len;
      break;
      }
    }
  if (dvdnav_priv->event.cell_really_change &&
	dvdnav_priv->started &&
	!dvdnav_priv->vts_domain) return len;
  }
mp_msg(MSGT_STREAM,MSGL_DBG2,"DVDNAV fill_buffer len: %d\n",len);
return len;
}

static int control(stream_t *stream,int cmd,void* arg) 
{
dvdnav_priv_t *priv = stream->priv;
switch(cmd) 
  {
  case STREAM_CTRL_GET_TIME_LENGTH:
    {
    return STREAM_OK;
    }
  case STREAM_CTRL_LANG_FROM_SID:
    {
    *(int*)arg = dvdnav_lang_from_sid(priv,*(int*)arg);
    return STREAM_OK;
    }
  case STREAM_CTRL_SID_FROM_LANG:
    {
    if (!arg) return STREAM_ERROR;
    (*(struct dvd_idfromlang_st*)arg).id=dvdnav_sid_from_lang(priv, 
	(*(struct dvd_idfromlang_st*)arg).lang);
    return STREAM_OK;
    }
  case STREAM_CTRL_AID_FROM_LANG:
    {
    if (!arg) return STREAM_ERROR;
    (*(struct dvd_idfromlang_st*)arg).id=dvdnav_aid_from_lang(priv, 
	(*(struct dvd_idfromlang_st*)arg).lang);
    return STREAM_OK;
    }
  case STREAM_CTRL_NUMBER_OF_SUBS:
    {
    *(int*)arg = dvdnav_number_of_subs(priv);
    return STREAM_OK;
    }
  case STREAM_CTRL_DVDNAV_REALLYEOF:
    {
    if (dvdnav_reallyeof(priv))
      return STREAM_OK;
    return STREAM_ERROR;
    }
  case STREAM_CTRL_DVDNAV_EVENT_STOP:
    {
    if (priv->event.eventflag.stop)
      return STREAM_OK;
    return STREAM_ERROR;
    }
  case STREAM_CTRL_DVDNAV_EVENT_WAIT:
    {
    if (priv->event.eventflag.wait)
      return STREAM_OK;
    return STREAM_ERROR;
    }
  case STREAM_CTRL_DVDNAV_EVENT_STILL:
    {
    if (priv->event.eventflag.still_frame)
      return STREAM_OK;
    return STREAM_ERROR;
    }
  case STREAM_CTRL_DVDNAV_EVENT_VTS:
    {
    if (priv->event.eventflag.vts_change)
      return STREAM_OK;
    return STREAM_ERROR;
    }
  case STREAM_CTRL_DVDNAV_EVENT_VTS_DOMAIN:
    {
    if (priv->vts_domain)
      return STREAM_OK;
    return STREAM_ERROR;
    }
  case STREAM_CTRL_GET_AUDIO_ID:
    {
    if (!arg) return STREAM_ERROR;
    *(int*)arg = priv->alang;
    return STREAM_OK;
    }
  case STREAM_CTRL_GET_DVDSUB_ID:
    {
    if (!arg) return STREAM_ERROR;
    *(int*)arg = priv->slang;
    return STREAM_OK;
    }
  case STREAM_CTRL_DVDNAV_EVENT_CELL:
    {
    if (priv->event.eventflag.cell_change)
      return STREAM_OK;
    return STREAM_ERROR;
    }
  case STREAM_CTRL_DVDNAV_REALLY_CHANGE:
    {
    if (priv->event.cell_really_change)
      return STREAM_OK;
    return STREAM_ERROR;
    }
  case STREAM_CTRL_DVDNAV_TITLESET:
    {
    priv->lasttitle=priv->title;
    priv->lastpart=priv->part;
    priv->old_vts_domain=priv->vts_domain;
    return STREAM_OK;
    }
  case STREAM_CTRL_DVDNAV_IS_NEW_TITLE:
    {
    if (priv->lasttitle!=priv->title)
      return STREAM_OK;
    return STREAM_ERROR;
    }
  case STREAM_CTRL_DVDNAV_EVENT_SPU_CLUT:
    {
    if (priv->event.eventflag.spu_clut_change)
      return STREAM_OK;
    return STREAM_ERROR;
    }
  case STREAM_CTRL_GET_SPU_CLUT:
    {
    memcpy(arg,&(priv->event.spu_clut),sizeof(spu_clut_t));
    return STREAM_OK;
    }
  case STREAM_CTRL_GET_SPU_PALETTE:
    {
    if (!arg) return STREAM_ERROR;
    *(uint32_t*)arg=priv->event.spu_palette;
    return STREAM_OK;
    }
  case STREAM_CTRL_DVDNAV_EVENT_HIGHLIGHT:
    {
    if (priv->event.eventflag.highlight)
      return STREAM_OK;
    return STREAM_ERROR;
    }
  case STREAM_CTRL_DVDNAV_EVENT_NAV_PACKET:
    {
    if (priv->event.eventflag.nav_packet)
      return STREAM_OK;
    return STREAM_ERROR;
    }
  case STREAM_CTRL_DVDNAV_EVENT_CLEAR:
    {
    dvdnav_event_clear(priv);
    return STREAM_OK;
    }
  case STREAM_CTRL_DVDNAV_STILLOK:
    {
    if (priv->stillok) return STREAM_OK;
    return STREAM_ERROR;
    }
  case STREAM_CTRL_DVDNAV_GET_HIGHLIGHT_SHOW:
    {
    if (!arg) return STREAM_ERROR;
    dvdnav_highlight_event_t highlight_event;
    dvdnav_get_highlight(priv,&highlight_event,1);
    (*(mp_highlight_t*)arg).display=highlight_event.display;
    (*(mp_highlight_t*)arg).sx=highlight_event.sx;
    (*(mp_highlight_t*)arg).sy=highlight_event.sy;
    (*(mp_highlight_t*)arg).ex=highlight_event.ex;
    (*(mp_highlight_t*)arg).ey=highlight_event.ey;
    (*(mp_highlight_t*)arg).pts=highlight_event.pts;
    (*(mp_highlight_t*)arg).palette=highlight_event.palette;
    (*(mp_highlight_t*)arg).buttonN=highlight_event.buttonN;
    return STREAM_OK;
    }
  case STREAM_CTRL_DVDNAV_GET_HIGHLIGHT_ACTIVATE:
    {
    if (!arg) return STREAM_ERROR;
    dvdnav_highlight_event_t highlight_event;
    dvdnav_get_highlight(priv,&highlight_event,2);
    (*(mp_highlight_t*)arg).display=highlight_event.display;
    (*(mp_highlight_t*)arg).sx=highlight_event.sx;
    (*(mp_highlight_t*)arg).sy=highlight_event.sy;
    (*(mp_highlight_t*)arg).ex=highlight_event.ex;
    (*(mp_highlight_t*)arg).ey=highlight_event.ey;
    (*(mp_highlight_t*)arg).palette=highlight_event.palette;
    (*(mp_highlight_t*)arg).pts=highlight_event.pts;
    (*(mp_highlight_t*)arg).buttonN=highlight_event.buttonN;
    return STREAM_OK;
    }
  case STREAM_CTRL_CHANGE_ASPECT:
    {
    if (priv->lastaspect!=priv->aspect) return STREAM_OK;
    return STREAM_ERROR;
    }
  case STREAM_CTRL_GET_ASPECT:
    {
    if (!arg) return STREAM_ERROR;
    *(int*)arg=priv->aspect;
    return STREAM_OK;
    }
  case STREAM_CTRL_SYNC_ASPECT:
    {
    priv->lastaspect=priv->aspect;
    return STREAM_OK;
    }
  case STREAM_CTRL_DVDNAV_SET_LOCKSEEK:
    {
    if (!arg) return STREAM_ERROR;
    priv->lockseek=*(int*)arg;
    return STREAM_OK;
    }
  case STREAM_CTRL_GET_FINALPTS:
    {
    if (!arg) return STREAM_ERROR;
    *(float*)arg=priv->final_pts;
    return STREAM_OK;
    }
  case STREAM_CTRL_GET_TLEN:
    {
    if (!arg) return STREAM_ERROR;
    *(uint32_t*)arg=priv->tlen;
    return STREAM_OK;
    }
#ifdef HAVE_NEW_GUI
  case STREAM_CTRL_DVDNAV_MOUSE:
    {
    dvdnav_mouse(priv);
    return STREAM_OK;
    }
#endif
  case STREAM_CTRL_DVDNAV_TITLE_PLAY:
    {
    if (!arg) return STREAM_ERROR;
    dvdnav_title_play(priv->dvdnav,*(int32_t*)arg);
    return STREAM_OK;
    }
  case STREAM_CTRL_DVDNAV_PART_PLAY:
    {
    if (!arg) return STREAM_ERROR;
    dvdnav_part_play(priv->dvdnav,priv->title,*(int32_t*)arg);
    return STREAM_OK;
    }
  case STREAM_CTRL_DVDNAV_MENUCALL:
    {
    if (!arg) return STREAM_ERROR;
    switch (*(int*)arg) {
      case DVD_MENUCALL_Escape: {
	dvdnav_menu_call(priv->dvdnav,DVD_MENU_Escape);
	return STREAM_OK;}
      case DVD_MENUCALL_Title: {
	dvdnav_menu_call(priv->dvdnav,DVD_MENU_Title);
	return STREAM_OK;}
      case DVD_MENUCALL_Root: {
	dvdnav_menu_call(priv->dvdnav,DVD_MENU_Root);
	return STREAM_OK;}
      case DVD_MENUCALL_Subpicture: {
	dvdnav_menu_call(priv->dvdnav,DVD_MENU_Subpicture);
	return STREAM_OK;}
      case DVD_MENUCALL_Audio: {
	dvdnav_menu_call(priv->dvdnav,DVD_MENU_Audio);
	return STREAM_OK;}
      case DVD_MENUCALL_Angle: {
	dvdnav_menu_call(priv->dvdnav,DVD_MENU_Angle);
	return STREAM_OK;}
      case DVD_MENUCALL_Part: {
	dvdnav_menu_call(priv->dvdnav,DVD_MENU_Part);
	return STREAM_OK;}
      }
    return STREAM_ERROR;
    }
  case STREAM_CTRL_DVDNAV_MENUFORCE:
    {
    dvdnav_menu_force(priv);
    return STREAM_OK;
    }
  case STREAM_CTRL_DVDNAV_MENU_ACTION:
    {
    if (!arg) return STREAM_ERROR;
    dvdnav_menu_action(priv,*(int*)arg);
    return STREAM_OK;
    }
  case STREAM_CTRL_FULL_START:
    {
    dvdnav_stream_fullstart(priv);
    return STREAM_OK;
    }
  case STREAM_CTRL_SET_ALANG:
    {
    if (!arg) return STREAM_ERROR;
    if (!*(char**)arg) return STREAM_ERROR;
    if (dvdnav_audio_language_select(priv->dvdnav, *(char**)arg ) !=
	DVDNAV_STATUS_OK) {	/* FIXME: don't work! */
      mp_msg(MSGT_FIXME, MSGL_FIXME, "Error on setting spu languages: %s\n",
	dvdnav_err_to_string(priv->dvdnav)); 
      return STREAM_ERROR;
      }
    return STREAM_OK;
    }
  case STREAM_CTRL_SET_SLANG:
    {
    if (!arg) return STREAM_ERROR;
    if (!*(char**)arg) return STREAM_ERROR;
    if (dvdnav_spu_language_select(priv->dvdnav, *(char**)arg ) !=
	DVDNAV_STATUS_OK) {	/* FIXME: don't work! */
      mp_msg(MSGT_FIXME, MSGL_FIXME, "Error on setting spu languages: %s\n",
	dvdnav_err_to_string(priv->dvdnav)); 
      return STREAM_ERROR;
      }
    return STREAM_OK;
    }
  case STREAM_CTRL_SET_MLANG:
    {
    if (!arg) return STREAM_ERROR;
    if (!*(char**)arg) return STREAM_ERROR;
    if (dvdnav_menu_language_select(priv->dvdnav, *(char**)arg ) !=
	DVDNAV_STATUS_OK) {	/* FIXME: don't work! */
      mp_msg(MSGT_FIXME, MSGL_FIXME, "Error on setting spu languages: %s\n",
	dvdnav_err_to_string(priv->dvdnav)); 
      return STREAM_ERROR;
      }
    return STREAM_OK;
    }
  case STREAM_CTRL_DVDNAV_GET_MENU_SID:
    {
    if (!arg) return STREAM_ERROR;
    *(int*)arg=priv->menu_sid;
    return STREAM_OK;
    }
  case STREAM_CTRL_GET_PALETTE:
    {
    if (!arg) return STREAM_ERROR;
    *(unsigned int*)arg=dvdnav_stream_get_palette(priv);;
    return STREAM_OK;
    }

  }
return STREAM_UNSUPORTED;
}


dvdnav_priv_t * new_dvdnav_stream(char * filename, uint32_t titlenum)
{
char * title_str;
dvdnav_priv_t *dvdnav_priv;
if (!filename) return NULL;
if (!(dvdnav_priv=(dvdnav_priv_t*)calloc(1,sizeof(*dvdnav_priv)))) return NULL;
if (!(dvdnav_priv->filename=strdup(filename)))
  {
  free(dvdnav_priv);
  return NULL;
  }
if(dvdnav_open(&(dvdnav_priv->dvdnav),dvdnav_priv->filename)!=
    DVDNAV_STATUS_OK)
  {
  free(dvdnav_priv->filename);
  free(dvdnav_priv);
  return NULL;
  }
if (!dvdnav_priv->dvdnav)
  {
  free(dvdnav_priv);
  return NULL;
  }
/* turn on dvdnav caching */
dvdnav_set_readahead_flag(dvdnav_priv->dvdnav,0);
/* report the title?! */
if (dvdmenu_lang)	// menu
  {
  if (dvdnav_menu_language_select(dvdnav_priv->dvdnav, dvdmenu_lang ) !=
	DVDNAV_STATUS_OK)
    mp_msg(MSGT_FIXME, MSGL_FIXME,
	"Error on setting menu languages: %s\n",
	dvdnav_err_to_string(dvdnav_priv->dvdnav));
  }
/* use title time length (default: part time length) */
if (dvdnav_set_PGC_positioning_flag(dvdnav_priv->dvdnav, 1) !=
	DVDNAV_STATUS_OK)
  mp_msg(MSGT_FIXME, MSGL_FIXME,
	"Error on setting pgc based: %s\n",
	dvdnav_err_to_string(dvdnav_priv->dvdnav));
dvdnav_event_clear(dvdnav_priv);
if (titlenum>0) dvdnav_go_title=titlenum;
dvdnav_priv->lastaspect=-1;
return dvdnav_priv;
}

void free_dvdnav_stream(dvdnav_priv_t * dvdnav_priv)
{
if (!dvdnav_priv) return;
dvdnav_close(dvdnav_priv->dvdnav);
dvdnav_priv->dvdnav=NULL;
free(dvdnav_priv);
}


static int open_s(stream_t *stream,int mode, void* opts, int* file_format)
{
struct stream_priv_s* p = (struct stream_priv_s*)opts;
char *filename, *name;
int event,len,tmplen=0;
dvdnav_priv_t *dvdnav_priv;

mp_msg(MSGT_OPEN,MSGL_INFO,"URL: %s\n", filename);
filename = strdup(stream->url);
name = (filename[9] == '\0') ? NULL : filename + 9;
uint32_t titlenum=0;
if (name) titlenum=atoi(name);	/* eg. mplayer dvdnav://1 */
if (dvd_device)
  {
  if(!(dvdnav_priv=new_dvdnav_stream(dvd_device,titlenum)))
    {
    mp_msg(MSGT_OPEN,MSGL_ERR,MSGTR_CantOpenDVD,dvd_device);
    return STREAM_UNSUPORTED;
    }
  } else {
  if(!(dvdnav_priv=new_dvdnav_stream(DEFAULT_DVD_DEVICE,titlenum)))
    {
    mp_msg(MSGT_OPEN,MSGL_ERR,MSGTR_CantOpenDVD,dvd_device);
    return STREAM_UNSUPORTED;
    }
  }
stream->sector_size = 2048;
stream->flags = STREAM_READ | STREAM_SEEK;
stream->fill_buffer = fill_buffer;
stream->seek = seek;
stream->control = control;
stream->close = stream_dvdnav_close;
stream->type = STREAMTYPE_DVDNAV;
stream->priv=(void*)dvdnav_priv;
return STREAM_OK;
}

stream_info_t stream_info_dvdnav = {
  "DVDNAV stream",
  "dvdnav",
  "Otvos Attila",
  "",
  open_s,
  { "dvdnav", NULL },
  &stream_opts,
  1 // Urls are an option string
};

#endif	// #ifdef USE_MPDVDNAV
