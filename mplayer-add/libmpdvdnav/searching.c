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
 * $Id: searching.c,v 1.35 2004/01/07 19:35:12 mroi Exp $
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
#include "dvdnav_internal.h"

/*
#define LOG_DEBUG
*/

#ifdef USE_MPDVDNAV
#include "../mp_msg.h"
#include "../help_mp.h"
#endif

/* Searching API calls */

dvdnav_status_t dvdnav_time_search(dvdnav_t *this,
				   uint64_t time) {
  /* FIXME: Time search the current PGC based on the xxx table */
  return DVDNAV_STATUS_OK;
}

/* Scan the ADMAP for a particular block number. */
/* Return placed in vobu. */
/* Returns error status */
/* FIXME: Maybe need to handle seeking outside current cell. */
static dvdnav_status_t dvdnav_scan_admap(dvdnav_t *this, int32_t domain, uint32_t seekto_block, uint32_t *vobu) {
  vobu_admap_t *admap = NULL;

#ifdef LOG_DEBUG
  mp_msg(MSGT_FIXME,MSGL_FIXME, "libdvdnav: Seeking to target %u ...\n", seekto_block);
#endif
  *vobu = -1;

  /* Search through the VOBU_ADMAP for the nearest VOBU
   * to the target block */
  switch(domain) {
  case FP_DOMAIN:
  case VMGM_DOMAIN:
    admap = this->vm->vmgi->menu_vobu_admap;
    break;
  case VTSM_DOMAIN:
    admap = this->vm->vtsi->menu_vobu_admap;
    break;
  case VTS_DOMAIN:
    admap = this->vm->vtsi->vts_vobu_admap;
    break;
  default:
    mp_msg(MSGT_CPLAYER,MSGL_INFO,MSGTR_LIBMPDVDNAV_UnknownDomainForSeeking);
  }
  if(admap) {
    uint32_t address = 0;
    uint32_t vobu_start, next_vobu;
    int32_t found = 0;

    /* Search through ADMAP for best sector */
    vobu_start = SRI_END_OF_CELL;
    /* FIXME: Implement a faster search algorithm */
    while((!found) && ((address<<2) < admap->last_byte)) {
      next_vobu = admap->vobu_start_sectors[address];

      /* mp_msg(MSGT_FIXME,MSGL_FIXME, "libdvdnav: Found block %u\n", next_vobu); */

      if(vobu_start <= seekto_block &&
          next_vobu > seekto_block) {
        found = 1;
      } else {
        vobu_start = next_vobu;
      }
      address ++;
    }
    if(found) {
      *vobu = vobu_start;
      return DVDNAV_STATUS_OK;
    } else {
      mp_msg(MSGT_CPLAYER,MSGL_INFO,MSGTR_LIBMPDVDNAV_CouldNotLocateBlock);
      return DVDNAV_STATUS_ERR;
    }
  }
  mp_msg(MSGT_CPLAYER,MSGL_INFO,MSGTR_LIBMPDVDNAV_AdmapNotLocated);
  return DVDNAV_STATUS_ERR;
}

