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
 * $Id: highlight.c,v 1.32 2004/01/20 01:22:24 jcdutton Exp $
 *
 */

#ifndef HAVE_MPLAYER
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#else
#include "config.h"
#endif

#include <assert.h>
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
#include "dvdnav_internal.h"

#ifdef USE_MPDVDNAV
#include "../mp_msg.h"
#include "../help_mp.h"
#endif
#ifdef USE_MPDVDNAV_TRACE
extern int dvdnav_trace;
#endif

/*
#define BUTTON_TESTING
*/

#ifdef BUTTON_TESTING

#include "nav_print.h"



static void print_time(dvd_time_t *dtime) {
  const char *rate;

  assert((dtime->hour>>4) < 0xa && (dtime->hour&0xf) < 0xa);
  assert((dtime->minute>>4) < 0x7 && (dtime->minute&0xf) < 0xa);
  assert((dtime->second>>4) < 0x7 && (dtime->second&0xf) < 0xa);
  assert((dtime->frame_u&0xf) < 0xa);

  mp_msg(MSGT_CPLAYER,MSGL_INFO,"%02x:%02x:%02x.%02x",
         dtime->hour,
         dtime->minute,
         dtime->second,
         dtime->frame_u & 0x3f);
  switch((dtime->frame_u & 0xc0) >> 6) {
  case 1:
    rate = "25.00";
    break;
  case 3:
    rate = "29.97";
    break;
  default:
    rate = "(please send a bug report)";
    break;
  }
  mp_msg(MSGT_CPLAYER,MSGL_INFO," @ %s fps", rate);
}

static void nav_print_PCI_GI(pci_gi_t *pci_gi) {
  int32_t i;

  mp_msg(MSGT_CPLAYER,MSGL_INFO,"libdvdnav: pci_gi:\n");
  mp_msg(MSGT_CPLAYER,MSGL_INFO,"libdvdnav: nv_pck_lbn    0x%08x\n", pci_gi->nv_pck_lbn);
  mp_msg(MSGT_CPLAYER,MSGL_INFO,"libdvdnav: vobu_cat      0x%04x\n", pci_gi->vobu_cat);
  mp_msg(MSGT_CPLAYER,MSGL_INFO,"libdvdnav: vobu_uop_ctl  0x%08x\n", *(uint32_t*)&pci_gi->vobu_uop_ctl);
  mp_msg(MSGT_CPLAYER,MSGL_INFO,"libdvdnav: vobu_s_ptm    0x%08x\n", pci_gi->vobu_s_ptm);
  mp_msg(MSGT_CPLAYER,MSGL_INFO,"libdvdnav: vobu_e_ptm    0x%08x\n", pci_gi->vobu_e_ptm);
  mp_msg(MSGT_CPLAYER,MSGL_INFO,"libdvdnav: vobu_se_e_ptm 0x%08x\n", pci_gi->vobu_se_e_ptm);
  mp_msg(MSGT_CPLAYER,MSGL_INFO,"libdvdnav: e_eltm        ");
  print_time(&pci_gi->e_eltm);
  mp_msg(MSGT_CPLAYER,MSGL_INFO,"\n");

  mp_msg(MSGT_CPLAYER,MSGL_INFO,"libdvdnav: vobu_isrc     \"");
  for(i = 0; i < 32; i++) {
    char c = pci_gi->vobu_isrc[i];
    if((c >= ' ') && (c <= '~'))
      mp_msg(MSGT_CPLAYER,MSGL_INFO,"%c", c);
    else
      mp_msg(MSGT_CPLAYER,MSGL_INFO,".");
  }
  mp_msg(MSGT_CPLAYER,MSGL_INFO,"\"\n");
}

static void nav_print_NSML_AGLI(nsml_agli_t *nsml_agli) {
  int32_t i, j = 0;

  for(i = 0; i < 9; i++)
    j |= nsml_agli->nsml_agl_dsta[i];
  if(j == 0)
    return;

  mp_msg(MSGT_CPLAYER,MSGL_INFO,"libdvdnav: nsml_agli:\n");
  for(i = 0; i < 9; i++)
    if(nsml_agli->nsml_agl_dsta[i])
      mp_msg(MSGT_CPLAYER,MSGL_INFO,"libdvdnav: nsml_agl_c%d_dsta  0x%08x\n", i + 1,
             nsml_agli->nsml_agl_dsta[i]);
}

