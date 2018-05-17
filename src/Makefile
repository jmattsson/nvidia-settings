#
# nvidia-settings: A tool for configuring the NVIDIA X driver on Unix
# and Linux systems.
#
# Copyright (C) 2008-2012 NVIDIA Corporation.
#
# This program is free software; you can redistribute it and/or modify it
# under the terms and conditions of the GNU General Public License,
# version 2, as published by the Free Software Foundation.
#
# This program is distributed in the hope that it will be useful, but WITHOUT
# ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
# FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
# more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses>.
#


##############################################################################
# include common variables and functions
##############################################################################

UTILS_MK_DIR ?= ..

include $(UTILS_MK_DIR)/utils.mk


##############################################################################
# The calling Makefile may export any of the following variables; we
# assign default values if they are not exported by the caller
##############################################################################

ifndef X_LDFLAGS
  ifeq ($(TARGET_OS)-$(TARGET_ARCH),Linux-x86_64)
    X_LDFLAGS          = -L/usr/X11R6/lib64
  else
    X_LDFLAGS          = -L/usr/X11R6/lib
  endif
endif

X_CFLAGS              ?=

PKG_CONFIG            ?= pkg-config

ifndef VDPAU_CFLAGS
  VDPAU_CFLAGS        := $(shell $(PKG_CONFIG) --cflags vdpau 2> /dev/null)
  ifeq ($(VDPAU_CFLAGS),)
    VDPAU_CFLAGS       = -I /usr/include
  endif
endif

ifndef DBUS_CFLAGS
  DBUS_CFLAGS        := $(shell $(PKG_CONFIG) --cflags dbus-1 2> /dev/null)
  ifeq ($(DBUS_CFLAGS),)
    DBUS_CFLAGS       = -I /usr/include/dbus-1.0/
  endif
endif

##############################################################################
# The XF86Config-parser, libXNVCtrl, and common-utils directories may
# be in one of two places: either elsewhere in the driver source tree
# when building nvidia-settings as part of the NVIDIA driver build (in
# which case, XNVCTRL_DIR, XNVCTRL_ARCHIVE, XCONFIG_PARSER_DIR,
# COMMON_UTILS_DIR and COMMON_UNIX_DIR should be defined by the calling
# makefile), or directly in the source directory when building from the
# nvidia-settings source tarball (in which case, the below conditional
# assignments should be used)
##############################################################################

XNVCTRL_DIR             ?= libXNVCtrl
XNVCTRL_MAKEFILE        ?= Makefile
XNVCTRL_ARCHIVE         ?= $(XNVCTRL_DIR)/libXNVCtrl.a
COMMON_UTILS_DIR        ?= common-utils

##############################################################################
# assign variables
##############################################################################

NVIDIA_SETTINGS = $(OUTPUTDIR)/nvidia-settings

NVIDIA_SETTINGS_PROGRAM_NAME = "nvidia-settings"

NVIDIA_SETTINGS_VERSION := $(NVIDIA_VERSION)

CFLAGS += $(X_CFLAGS)

LDFLAGS += $(X_LDFLAGS)

NVML_EXPERIMENTAL ?=
CFLAGS += $(if $(NVML_EXPERIMENTAL),-DNVML_EXPERIMENTAL)


# Some older Linux distributions do not have the dynamic library
# libXxf86vm.so, though some newer Linux distributions do not have the
# static library libXxf86vm.a.  Statically link against libXxf86vm
# when building nvidia-settings within the NVIDIA driver build, but
# dynamically link against libXxf86vm in the public builds.
NV_LINK_LIBXXF86VM_STATICALLY ?= 0

ifneq ($(NV_LINK_LIBXXF86VM_STATICALLY),0)
    LIBS += -Wl,-Bstatic -lXxf86vm -Wl,-Bdynamic
else
    LIBS += -lXxf86vm
endif

