#include <stdlib.h>
#include <string.h>
#include "stringBuffer.h"
#include "../error/error.h"

#define ASSERT_NULL(p, fnc) ifassert((p == NULL), fnc, "値がnullです");

STRBUF* createStringBuffer(int length){
	STRBUF* new_buffer;
	
	new_buffer = malloc(sizeof(STRBUF));
	if( new_buffer == NULL ){
		error("createStringBuffer", "メモリの確保に失敗しました");
	}
	new_buffer->buffer = malloc(sizeof(char) * length);
	if( new_buffer->buffer == NULL ){
		error("createStringBuffer", "バッファの確保に失敗しました");
	}
	
	new_buffer->buffer_len = length;
	
	initStringBuffer(new_buffer);
	
	return new_buffer;
}


void initStringBuffer(STRBUF* sbuf){
	ASSERT_NULL(sbuf, "initStringBuffer");
	
	memset(sbuf->buffer, 0, sbuf->buffer_len);
}


void destroyStringBuffer(STRBUF* sbuf){
	ASSERT_NULL(sbuf, "destroyStringBuffer");
	
	free(sbuf->buffer);
	free(sbuf);
}


void sbCopyString(STRBUF* sbuf, char* str){
	ASSERT_NULL(sbuf, "sbCopyString");
	
	strncpy(sbuf->buffer, str, sbuf->buffer_len - 1);
}


void sbCatString(STRBUF* sbuf, char* str){
	int cat_len;
	ASSERT_NULL(sbuf, "sbCatString");
	
	cat_len = sbuf->buffer_len - strlen(sbuf->buffer) - 1;
	strncat(sbuf->buffer, str, cat_len);
}


char* sbGetString(STRBUF* sbuf, char* cp, int len){
	ASSERT_NULL(sbuf, "sbGetString");
	
	if( cp != NULL ){
		memset(cp, 0, len);
		strncpy(sbuf->buffer, cp, len - 1);
	}
	
	return sbuf->buffer;
}


int sbStringLength(STRBUF *sbuf){
	ASSERT_NULL(sbuf, "sbStringLength");
	
	return strlen(sbuf->buffer);
}


int sbLimitStringLength(STRBUF *sbuf){
	ASSERT_NULL(sbuf, "sbLimitStringLength");
	
	return sbuf->buffer_len - 1;
}

int sbIsBufferFull(STRBUF* sbuf){
	ASSERT_NULL(sbuf, "sbBufferFull")+
	
	return strlen(sbuf->buffer) >= (sbuf->buffer_len - 1);
}
