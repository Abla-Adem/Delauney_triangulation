CC = gcc
CC1=mpicc
CFLAGS = -Wall -lm -fopenmp -g -O2
EXEC = exec
INCLUDE = ./headers/
all : ./exec
clean : cleanmaster
./exec: main.c
		$(CC) $< -o $@ $(CFLAGS)




clean:
	rm -f *.o
	rm  exec

#################
##### CLEAN #####
#################
cleanmaster :
	make cleanlib

cleanlib :
	rm -f ./lib/*.a
	rm -f ./lib/*.so
	rm -f ./lib/*.o
	rm -f 2*.txt