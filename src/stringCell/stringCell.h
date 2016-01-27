#ifndef STRINGCELL_H
#define STRINGCELL_H

#ifndef STDIO_H
#	include <stdio.h>
#endif

struct s_strcell {
	char* cb;
	int cblen;
	struct s_strcell* next;
};
typedef struct s_strcell STRCELL;

struct s_simpleStrcellItr{
	STRCELL* cellp;
	int pos;
};
typedef struct s_simpleStrcellItr SC_SIMPLEITR;


extern int STRCELL_DEFAULT_CBLEN_CREATE;
extern int STRCELL_DEFAULT_CBLEN_EXPAND;


STRCELL* createStringCell_ls(int len);
STRCELL* createStringCell(void);
void destroyStringCell_nr(STRCELL* cell);
void destroyStringCell(STRCELL* head);

void strcel_core_expandCell(STRCELL* pre, int len, int cnt);
void strcel_core_removeCell(STRCELL* pre);
char* strcel_sitr_set(SC_SIMPLEITR* itr, STRCELL* head, int spos);
char* strcel_sitr_next(SC_SIMPLEITR* itr);
STRCELL* strcel_core_getRear(STRCELL* head, int* ret_rearpos);
STRCELL* strcel_core_getPosition(STRCELL* head, int charat, int* ret_rearpos);
int strcel_core_writeString(STRCELL* head, int celofs, char* str_ptr);

void strcel_resize(STRCELL* cell, int length);
int strcel_getLength(STRCELL* cell);
int strcel_getBufferLength(STRCELL* cell);

void strcel_catString(STRCELL* cell, char* str);
void strcel_setString(STRCELL* cell, char* str);
char* strcel_copyto(STRCELL* cell, char* dst, int dst_len);
char* strcel_createString(STRCELL* cell);
int strcel_outputFile(STRCELL* cell, FILE* dst);

void strcel_dumpStringCell(STRCELL* cell, FILE* dst);
void strcel_dumpStringCells(STRCELL* cell, FILE* dst);

#endif
