CC = gcc
FLAGS = -Wall -g -o

upgrade: Interpreter/main.c Interpreter/PROTOTYPES.h Interpreter/SOURCE.c Interpreter/String_Functions.h
	$(CC) $(FLAGS) abl Interpreter/main.c Interpreter/SOURCE.c

clean: abl
	rm main
