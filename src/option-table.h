/*
 * nvidia-settings: A tool for configuring the NVIDIA X driver on Unix
 * and Linux systems.
 *
 * Copyright (C) 2010 NVIDIA Corporation.
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

#ifndef __OPTION_TABLE_H__
#define __OPTION_TABLE_H__

#include "nvgetopt.h"
#include "command-line.h"

#define TAB    "  "
#define BIGTAB "      "

/*
 * Options table; see nvgetopt.h for a description of the fields, and
 * gen-manpage-opts.c:print_option() for a description of special
 * characters that are converted during manpage generation.
 */

static const NVGetoptOption __options[] = {
    { "version", 'v', NVGETOPT_HELP_ALWAYS, NULL,
      "Print the ^nvidia-settings^ version and exit." },

    { "help", 'h', NVGETOPT_HELP_ALWAYS, NULL,
      "Print usage information and exit." },

    { "ctrl-display", 'c',
      NVGETOPT_STRING_ARGUMENT | NVGETOPT_HELP_ALWAYS, NULL,
      "Control the specified X display.  If this option is not given, then "
      "^nvidia-settings^ will control the display specified by ^'--display'^; "
      "if that is not given, then the &$DISPLAY& environment "
      "variable is used." },

    { "assign", 'a', NVGETOPT_STRING_ARGUMENT | NVGETOPT_HELP_ALWAYS, NULL,
      "The &ASSIGN& argument to the ^'--assign'^ command line option is of the "
      "form:\n"
      "\n"
      TAB "{DISPLAY}/{attribute name}[{display devices}]={value}\n"
      "\n"
      "This assigns the attribute {attribute name} to the value {value} on the "
      "X Display {DISPLAY}.  {DISPLAY} follows the usual {host}:{display}."
      "{screen} syntax of the DISPLAY environment variable and is optional; "
      "when it is not specified, then it is implied following the same rule as "
      "the ^--ctrl-display^ option.  If the X screen is not specified, then the "
      "assignment is made to all X screens.  Note that the '/' is only required "
      "when {DISPLAY} is present.\n"
      "\n"
      "{DISPLAY} can additionally include a target specification to direct "
      "an assignment to something other than an X screen.  A target "
      "specification is contained within brackets and consists of a target "
      "type name, a colon, and the target id.  The target type name can be "
      "one of ^\"screen\", \"gpu\", \"framelock\", \"vcs\", \"gvi\", \"fan\", "
      "\"thermalsensor\", \"svp\",^ or ^\"dpy\";^ the target id is the index "
      "into the list of targets (for that target type).  The target "
      "specification can be used in {DISPLAY} wherever an X screen can be used, "
      "following the syntax {host}:{display}[{target_type}:{target_id}].  See "
      "the output of\n"
      "\n"
      TAB "nvidia-settings -q all \n"
      "\n"
      "for information on which target types can be used with which "
      "attributes.  See the output of\n"
      "\n"
      TAB " nvidia-settings -q screens -q gpus -q framelocks -q vcs -q gvis "
      "-q fans -q thermalsensors -q svps -q dpys \n"
      "\n"
      "for lists of targets for each target type.\n"
      "\n"
      "The [{display devices}] portion is also optional; if it is not "
      "specified, then the attribute is assigned to all display devices.\n"
      "\n"
      "Some examples:\n"
      "\n"
      TAB "-a FSAA=5\n"
      TAB "-a localhost:0.0/DigitalVibrance[CRT-0]=0\n"
      TAB "--assign=\"SyncToVBlank=1\"\n"
      TAB "-a [gpu:0]/DigitalVibrance[DFP-1]=63\n" },

    { "query", 'q', NVGETOPT_STRING_ARGUMENT | NVGETOPT_HELP_ALWAYS, NULL,
      "The &QUERY& argument to the ^'--query'^ command line option is of the "
      "form:\n"
      "\n"
      TAB "{DISPLAY}/{attribute name}[{display devices}]\n"
      "\n"
      "This queries the current value of the attribute {attribute name} on the "
      "X Display {DISPLAY}.  The syntax is the same as that for the "
      "^'--assign'^ option, without '=^{value}'^; specify ^'-q screens', "
      "'-q gpus', '-q framelocks', '-q vcs', '-q gvis', '-q fans'^, "
      "'-q thermalsensors', '-q svps', or '-q dpys' to query a list of X "
      "screens, GPUs, Frame Lock devices, Visual Computing Systems, SDI Input "
      "Devices, Fans, Thermal Sensors, 3D Vision Pro Transceivers, or Display "
      "Devices, respectively, that are present on the X Display {DISPLAY}.  "
      "Specify ^'-q all'^ to query all attributes." },

    { "terse", 't', NVGETOPT_HELP_ALWAYS, NULL,
      "When querying attribute values with the '--query' command line option, "
      "only print the current value, rather than the more verbose description "
      "of the attribute, its valid values, and its current value." },

    { "display-device-string", 'd', NVGETOPT_HELP_ALWAYS, NULL,
      "When printing attribute values in response to the '--query' option, "
      "if the attribute value is a display device mask, print the value "
      "as a list of display devices (e.g., \"CRT-0, DFP-0\"), rather than "
      "a hexadecimal bit mask (e.g., 0x00010001)." },

    { "describe", 'e', NVGETOPT_STRING_ARGUMENT | NVGETOPT_HELP_ALWAYS, NULL,
      "Prints information about a particular attribute.  Specify 'all' to "
      "list the descriptions of all attributes.  Specify 'list' to list the "
      "attribute names without a descriptions." },

    { NULL, 0, 0, NULL, NULL},
};

#endif //_OPTION_TABLE_H
