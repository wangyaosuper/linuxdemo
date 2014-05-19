obj-m += wydev.o
wydev-objs := wydev_main.o wychdev.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
	cp *.ko  ../../../../bin/demo/driverdemo/driver

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean 2>/dev/null
	-rm  *.o 2>/dev/null
	-rm  *.ko 2>/dev/null
	-rm  *.symvers 2>/dev/null
	-rm  *.order 2>/dev/null
