flags=-O2 -Wall -std=c2x -I../osapi  #include directory osapi for using os.h 
ldflags=

.PHONY: all clean 

all: clean  command.com

#osapi: ../osapi/osapi.o
#	$(MAKE) -C ../osapi

command.com: command.o ../osapi/osapi.o
	cc $(flags) $^ -o $@ $(ldflags)

command.o: command.c command.h
	cc $(flags) -c $<



clean:
	rm -f *.o ../osapi/osapi.o command.com