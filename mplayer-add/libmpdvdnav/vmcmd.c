/*
 * Copyright (C) 2000, 2001 Martin Norbäck, Håkan Hjort
 *               2002-2004 the dvdnav project
 *
 * This file is part of libdvdnav, a DVD navigation library. It is modified
 * from a file originally part of the Ogle DVD player.
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
 * $Id: vmcmd.c,v 1.2 2004/03/03 16:50:42 mroi Exp $
 *
 */

#ifndef HAVE_MPLAYER
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#else
#include "config.h"
#endif

#include <stdio.h>
#include <ctype.h>
#include <inttypes.h>

#include "dvdnav_internal.h"

#ifdef USE_MPDVDNAV
#include "../mp_msg.h"
#include "../help_mp.h"
#endif


/*  freebsd compatibility */
#ifndef PRIu8
#define PRIu8 "d"
#endif

/*  freebsd compatibility */
#ifndef PRIu16
#define PRIu16 "d"
#endif

static const char *cmp_op_table[] = {
  NULL, "&", "==", "!=", ">=", ">", "<=", "<"
};
static const char *set_op_table[] = {
  NULL, "=", "<->", "+=", "-=", "*=", "/=", "%=", "rnd", "&=", "|=", "^="
};

static const char *link_table[] = {
  "LinkNoLink",  "LinkTopC",    "LinkNextC",   "LinkPrevC",
  NULL,          "LinkTopPG",   "LinkNextPG",  "LinkPrevPG",
  NULL,          "LinkTopPGC",  "LinkNextPGC", "LinkPrevPGC",
  "LinkGoUpPGC", "LinkTailPGC", NULL,          NULL,
  "RSM"
};

static const char *system_reg_table[] = {
  "Menu Description Language Code",
  "Audio Stream Number",
  "Sub-picture Stream Number",
  "Angle Number",
  "Title Track Number",
  "VTS Title Track Number",
  "VTS PGC Number",
  "PTT Number for One_Sequential_PGC_Title",
  "Highlighted Button Number",
  "Navigation Timer",
  "Title PGC Number for Navigation Timer",
  "Audio Mixing Mode for Karaoke",
  "Country Code for Parental Management",
  "Parental Level",
  "Player Configurations for Video",
  "Player Configurations for Audio",
  "Initial Language Code for Audio",
  "Initial Language Code Extension for Audio",
  "Initial Language Code for Sub-picture",
  "Initial Language Code Extension for Sub-picture",
  "Player Regional Code",
  "Reserved 21",
  "Reserved 22",
  "Reserved 23"
};

static const char *system_reg_abbr_table[] = {
  NULL,
  "ASTN",
  "SPSTN",
  "AGLN",
  "TTN",
  "VTS_TTN",
  "TT_PGCN",
  "PTTN",
  "HL_BTNN",
  "NVTMR",
  "NV_PGCN",
  NULL,
  "CC_PLT",
  "PLT",
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
};

static void print_system_reg(uint16_t reg) {
  if(reg < sizeof(system_reg_abbr_table) / sizeof(char *))
    mp_msg(MSGT_CPLAYER,MSGL_INFO, "%s (SRPM:%d)", system_reg_table[reg], reg);
  else
    mp_msg(MSGT_CPLAYER,MSGL_INFO, " WARNING: Unknown system register ( reg=%d ) ", reg);
}

static void print_g_reg(uint8_t reg) {
    if(reg < 16)
      mp_msg(MSGT_CPLAYER,MSGL_INFO, "g[%" PRIu8 "]", reg);
    else
      mp_msg(MSGT_CPLAYER,MSGL_INFO, " WARNING: Unknown general register ");
}

static void print_reg(uint8_t reg) {
  if(reg & 0x80)
    print_system_reg(reg & 0x7f);
  else
    print_g_reg(reg & 0x7f);
}

static void print_cmp_op(uint8_t op) {
  if(op < sizeof(cmp_op_table) / sizeof(char *) && cmp_op_table[op] != NULL)
    mp_msg(MSGT_CPLAYER,MSGL_INFO, " %s ", cmp_op_table[op]);
  else
    mp_msg(MSGT_CPLAYER,MSGL_INFO, " WARNING: Unknown compare op ");
}

static void print_set_op(uint8_t op) {
  if(op < sizeof(set_op_table) / sizeof(char *) && set_op_table[op] != NULL)
    mp_msg(MSGT_CPLAYER,MSGL_INFO, " %s ", set_op_table[op]);
  else
    mp_msg(MSGT_CPLAYER,MSGL_INFO, " WARNING: Unknown set op ");
}

