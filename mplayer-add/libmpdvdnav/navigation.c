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
 * $Id: navigation.c,v 1.21 2004/01/07 19:34:28 mroi Exp $
 *
 */

#ifndef HAVE_MPLAYER
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#else
#include "config.h"
#endif

#include "dvdnav_internal.h"

#ifdef USE_MPDVDNAV
#include "../mp_msg.h"
#include "../help_mp.h"
#endif

/* Navigation API calls */

dvdnav_status_t dvdnav_still_skip(dvdnav_t *this) {
  if(!this) {
    mp_msg(MSGT_CPLAYER,MSGL_ERR,MSGTR_LIBMPDVDNAV_PassedANullPointer);
    return DVDNAV_STATUS_ERR;
  }

  this->position_current.still = 0;
  this->skip_still = 1;
  this->sync_wait = 0;
  this->sync_wait_skip = 1;

  return DVDNAV_STATUS_OK;
}

#ifdef USE_MPDVDNAV
dvdnav_status_t dvdnav_still_back(dvdnav_t *this) {
  if(!this) {
    mp_msg(MSGT_CPLAYER,MSGL_ERR,MSGTR_LIBMPDVDNAV_PassedANullPointer);
    return DVDNAV_STATUS_ERR;
  }

  this->position_current.still = 0;
  this->skip_still = 0;
  this->sync_wait = 0;
  this->sync_wait_skip = 1;

  pthread_mutex_lock(&this->vm_lock);
  vm_play_cell(this->vm);
//  vm_play_pgc(this->vm);
  pthread_mutex_unlock(&this->vm_lock);

  return DVDNAV_STATUS_OK;
}

dvdnav_status_t dvdnav_wait_back(dvdnav_t *this) {
  if(!this) {
    mp_msg(MSGT_CPLAYER,MSGL_ERR,MSGTR_LIBMPDVDNAV_PassedANullPointer);
    return DVDNAV_STATUS_ERR;
  }

  this->position_current.still = 0;
  this->skip_still = 0;
  this->sync_wait = 0;
  this->sync_wait_skip = 0;

  pthread_mutex_lock(&this->vm_lock);
  vm_play_cell(this->vm);
//  vm_play_pgc(this->vm);
  pthread_mutex_unlock(&this->vm_lock);

  return DVDNAV_STATUS_OK;
}

dvdnav_status_t dvdnav_wait_still_clear(dvdnav_t *this) {
  if(!this) {
    mp_msg(MSGT_CPLAYER,MSGL_ERR,MSGTR_LIBMPDVDNAV_PassedANullPointer);
    return DVDNAV_STATUS_ERR;
  }

  this->position_current.still = 0;
  this->skip_still = 0;
  this->sync_wait = 0;
  this->sync_wait_skip = 0;

  return DVDNAV_STATUS_OK;
}

dvdnav_status_t dvdnav_is_still_cell(dvdnav_t *this, int *flag)
{
  if(!this || !flag) {
    mp_msg(MSGT_CPLAYER,MSGL_ERR,MSGTR_LIBMPDVDNAV_PassedANullPointer);
    return DVDNAV_STATUS_ERR;
  }
  *flag=this->position_current.still;
  return DVDNAV_STATUS_OK;
}
#endif

dvdnav_status_t dvdnav_wait_skip(dvdnav_t *this) {
  if(!this) {
    mp_msg(MSGT_CPLAYER,MSGL_ERR,MSGTR_LIBMPDVDNAV_PassedANullPointer);
    return DVDNAV_STATUS_ERR;
  }

  this->sync_wait = 0;
  this->sync_wait_skip = 1;

  return DVDNAV_STATUS_OK;
}

