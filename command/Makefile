flags=-O2 -Wall -std=c2x -I../osapi  #include directory osapi for using os.h 
ldflags=

.PHONY: all clean #tells that these are commands

all: clean  command.com #when we run "make" then first clean then run command.com

#osapi: ../osapi/osapi.o
#	$(MAKE) -C ../osapi

command.com: command.o ../osapi/osapi.o
	cc $(flags) $^ -o $@ $(ldflags)    
# ACTUAL COMMAND THAT RUNS
# cc -O2 -Wall -std=c2x -I../osapi command.o ../osapi/osapi.o -o command.com


command.o: command.c command.h
	cc $(flags) -c $<



clean:
	rm -f *.o ../osapi/osapi.o command.com