dvdnav_status_t dvdnav_sector_search(dvdnav_t *this,
				     uint64_t offset, int32_t origin) {
  uint32_t target = 0;
  uint32_t length = 0;
  uint32_t first_cell_nr, last_cell_nr, cell_nr;
  int32_t found;
  cell_playback_t *cell;
  dvd_state_t *state;
  dvdnav_status_t result;

  if(this->position_current.still != 0) {
    printerr(MSGTR_LIBMPDVDNAV_Err_CannotSeekInAStillFrame);
    return DVDNAV_STATUS_ERR;
  }

  result = dvdnav_get_position(this, &target, &length);
  if(!result) {
    return DVDNAV_STATUS_ERR;
  }

  pthread_mutex_lock(&this->vm_lock);
  state = &(this->vm->state);
  if(!state->pgc) {
    printerr(MSGTR_LIBMPDVDNAV_Err_NoCurrentPGC);
    pthread_mutex_unlock(&this->vm_lock);
    return DVDNAV_STATUS_ERR;
  }
#ifdef LOG_DEBUG
  mp_msg(MSGT_FIXME,MSGL_FIXME, "libdvdnav: seeking to offset=%lu pos=%u length=%u\n", offset, target, length);
  mp_msg(MSGT_FIXME,MSGL_FIXME, "libdvdnav: Before cellN=%u blockN=%u\n", state->cellN, state->blockN);
#endif

  switch(origin) {
   case SEEK_SET:
    if(offset > length) {
      printerr(MSGTR_LIBMPDVDNAV_Err_RequestToSeekBehindEnd);
      pthread_mutex_unlock(&this->vm_lock);
      return DVDNAV_STATUS_ERR;
    }
    target = offset;
    break;
   case SEEK_CUR:
    if(target + offset > length) {
      printerr(MSGTR_LIBMPDVDNAV_Err_RequestToSeekBehindEnd);
      pthread_mutex_unlock(&this->vm_lock);
      return DVDNAV_STATUS_ERR;
    }
    target += offset;
    break;
   case SEEK_END:
    if(length - offset < 0) {
      printerr(MSGTR_LIBMPDVDNAV_Err_RequestToSeekBeforeStart);
      pthread_mutex_unlock(&this->vm_lock);
      return DVDNAV_STATUS_ERR;
    }
    target = length - offset;
    break;
   default:
    /* Error occured */
    printerr(MSGTR_LIBMPDVDNAV_Err_IllegalSeekMode);
    pthread_mutex_unlock(&this->vm_lock);
    return DVDNAV_STATUS_ERR;
  }

  if (this->pgc_based) {
    first_cell_nr = 1;
    last_cell_nr = state->pgc->nr_of_cells;
  } else {
    /* Find start cell of program. */
    first_cell_nr = state->pgc->program_map[state->pgN-1];
    /* Find end cell of program */
    if(state->pgN < state->pgc->nr_of_programs)
      last_cell_nr = state->pgc->program_map[state->pgN] - 1;
    else
      last_cell_nr = state->pgc->nr_of_cells;
  }

  found = 0;
  for(cell_nr = first_cell_nr; (cell_nr <= last_cell_nr) && !found; cell_nr ++) {
    cell =  &(state->pgc->cell_playback[cell_nr-1]);
    length = cell->last_sector - cell->first_sector + 1;
    if (target >= length) {
      target -= length;
    } else {
      /* convert the target sector from Cell-relative to absolute physical sector */
      target += cell->first_sector;
      found = 1;
      break;
    }
  }

  if(found) {
    int32_t vobu;
#ifdef LOG_DEBUG
    mp_msg(MSGT_FIXME,MSGL_FIXME, "libdvdnav: Seeking to cell %i from choice of %i to %i\n",
	    cell_nr, first_cell_nr, last_cell_nr);
#endif
    if (dvdnav_scan_admap(this, state->domain, target, &vobu) == DVDNAV_STATUS_OK) {
      int32_t start = state->pgc->cell_playback[cell_nr-1].first_sector;

      if (vm_jump_cell_block(this->vm, cell_nr, vobu - start)) {
#ifdef LOG_DEBUG
        mp_msg(MSGT_FIXME,MSGL_FIXME, "libdvdnav: After cellN=%u blockN=%u target=%x vobu=%x start=%x\n" ,
          state->cellN, state->blockN, target, vobu, start);
#endif
        this->vm->hop_channel += HOP_SEEK;
        pthread_mutex_unlock(&this->vm_lock);
        return DVDNAV_STATUS_OK;
      }
    }
  }

  mp_msg(MSGT_CPLAYER,MSGL_INFO,MSGTR_LIBMPDVDNAV_ErrorWhenSeeking);
  mp_msg(MSGT_CPLAYER,MSGL_INFO,MSGTR_LIBMPDVDNAV_FIXMEImplementSeekingToLocation, target);
  printerr(MSGTR_LIBMPDVDNAV_Err_ErrorWhenSeeking);
  pthread_mutex_unlock(&this->vm_lock);
  return DVDNAV_STATUS_ERR;
}

