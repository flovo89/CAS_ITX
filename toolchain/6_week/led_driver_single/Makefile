# To build modules outside of the kernel tree, we run "make"
# in the kernel source tree; the Makefile these then includes this
# Makefile once again.
# This conditional selects whether we are being included from the
# kernel Makefile or not.
#
# Note: The target rootfs has to be mounted via nfs.
#
# Common installation variables
TOOLCHAIN	:= /opt/crosstools/gcc-linaro-6.4.1-2018.05-i686_aarch64-linux-gnu/bin
PLATFORM	:= aarch64-linux-gnu-
CROSS_CMP	:= $(TOOLCHAIN)/$(PLATFORM)
ROOT_FS_PATH	:= /opt/embedded/firefly/rootfs

# Installation variables for the kernel space.
MODULE=led_driver_single
KERNEL_VER=4.4.77

ifeq ($(KERNELRELEASE),)

    # Assume the source tree is where the running kernel was built
    # You should set KERNEL_SRC_BUILD in the environment if it's elsewhere

    KERNEL_DIR	?= $(ROOT_FS_PATH)/lib/modules/$(KERNEL_VER)
    KERNEL_SRC   = $(KERNEL_DIR)/source
    KERNEL_BUILD = $(KERNEL_DIR)/build
    # The current directory is passed to sub-makes as argument
    PWD := $(shell pwd)

modules:
	@echo 'Invoking build system'
	$(MAKE) -C $(KERNEL_SRC) M=$(PWD) ARCH=arm64 CROSS_COMPILE=$(CROSS_CMP) modules

# The module will be installed in KERNEL_VER/extra
# To install a module use the following command:
# @host sudo -E make modules_install
modules_install:
	@echo 'Installing modules'
	$(MAKE) -C $(KERNEL_SRC) M=$(PWD) ARCH=arm64 INSTALL_MOD_PATH=$(ROOT_FS_PATH) modules_install

clean:
	rm -rf *.o *~ core .depend .*.cmd *.ko *.dtbo *.mod.c *mod.dwo .tmp_versions Module.symvers modules.order

.PHONY: modules modules_install clean

else
# Determine what's needed to compile
# Every '.o' file corresponds to a '.c' file.
#led_driver_single-objs := foo1.o foo2.o 

# Called from kernel build system: just declare what our modules are
# obj-m will generate the button.ko
# obj-y will integrate the code into the kernel.
obj-m := $(MODULE).o
endif