static void print_reg_or_data(command_t* command, int immediate, int start) {
  if(immediate) {
    uint32_t i = vm_getbits(command, start, 16);

    mp_msg(MSGT_CPLAYER,MSGL_INFO, "0x%x", i);
    if(isprint(i & 0xff) && isprint((i>>8) & 0xff))
      mp_msg(MSGT_CPLAYER,MSGL_INFO, " (\"%c%c\")", (char)((i>>8) & 0xff), (char)(i & 0xff));
  } else {
    print_reg(vm_getbits(command, start - 8, 8));
  }
}

static void print_reg_or_data_2(command_t* command, int immediate, int start) {
  if(immediate)
    mp_msg(MSGT_CPLAYER,MSGL_INFO, "0x%x", vm_getbits(command, start - 1, 7));
  else
    mp_msg(MSGT_CPLAYER,MSGL_INFO, "g[%" PRIu8 "]", vm_getbits(command, start - 4, 4));
}

static void print_reg_or_data_3(command_t* command, int immediate, int start) {
  if(immediate) {
    uint32_t i = vm_getbits(command, start, 16);

    mp_msg(MSGT_CPLAYER,MSGL_INFO, "0x%x", i);
    if(isprint(i & 0xff) && isprint((i>>8) & 0xff))
      mp_msg(MSGT_CPLAYER,MSGL_INFO, " (\"%c%c\")", (char)((i>>8) & 0xff), (char)(i & 0xff));
  } else {
    print_reg(vm_getbits(command, start, 8));
  }
}


static void print_if_version_1(command_t* command) {
  uint8_t op = vm_getbits(command, 54, 3);

  if(op) {
    mp_msg(MSGT_CPLAYER,MSGL_INFO, "if (");
    print_g_reg(vm_getbits(command,39,8));
    print_cmp_op(op);
    print_reg_or_data(command, vm_getbits(command, 55,1), 31);
    mp_msg(MSGT_CPLAYER,MSGL_INFO, ") ");
  }
}

static void print_if_version_2(command_t* command) {
  uint8_t op = vm_getbits(command, 54, 3);

  if(op) {
    mp_msg(MSGT_CPLAYER,MSGL_INFO, "if (");
    print_reg(vm_getbits(command, 15, 8));
    print_cmp_op(op);
    print_reg(vm_getbits(command, 7, 8));
    mp_msg(MSGT_CPLAYER,MSGL_INFO, ") ");
  }
}

static void print_if_version_3(command_t* command) {
  uint8_t op = vm_getbits(command, 54, 3);

  if(op) {
    mp_msg(MSGT_CPLAYER,MSGL_INFO, "if (");
    print_g_reg(vm_getbits(command, 43, 4));
    print_cmp_op(op);
    print_reg_or_data(command, vm_getbits(command, 55, 1), 15);
    mp_msg(MSGT_CPLAYER,MSGL_INFO, ") ");
  }
}

static void print_if_version_4(command_t* command) {
  uint8_t op = vm_getbits(command, 54, 3);

  if(op) {
    mp_msg(MSGT_CPLAYER,MSGL_INFO, "if (");
    print_g_reg(vm_getbits(command, 51, 4));
    print_cmp_op(op);
    print_reg_or_data(command, vm_getbits(command, 55, 1), 31);
    mp_msg(MSGT_CPLAYER,MSGL_INFO, ") ");
  }
}

static void print_if_version_5(command_t* command) {
  uint8_t op = vm_getbits(command, 54, 3);
  int set_immediate = vm_getbits(command, 60, 1);

  if(op) {
    if (set_immediate) {
      mp_msg(MSGT_CPLAYER,MSGL_INFO, "if (");
      print_g_reg(vm_getbits(command, 31, 8));
      print_cmp_op(op);
      print_reg(vm_getbits(command, 23, 8));
      mp_msg(MSGT_CPLAYER,MSGL_INFO, ") ");
    } else {
      mp_msg(MSGT_CPLAYER,MSGL_INFO, "if (");
      print_g_reg(vm_getbits(command, 39, 8));
      print_cmp_op(op);
      print_reg_or_data(command, vm_getbits(command, 55, 1), 31);
      mp_msg(MSGT_CPLAYER,MSGL_INFO, ") ");
    }
  }
}