# Preferably, we would use pkg-config's "--libs-only-l" and
# "--libs-only-L" options to get separate GTK_LDFLAGS and GTK_LIBS,
# appending them to LDFLAGS and LIBS, respectively.  However, the
# pkg-config(1) man page cautions:
#
#     [...] Note that the union of "--libs-only-l"  and
#     "--libs-only-L"  may be smaller than "--libs", due to flags such
#     as -rdynamic.
#
# So append all of GTK_LDFLAGS to LIBS, so that LIBS can go after
# $(OBJECTS) on the link commandline, causing libraries for linking to
# be named after the objects that depend on those libraries (needed
# for "--as-needed" linker behavior).
LIBS += -lX11 -lXext -lm $(LIBDL_LIBS)

# Include all the source lists; dist-files.mk will define NVIDIA_SETTINGS_SRC
include src.mk
SRC        += $(NVIDIA_SETTINGS_SRC)

include $(COMMON_UTILS_DIR)/src.mk
SRC        += $(addprefix $(COMMON_UTILS_DIR)/,$(COMMON_UTILS_SRC))

SRC        += $(STAMP_C)

OBJS        = $(call BUILD_OBJECT_LIST,$(SRC))
XCP_OBJS    = $(call BUILD_OBJECT_LIST,$(XCP_SRC))

CFLAGS     += -I .
CFLAGS     += -I $(XNVCTRL_DIR)
CFLAGS     += -I libXNVCtrlAttributes

CFLAGS     += -I $(COMMON_UTILS_DIR)
CFLAGS     += -I $(OUTPUTDIR)
CFLAGS     += $(VDPAU_CFLAGS)
CFLAGS     += $(DBUS_CFLAGS)
CFLAGS     += -DPROGRAM_NAME=\"nvidia-settings\"

$(call BUILD_OBJECT_LIST,$(XCP_SRC)): CFLAGS += -fPIC

define BINARY_DATA_HEADER_RULE
  $$(OUTPUTDIR)/$(notdir $(1)).h:
	$(at_if_quiet){ \
	  $$(PRINTF) "extern const char _binary_$(subst .,_,$(notdir $(1)))_start[];\n"; \
	  $$(PRINTF) "extern const char _binary_$(subst .,_,$(notdir $(1)))_end[];\n"; \
	} > $$@
endef

##############################################################################
# build rules
##############################################################################

.PHONY: all install NVIDIA_SETTINGS_install clean clobber build-xnvctrl

all: $(NVIDIA_SETTINGS)

install: NVIDIA_SETTINGS_install

NVIDIA_SETTINGS_install: $(NVIDIA_SETTINGS)
	$(MKDIR) $(BINDIR)
	$(INSTALL) $(INSTALL_BIN_ARGS) $< $(BINDIR)/$(notdir $<)

$(eval $(call DEBUG_INFO_RULES, $(NVIDIA_SETTINGS)))
$(NVIDIA_SETTINGS).unstripped: $(OBJS) $(XNVCTRL_ARCHIVE)
	$(call quiet_cmd,LINK) $(CFLAGS) $(LDFLAGS) $(BIN_LDFLAGS) \
	    -rdynamic -o $@ $(OBJS) $(XNVCTRL_ARCHIVE) $(LIBS)

# define the rule to build each object file
$(foreach src,$(SRC),$(eval $(call DEFINE_OBJECT_RULE,TARGET,$(src))))
$(foreach src,$(XCP_SRC),$(eval $(call DEFINE_OBJECT_RULE,TARGET,$(src))))

# define the rule to generate $(STAMP_C)
$(eval $(call DEFINE_STAMP_C_RULE, $(OBJS),$(NVIDIA_SETTINGS_PROGRAM_NAME)))

# define the rule to build $(XNVCTRL_ARCHIVE)
$(XNVCTRL_ARCHIVE): build-xnvctrl

build-xnvctrl:
	@$(MAKE) -C $(XNVCTRL_DIR) -f $(XNVCTRL_MAKEFILE)

clean clobber:
	rm -rf $(NVIDIA_SETTINGS) *~ $(STAMP_C) \
		$(OUTPUTDIR)/*.o $(OUTPUTDIR)/*.d
	@$(MAKE) -C $(XNVCTRL_DIR) -f $(XNVCTRL_MAKEFILE) clean
