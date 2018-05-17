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

#include "NvCtrlAttributes.h"

#include "command-line.h"
#include "query-assign.h"
#include "msg.h"
#include "version.h"

#include <sys/stat.h>
#include <getopt.h>
#include <string.h>
#include <stdlib.h>



/*
 * main() - nvidia-settings application start
 */

int main(int argc, char **argv)
{
    CtrlSystemList systems;
    Options *op;
    int ret;

    systems.n = 0;
    systems.array = NULL;

    nv_set_verbosity(NV_VERBOSITY_DEPRECATED);

    /* parse the commandline */

    op = parse_command_line(argc, argv, &systems);

    /* quit here if we don't have a ctrl_display - TY 2005-05-27 */

    if (op->ctrl_display == NULL) {
        nv_error_msg("The control display is undefined; please run "
                     "`%s --help` for usage information.\n", argv[0]);
        return 1;
    }

    /* Allocate handle for ctrl_display */

    NvCtrlConnectToSystem(op->ctrl_display, &systems);

    /* process any query or assignment commandline options */

    if (op->num_assignments || op->num_queries) {
        ret = nv_process_assignments_and_queries(op, &systems);
        NvCtrlFreeAllSystems(&systems);
        return ret ? 0 : 1;
    }
    else {
      nv_error_msg("Nothing to do.\n");
      NvCtrlFreeAllSystems(&systems);
      return 1;
    }
} /* main() */