dvdnav_status_t dvdnav_get_number_of_titles(dvdnav_t *this, int32_t *titles) {
  if(!this || !titles) {
    mp_msg(MSGT_CPLAYER,MSGL_ERR,MSGTR_LIBMPDVDNAV_PassedANullPointer);
    return DVDNAV_STATUS_ERR;
  }
  if(!this->started) {
    mp_msg(MSGT_CPLAYER,MSGL_ERR,MSGTR_LIBMPDVDNAV_VirtualDVDMachineNotStarted);
    return DVDNAV_STATUS_ERR;
  }

  (*titles) = vm_get_vmgi(this->vm)->tt_srpt->nr_of_srpts;

  return DVDNAV_STATUS_OK;
}

dvdnav_status_t dvdnav_get_number_of_parts(dvdnav_t *this, int32_t title, int32_t *parts) {
  if(!this || !parts) {
    mp_msg(MSGT_CPLAYER,MSGL_ERR,MSGTR_LIBMPDVDNAV_PassedANullPointer);
    return DVDNAV_STATUS_ERR;
  }
  if(!this->started) {
    mp_msg(MSGT_CPLAYER,MSGL_ERR,MSGTR_LIBMPDVDNAV_VirtualDVDMachineNotStarted);
    return DVDNAV_STATUS_ERR;
  }
  if ((title < 1) || (title > vm_get_vmgi(this->vm)->tt_srpt->nr_of_srpts) ) {
    mp_msg(MSGT_CPLAYER,MSGL_ERR,MSGTR_LIBMPDVDNAV_PassedATitleNumberOutOfRange);
    return DVDNAV_STATUS_ERR;
  }

  (*parts) = vm_get_vmgi(this->vm)->tt_srpt->title[title-1].nr_of_ptts;

  return DVDNAV_STATUS_OK;
}

dvdnav_status_t dvdnav_current_title_info(dvdnav_t *this, int32_t *title, int32_t *part) {
  int32_t retval;

  if(!this || !title || !part) {
    mp_msg(MSGT_CPLAYER,MSGL_ERR,MSGTR_LIBMPDVDNAV_PassedANullPointer);
    return DVDNAV_STATUS_ERR;
  }

  pthread_mutex_lock(&this->vm_lock);
  if (!this->vm->vtsi || !this->vm->vmgi) {
    mp_msg(MSGT_CPLAYER,MSGL_ERR,MSGTR_LIBMPDVDNAV_BadVMState);
    pthread_mutex_unlock(&this->vm_lock);
    return DVDNAV_STATUS_ERR;
  }
  if (!this->vm->state.pgc) {
    mp_msg(MSGT_CPLAYER,MSGL_ERR,MSGTR_LIBMPDVDNAV_NoCurrentPGC);
    pthread_mutex_unlock(&this->vm_lock);
    return DVDNAV_STATUS_ERR;
  }
  if ( (this->vm->state.domain == VTSM_DOMAIN)
      || (this->vm->state.domain == VMGM_DOMAIN) ) {
    /* Get current Menu ID: into *part. */
    vm_get_current_menu(this->vm, part);
    if (*part > -1) {
      *title = 0;
      pthread_mutex_unlock(&this->vm_lock);
      return DVDNAV_STATUS_OK;
    }
  }
  if (this->vm->state.domain == VTS_DOMAIN) {
    retval = vm_get_current_title_part(this->vm, title, part);
    pthread_mutex_unlock(&this->vm_lock);
    return retval ? DVDNAV_STATUS_OK : DVDNAV_STATUS_ERR;
  }
  mp_msg(MSGT_CPLAYER,MSGL_ERR,MSGTR_LIBMPDVDNAV_NotInATitleOrMenu);
  pthread_mutex_unlock(&this->vm_lock);
  return DVDNAV_STATUS_ERR;
}

dvdnav_status_t dvdnav_title_play(dvdnav_t *this, int32_t title) {
  if(!this) {
    mp_msg(MSGT_CPLAYER,MSGL_ERR,MSGTR_LIBMPDVDNAV_PassedANullPointer);
    return DVDNAV_STATUS_ERR;
  }
  return dvdnav_part_play(this, title, 1);
}