static void nav_print_HL_GI(hl_gi_t *hl_gi, int32_t *btngr_ns, int32_t *btn_ns) {

  if((hl_gi->hli_ss & 0x03) == 0)
    return;

  mp_msg(MSGT_CPLAYER,MSGL_INFO,"libdvdnav: hl_gi:\n");
  mp_msg(MSGT_CPLAYER,MSGL_INFO,"libdvdnav: hli_ss        0x%01x\n", hl_gi->hli_ss & 0x03);
  mp_msg(MSGT_CPLAYER,MSGL_INFO,"libdvdnav: hli_s_ptm     0x%08x\n", hl_gi->hli_s_ptm);
  mp_msg(MSGT_CPLAYER,MSGL_INFO,"libdvdnav: hli_e_ptm     0x%08x\n", hl_gi->hli_e_ptm);
  mp_msg(MSGT_CPLAYER,MSGL_INFO,"libdvdnav: btn_se_e_ptm  0x%08x\n", hl_gi->btn_se_e_ptm);

  *btngr_ns = hl_gi->btngr_ns;
  mp_msg(MSGT_CPLAYER,MSGL_INFO,"libdvdnav: btngr_ns      %d\n",  hl_gi->btngr_ns);
  mp_msg(MSGT_CPLAYER,MSGL_INFO,"libdvdnav: btngr%d_dsp_ty    0x%02x\n", 1, hl_gi->btngr1_dsp_ty);
  mp_msg(MSGT_CPLAYER,MSGL_INFO,"libdvdnav: btngr%d_dsp_ty    0x%02x\n", 2, hl_gi->btngr2_dsp_ty);
  mp_msg(MSGT_CPLAYER,MSGL_INFO,"libdvdnav: btngr%d_dsp_ty    0x%02x\n", 3, hl_gi->btngr3_dsp_ty);

  mp_msg(MSGT_CPLAYER,MSGL_INFO,"libdvdnav: btn_ofn       %d\n", hl_gi->btn_ofn);
  *btn_ns = hl_gi->btn_ns;
  mp_msg(MSGT_CPLAYER,MSGL_INFO,"libdvdnav: btn_ns        %d\n", hl_gi->btn_ns);
  mp_msg(MSGT_CPLAYER,MSGL_INFO,"libdvdnav: nsl_btn_ns    %d\n", hl_gi->nsl_btn_ns);
  mp_msg(MSGT_CPLAYER,MSGL_INFO,"libdvdnav: fosl_btnn     %d\n", hl_gi->fosl_btnn);
  mp_msg(MSGT_CPLAYER,MSGL_INFO,"libdvdnav: foac_btnn     %d\n", hl_gi->foac_btnn);
}

static void nav_print_BTN_COLIT(btn_colit_t *btn_colit) {
  int32_t i, j;

  j = 0;
  for(i = 0; i < 6; i++)
    j |= btn_colit->btn_coli[i/2][i&1];
  if(j == 0)
    return;

  mp_msg(MSGT_CPLAYER,MSGL_INFO,"libdvdnav: btn_colit:\n");
  for(i = 0; i < 3; i++)
    for(j = 0; j < 2; j++)
      mp_msg(MSGT_CPLAYER,MSGL_INFO,"libdvdnav: btn_cqoli %d  %s_coli:  %08x\n",
             i, (j == 0) ? "sl" : "ac",
             btn_colit->btn_coli[i][j]);
}

