#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../error/error.h"
#include "stringCell.h"

#define DUMP_LF 10

#define NULL_CHECK(p, fnc) \
	ifassert((p == NULL), fnc, "argument pointer is null");

int STRCELL_DEFAULT_CBLEN_CREATE = 64;
int STRCELL_DEFAULT_CBLEN_EXPAND = 64;


STRCELL* createStringCell_ls(int len){
	STRCELL* new_cell;

	ifassert((len <= 0), 
		"createStringCell_ls", "illigal length value");

	new_cell = malloc(sizeof(STRCELL));
	ifassert((new_cell == NULL),
		"createStringCell_ls", "cannot create string cell");

	new_cell->cb = malloc(sizeof(char) * len);
	ifassert((new_cell->cb == NULL),
		"createStringCell_ls", "cannot create string buffer");

	memset(new_cell->cb, 0, len);
	new_cell->cblen = len;
	new_cell->next = NULL;
}


STRCELL* createStringCell(void){
	return createStringCell_ls(STRCELL_DEFAULT_CBLEN_CREATE);
}


void destroyStringCell_nr(STRCELL* cell){
	NULL_CHECK(cell, "destroyStringCell_nr");

	memset(cell->cb, 0, cell->cblen);
	free(cell->cb);
	memset(cell, 0, sizeof(STRCELL));
	free(cell);
}


void destroyStringCell(STRCELL* head){
	NULL_CHECK(head, "destroyStringCell");

	if( head->next != NULL ){
		destroyStringCell(head->next);
	}
	destroyStringCell_nr(head);
}


void strcel_core_expandCell(STRCELL* pre, int len, int cnt){
	STRCELL* cp;
	int i;
	NULL_CHECK(pre, "strcel_core_expandCell");

	cp = pre;
	while( cp->next != NULL ){
		cp = cp->next;
	}

	for( i=0; i<cnt; i++){
		cp->next = createStringCell_ls(len);
		cp = cp->next;
	}
}


void strcel_core_removeCell(STRCELL* pre){
	NULL_CHECK(pre, "strcel_core_removeCell");

	if( pre->next != NULL ){
		destroyStringCell(pre->next);
		pre->next = NULL;
	}
}


char* strcel_sitr_set(SC_SIMPLEITR* itr, STRCELL* head, int spos){
	NULL_CHECK(itr, "strcel_sitr_set");
	NULL_CHECK(head, "strcel_sitr_set");

	itr->cellp = head;
	itr->pos = 0;

	if( spos < head->cblen ){
		itr->pos = spos;
	}else{
		return NULL;
	}

	return head->cb + itr->pos;
}


char* strcel_sitr_next(SC_SIMPLEITR* itr){
	NULL_CHECK(itr, "strcel_sitr_next");
	if( itr->cellp == NULL ) return NULL;

	itr->pos = itr->pos + 1;
	if( itr->pos >= (itr->cellp)->cblen ){
		itr->cellp = (itr->cellp)->next;
		itr->pos = 0;
		if( itr->cellp == NULL ) return NULL;
	}

	return (itr->cellp)->cb + itr->pos;
}


STRCELL* strcel_core_getRear(STRCELL* head, int* ret_rearpos){
	char* cp;
	SC_SIMPLEITR itr;
	NULL_CHECK(head, "strcel_core_getRear");

	cp = strcel_sitr_set(&itr, head, 0);
	while( cp != NULL && *cp != '\0' ){
		cp = strcel_sitr_next(&itr);
	}

	if( ret_rearpos != NULL ) *ret_rearpos = itr.pos;
	return itr.cellp;
}


STRCELL* strcel_core_getPosition(STRCELL* head, int charat, int* ret_rearpos){
	int i, cnt;
	STRCELL* cellp;
	SC_SIMPLEITR itr;
	NULL_CHECK(head, "strcel_core_getPosition");

	strcel_sitr_set(&itr, head, 0);
	for( i=0; i<charat; i++){
		if( strcel_sitr_next(&itr) == NULL ){
			return NULL;
		}
	}

	if( ret_rearpos != NULL ) *ret_rearpos = itr.pos;
	return itr.cellp;
}


int strcel_core_writeString(STRCELL* head, int celofs, char* str_ptr){
	char *cp, *strp;
	int cnt;
	STRCELL* tmp_cellp;
	SC_SIMPLEITR itr;
	NULL_CHECK(head, "strcel_core_writeString");

	cp = strcel_sitr_set(&itr, head, celofs);
	if( cp == NULL ) return EOF;

	strp = str_ptr;
	while( 1 ){
		*cp = *strp;
		if( *strp == '\0' ) break;

		tmp_cellp = itr.cellp;
		cp = strcel_sitr_next(&itr);
		if( cp == NULL ){
			strcel_core_expandCell(
				tmp_cellp, STRCELL_DEFAULT_CBLEN_EXPAND, 1);
			cp = strcel_sitr_set(&itr, tmp_cellp->next, 0);
		}

		strp++;
	}

	return 0;
}


