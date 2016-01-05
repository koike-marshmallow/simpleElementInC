#include <stdio.h>
#include <stdlib.h>
#include "error.h"

void fnerror(char* fnc, char* msg){
	fprintf(stderr, "%s: %s\n", fnc, msg);
	exit(1);
}

void ifassert(int result, char* fnc, char* msg){
	if( result ){
		fnerror(fnc, msg);
	}
}

void nullCheck(void* p, char* fnc, char* msg){
	ifassert((p == NULL), fnc, msg);
}