dvdnav_status_t dvdnav_part_search(dvdnav_t *this, int32_t part) {
  int32_t title, old_part;

  if (dvdnav_current_title_info(this, &title, &old_part) == DVDNAV_STATUS_OK)
    return dvdnav_part_play(this, title, part);
  return DVDNAV_STATUS_ERR;
}

dvdnav_status_t dvdnav_prev_pg_search(dvdnav_t *this) {

  if(!this) {
    printerr(MSGTR_LIBMPDVDNAV_Err_PassedANullPointer);
    return DVDNAV_STATUS_ERR;
  }

  pthread_mutex_lock(&this->vm_lock);
  if(!this->vm->state.pgc) {
    printerr(MSGTR_LIBMPDVDNAV_Err_NoCurrentPGC);
    pthread_mutex_unlock(&this->vm_lock);
    return DVDNAV_STATUS_ERR;
  }

#ifdef LOG_DEBUG
  mp_msg(MSGT_FIXME,MSGL_FIXME, "libdvdnav: previous chapter\n");
#endif
  if (!vm_jump_prev_pg(this->vm)) {
    mp_msg(MSGT_CPLAYER,MSGL_INFO,MSGTR_LIBMPDVDNAV_PreviousChapterFailed);
    printerr(MSGTR_LIBMPDVDNAV_Err_SkipToPreviousChapterFailed);
    pthread_mutex_unlock(&this->vm_lock);
    return DVDNAV_STATUS_ERR;
  }
  this->position_current.still = 0;
  this->vm->hop_channel++;
#ifdef LOG_DEBUG
  mp_msg(MSGT_FIXME,MSGL_FIXME, "libdvdnav: previous chapter done\n");
#endif
  pthread_mutex_unlock(&this->vm_lock);

  return DVDNAV_STATUS_OK;
}

dvdnav_status_t dvdnav_top_pg_search(dvdnav_t *this) {

  if(!this) {
    printerr(MSGTR_LIBMPDVDNAV_Err_PassedANullPointer);
    return DVDNAV_STATUS_ERR;
  }

  pthread_mutex_lock(&this->vm_lock);
  if(!this->vm->state.pgc) {
    printerr(MSGTR_LIBMPDVDNAV_Err_NoCurrentPGC);
    pthread_mutex_unlock(&this->vm_lock);
    return DVDNAV_STATUS_ERR;
  }

#ifdef LOG_DEBUG
  mp_msg(MSGT_FIXME,MSGL_FIXME, "libdvdnav: top chapter\n");
#endif
  if (!vm_jump_top_pg(this->vm)) {
    mp_msg(MSGT_CPLAYER,MSGL_INFO,MSGTR_LIBMPDVDNAV_TopChapterFailed);
    printerr(MSGTR_LIBMPDVDNAV_Err_SkipToTopChapterFailed);
    pthread_mutex_unlock(&this->vm_lock);
    return DVDNAV_STATUS_ERR;
  }
  this->position_current.still = 0;
  this->vm->hop_channel++;
#ifdef LOG_DEBUG
  mp_msg(MSGT_FIXME,MSGL_FIXME, "libdvdnav: top chapter done\n");
#endif
  pthread_mutex_unlock(&this->vm_lock);

  return DVDNAV_STATUS_OK;
}

