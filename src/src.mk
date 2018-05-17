##############################################################################
# define the list of files that should be built and distributed in the
# nvidia-settings source tarball; this is used by the NVIDIA driver
# build when packaging the tarball, and by the nvidia-settings
# makefile when building nvidia-settings.
#
# Defines NVIDIA_SETTINGS_SRC, NVIDIA_SETTINGS_EXTRA_DIST, and
# NVIDIA_SETTINGS_DIST_FILES
##############################################################################


#
# files in the src directory of nvidia-settings
#

SRC_SRC += command-line.c
SRC_SRC += nvidia-settings.c
SRC_SRC += parse.c
SRC_SRC += query-assign.c

NVIDIA_SETTINGS_SRC += $(SRC_SRC)

SRC_EXTRA_DIST += src.mk
SRC_EXTRA_DIST += command-line.h
SRC_EXTRA_DIST += option-table.h
SRC_EXTRA_DIST += parse.h
SRC_EXTRA_DIST += query-assign.h
SRC_EXTRA_DIST += gen-manpage-opts.c

NVIDIA_SETTINGS_EXTRA_DIST += $(SRC_EXTRA_DIST)

#
# files in the src/libXNVCtrlAttributes directory of nvidia-settings
#

LIB_XNVCTRL_ATTRIBUTES_SRC += libXNVCtrlAttributes/NvCtrlAttributes.c
LIB_XNVCTRL_ATTRIBUTES_SRC += libXNVCtrlAttributes/NvCtrlAttributesNvControl.c
LIB_XNVCTRL_ATTRIBUTES_SRC += libXNVCtrlAttributes/NvCtrlAttributesUtils.c
LIB_XNVCTRL_ATTRIBUTES_SRC += libXNVCtrlAttributes/NvCtrlAttributesNvml.c

NVIDIA_SETTINGS_SRC += $(LIB_XNVCTRL_ATTRIBUTES_SRC)

LIB_XNVCTRL_ATTRIBUTES_EXTRA_DIST += libXNVCtrlAttributes/NvCtrlAttributes.h
LIB_XNVCTRL_ATTRIBUTES_EXTRA_DIST += libXNVCtrlAttributes/NvCtrlAttributesPrivate.h

NVIDIA_SETTINGS_EXTRA_DIST += $(LIB_XNVCTRL_ATTRIBUTES_EXTRA_DIST)

NVIDIA_SETTINGS_DIST_FILES += $(NVIDIA_SETTINGS_SRC)
NVIDIA_SETTINGS_DIST_FILES += $(NVIDIA_SETTINGS_EXTRA_DIST)
