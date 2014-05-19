all : demoloader

demoloader : demoloaderlist.o demoloaderxml.o demoloadermain.o demoloadershell.o
	gcc  demoloadershell.o  demoloaderlist.o  demoloaderxml.o  demoloadermain.o -lexpat -ldl -o  demoloader 
	cp demoloader ../../bin/demoloader
	cp democase.xml ../../bin/demoloader
	-mkdir ../../bin/demoloader/script
	cp ./script/* ../../bin/demoloader/script

demoloadershell.o : demoloadershell.c
	gcc -g -c demoloadershell.c -o  demoloadershell.o


demoloaderlist.o : demoloaderlist.c
	gcc -g -c demoloaderlist.c -o  demoloaderlist.o


demoloaderxml.o : demoloaderxml.c
	gcc -g -c demoloaderxml.c -o  demoloaderxml.o



demoloadermain.o : demoloadermain.c
	gcc -g -c demoloadermain.c -o  demoloadermain.o


clean:
	-rm  *.o  ./demoloader 2>/dev/null