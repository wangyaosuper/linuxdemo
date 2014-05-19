all: all_driverdemo all_testdemo1 all_memKernelShareToUsr


all_driverdemo:
	-mkdir ../../bin/demo/driverdemo
	cd driverdemo && make all

all_testdemo1:
	-mkdir ../../bin/demo/testdemo1
	cd testdemo1 && make all

all_memKernelShareToUsr:
	-mkdir ../../bin/demo/memKernelShareToUsr
	cd memKernelShareToUsr && make all

clean: clean_driverdemo clean_testdemo1 clean_memKernelShareToUsr

clean_driverdemo:
	-cd driverdemo && make clean

clean_testdemo1:
	-cd testdemo1 && make clean

clean_memKernelShareToUsr:
	-cd memKernelShareToUsr && make clean