static void print_special_instruction(command_t* command) {
  uint8_t op = vm_getbits(command, 51, 4);

  switch(op) {
    case 0: /*  NOP */
      mp_msg(MSGT_CPLAYER,MSGL_INFO, "Nop");
      break;
    case 1: /*  Goto line */
      mp_msg(MSGT_CPLAYER,MSGL_INFO, "Goto %" PRIu8, vm_getbits(command, 7, 8));
      break;
    case 2: /*  Break */
      mp_msg(MSGT_CPLAYER,MSGL_INFO, "Break");
      break;
    case 3: /*  Parental level */
      mp_msg(MSGT_CPLAYER,MSGL_INFO, "SetTmpPML %" PRIu8 ", Goto %" PRIu8,
	      vm_getbits(command, 11, 4), vm_getbits(command, 7, 8));
      break;
    default:
      mp_msg(MSGT_CPLAYER,MSGL_INFO, "WARNING: Unknown special instruction (%i)",
	      vm_getbits(command, 51, 4));
  }
}

static void print_linksub_instruction(command_t* command) {
  uint32_t linkop = vm_getbits(command, 7, 8);
  uint32_t button = vm_getbits(command, 15, 6);

  if(linkop < sizeof(link_table)/sizeof(char *) && link_table[linkop] != NULL)
    mp_msg(MSGT_CPLAYER,MSGL_INFO, "%s (button %" PRIu8 ")", link_table[linkop], button);
  else
    mp_msg(MSGT_CPLAYER,MSGL_INFO, "WARNING: Unknown linksub instruction (%i)", linkop);
}

static void print_link_instruction(command_t* command, int optional) {
  uint8_t op = vm_getbits(command, 51, 4);

  if(optional && op)
    mp_msg(MSGT_CPLAYER,MSGL_INFO, ", ");

  switch(op) {
    case 0:
      if(!optional)
      mp_msg(MSGT_CPLAYER,MSGL_INFO, "WARNING: NOP (link)!");
      break;
    case 1:
      print_linksub_instruction(command);
      break;
    case 4:
      mp_msg(MSGT_CPLAYER,MSGL_INFO, "LinkPGCN %" PRIu16, vm_getbits(command, 14, 15));
      break;
    case 5:
      mp_msg(MSGT_CPLAYER,MSGL_INFO, "LinkPTT %" PRIu16 " (button %" PRIu8 ")",
	      vm_getbits(command, 9, 10), vm_getbits(command, 15, 6));
      break;
    case 6:
      mp_msg(MSGT_CPLAYER,MSGL_INFO, "LinkPGN %" PRIu8 " (button %" PRIu8 ")",
	      vm_getbits(command, 6, 7), vm_getbits(command, 15, 6));
      break;
    case 7:
      mp_msg(MSGT_CPLAYER,MSGL_INFO, "LinkCN %" PRIu8 " (button %" PRIu8 ")",
	      vm_getbits(command, 7, 8), vm_getbits(command, 15, 6));
      break;
    default:
      mp_msg(MSGT_CPLAYER,MSGL_INFO, "WARNING: Unknown link instruction");
  }
}

static void print_jump_instruction(command_t* command) {
  switch(vm_getbits(command, 51, 4)) {
    case 1:
      mp_msg(MSGT_CPLAYER,MSGL_INFO, "Exit");
      break;
    case 2:
      mp_msg(MSGT_CPLAYER,MSGL_INFO, "JumpTT %" PRIu8, vm_getbits(command, 22, 7));
      break;
    case 3:
      mp_msg(MSGT_CPLAYER,MSGL_INFO, "JumpVTS_TT %" PRIu8, vm_getbits(command, 22, 7));
      break;
    case 5:
      mp_msg(MSGT_CPLAYER,MSGL_INFO, "JumpVTS_PTT %" PRIu8 ":%" PRIu16,
	      vm_getbits(command, 22, 7), vm_getbits(command, 41, 10));
      break;
    case 6:
      switch(vm_getbits(command, 23, 2)) {
        case 0:
          mp_msg(MSGT_CPLAYER,MSGL_INFO, "JumpSS FP");
          break;
        case 1:
          mp_msg(MSGT_CPLAYER,MSGL_INFO, "JumpSS VMGM (menu %" PRIu8 ")", vm_getbits(command, 19, 4));
          break;
        case 2:
          mp_msg(MSGT_CPLAYER,MSGL_INFO, "JumpSS VTSM (vts %" PRIu8 ", title %" PRIu8
		  ", menu %" PRIu8 ")", vm_getbits(command, 30, 7), vm_getbits(command, 38, 7), vm_getbits(command, 19, 4));
          break;
        case 3:
          mp_msg(MSGT_CPLAYER,MSGL_INFO, "JumpSS VMGM (pgc %" PRIu8 ")", vm_getbits(command, 46, 15));
          break;
        }
      break;
    case 8:
      switch(vm_getbits(command, 23, 2)) {
        case 0:
          mp_msg(MSGT_CPLAYER,MSGL_INFO, "CallSS FP (rsm_cell %" PRIu8 ")",
              vm_getbits(command, 31, 8));
          break;
        case 1:
          mp_msg(MSGT_CPLAYER,MSGL_INFO, "CallSS VMGM (menu %" PRIu8
		  ", rsm_cell %" PRIu8 ")", vm_getbits(command, 19, 4), vm_getbits(command, 31, 8));
          break;
        case 2:
          mp_msg(MSGT_CPLAYER,MSGL_INFO, "CallSS VTSM (menu %" PRIu8
		  ", rsm_cell %" PRIu8 ")", vm_getbits(command, 19, 4), vm_getbits(command, 31, 8));
          break;
        case 3:
          mp_msg(MSGT_CPLAYER,MSGL_INFO, "CallSS VMGM (pgc %" PRIu8 ", rsm_cell %" PRIu8 ")",
		  vm_getbits(command, 46, 15), vm_getbits(command, 31, 8));
          break;
      }
      break;
    default:
      mp_msg(MSGT_CPLAYER,MSGL_INFO, "WARNING: Unknown Jump/Call instruction");
  }
}