static void nav_print_BTNIT(btni_t *btni_table, int32_t btngr_ns, int32_t btn_ns) {
  int32_t i, j, k;

  mp_msg(MSGT_CPLAYER,MSGL_INFO,"libdvdnav: btnit:\n");
  mp_msg(MSGT_CPLAYER,MSGL_INFO,"libdvdnav: btngr_ns: %i\n", btngr_ns);
  mp_msg(MSGT_CPLAYER,MSGL_INFO,"libdvdnav: btn_ns: %i\n", btn_ns);

  if(btngr_ns == 0)
    return;

  for(i = 0; i < btngr_ns; i++) {
    for(j = 0; j < (36 / btngr_ns); j++) {
      if(j < btn_ns) {
        btni_t *btni = &btni_table[(36 / btngr_ns) * i + j];

        mp_msg(MSGT_CPLAYER,MSGL_INFO,"libdvdnav: group %d btni %d:  ", i+1, j+1);
        mp_msg(MSGT_CPLAYER,MSGL_INFO,"btn_coln %d, auto_action_mode %d\n",
               btni->btn_coln, btni->auto_action_mode);
        mp_msg(MSGT_CPLAYER,MSGL_INFO,"libdvdnav: coords   (%d, %d) .. (%d, %d)\n",
               btni->x_start, btni->y_start, btni->x_end, btni->y_end);

        mp_msg(MSGT_CPLAYER,MSGL_INFO,"libdvdnav: up %d, ", btni->up);
        mp_msg(MSGT_CPLAYER,MSGL_INFO,"down %d, ", btni->down);
        mp_msg(MSGT_CPLAYER,MSGL_INFO,"left %d, ", btni->left);
        mp_msg(MSGT_CPLAYER,MSGL_INFO,"right %d\n", btni->right);
        for(k = 0; k < 8; k++) {
          mp_msg(MSGT_CPLAYER,MSGL_INFO,"libdvdnav: %02x ", btni->cmd.bytes[k]);
        }
        mp_msg(MSGT_CPLAYER,MSGL_INFO,, "| ");
#ifdef USE_MPDVDNAV_TRACE
        if (dvdnav_trace) vm_print_mnemonic(&btni->cmd);
#endif
        mp_msg(MSGT_CPLAYER,MSGL_INFO,"\n");
      }
    }
  }
}

static void nav_print_HLI(hli_t *hli) {
  int32_t btngr_ns = 0, btn_ns = 0;

  mp_msg(MSGT_CPLAYER,MSGL_INFO,"libdvdnav: hli:\n");
  nav_print_HL_GI(&hli->hl_gi, & btngr_ns, & btn_ns);
  nav_print_BTN_COLIT(&hli->btn_colit);
  nav_print_BTNIT(hli->btnit, btngr_ns, btn_ns);
}

void nav_print_PCI(pci_t *pci) {
  mp_msg(MSGT_CPLAYER,MSGL_INFO,"libdvdnav: pci packet:\n");
  nav_print_PCI_GI(&pci->pci_gi);
  nav_print_NSML_AGLI(&pci->nsml_agli);
  nav_print_HLI(&pci->hli);
}

#endif


/* Highlighting API calls */

dvdnav_status_t dvdnav_get_current_highlight(dvdnav_t *this, int32_t *button) {

  if(!this || !button) {
    printerr(MSGTR_LIBMPDVDNAV_Err_PassedANullPointer);
    return DVDNAV_STATUS_ERR;
  }

  /* Simply return the appropriate value based on the SPRM */
  if(((*button) = this->position_current.button) == -1)
    (*button) = this->vm->state.HL_BTNN_REG >> 10;

  return DVDNAV_STATUS_OK;
}

static btni_t *get_current_button(dvdnav_t *this, pci_t *pci) {
  int32_t button = 0;

  if(!this || !pci) {
    printerr(MSGTR_LIBMPDVDNAV_Err_PassedANullPointer);
    return NULL;
  }
  if(!pci->hli.hl_gi.hli_ss) {
    mp_msg( MSGT_CPLAYER,MSGL_ERR,MSGTR_LIBMPDVDNAV_NotInAMenu);
    return NULL;
  }
  if(this->last_cmd_nav_lbn == pci->pci_gi.nv_pck_lbn) {
    mp_msg( MSGT_CPLAYER,MSGL_ERR,MSGTR_LIBMPDVDNAV_ThisNAVHasAlreadyBeenLeft);
    return NULL;
  }

  button = this->vm->state.HL_BTNN_REG >> 10;
#ifdef BUTTON_TESTING
  nav_print_PCI(pci);
#endif

  return &(pci->hli.btnit[button-1]);
}

