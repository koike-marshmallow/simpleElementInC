#include <stdio.h>
#include <stdlib.h>
#include "stringCell/stringCell.h"

#define BUFLEN 64

int main(void){
	STRCELL *str1;
	char buf[BUFLEN];

	STRCELL_DEFAULT_CBLEN_CREATE = 4;
	STRCELL_DEFAULT_CBLEN_EXPAND = 4;
	str1 = createStringCell();

	strcel_setString(str1, "I am takaaki.");
	printf("%s\n", strcel_copyto(str1, buf, BUFLEN));
	strcel_catString(str1, " Nice to meet you.");
	printf("%s\n", strcel_copyto(str1, buf, BUFLEN));


	strcel_dumpStringCells(str1, stdout);

	destroyStringCell(str1);

	return 0;
}