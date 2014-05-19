all: libDriverTest.so.1

libDriverTest.so.1: driverTest.o
	gcc -shared -Wl,-h,libDriverTest.so.1.1.1  driverTest.o  -o  libDriverTest.so.1
	cp libDriverTest.so.1 ../../../../bin/demo/driverdemo/driverTest/libDriverTest.so.1



driverTest.o : driverTest.c
	gcc -fPIC -c driverTest.c -o  driverTest.o

clean:
	-rm *.o 2>/dev/null
	-rm libDriverTest.so.1 2>/dev/null