static dvdnav_status_t button_auto_action(dvdnav_t *this, pci_t *pci) {
#ifdef USE_MPDVDNAV
  if (this->vm->auto_action_mode) return DVDNAV_STATUS_OK;
#endif
  if (get_current_button(this, pci)->auto_action_mode)
    return dvdnav_button_activate(this, pci);
  return DVDNAV_STATUS_OK;
}

dvdnav_status_t dvdnav_upper_button_select(dvdnav_t *this, pci_t *pci) {
  btni_t *button_ptr;

  if(!(button_ptr = get_current_button(this, pci)))
    return DVDNAV_STATUS_ERR;

  dvdnav_button_select(this, pci, button_ptr->up);
  return button_auto_action(this, pci);
}

dvdnav_status_t dvdnav_lower_button_select(dvdnav_t *this, pci_t *pci) {
  btni_t *button_ptr;

  if(!(button_ptr = get_current_button(this, pci)))
    return DVDNAV_STATUS_ERR;

  dvdnav_button_select(this, pci, button_ptr->down);
  return button_auto_action(this, pci);
}

dvdnav_status_t dvdnav_right_button_select(dvdnav_t *this, pci_t *pci) {
  btni_t *button_ptr;

  if(!(button_ptr = get_current_button(this, pci)))
    return DVDNAV_STATUS_ERR;

  dvdnav_button_select(this, pci, button_ptr->right);
  return button_auto_action(this, pci);
}

dvdnav_status_t dvdnav_left_button_select(dvdnav_t *this, pci_t *pci) {
  btni_t *button_ptr;

  if(!(button_ptr = get_current_button(this, pci)))
    return DVDNAV_STATUS_ERR;

  dvdnav_button_select(this, pci, button_ptr->left);
  return button_auto_action(this, pci);
}

dvdnav_status_t dvdnav_get_highlight_area(pci_t *nav_pci , int32_t button, int32_t mode,
					  dvdnav_highlight_area_t *highlight) {
  btni_t *button_ptr;

#ifdef BUTTON_TESTING
  mp_msg(MSGT_CPLAYER,MSGL_INFO, "libdvdnav: Button get_highlight_area %i\n", button);
#endif

  if(!nav_pci->hli.hl_gi.hli_ss)
    return DVDNAV_STATUS_ERR;
  if((button <= 0) || (button > nav_pci->hli.hl_gi.btn_ns))
    return DVDNAV_STATUS_ERR;


  button_ptr = &nav_pci->hli.btnit[button-1];

  highlight->sx = button_ptr->x_start;
  highlight->sy = button_ptr->y_start;
  highlight->ex = button_ptr->x_end;
  highlight->ey = button_ptr->y_end;
  if(button_ptr->btn_coln != 0) {
    highlight->palette = nav_pci->hli.btn_colit.btn_coli[button_ptr->btn_coln-1][mode];
  } else {
    highlight->palette = 0;
  }
  highlight->pts = nav_pci->hli.hl_gi.hli_s_ptm;
  highlight->buttonN = button;
#ifdef BUTTON_TESTING
  mp_msg(MSGT_CPLAYER,MSGL_INFO, "libdvdnav: highlight: Highlight area is (%u,%u)-(%u,%u), display = %i, button = %u\n",
               button_ptr->x_start, button_ptr->y_start,
               button_ptr->x_end, button_ptr->y_end,
               1,
               button);
#endif

  return DVDNAV_STATUS_OK;
}