dvdnav_status_t dvdnav_next_pg_search(dvdnav_t *this) {
  vm_t *try_vm;

  if(!this) {
    printerr(MSGTR_LIBMPDVDNAV_Err_PassedANullPointer);
    return DVDNAV_STATUS_ERR;
  }

  pthread_mutex_lock(&this->vm_lock);
  if(!this->vm->state.pgc) {
    printerr(MSGTR_LIBMPDVDNAV_Err_NoCurrentPGC);
    pthread_mutex_unlock(&this->vm_lock);
    return DVDNAV_STATUS_ERR;
  }

#ifdef LOG_DEBUG
  mp_msg(MSGT_FIXME,MSGL_FIXME, "libdvdnav: next chapter\n");
#endif
  /* make a copy of current VM and try to navigate the copy to the next PG */
  try_vm = vm_new_copy(this->vm);
  if (!vm_jump_next_pg(try_vm) || try_vm->stopped) {
    vm_free_copy(try_vm);
    /* next_pg failed, try to jump at least to the next cell */
    try_vm = vm_new_copy(this->vm);
    vm_get_next_cell(try_vm);
    if (try_vm->stopped) {
      vm_free_copy(try_vm);
      mp_msg(MSGT_CPLAYER,MSGL_INFO,MSGTR_LIBMPDVDNAV_NextChapterFailed);
      printerr(MSGTR_LIBMPDVDNAV_Err_SkipToNextChapterFailed);
      pthread_mutex_unlock(&this->vm_lock);
      return DVDNAV_STATUS_ERR;
    }
  }
  /* merge changes on success */
  vm_merge(this->vm, try_vm);
  vm_free_copy(try_vm);
  this->position_current.still = 0;
  this->vm->hop_channel++;
#ifdef LOG_DEBUG
  mp_msg(MSGT_FIXME,MSGL_FIXME, "libdvdnav: next chapter done\n");
#endif
  pthread_mutex_unlock(&this->vm_lock);

  return DVDNAV_STATUS_OK;
}

dvdnav_status_t dvdnav_menu_call(dvdnav_t *this, DVDMenuID_t menu) {
  vm_t *try_vm;

  if(!this) {
    printerr(MSGTR_LIBMPDVDNAV_Err_PassedANullPointer);
    return DVDNAV_STATUS_ERR;
  }

  pthread_mutex_lock(&this->vm_lock);
  if(!this->vm->state.pgc) {
    printerr(MSGTR_LIBMPDVDNAV_Err_NoCurrentPGC);
    pthread_mutex_unlock(&this->vm_lock);
    return DVDNAV_STATUS_ERR;
  }

  /* make a copy of current VM and try to navigate the copy to the menu */
  try_vm = vm_new_copy(this->vm);
  if ( (menu == DVD_MENU_Escape) && (this->vm->state.domain != VTS_DOMAIN)) {
    /* Try resume */
    if (vm_jump_resume(try_vm) && !try_vm->stopped) {
        /* merge changes on success */
        vm_merge(this->vm, try_vm);
        vm_free_copy(try_vm);
        this->position_current.still = 0;
        this->vm->hop_channel++;
        pthread_mutex_unlock(&this->vm_lock);
        return DVDNAV_STATUS_OK;
    }
  }
  if (menu == DVD_MENU_Escape) menu = DVD_MENU_Root;

  if (vm_jump_menu(try_vm, menu) && !try_vm->stopped) {
    /* merge changes on success */
    vm_merge(this->vm, try_vm);
    vm_free_copy(try_vm);
    this->position_current.still = 0;
    this->vm->hop_channel++;
    pthread_mutex_unlock(&this->vm_lock);
    return DVDNAV_STATUS_OK;
  } else {
    vm_free_copy(try_vm);
    printerr(MSGTR_LIBMPDVDNAV_Err_NoSuchMenuOrMenuNotReachable);
    pthread_mutex_unlock(&this->vm_lock);
    return DVDNAV_STATUS_ERR;
  }
}

