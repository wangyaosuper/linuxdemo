all: prepare all_demo all_demoloader
	@echo build demo and demoload finished sucessfully :\)


prepare:
	-mkdir ../bin
all_demo:
	-mkdir ../bin/demo
	cd demo && make all

all_demoloader:
	-mkdir ../bin/demoloader
	cd demoloader && make all

clean:	clean_demo clean_demoloader


clean_demo:
	-cd demo && make clean

clean_demoloader:
	-cd demoloader && make clean

