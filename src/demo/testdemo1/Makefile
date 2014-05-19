all : libtestdemo1.so

libtestdemo1.so : testdemo1.o
	gcc -shared -Wl,-h,libtestdemo1.so.1.1.1  testdemo1.o  -o  libtestdemo1.so
	cp libtestdemo1.so ../../../bin/demo/testdemo1/

testdemo1.o : testdemo1.c
	gcc -fPIC -c testdemo1.c -o  testdemo1.o

clean:
	-rm *.o
	-rm libtestdemo1.so