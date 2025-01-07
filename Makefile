CC = gcc
FLAGS = -Wall -g -o

compile: Compiler/main.c Compiler/PROTOTYPES.h Compiler/SOURCE.c Compiler/String_Functions.h
	$(CC) $(FLAGS) abl Compiler/main.c Compiler/SOURCE.c

clean: abl
	rm main
