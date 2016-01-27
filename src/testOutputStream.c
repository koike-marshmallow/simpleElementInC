#include <stdio.h>
#include "stream/outputStream.h"


int main(void){
	OUTSTREAM* stream;

	stream = createFileOutputStream(fopen("output.txt", "w"));

	outstream_writec(stream, '8');
	outstream_writec(stream, '\n');
	outstream_writes(stream, "5246543513513\n");

	destroyOutputStream(stream);

	return 0;
}