static void print_system_set(command_t* command) {
  int i;
/* FIXME: What about SPRM11 ? Karaoke */
/*        Surely there must be some system set command for that ? */

  switch(vm_getbits(command, 59, 4)) {
    case 1: /*  Set system reg 1 &| 2 &| 3 (Audio, Subp. Angle) */
      for(i = 1; i <= 3; i++) {
        if(vm_getbits(command, 47 - (i*8), 1)) {
          print_system_reg(i);
          mp_msg(MSGT_CPLAYER,MSGL_INFO, " = ");
          print_reg_or_data_2(command, vm_getbits(command, 60, 1), 47 - (i*8) );
          mp_msg(MSGT_CPLAYER,MSGL_INFO, " ");
        }
      }
      break;
    case 2: /*  Set system reg 9 & 10 (Navigation timer, Title PGC number) */
      print_system_reg(9);
      mp_msg(MSGT_CPLAYER,MSGL_INFO, " = ");
      print_reg_or_data(command, vm_getbits(command, 60, 1), 47);
      mp_msg(MSGT_CPLAYER,MSGL_INFO, " ");
      print_system_reg(10);
      mp_msg(MSGT_CPLAYER,MSGL_INFO, " = %" PRIu16, vm_getbits(command, 30, 15)); /*  ?? */
      break;
    case 3: /*  Mode: Counter / Register + Set */
      mp_msg(MSGT_CPLAYER,MSGL_INFO, "SetMode ");
      if(vm_getbits(command, 23, 1))
	mp_msg(MSGT_CPLAYER,MSGL_INFO, "Counter ");
      else
	mp_msg(MSGT_CPLAYER,MSGL_INFO, "Register ");
      print_g_reg(vm_getbits(command, 19, 4));
      print_set_op(0x1); /*  '=' */
      print_reg_or_data(command, vm_getbits(command, 60, 1), 47);
      break;
    case 6: /*  Set system reg 8 (Highlighted button) */
      print_system_reg(8);
      if(vm_getbits(command, 60, 1)) /*  immediate */
        mp_msg(MSGT_CPLAYER,MSGL_INFO, " = 0x%x (button no %d)", vm_getbits(command, 31, 16), vm_getbits(command, 31, 6));
      else
        mp_msg(MSGT_CPLAYER,MSGL_INFO, " = g[%" PRIu8 "]", vm_getbits(command, 19, 4));
      break;
    default:
      mp_msg(MSGT_CPLAYER,MSGL_INFO, "WARNING: Unknown system set instruction (%i)",
	      vm_getbits(command, 59, 4));
  }
}

static void print_set_version_1(command_t* command) {
  uint8_t set_op = vm_getbits(command, 59, 4);

  if(set_op) {
    print_g_reg(vm_getbits(command, 35, 4));
    print_set_op(set_op);
    print_reg_or_data(command, vm_getbits(command, 60, 1), 31);
  } else {
    mp_msg(MSGT_CPLAYER,MSGL_INFO, "NOP");
  }
}

