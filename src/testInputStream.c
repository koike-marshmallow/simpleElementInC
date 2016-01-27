#include <stdio.h>
#include "stream/inputStream.h"

#define BUFFER_LEN 32

#define ASSERT_NULL(a, s) if(a == NULL) fprintf(stderr, "NULL: %s\n", s)
#define ASSERT_EOF(a, s) if(a == EOF) fprintf(stderr, "EOF: %s\n", s)

void testStream(INSTREAM* stream){
	int tmp;
	char buffer[BUFFER_LEN] = "";
	ASSERT_NULL(stream, "stream null");

	tmp = instream_readc(stream);
	ASSERT_EOF(tmp, "readc");
	fputc(tmp, stdout);

	tmp = instream_read(stream, buffer, BUFFER_LEN - 1);
	ASSERT_EOF(tmp, "reads");
	buffer[tmp] = '\0';
	printf("[%d] %s\n", tmp, buffer);

	destroyInputStream(stream);
}

int main(void){
	int c; char buf[BUFFER_LEN];

	testStream(createFileInputStream(stdin));
	printf("next\n");
	testStream(createFileInputStream(fopen("output.txt", "r")));

	while( (c = instream_reads(createFileInputStream(stdin), buf, BUFFER_LEN)) != EOF ){
		printf("[%d]%s\n", c, buf);
		fflush(stdout);
	}
	return 0;
}