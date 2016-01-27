#include <stdio.h>
#include <stdlib.h>
#include "stringCell/stringCell.h"

#define BUFLEN 64

int main(void){
	STRCELL *str1;
	char buf[BUFLEN];

	STRCELL_DEFAULT_CBLEN_CREATE = 16;
	STRCELL_DEFAULT_CBLEN_EXPAND = 8;
	str1 = createStringCell();

	strcel_setString(str1, "I am takaaki.");
	printf("%s\n", strcel_copyto(str1, buf, BUFLEN));
	strcel_catString(str1, " Nice to meet you.");
	printf("%s\n", strcel_copyto(str1, buf, BUFLEN));
	strcel_catString(str1, " ");

	printf("STRING LEN = %d\n", strcel_getLength(str1));
	printf("BUFFER LEN = %d\n", strcel_getBufferLength(str1));
	strcel_dumpStringCells(str1, stdout);

	strcel_setString(str1, "SUCCESS");
	strcel_dumpStringCells(str1, stdout);

	strcel_setString(str1, "LOOKING FORWARD TO HEARING FROM YOU");
	strcel_resize(str1, 20);
	strcel_outputFile(str1, stdout);
	printf("\n");
	printf("BUFFER LEN = %d\n", strcel_getBufferLength(str1));
	strcel_dumpStringCells(str1, stdout);

	destroyStringCell(str1);

	return 0;
}