dvdnav_status_t dvdnav_button_activate(dvdnav_t *this, pci_t *pci) {
  int32_t button;
  btni_t *button_ptr = NULL;

  if(!this || !pci) {
    printerr(MSGTR_LIBMPDVDNAV_Err_PassedANullPointer);
    return DVDNAV_STATUS_ERR;
  }
  if(!pci->hli.hl_gi.hli_ss) {
    mp_msg( MSGT_CPLAYER,MSGL_ERR,MSGTR_LIBMPDVDNAV_NotInAMenu);
    return DVDNAV_STATUS_ERR;
  }
  if(this->last_cmd_nav_lbn == pci->pci_gi.nv_pck_lbn) {
    mp_msg( MSGT_CPLAYER,MSGL_ERR,MSGTR_LIBMPDVDNAV_ThisNAVHasAlreadyBeenLeft);
    return DVDNAV_STATUS_ERR;
  }
  pthread_mutex_lock(&this->vm_lock);

  button = this->vm->state.HL_BTNN_REG >> 10;

  if((button <= 0) || (button > pci->hli.hl_gi.btn_ns)) {
    /* Special code to handle still menus with no buttons.
     * The navigation is expected to report to the application that a STILL is
     * underway. In turn, the application is supposed to report to the user
     * that the playback is paused. The user is then expected to undo the pause,
     * ie: hit play. At that point, the navigation should release the still and
     * go to the next Cell.
     * Explanation by Mathieu Lacage <mathieu_lacage@realmagic.fr>
     * Code added by jcdutton.
     */
    if (this->position_current.still != 0) {
      /* In still, but no buttons. */
      vm_get_next_cell(this->vm);
      this->position_current.still = 0;
      this->sync_wait = 0;
      this->last_cmd_nav_lbn = pci->pci_gi.nv_pck_lbn;
      pthread_mutex_unlock(&this->vm_lock);
      /* clear error message */
      printerr("");
      return DVDNAV_STATUS_OK;
    }
    pthread_mutex_unlock(&this->vm_lock);
    return DVDNAV_STATUS_ERR;
  }

  button_ptr = get_current_button(this, pci);
  /* Finally, make the VM execute the appropriate code and probably
   * scedule a jump */
#ifdef BUTTON_TESTING
  mp_msg(MSGT_CPLAYER,MSGL_INFO, "libdvdnav: Evaluating Button Activation commands.\n");
#endif
  if(vm_exec_cmd(this->vm, &(button_ptr->cmd)) == 1) {
    /* Command caused a jump */
    this->vm->hop_channel++;
    this->position_current.still = 0;
    this->last_cmd_nav_lbn = pci->pci_gi.nv_pck_lbn;
  }

  pthread_mutex_unlock(&this->vm_lock);
  return DVDNAV_STATUS_OK;
}

dvdnav_status_t dvdnav_button_activate_cmd(dvdnav_t *this, int32_t button, vm_cmd_t *cmd)
{
  if(!this || !cmd) {
    printerr(MSGTR_LIBMPDVDNAV_Err_PassedANullPointer);
    return DVDNAV_STATUS_ERR;
  }

  pthread_mutex_lock(&this->vm_lock);
  /* make the VM execute the appropriate code and probably
   * schedule a jump */
#ifdef BUTTON_TESTING
  mp_msg(MSGT_CPLAYER,MSGL_INFO, "libdvdnav: dvdnav_button_activate_cmd: Evaluating Button Activation commands.\n");
#endif
  if(button > 0) {
    this->vm->state.HL_BTNN_REG = (button << 10);
    if(vm_exec_cmd(this->vm, cmd) == 1) {
      /* Command caused a jump */
      this->vm->hop_channel++;
    }
  }
  /* Always remove still, because some still menus have no buttons. */
  this->position_current.still = 0;
  this->sync_wait = 0;
  pthread_mutex_unlock(&this->vm_lock);
  return DVDNAV_STATUS_OK;
}

