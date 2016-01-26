#include <stdio.h>
#include <stdlib.h>
#include "../error/error.h"
#include "stringCell.h"


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
	CHECK_NULL(cell, "destroyStringCell_nr");

	memset(cell->cb, 0, cell->cblen);
	free(cell->cb);
	memset(cell, 0, sizeof(STRCELL));
	free(cell);
}


void destroyStringCell(STRCELL* head){
	CHECK_NULL(cell, "destroyStringCell");

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


char* strcel_sitr_set(SC_SIMPLEITR* itr, STRCELL* head){
	NULL_CHECK(itr, "strcel_sitr_set");
	NULL_CHECK(head, "strcel_sitr_set");

	itr->cellp = head;
	itr->pos = 0;

	return head->cb;
}


char* strcel_sitr_next(SC_SIMPLEITR* itr){
	STRCELL* cellp_tmp;
	NULL_CHECK(itr, "strcel_sitr_next");
	NULL_CHECK(itr->cellp, "strcel_sitr_next");

	itr->pos = itr->pos + 1;
	cellp_tmp = itr->cellp;
	if( itr->pos >= cellp_tmp->cblen ){
		itr->cellp = cellp_tmp->next;
		itr->cnt = 0;
		if( cellp_tmp->next == NULL ) return NULL;
	}

	return cellp_tmp->cb + itr->pos;
}


STRCELL* strcel_core_getRear(STRCELL* head, int* ret_rearpos){
	char* cp;
	int cnt;
	STRCELL* cellp;
	NULL_CHECK(head, "strcel_core_getRear");

	cellp = head;
	cnt = 0;
	cp = cellp->cb;
	while( *cp != '\0' ){
		cnt++;

		if( cnt < cellp->cblen ){
			cp++;
		}else{
			if( cellp->next != NULL ){
				cellp = cellp->next;
				cp = cellp->cb;
				cnt = 0;
			}else{
				return NULL;
			}
		}
	}

	if( ret_rearpos != NULL ) *ret_rearpos = cnt;
	return cellp;
}


STRCELL* strcel_core_getPosition(STRCELL* head, int charat, int* ret_rearpos){
	int i, cnt;
	STRCELL* cellp;
	NULL_CHECK(head, "strcel_core_getPosition");

	cellp = head;
	cnt = 0;
	for( i=0; i<charat; i++){
		cnt++;
		if( cnt >= cellp->cblen ){
			if( cellp->next != NULL ){
				cellp = cellp->next;
				cnt = 0;
			}else{
				return NULL;
			}
		}
	}

	if( ret_rearpos != NULL ) *ret_rearpos = cnt;
	return cellp;
}


int strcel_core_writeString(STTRCELL* head, int celofs, char* str_ptr){
	char* cp, strp;
	int cnt;
	STRCELL* cellp;
	NULL_CHECK(head, "strcel_core_writeString");

	cellp = head;
	if( celofs < cellp->cblen ){
		cp = cellp->cb + celofs;
		cnt = celofs;
	}else{
		return EOF;
	}

	strp = str_ptr;
	while( 1 ){
		*cp = *strp;
		if( *strp == '\0' ) break;

		cnt++;
		if( cnt < cellp->cblen ){
			cp++;
		}else{
			if( cellp->next == NULL ){
				strcel_core_expandCell(
					cellp, STRCELL_DEFAULT_CBLEN_EXPAND, 1);
			}
			cellp = cellp->next;
			cnt = 0;
			cp = cellp->cb;
		}
		strp++;
	}

	return 0;
}


void strcel_resize(STRCELL* cell, int length){
	STRBUF* cellp;
	NULL_CHECK(cell, "strcel_resize");

	remain = length;
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
	cp = strcel_sitr_set(&itr, cell);
	while( cp != NULL && *cp != '\0' ){
		cp = strcel_sitr_next(&itr);
		count++;
	}

	return count;
}


int strcel_getBufferLength(STRCELL* cell){
	int count;
	SC_SIMPLEITR itr;

	count = 0;
	strcel_sitr_set(&itr, cell);
	while( itr.cellp != NULL ){
		count = count + (itr.cellp)->cblen;
		strcel_sitr_next(&itr);
	}

	return count;
}
