#include "PROTOTYPES.h"
#include "String_Functions.h"

/**
	* @brief Break up complex expressions and store them in a token struct in the form of the beginning, ending, size, and contents
	* @ param string Typicall the code but can sometimes refer to the bodies of nested loops
	* @ param op1 The expected entry
	* @ param op2 The expected exit
	* @ start index The current index
	* @ return The token struct
*/
Token Collect(const char* string, char op1, char op2, size_t start){
	size_t curIndex, j, repeatTimes=0, loopDebounce=0;
	if((op1 == LOOP_LEFT && op2 == LOOP_RIGHT)) 
		loopDebounce = 1;
	Token collect = {.sz = 1, .contents = (char*)malloc(collect.sz)};
	CHECKMEMORY(collect.contents);
	for(curIndex = start, j = 0, repeatTimes = 0;  string[curIndex] != '\0'; curIndex++){
		if(collect.beg){
			if(loopDebounce){
				repeatTimes+= string[curIndex] == op1;
			}
			if(collect.sz <= j){
				char* temp = collect.contents;
				collect.contents = (char*)realloc(collect.contents, ++collect.sz);
				if(collect.contents==NULL){
					free(temp);
					ERROR(MEMORY_ERROR);
				}
			}
			if(string[curIndex] == op2 && !(repeatTimes--)){
				collect.end  = op2, collect.closing = curIndex;
				break;
			}
			collect.contents[j++] = string[curIndex];
			continue;
		}
		if(string[curIndex] == op1)
			collect.beg = op1, collect.opening = curIndex;
	}
	collect.contents[j] = '\0';
	return collect;
}


/**
	* @brief Simply Execute commands based on a specific character
	* @ param character The character to be evaluated
	* @ param Storage The array holding the data
	* @ param index The current index of the array
	* @ param mcapacity The length of the array through the storage pointer
*/
void Basic_Syntax(char character, char* storage, long* index, long mcapacity){
	switch(character){
		case SHIFT_RIGHT:
			if(*index+1 >= mcapacity) ERROR(INDEX_ERROR);
			++*index;
			break;
		case SHIFT_LEFT:
			if(*index-1 < 0) ERROR(INDEX_ERROR);
			--*index;
			break;
		case ADDITION:
			if(storage[*index]+1 > 127) ERROR(BYTE_ERROR);
			storage[*index]++;
			break;
		case SUBTRACTION:
			if(storage[*index]-1 < -128) ERROR(BYTE_ERROR);
			storage[*index]--;
			break;
		case INPUT:
			storage[*index] = getchar();
			break;
		case CHAR_PRINTL:
		case CHAR_PRINTU:
			printf("%c", storage[*index]);
			break;
		case INT_PRINTL:
		case INT_PRINTU:
			printf("%d", storage[*index]);
			break;
		case STR_PRINTL:
		case STR_PRINTU:
			printf("%s", storage);
			break;

	}
}

/**
	* @brief Handle more complicated commands like looping, the multi-operator, and memory assigment
	* @ param character The character to be evaluated
	* @ param code The code itself
	* @ param storage The array holding the data
	* @ param storageIndex The current index of the storage array
	* @ param fileIndex The current index of the array
	* @ param mcapacity The length of the array through the storage pointer
*/
void Complex_Syntax(char character, char* code, char** storage, long* storageIndex, size_t* fileIndex, long* mcapacity){
	Token token = {}; long v = 0;
		switch(character){
			case SIZE_LEFT:
				token = Collect(code, SIZE_LEFT, SIZE_RIGHT, *fileIndex);
				if(token.beg && token.end){
					if(*storage != NULL) 
						free(*storage);
					*storage = (char*)calloc(sizeof(char), *mcapacity=atoi(token.contents));
					CHECKMEMORY(*storage);
					memset(*storage, 0, *mcapacity); // Justin Case :p
					*storageIndex = 0;
				} else ERROR(SYNTAX_ERROR);
				free(token.contents);
				break;
			case COMMENT:
				if(code[*fileIndex] == COMMENT)
					*fileIndex = ((v = ffo(code, *fileIndex, "\n"))!=-1) ? v:*fileIndex;
				return;
			case CURRENT:
				token = Collect(code, CURRENT, CURRENT, *fileIndex);
				if(token.beg&&token.end){
					int tph = atoi(token.contents);
					if(tph > *mcapacity-1) ERROR(INDEX_ERROR);
					*storageIndex = atoi(token.contents);
				}
				free(token.contents);
				break;
			case MULTI_LEFT:
				token = Collect(code, MULTI_LEFT, MULTI_RIGHT, *fileIndex);
				if(token.beg&&token.end){
					char C; int D;
					sscanf(token.contents, "%c%d", &C, &D);
					D = (D||C==CURRENT) ? D: *(*storage+*storageIndex);
					switch(C){
						case MODULUS:
							if(*(*storage+*storageIndex)%D > 127||
							*(*storage+*storageIndex)%D < -128) ERROR(BYTE_ERROR);
							*(*storage+*storageIndex) %= D;
							break;
						case MULTIPLATION:
							if(*(*storage+*storageIndex)*D > 127||
							*(*storage+*storageIndex)*D < -128) ERROR(BYTE_ERROR);
							*(*storage+*storageIndex) *= D;
							break;
						case DIVISION:
							if(*(*storage+*storageIndex)/D > 127||
							*(*storage+*storageIndex)/D < -128) ERROR(BYTE_ERROR);
							*(*storage+*storageIndex) /= D;
							break;
						case ADDITION:
							if(*(*storage+*storageIndex)+D > 127) ERROR(BYTE_ERROR);
							*(*storage+*storageIndex) += D;
							break;
						case SUBTRACTION:
							if(*(*storage+*storageIndex)-D < -128) ERROR(BYTE_ERROR);
							*(*storage+*storageIndex) -= D;
							break;
						case CURRENT:
							if(D > *mcapacity-1||D<=-1) ERROR(INDEX_ERROR);
							*(*storage+*storageIndex) = *(*storage+D);
							break;
						case SHIFT_RIGHT:
							if(*storageIndex+D > *mcapacity-1) ERROR(INDEX_ERROR);
							*storageIndex += D;
							break;
						case SHIFT_LEFT:
							if(*storageIndex-D <= -1) ERROR(INDEX_ERROR);
							*storageIndex -= D;
							break;
						default:
							ERROR(SYNTAX_ERROR);
							break;
					}
				} else ERROR(SYNTAX_ERROR);
				free(token.contents);
				break;	
			case LOOP_LEFT:
				token = Collect(code, LOOP_LEFT, LOOP_RIGHT, *fileIndex);
				if(token.beg&&token.end){
					while(*(*storage+*storageIndex)){
						for(size_t X = 0; token.contents[X]; X++){
							//printf("\n<< %ldTHIS IS THE DATA: %s>>\n", token.sz, token.contents);
							if(token.contents[X] == COMMENT)
								X = ffo(token.contents, X, "\n") + 1;
							Basic_Syntax(token.contents[X], *storage, storageIndex, *mcapacity);
							Complex_Syntax(token.contents[X], token.contents, storage, storageIndex, &X, mcapacity);
						}
					}
				} else ERROR(SYNTAX_ERROR);
				free(token.contents);
				break;
			case LOOP_RIGHT:
			case SIZE_RIGHT:
			case MULTI_RIGHT:
				ERROR(SYNTAX_ERROR);
				break;
		}
		if(token.closing) 
			*fileIndex = token.closing;
}
