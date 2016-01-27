#ifndef JSONPARSER_H
#define JSONPARSER_H

#define JPC_VALUEC
#define JPC_LITERALHEADC
#define JPC_ARRAYSTART
#define JPC_OBJECTSTART
#define JPC_QUOTE
#define JPC_COMMA
#define JPC_ARRAYEND
#define JPC_OBJECTEND
#define JPC_CORON
#define JPC_NULLEOF
#define JPC_OTHER


int jp_checkCharType(char c);
void jp_cmpCharInStr(char c, char* str);

char* jp_readStringToStrcell(INSTREAM* stream, STRCELL* scell, char* terminal);
char* jp_readStringToBlank(INSTREAM* stream, char* dst, int dst_len);

char* jp_readStirngToBlank




