#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "outputStream.h"

OUTSTREAM* createEmptyOutputStream(void){
	OUTSTREAM* new_stream;
	new_stream = malloc(sizeof(OUTSTREAM));
	if( new_stream == NULL ) return NULL;

	memset(new_stream, 0, sizeof(OUTSTREAM));
	new_stream->dest = NULL;
	return new_stream;
}


int outstream_writec(OUTSTREAM* stream, char c){
	if( stream != NULL && stream->dest != NULL ){
		return (*(stream->f_write_c))(stream->dest, c);
	}else{
		return OUTPUT_FAILED;
	}
}


int outstream_writes(OUTSTREAM* stream, char* sh, int len){
	if( stream != NULL && stream->dest != NULL ){
		return (*(stream->f_write_s))(stream->dest, sh, len);
	}else{
		return OUTPUT_FAILED;
	}
}


void outstream_close(OUTSTREAM* stream){
	if(  stream != NULL && stream->dest != NULL ){
		(*(stream->f_close))(stream->dest);
		stream->dest = NULL;
	}
}


void destroyOutputStream(OUTSTREAM* stream){
	if( stream != NULL ){
		if( stream->dest != NULL) outstream_close(stream);

		memset(stream, 0, sizeof(OUTSTREAM));
		free(stream);
	}
}



/* FILE OUTPUT STREAM FACTORY */
OUTSTREAM* createFileOutputStream(FILE* fp){
	OUTSTREAM* new_stream;

	new_stream = createEmptyOutputStream();
	if( new_stream == NULL || fp == NULL ) return NULL;

	new_stream->dest = fp;
	new_stream->f_write_c = os_fileos_writec;
	new_stream->f_write_s = os_fileos_writes;
	new_stream->f_close = os_fileos_close;

	return new_stream;
}


int os_fileos_writec(void* fp, char c){
	if( fp != NULL ){
		return fputc(c, (FILE*)fp);
	}else{
		return OUTPUT_FAILED;
	}
}


int os_fileos_writes(void* fp, char* s, int len){
	if( fp != NULL ){
		return fwrite(s, sizeof(char), len, (FILE*)fp);
	}else{
		return OUTPUT_FAILED;
	}
}


void os_fileos_close(void* fp){
	if( fp != NULL ){
		if(fp == stdout || fp == stderr ) return;

		fclose((FILE*)fp);
	}
}