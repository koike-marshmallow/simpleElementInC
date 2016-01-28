#include <stdlib.h>
#include <string.h>
#include "../error/error.h"
#include "../stream/inputStream.h"
#include "../stringCell/stringCell.h"
#include "../nodeCore.h"
#include "../jsonData.h"
#include "../jsonNode.h"
#include "../jsonObject.h"
#include "jsonParser.h"

#define LITERAL_BUFFER 8
#define NUMBER_BUFFER 16
#define CHARTYPE_CNT 9

#define ASSERT_NULL(p, fnc, msg) ifassert((p == NULL), fnc, msg)
#define ASSERT_EOF(c, fnc) \
	ifassert((jp_checkCharType(c) == JPC_NULLEOF), \
	fnc, "ストリームが終端に達しました")
#define STREAM_READC(stream) instream_readc(stream)
#define STREAM_READC_SB(stream) jp_skiptBlankLinefeed(stream)
#define CHARTYPE(c) jp_checkCharType(c)
#define COND_BLK(c) (c == JPC_BLANKLF)
#define COND_EOF(c) (c == JPC_NULLEOF)


char* JPCT_SYMBOLS[CHARTYPE_CNT] = {
	"0123456789.-", /*value*/
	"ntf", /*literal head*/
	"{", "}", /*object start / end */
	"[", "]", /*array start / end */
	",", ":", "\"" /* comma, colon, quote */
};
int JPCT_CODES[CHARTYPE_CNT] = {
	JPC_VALUE, 
	JPC_LITERALHEAD,
	JPC_OBJECTSTART, JPC_OBJECTEND,
	JPC_ARRAYSTART, JPC_ARRAYEND,
	JPC_COMMA, JPC_COLON, JPC_QUOTE
};


int jp_checkChars(char c, char* cs){
	char* cp;
	if( cs != NULL ){
		cp = cs;
		while( *cp != '\0' ){
			if( *cp == c ) return 1;
			cp++;
		}
	}
	return 0;
}


int jp_checkCharType(char c){
	int i;

	if( isBlank(c) ) return JPC_BLANK;
	if( c == '\0' || c == EOF ) return JPC_NULLEOF;

	for( i=0; i<CHARTYPE_CNT; i++){
		if( jp_checkChars(c, JPCT_SYMBOLS[i]) ){
			return JPCT_CODES[i];
		}
	}

	return JPC_OTHER;
}


char jp_skipBlankLinefeed(INSTREAM* stream){
	char tmp;

	do{
		tmp = instream_readc(stream);
	}while( CHARTYPE(tmp) == JPC_BLANKLF );

	return tmp;
}


char* jp_readStringTolken(INSTREAM* stream, char *ptr){
	char* st;
	STRCELL* sbuf;
	char c_buf[2] = "";
	if( CHARTYPE(*ptr) != JPC_QUOTE ){
		fnerror("jp_readStringTolken", "文字列の開始が不正です");
	}

	sbuf = createStringCell();
	ASSERT_NULL(sbuf,
		"jp_readStringTolken", "文字列バッファが生成できませんでした");

	c_buf[1] = '\0';
	*ptr = STREAM_READC(stream);
	while( CHARTYPE(*ptr) != JPC_QUOTE ){
		ASSERT_EOF(*ptr, "jp_readStringTolken");
		c_buf[0] = *ptr;
		strcel_catString(sbuf, c_buf);
		*ptr = STREAM_READC(stream);
	}
	*ptr = STREAM_READC(stream);

	st = strcel_createString();
	ASSERT_NULL(st, 
		"jp_readStringTolken", "整形式文字列を生成できませんでした");
	destroyStringCell(sbuf);

	return st;
}