dvdnav_status_t dvdnav_part_play(dvdnav_t *this, int32_t title, int32_t part) {
  int32_t retval;

  if(!this) {
    mp_msg(MSGT_CPLAYER,MSGL_ERR,MSGTR_LIBMPDVDNAV_PassedANullPointer);
    return DVDNAV_STATUS_ERR;
  }

  pthread_mutex_lock(&this->vm_lock);
  if (!this->vm->vmgi) {
    mp_msg(MSGT_CPLAYER,MSGL_ERR,MSGTR_LIBMPDVDNAV_BadVMState);
    pthread_mutex_unlock(&this->vm_lock);
    return DVDNAV_STATUS_ERR;
  }
  if (!this->vm->state.pgc) {
    mp_msg(MSGT_CPLAYER,MSGL_ERR,MSGTR_LIBMPDVDNAV_NoCurrentPGC);
    pthread_mutex_unlock(&this->vm_lock);
    return DVDNAV_STATUS_ERR;
  }
  if((title < 1) || (title > this->vm->vmgi->tt_srpt->nr_of_srpts)) {
    mp_msg(MSGT_CPLAYER,MSGL_ERR,MSGTR_LIBMPDVDNAV_TitleOutOfRange);
    pthread_mutex_unlock(&this->vm_lock);
    return DVDNAV_STATUS_ERR;
  }
  if((part < 1) || (part > this->vm->vmgi->tt_srpt->title[title-1].nr_of_ptts)) {
    mp_msg(MSGT_CPLAYER,MSGL_ERR,MSGTR_LIBMPDVDNAV_PartOutOfRange);
    pthread_mutex_unlock(&this->vm_lock);
    return DVDNAV_STATUS_ERR;
  }

  retval = vm_jump_title_part(this->vm, title, part);
  if (retval)
    this->vm->hop_channel++;
  pthread_mutex_unlock(&this->vm_lock);

  return retval ? DVDNAV_STATUS_OK : DVDNAV_STATUS_ERR;
}

dvdnav_status_t dvdnav_part_play_auto_stop(dvdnav_t *this, int32_t title,
					   int32_t part, int32_t parts_to_play) {
  /* FIXME: Implement auto-stop */
 if (dvdnav_part_play(this, title, part) == DVDNAV_STATUS_OK)
   mp_msg(MSGT_CPLAYER,MSGL_ERR,MSGTR_LIBMPDVDNAV_NotImplementedYet);
 return DVDNAV_STATUS_ERR;
}

dvdnav_status_t dvdnav_time_play(dvdnav_t *this, int32_t title,
				 uint64_t time) {
  if(!this) {
    mp_msg(MSGT_CPLAYER,MSGL_ERR,MSGTR_LIBMPDVDNAV_PassedANullPointer);
    return DVDNAV_STATUS_ERR;
  }

  /* FIXME: Implement */
   mp_msg(MSGT_CPLAYER,MSGL_ERR,MSGTR_LIBMPDVDNAV_NotImplementedYet);
  return DVDNAV_STATUS_ERR;
}

dvdnav_status_t dvdnav_stop(dvdnav_t *this) {
  if(!this) {
    mp_msg(MSGT_CPLAYER,MSGL_ERR,MSGTR_LIBMPDVDNAV_PassedANullPointer);
    return DVDNAV_STATUS_ERR;
  }

  pthread_mutex_lock(&this->vm_lock);
  this->vm->stopped = 1;
  pthread_mutex_unlock(&this->vm_lock);
  return DVDNAV_STATUS_OK;
}

dvdnav_status_t dvdnav_go_up(dvdnav_t *this) {
  if(!this) {
    mp_msg(MSGT_CPLAYER,MSGL_ERR,MSGTR_LIBMPDVDNAV_PassedANullPointer);
    return DVDNAV_STATUS_ERR;
  }

  /* A nice easy function... delegate to the VM */
  pthread_mutex_lock(&this->vm_lock);
  vm_jump_up(this->vm);
  pthread_mutex_unlock(&this->vm_lock);

  return DVDNAV_STATUS_OK;
}