dvdnav_status_t dvdnav_button_select(dvdnav_t *this, pci_t *pci, int32_t button) {

  if(!this || !pci) {
    printerr(MSGTR_LIBMPDVDNAV_Err_PassedANullPointer);
    return DVDNAV_STATUS_ERR;
  }
  if(!pci->hli.hl_gi.hli_ss) {
    mp_msg( MSGT_CPLAYER,MSGL_ERR,MSGTR_LIBMPDVDNAV_NotInAMenu);
    return DVDNAV_STATUS_ERR;
  }
  if(this->last_cmd_nav_lbn == pci->pci_gi.nv_pck_lbn) {
    mp_msg( MSGT_CPLAYER,MSGL_ERR,MSGTR_LIBMPDVDNAV_ThisNAVHasAlreadyBeenLeft);
    return DVDNAV_STATUS_ERR;
  }

#ifdef BUTTON_TESTING
  mp_msg(MSGT_CPLAYER,MSGL_INFO, "libdvdnav: Button select %i\n", button);
#endif

  if((button <= 0) || (button > pci->hli.hl_gi.btn_ns)) {
    mp_msg( MSGT_CPLAYER,MSGL_ERR,MSGTR_LIBMPDVDNAV_ButtonDoesNotExist);
    return DVDNAV_STATUS_ERR;
  }

  this->vm->state.HL_BTNN_REG = (button << 10);
  this->position_current.button = -1; /* Force Highligh change */

  return DVDNAV_STATUS_OK;
}

dvdnav_status_t dvdnav_button_select_and_activate(dvdnav_t *this, pci_t *pci,
						  int32_t button) {
  /* A trivial function */
  if(dvdnav_button_select(this, pci, button) != DVDNAV_STATUS_ERR)
    return dvdnav_button_activate(this, pci);
  return DVDNAV_STATUS_ERR;
}

dvdnav_status_t dvdnav_mouse_select(dvdnav_t *this, pci_t *pci, int32_t x, int32_t y) {
  int32_t button, cur_button;
  int32_t best,dist,d;
  int32_t mx,my,dx,dy;

  if(!this || !pci) {
    printerr(MSGTR_LIBMPDVDNAV_Err_PassedANullPointer);
    return DVDNAV_STATUS_ERR;
  }
  if(!pci->hli.hl_gi.hli_ss) {
    mp_msg( MSGT_CPLAYER,MSGL_ERR,MSGTR_LIBMPDVDNAV_NotInAMenu);
    return DVDNAV_STATUS_ERR;
  }
  if(this->last_cmd_nav_lbn == pci->pci_gi.nv_pck_lbn) {
    mp_msg( MSGT_CPLAYER,MSGL_ERR,MSGTR_LIBMPDVDNAV_ThisNAVHasAlreadyBeenLeft);
    return DVDNAV_STATUS_ERR;
  }

  cur_button = this->vm->state.HL_BTNN_REG >> 10;

  best = 0;
  dist = 0x08000000; /* >> than  (720*720)+(567*567); */

  /* Loop through all buttons */
  for(button = 1; button <= pci->hli.hl_gi.btn_ns; button++) {
    btni_t *button_ptr = &(pci->hli.btnit[button-1]);

    if((x >= button_ptr->x_start) && (x <= button_ptr->x_end) &&
       (y >= button_ptr->y_start) && (y <= button_ptr->y_end)) {
      mx = (button_ptr->x_start + button_ptr->x_end)/2;
      my = (button_ptr->y_start + button_ptr->y_end)/2;
      dx = mx - x;
      dy = my - y;
      d = (dx*dx) + (dy*dy);
      /* If the mouse is within the button and the mouse is closer
       * to the center of this button then it is the best choice. */
      if(d < dist) {
        dist = d;
        best = button;
      }
    }
  }
  /* As an efficiency measure, only re-select the button
   * if it is different to the previously selected one. */
  if (best != 0 && best != cur_button)
    dvdnav_button_select(this, pci, best);

  /* return DVDNAV_STATUS_OK only if we actually found a matching button */
  return best ? DVDNAV_STATUS_OK : DVDNAV_STATUS_ERR;
}

dvdnav_status_t dvdnav_mouse_activate(dvdnav_t *this, pci_t *pci, int32_t x, int32_t y) {
  /* A trivial function */
  if(dvdnav_mouse_select(this, pci, x,y) != DVDNAV_STATUS_ERR)
    return dvdnav_button_activate(this, pci);
  return DVDNAV_STATUS_ERR;
}