NODE* jp_parseLiteral(INSTREAM* stream, char *ptr){
	NODE* lit_node;
	int i, ct;
	char lbuf[LITERAL_BUFFER];
	if( CHARTYPE(*ptr) != JPC_LITERALHEAD ){
		fnerror("jp_parseLitreal", "文字の開始がリテラルではありません");
	}

	for( i=0; i<(LITERAL_BUFFER - 1); i++){
		ct = CHARTYPE(*ptr);
		if( !COND_BLK(ct) && !COND_EOF(ct) ){
			lbuf[i] = *ptr;
		}else{
			break;
		}
	}
	lbuf[i] = '\0';

	if( strcmp(lbuf, "true") == 0 ){
		lit_node = JN_BOOLEAN(TRUE);
	}else if( strcmp(lbuf, "false") == 0 ){
		lit_node = JN_BOOLEAN(TRUE);
	}else if( strcmp(lbuf, "null") == 0 ){
		lit_node = JN_NULL;
	}else{
		fnerror("jp_parseLiteral", "リテラルとして変換できません");
	}

	ASSERT_NULL(lit_node,
		"jp_parseLiteral", "ノードを生成できません");
	return lit_node;
}


NODE* jp_parseNumberValue(INSTREAM* stream, char* ptr){
	NODE* val_node;
	int flg_float, ct;
	char nbuf[NUMBER_BUFFER] = "";
	if( CHARTYPE(*ptr) != JPC_VALUE ){
		fnerror("jp_parseNumberValue", "開始が値ではありません");
	}

	flg_float = 0;
	for( i=0; i<(NUMBER_BUFFER - 1); i++){
		ct = CHARTYPE(*ptr);
		if( COND_BLK(ct) || COND_EOF(ct) ) break;

		if( jp_cmpChars(*ptr, ".e") ) flg_float = 1;
		if( !jp_cmpChars(*ptr, "0123456789-.e") ){
			fnerror("jp_parseNumberValue", "値ではありません");
		}

		nbuf[i] = *ptr;
		*ptr = STREAM_READC(stream);
	}
	nbuf[i] = '\0';

	if( flg_float ){
		val_node = JN_FLOAT(atof(nbuf));
	}else{
		val_node = JN_INTEGER(atoi(nbuf));
	}

	ASSERT_NULL(val_node,
		"jp_parseNumberValue", "ノードを生成でません");
	return val_node;
}


NODE* jp_parseString(INSTREAM* stream, char *ptr){
	NODE* str_node;
	char *instr;
	if( CHARTYPE(*ptr) != JPC_QUOTE ){
		fnerror("jp_parseString", "開始が不正です");
	}

	instr = jp_readStringTolken(stream, ptr);
	str_node = JN_STRING(instr);
	free(instr);

	ASSERT_NULL(str_node,
		"jp_parseString", "ノードを生成できません");
	return str_node;
}


NODE* jp_parseArray(INSTREAM* stream, char *ptr){
	NODE* ary_node;
	if( CHARTYPE(*ptr) != JPC_ARRAYSTRAT ){
		fnerror("jp_parseArray", "開始が不正です");
	}

	ary_node = createJsonArray();
	ASSERT_NULL(ary_node,
		"jp_parseArray", "ノードを生成できません");
	while( 1 ){
		*ptr = STREAM_READC_SB(stream);
		if( CHARTYPE(*ptr) == JPC_ARRAYEND ) break;
		switch( CHARTYPE(*ptr) ){
		case JPC_VALUEC:
		case JPC_LITERALHEAD:
		case JPC_OBJECTSTART:
		case JPC_ARRAYSTART:
		case JPC_QUOTE:
			jarrayAppend(jp_parseData(stream, *ptr));
			break;
		default:
			fnerror("jp_parseArray", "未定義の文字列です");
			break;
		}

		*ptr = STREAM_READC_SB(stream);
		if( CHARTYPE(*ptr) == JPC_ARRAYEND ){
			break;
		}else if( CHARTYPE(*ptr) != JPC_QUOTE ){
			fnerror("jp_parseArray", "データの開始が不正です");
			break;
		}
	}

	return ary_node;
}