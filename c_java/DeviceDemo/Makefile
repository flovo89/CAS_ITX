# Embedded-Linux (BTE5446)
# Project: Basic framebuffer Exercise 1.0
# Version: 1.0
# File:    Makefile
# Date:    04.10.2013
# Author   Martin Aebersold (AOM1)
#
# Last Modifications: V1.0, AOM1, 04.10.2013
# Initial release

SHELL = /bin/bash

# Include the ARCH (host or target) enviroments variables
# make HOST=1 
ifdef HOST
 include make_env_host
else
 include make_env_target
endif

# Tool names
TARGET_ARCH	= ${TARGET}-
AS		= $(TARGET_ARCH)as
AR 		= $(TARGET_ARCH)ar
CC 		= $(TARGET_ARCH)gcc
CPP 		= $(TARGET_ARCH)g++
LD 		= $(TARGET_ARCH)ld
NM 		= $(TARGET_ARCH)nm
OBJCOPY 	= $(TARGET_ARCH)objcopy
OBJDUMP 	= $(TARGET_ARCH)objdump
RANLIB 		= $(TARGET_ARCH)ranlib
READELF 	= $(TARGET_ARCH)readelf
SIZE 		= $(TARGET_ARCH)size
STRINGS 	= $(TARGET_ARCH)strings
STRIP 		= $(TARGET_ARCH)strip
export	AS AR CC CPP LD NM OBJCOPY OBJDUMP RANLIB READELF SIZE STRINGS STRIP

# Build settings
CFLAGS		= ${EXTRA_CFLAGS} -g -gdwarf-2 -Wall
HEADER		= -I${LOCAL_INC} -I${SYSTEM_INC}
LIBS		= -lm -lrt
LDFLAGS 	= $(LIBS) -Wl,-Map=${EXEC_NAME}.map -L${LOCAL_LIB} -L${SYSTEM_LIB}

# Name of Executable
EXEC_NAME	= DeviceDemo

# Installation variables like scripts images etc.
SHELL_SCRIPT	= 
IMAGES		=
INSTALL_DIR	= ${TARGET_ROOTFS}

# Files needed for the build
SOURCES		= $(wildcard *.c)
OBJECTS 	= $(patsubst %.c, %.o, $(SOURCES))

# Make rules
all: ${EXEC_NAME}

${EXEC_NAME}: ${OBJECTS}
		$(CC) $^ -o $@ $(LDFLAGS)

%.o: %.c
		$(CC) $(CFLAGS) -c $<

clean:
		rm -f *~
		rm -f *.S
		rm -f *.map
		rm -f *.o
		rm -f $(EXEC_NAME) 

