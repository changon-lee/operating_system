obj-m = mydrv.o

CC = gcc 

KERNEL_DIR = /lib/modules/$(shell uname -r)/build
PWD = $(shell pwd)

default:
	$(MAKE) -C $(KERNEL_DIR) SUBDIRS=$(PWD) modules

clean:
	$(MAKE) -C $(KERNEL_DIR) SUBDIRS=$(PWD) clean

test:
	sudo rmmod mydrv
	sudo insmod mydrv.ko
	sudo ./test_app
apitest:
	sudo ./test_app