dvdnav_status_t dvdnav_get_position(dvdnav_t *this, uint32_t *pos,
				    uint32_t *len) {
  uint32_t cur_sector;
  int32_t cell_nr, first_cell_nr, last_cell_nr;
  cell_playback_t *cell;
  dvd_state_t *state;

  if(!this || !pos || !len) {
    printerr(MSGTR_LIBMPDVDNAV_Err_PassedANullPointer);
    return DVDNAV_STATUS_ERR;
  }
  if(!this->started) {
    printerr(MSGTR_LIBMPDVDNAV_Err_VirtualDVDMachineNotStarted);
    return DVDNAV_STATUS_ERR;
  }

  pthread_mutex_lock(&this->vm_lock);
  state = &(this->vm->state);
  if(!state->pgc || this->vm->stopped) {
    printerr(MSGTR_LIBMPDVDNAV_Err_NoCurrentPGC);
    pthread_mutex_unlock(&this->vm_lock);
    return DVDNAV_STATUS_ERR;
  }
  if (this->position_current.hop_channel  != this->vm->hop_channel ||
      this->position_current.domain       != state->domain         ||
      this->position_current.vts          != state->vtsN           ||
      this->position_current.cell_restart != state->cell_restart) {
    printerr(MSGTR_LIBMPDVDNAV_Err_NewPositionNotYetDetermined);
    pthread_mutex_unlock(&this->vm_lock);
    return DVDNAV_STATUS_ERR;
  }

  /* Get current sector */
  cur_sector = this->vobu.vobu_start + this->vobu.blockN;

  if (this->pgc_based) {
    first_cell_nr = 1;
    last_cell_nr = state->pgc->nr_of_cells;
  } else {
    /* Find start cell of program. */
    first_cell_nr = state->pgc->program_map[state->pgN-1];
    /* Find end cell of program */
    if(state->pgN < state->pgc->nr_of_programs)
      last_cell_nr = state->pgc->program_map[state->pgN] - 1;
    else
      last_cell_nr = state->pgc->nr_of_cells;
  }

  *pos = -1;
  *len = 0;
  for (cell_nr = first_cell_nr; cell_nr <= last_cell_nr; cell_nr++) {
    cell = &(state->pgc->cell_playback[cell_nr-1]);
    if (cell_nr == state->cellN) {
      /* the current sector is in this cell,
       * pos is length of PG up to here + sector's offset in this cell */
      *pos = *len + cur_sector - cell->first_sector;
    }
    *len += cell->last_sector - cell->first_sector + 1;
  }

  assert((signed)*pos != -1);

  pthread_mutex_unlock(&this->vm_lock);

  return DVDNAV_STATUS_OK;
}

dvdnav_status_t dvdnav_get_position_in_title(dvdnav_t *this,
					     uint32_t *pos,
					     uint32_t *len) {
  uint32_t cur_sector;
  uint32_t first_cell_nr;
  uint32_t last_cell_nr;
  cell_playback_t *first_cell;
  cell_playback_t *last_cell;
  dvd_state_t *state;

  if(!this || !pos || !len) {
    printerr(MSGTR_LIBMPDVDNAV_Err_PassedANullPointer);
    return DVDNAV_STATUS_ERR;
  }

  state = &(this->vm->state);
  if(!state->pgc) {
    printerr(MSGTR_LIBMPDVDNAV_Err_NoCurrentPGC);
    return DVDNAV_STATUS_ERR;
  }

  /* Get current sector */
  cur_sector = this->vobu.vobu_start + this->vobu.blockN;

  /* Now find first and last cells in title. */
  first_cell_nr = state->pgc->program_map[0];
  first_cell = &(state->pgc->cell_playback[first_cell_nr-1]);
  last_cell_nr = state->pgc->nr_of_cells;
  last_cell = &(state->pgc->cell_playback[last_cell_nr-1]);

  *pos = cur_sector - first_cell->first_sector;
  *len = last_cell->last_sector - first_cell->first_sector;

  return DVDNAV_STATUS_OK;
}

#ifdef USE_MPDVDNAV
dvdnav_status_t dvdnav_get_pgc(dvdnav_t *this, int *pg_num)
{
  if(!this || !pg_num) {
    printerr(MSGTR_LIBMPDVDNAV_Err_PassedANullPointer);
    return DVDNAV_STATUS_ERR;
  }

  pthread_mutex_lock(&this->vm_lock);
  if(!this->vm->state.pgc) {
    printerr(MSGTR_LIBMPDVDNAV_Err_NoCurrentPGC);
    pthread_mutex_unlock(&this->vm_lock);
    return DVDNAV_STATUS_ERR;
  }
#ifdef LOG_DEBUG
  mp_msg(MSGT_FIXME,MSGL_FIXME, "libdvdnav: get pgc\n");
#endif
  *pg_num = vm_get_PGCN(this->vm);
  pthread_mutex_unlock(&this->vm_lock);
  return DVDNAV_STATUS_OK;
}
#endif
