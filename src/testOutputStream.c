#include <stdio.h>
#include <string.h>
#include "stream/outputStream.h"


int main(void){
	OUTSTREAM* stream;
	char str[] = "53187431535\n";

	stream = createFileOutputStream(fopen("output.txt", "w"));

	outstream_writec(stream, '8');
	outstream_writec(stream, '\n');
	outstream_writes(stream, str, strlen(str));

	destroyOutputStream(stream);

	return 0;
}