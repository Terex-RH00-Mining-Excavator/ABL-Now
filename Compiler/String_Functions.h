/*
 * 	Author: BRYAN
 * 	Date Of Refinement: 12 - 29 - 21
 * 	Comment: Added Start Parameter to find_first_of() ;; Update at -> (9:52pm) <-
 */

#ifndef _STRING_FUNCTIONS_
#define _STRING_FUNCTIONS_
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

size_t size(const char* str){
		size_t num = 0;
		for(; str[num] != '\0'; num++);
		return num;
}

int compare(const char* str1, const char* str2){
	if(size(str1)!=size(str2)) return 0;  
		for(int i = 0; str1[i] != '\0' && str2[i] != '\0'; i++) if(str1[i] != str2[i]) return 0;
		return 1;
}

int ffo(const char* str, size_t start, const char* letters){
	for(int i = start; str[i]!='\0';i++)
			for(int y = 0; letters[y]!='\0';y++)
					if(str[i]==letters[y])
							return i;
	return -1;//npos
}

#endif