void strcel_resize(STRCELL* cell, int length){
	int remain;
	STRCELL* cellp;
	NULL_CHECK(cell, "strcel_resize");
	ifassert((length <= 0),
		"strcel_resize", "illigal length value");

	remain = length;
	cellp = cell;
	while( remain > cellp->cblen ){
		remain = remain - cellp->cblen;

		if( cellp->next == NULL ){
			strcel_core_expandCell(
				cellp, 
				STRCELL_DEFAULT_CBLEN_EXPAND,
				(remain / STRCELL_DEFAULT_CBLEN_EXPAND) + 1
			);
		}
		cellp = cellp->next;
	}

	if( cellp->next != NULL ){
		strcel_core_removeCell(cellp);
		*(cellp->cb + (cellp->cblen - 1)) = '\0';
	}
}


int strcel_getLength(STRCELL* cell){
	int count;
	char* cp;
	SC_SIMPLEITR itr;

	count = 0;
	cp = strcel_sitr_set(&itr, cell, 0);
	while( cp != NULL && *cp != '\0' ){
		cp = strcel_sitr_next(&itr);
		count++;
	}

	return count;
}


int strcel_getBufferLength(STRCELL* cell){
	int count;
	STRCELL* cellp;

	count = 0;
	cellp = cell;
	while( cellp != NULL ){
		count = count + cellp->cblen;
		cellp = cellp->next;
	}

	return count;
}


void strcel_catString(STRCELL* cell, char* str){
	STRCELL* rear_cell;
	int rear_pos;
	NULL_CHECK(cell, "strcel_catString");

	rear_cell = strcel_core_getRear(cell, &rear_pos);
	ifassert((rear_cell == NULL),
		"strcel_catString", "rear iteration error");

	strcel_core_writeString(rear_cell, rear_pos, str);
}


void strcel_setString(STRCELL* cell, char* str){
	NULL_CHECK(cell, "strcel_setStirng");

	strcel_core_writeString(cell, 0, str);
}



char* strcel_copyto(STRCELL* cell, char* dst, int dst_len){
	char *ch, *dch;
	int cnt;
	SC_SIMPLEITR itr;
	NULL_CHECK(cell, "strcel_copyto");
	NULL_CHECK(dst, "strcel_copyto");

	dch = dst;
	ch = strcel_sitr_set(&itr, cell, 0);
	cnt = 0;
	while( ch != NULL ){
		if( cnt >= (dst_len - 1) ){
			*dch = '\0';
			break;
		}

		*dch = *ch;
		if( *ch == '\0' ){
			break;
		}

		dch++;
		cnt++;
		ch = strcel_sitr_next(&itr);
	}

	return dst;
}


char* strcel_createString(STRCELL* cell){
	int str_length;
	char* mlstr;
	NULL_CHECK(cell, "strcel_createString");

	str_length = strcel_getLength(cell);
	mlstr = malloc(sizeof(char) * (str_length + 1));
	ifassert((mlstr == NULL), 
		"strcel_createString", "cannot create string");

	return strcel_copyto(cell, mlstr, str_length + 1);
}


int strcel_outputFile(STRCELL* cell, FILE* dst){
	char* ch;
	SC_SIMPLEITR itr;
	NULL_CHECK(cell, "strcel_outputFile");

	ch = strcel_sitr_set(&itr, cell, 0);
	while( ch != NULL && *ch != '\0' ){
		if( fputc(*ch, dst) == EOF ) return EOF;
		ch = strcel_sitr_next(&itr);
	}

	return 0;
}


void strcel_dumpStringCell(STRCELL* cell, FILE* dst){
	int i;
	NULL_CHECK(cell, "strcel_dumpStringCell");

	fprintf(dst, "  <addr: %p, capasity: %d, next: %p>\n",
		cell, cell->cblen, cell->next);

	fprintf(dst, "  EXPR [");
	for( i=0; i<(cell->cblen); i++){
		if( *(cell->cb + i) == '\0' ) fputc(' ', dst);
		else fputc(*(cell->cb + i), dst);
	}
	fprintf(dst, "]\n");

	fprintf(dst, "  DUMP ");
	for( i=0; i<(cell->cblen); i++){
		if( (i % DUMP_LF) == 0 && i != (cell->cblen - 1) && i != 0 )
			fprintf(dst, "\n       ");
		fprintf(dst, "%02x ", *(cell->cb + i));
	}
	printf("\n");
}


void strcel_dumpStringCells(STRCELL* cell, FILE* dst){
	int i, cnt;
	STRCELL* cp;
	NULL_CHECK(cell, "strcel_dumpStringCells");

	cp = cell;
	cnt = 0;
	while( cp != NULL){
		cnt++;
		cp = cp->next;
	}

	cp = cell;
	i = 0;
	while( cp != NULL ){
		fprintf(dst, "--(dump: %d/%d)--------\n", ++i, cnt);
		strcel_dumpStringCell(cp, dst);
		cp = cp->next;
	}
	printf("---------- (terminated)\n");
}
