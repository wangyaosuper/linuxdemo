all: all_driver all_driverTest

all_driver:
	-mkdir ../../../bin/demo/driverdemo/driver
	cd driver && make all

all_driverTest:
	-mkdir ../../../bin/demo/driverdemo/driverTest
	cd driverTest && make all

clean: clean_driver clean_driverTest

clean_driver:
	-cd driver && make clean

clean_driverTest:
	-cd driverTest && make clean
