/*
 * nvidia-settings: A tool for configuring the NVIDIA X driver on Unix
 * and Linux systems.
 *
 * Copyright (C) 2004 NVIDIA Corporation.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses>.
 */

#ifndef __COMMAND_LINE_H__
#define __COMMAND_LINE_H__

#include "common-utils.h"

/*
 * Forward declaration to break circular dependancy with query-assign.h
 */
struct _CtrlSystemList;

#define DEFAULT_RC_FILE "~/.nvidia-settings-rc"
#define CONFIG_FILE_OPTION 1
#define DISPLAY_OPTION 2

/*
 * Options structure -- stores the parameters specified on the
 * commandline.
 */

typedef struct {
    
    char *ctrl_display;  /*
                          * The name of the display to control
                          * (doesn't have to be the same as the
                          * display on which the gui is shown
                          */

    char **assignments;  /*
                          * Dynamically allocated array of assignment
                          * strings specified on the commandline.
                          */
    
    int num_assignments; /*
                          * Number of assignment strings in the
                          * assignment array.
                          */
    
    char **queries;      /*
                          * Dynamically allocated array of query
                          * strings specified on the commandline.
                          */
    
    int num_queries;     /*
                          * Number of query strings in the query
                          * array.
                          */
    
    int list_targets;    /*
                          * If true, list resolved targets of operations
                          * (from query/assign or rc file) and exit.
                          */

    int terse;           /*
                          * If true, output minimal information to query
                          * operations.
                          */

    int dpy_string;      /*
                          * If true, output the display device mask as a list
                          * of display device names instead of a number.
                          */
} Options;


Options *parse_command_line(int argc, char *argv[],
                            struct _CtrlSystemList *systems);

#endif /* __COMMAND_LINE_H__ */
