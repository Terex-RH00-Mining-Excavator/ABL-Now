#include "PROTOTYPES.h"
#define MAX 100

int main(int argc, char** argv){
	long MCapacity = 0, StorageIndex = 0;
	char *Storage = NULL;
	
	FILE* File = fopen(argv[1], "r");
	if(!File){
		ERROR(FILE_ERROR);
		return 0;
	}
	
	if(argv[2]) printf("\nOutput: \n");

	// COLLECT DATA
	size_t index = 0, size = 2;
	char* code = (char*)malloc(size*sizeof(char));
	CHECKMEMORY(code);
	for(char c; (c = fgetc(File)) != EOF; index++){
		code = (char*)realloc(code, ++size);
		CHECKMEMORY(code);
		code[index] = c;
	}
	code[index] = '\n', code[++index] = '\0';

	// INTERPRET DATA
	for(index = 0; code[index] != '\0'; index++){
		Basic_Syntax(code[index], Storage, &StorageIndex, MCapacity);
		Complex_Syntax(code[index], code, &Storage, &StorageIndex, &index,&MCapacity);
	}
	free(code);
	code = NULL;

	// DATA
	if(argv[2]){
	printf("\n\nMEMORY: %li\nCUR_INDEX: %ld\n\nDATA INTERPRETATION:\n", MCapacity, StorageIndex);
	for(size_t Data = 0; Data < MCapacity; Data++)
		printf("ARRAY[%li]: DECIMAL: %d  |  CHARACTER: %c\n",
			Data,
			Storage[Data],
			Storage[Data]
		);
	}
	free(Storage);
	Storage = NULL;
	fclose(File);
	return 0;
}
