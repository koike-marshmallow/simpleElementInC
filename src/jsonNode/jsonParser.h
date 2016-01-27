#ifndef JSONPARSER_H
#define JSONPARSER_H

#ifndef INPUTSTREAM_H
#	include "../stream/inputStream.h"
#define

#define JPC_BLANK        100
#define JPC_VALUEC       200
#define JPC_LITERALHEADC 201
#define JPC_OBJECTSTART  301
#define JPC_OBJECTEND    302
#define JPC_ARRAYSTART   311
#define JPC_ARRAYEND     312
#define JPC_QUOTE        401
#define JPC_COMMA        402
#define JPC_COLON        403
#define JPC_NULLEOF      501
#define JPC_OTHER        601


int jp_checkCharType(char c);
void jp_cmpChars(char c, char* cs);

char jp_skipBlankLinefeed(INSTREAM* stream);

/* layer 0 */
char* jp_readStringTolken(INSTREAM* stream, char *ptr);
/* layer 1 */
NODE* jp_parseLiteral(INSTREAM* stream, char *ptr);
NODE* jp_parseNumberValue(INSTREAM* stream, char *ptr);
NODE* jp_parseString(INSTREAM* stream, char *ptr);
/* layer 2 */
NODE* jp_parseArray(INSTREAM* stream, char *ptr);
NODE* jp_parseMember(INSTREAM* stream, char *ptr);
NODE* jp_parseObject(INSTREAM* stream, char *ptr);

NODE* transformJson(INSTREAM* stream);









