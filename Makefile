PWD := $(shell pwd)
KERNEL_DIR := /lib/modules/$(shell uname -r)/build

MODULE_NAME := hello_world
obj-m := $(MODULE_NAME).o

.PHONY: build run remove install uninstall clean format check

build:
	$(MAKE) -C $(KERNEL_DIR) M=$(PWD) modules

run:
	insmod $(PWD)/$(MODULE_NAME).ko

remove:
	rmmod $(MODULE_NAME)

install:
	cp $(MODULE_NAME).ko /lib/modules/$(shell uname -r)
#	cp $(MODULE_NAME).conf /etc/modprobe.d/
	depmod -a
	modprobe $(MODULE_NAME)

uninstall:
	modprobe -r $(MODULE_NAME)
	rm -f /lib/modules/$(shell uname -r)/$(MODULE_NAME).ko
#	rm -f /etc/modules/$(MODULE_NAME).conf
	depmod -a

clean:
	$(MAKE) -C $(KERNEL_DIR) M=$(PWD) clean

format:
	clang-format -i $(PWD)/*.c

check:
	$(PWD)/check.sh