static void print_set_version_2(command_t* command) {
  uint8_t set_op = vm_getbits(command, 59, 4);

  if(set_op) {
    print_g_reg(vm_getbits(command, 51, 4));
    print_set_op(set_op);
    print_reg_or_data(command, vm_getbits(command, 60, 1), 47);
  } else {
    mp_msg(MSGT_CPLAYER,MSGL_INFO, "NOP");
  }
}

static void print_set_version_3(command_t* command) {
  uint8_t set_op = vm_getbits(command, 59, 4);

  if(set_op) {
    print_g_reg(vm_getbits(command, 51, 4));
    print_set_op(set_op);
    print_reg_or_data_3(command, vm_getbits(command, 60, 1), 47);
  } else {
    mp_msg(MSGT_CPLAYER,MSGL_INFO, "NOP");
  }
}


void vm_print_mnemonic(vm_cmd_t *vm_command)  {
  command_t command;
  command.instruction =( (uint64_t) vm_command->bytes[0] << 56 ) |
        ( (uint64_t) vm_command->bytes[1] << 48 ) |
        ( (uint64_t) vm_command->bytes[2] << 40 ) |
        ( (uint64_t) vm_command->bytes[3] << 32 ) |
        ( (uint64_t) vm_command->bytes[4] << 24 ) |
        ( (uint64_t) vm_command->bytes[5] << 16 ) |
        ( (uint64_t) vm_command->bytes[6] <<  8 ) |
          (uint64_t) vm_command->bytes[7] ;
  command.examined = 0;

  switch(vm_getbits(&command,63,3)) { /* three first bits */
    case 0: /*  Special instructions */
      print_if_version_1(&command);
      print_special_instruction(&command);
      break;
    case 1: /*  Jump/Call or Link instructions */
      if(vm_getbits(&command,60,1)) {
        print_if_version_2(&command);
        print_jump_instruction(&command);
      } else {
        print_if_version_1(&command);
        print_link_instruction(&command, 0); /*  must be pressent */
      }
      break;
    case 2: /*  Set System Parameters instructions */
      print_if_version_2(&command);
      print_system_set(&command);
      print_link_instruction(&command, 1); /*  either 'if' or 'link' */
      break;
    case 3: /*  Set General Parameters instructions */
      print_if_version_3(&command);
      print_set_version_1(&command);
      print_link_instruction(&command, 1); /*  either 'if' or 'link' */
      break;
    case 4: /*  Set, Compare -> LinkSub instructions */
      print_set_version_2(&command);
      mp_msg(MSGT_CPLAYER,MSGL_INFO, ", ");
      print_if_version_4(&command);
      print_linksub_instruction(&command);
      break;
    case 5: /*  Compare -> (Set and LinkSub) instructions */
      print_if_version_5(&command);
      mp_msg(MSGT_CPLAYER,MSGL_INFO, "{ ");
      print_set_version_3(&command);
      mp_msg(MSGT_CPLAYER,MSGL_INFO, ", ");
      print_linksub_instruction(&command);
      mp_msg(MSGT_CPLAYER,MSGL_INFO, " }");
      break;
    case 6: /*  Compare -> Set, always LinkSub instructions */
      print_if_version_5(&command);
      mp_msg(MSGT_CPLAYER,MSGL_INFO, "{ ");
      print_set_version_3(&command);
      mp_msg(MSGT_CPLAYER,MSGL_INFO, " } ");
      print_linksub_instruction(&command);
      break;
    default:
      mp_msg(MSGT_CPLAYER,MSGL_INFO, "WARNING: Unknown instruction type (%i)", vm_getbits(&command, 63, 3));
  }
  /*  Check if there still are bits set that were not examined */

  if(command.instruction & ~ command.examined) {
    mp_msg(MSGT_CPLAYER,MSGL_INFO, " libdvdnav: vmcmd.c: [WARNING, unknown bits:");
    mp_msg(MSGT_CPLAYER,MSGL_INFO, " %08llx", (command.instruction & ~ command.examined) );
    mp_msg(MSGT_CPLAYER,MSGL_INFO, "]");
  }
}

void vm_print_cmd(int row, vm_cmd_t *vm_command) {
  int i;

  mp_msg(MSGT_CPLAYER,MSGL_INFO, "(%03d) ", row + 1);
  for(i = 0; i < 8; i++)
    mp_msg(MSGT_CPLAYER,MSGL_INFO, "%02x ", vm_command->bytes[i]);
  mp_msg(MSGT_CPLAYER,MSGL_INFO, "| ");

  vm_print_mnemonic(vm_command);
  mp_msg(MSGT_CPLAYER,MSGL_INFO, "\n");
}

