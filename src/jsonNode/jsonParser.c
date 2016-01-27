#include <stdlib.h>
#include <string.h>
#include "../stream/inputStream.h"
#include "jsonParser.h"

#define CHARTYPE_CNT 9

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