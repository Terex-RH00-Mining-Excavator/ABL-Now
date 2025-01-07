#ifndef _PROTOTYPES_
#define _PROTOTYPES_
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define FILE_ERROR "File Naming Error."
#define INDEX_ERROR "Index Out of Bounds Error."
#define MEMORY_ERROR "Memory Error."
#define SYNTAX_ERROR "Syntax Error."
#define BYTE_ERROR "Byte Error."
#define ERROR(str){																	\
		fprintf(stderr,"%s\n", str);     								\
		fprintf(stderr, "ERROR: ARRAY DUMPED.\n");			\
		exit(0);																				\
		}	
#define CHECKMEMORY(pointer){		\
			if(pointer == NULL)				\
				ERROR(MEMORY_ERROR);		\
		}

enum tokenSymbols {	
	SHIFT_RIGHT = '>',
	SHIFT_LEFT = '<',
	ADDITION = '+',
	SUBTRACTION	= '-',
	MODULUS = '%',
	MULTIPLATION = '*',
	DIVISION = '/',
	CURRENT = '#',
	INPUT = '$',
	CHAR_PRINTU = 'C',
	CHAR_PRINTL = 'c',
	INT_PRINTU = 'D',
	INT_PRINTL = 'd',
	STR_PRINTU = 'S',
	STR_PRINTL = 's',
	COMMENT = ';',
	SIZE_LEFT = '[',
	SIZE_RIGHT = ']',
	MULTI_LEFT = '(',
	MULTI_RIGHT = ')',
	LOOP_LEFT = '{',
	LOOP_RIGHT = '}',
};

typedef struct{
	char beg, end;
	size_t sz, opening, closing;
	char* contents;
}Token;

Token Collect(const char*, char, char, size_t);

void Basic_Syntax(char, char*, long*, long);

void Complex_Syntax(char, char*, char**, long*, size_t*, long*);

#endif