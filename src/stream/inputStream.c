#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inputStream.h"

INSTREAM* createEmptyInputStream(void){
	INSTREAM* new_stream;
	new_stream = malloc(sizeof(INSTREAM));
	if( new_stream == NULL ) return NULL;

	memset(new_stream, 0, sizeof(INSTREAM));
	new_stream->dest = NULL;
	return new_stream;
}


int instream_readc(INSTREAM* stream){
	if( stream != NULL && stream->dest != NULL ){
		return (*(stream->f_read_c))(stream->dest);
	}else{
		return EOF;
	}
}


int instream_reads(INSTREAM* stream, char* dst, int len){
	if( stream != NULL && stream->dest != NULL ){
		return (*(stream->f_read_s))(stream->dest, dst, len);
	}else{
		return EOF;
	}
}


int instream_skip(INSTREAM* stream, int byte){
	if( stream != NULL && stream->dest != NULL ){
		return (*(stream->f_skip))(stream->dest, byte);
	}else{
		return EOF;
	}
}


void instream_close(INSTREAM* stream){
	if( stream != NULL && stream->dest != NULL ){
		(*(stream->f_close))(stream->dest);
		stream->dest = NULL;
	}
}


void destroyInputStream(INSTREAM* stream){
	if( stream != NULL ){
		if( stream->dest != NULL ) instream_close(stream);

		memset(stream, 0, sizeof(INSTREAM));
		free(stream);
	}
}



/* FILE INPUT STREAM FACTORY */
INSTREAM* createFileInputStream(FILE* fp){
	INSTREAM* new_stream;
	if( fp == NULL ) return NULL;

	new_stream = createEmptyInputStream();
	if( new_stream == NULL ) return NULL;

	new_stream->dest = fp;
	new_stream->f_read_c = is_fileis_readc;
	new_stream->f_read_s = is_fileis_reads;
	new_stream->f_skip = is_fileis_skip;
	new_stream->f_close = is_fileis_close;

	return new_stream;
}


int is_fileis_readc(void* fp){
	if( fp != NULL ){
		return fgetc((FILE*)fp);
	}else{
		return EOF;
	}
}


int is_fileis_reads(void* fp, char* dst, int len){
	char *cp;
	int tmp, cnt;

	if( fp != NULL ){
		cp = dst;
		for( cnt = 0; cnt < len; cnt++){
			if( (tmp = fgetc((FILE*)fp)) == EOF ) break;
			*cp = (char)tmp;
			cp++;
		}

		if( cnt > 0 ){
			return cnt;
		}else{
			return EOF;
		}
	}else{
		return EOF;
	}
}


int is_fileis_skip(void* fp, int byte){
	int cnt;
	if( fp != NULL ){
		for( cnt = 0; cnt < byte; cnt++){
			if( fgetc((FILE*)fp) == EOF ) break;
		}

		return cnt;
	}else{
		return 0;
	}
}


void is_fileis_close(void* fp){
	if( fp != NULL ){
		if(fp == stdin) return;

		fclose((FILE*)fp);
	}
}