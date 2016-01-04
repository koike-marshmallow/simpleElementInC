#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "nodeCore.h"

#define BUF_SHORT_LEN 32
#define BUF_LONG_LEN 256

/*
NODE* createElement(char* name);
NODE* createTextNode(char* text);
void destroyElement(NODE* element);

void initElement(NODE* element);
void clearElement(NODE* element);

void addAttribute(NODE* element, char* name, char* value);
void deleteAttribute(NODE* element, char* name);
void clearAttribute(NODE* element);
int getAttributeNameList(NODE* element, char* list[], int len);
void getAttributeValue(NODE* element, char* name, char buf[], int len);

void setText(NODE* element, char* text);
void getText(NODE* element, char buf[], int len);
void clearText(NODE* element);
*/


NODE* createElement(char* name){
	NODE *new_element;
	
	new_element = createNode(NODE_ELEMENT);
	setNodeName(new_element, name);
	
	return new_element;
}


NODE* createTextNode(char* text){
	NODE *new_element;
	
	new_element = createNode(NODE_TEXT);
	setNodeValue(new_element, text);
	
	return new_element;
}


void destroyElement(NODE* element){
	destroyNode(element);
}


void recursiveDestroyElement(NODE* element){
	recursiveDestroyNode(element);
}


void initElement(NODE* element){
	int type = getNodeType(element);
	
	initNode(element, type);
}


void clearElement(NODE* element){
	clearNode(element);
}


void addAttribute(NODE* element, char* name, char* value){
	NODE* new_attr;
	
	new_attr = createNode(NODE_ATTRIBUTE);
	setNodeName(new_attr, name);
	setNodeValue(new_attr, value);
	
	appendChildNode(element, new_attr);
}


void deleteAttribute(NODE* element, char* name){
	int child_len, i;
	char buffer[BUF_SHORT_LEN];
	NODE* child;
	
	child_len = getChildNodeCount(element);
	for( i=(child_len - 1); i>=0; i--){
		child = getChildNode(element, i);
		if( getNodeType(child) == NODE_ATTRIBUTE ){
			getNodeName(child, buffer, BUF_SHORT_LEN);
			
			if( strcmp(buffer, name) == 0 ){
				removeChildNode(element, i);
			}
		}
	}
}


void clearAttribute(NODE* element){
	int child_len, i;
	NODE* child;
	
	child_len = getChildNodeCount(element);
	for( i=(child_len - 1); i>=0; i--){
		child = getChildNode(element, i);
		if( getNodeType(child) == NODE_ATTRIBUTE ){
			removeChildNode(element, i);
		}
	}
}


int getAttributeNameList(NODE* element, char* list, int l_size, int b_size){
	int child_len, i, cnt;
	char* list_pt;
	NODE* child;
	
	child_len = getChildNodeCount(element);
	list_pt = list;
	cnt = 0;
	for( i=0; (i < child_len) && (cnt < l_size); i++){
		child = getChildNode(element, i);
		if( getNodeType(child) == NODE_ATTRIBUTE ){
			getNodeName(child, list_pt, b_size);
			list_pt += b_size;
			cnt++;
		}
	}
	
	return cnt;
}


void getAttributeValue(NODE* element, char* name, char buf[], int len){
	int child_len, i;
	char buffer[BUF_SHORT_LEN];
	NODE* child;
	
	child_len = getChildNodeCount(element);
	for( i=(child_len - 1); i>=0; i--){
		child = getChildNode(element, i);
		if( getNodeType(child) == NODE_ATTRIBUTE ){
			getNodeName(child, buffer, BUF_SHORT_LEN);
			
			if( strcmp(buffer, name) == 0 ){
				getNodeValue(child, buf, len);
			}
		}
	}
}
		
	
void addText(NODE* element, char* text){
	NODE* new_text;
	
	new_text = createNode(NODE_TEXT);
	setNodeValue(new_text, text);
	
	appendChildNode(element, new_text);
}


void getText(NODE* element, char buf[], int len){
	int child_len, i;
	char buffer[BUF_LONG_LEN];
	NODE* child;
	
	memset(buf, 0, len);
	child_len = getChildNodeCount(element);
	for( i=0; (i < child_len) && (strlen(buf) < len - 1); i++){
		child = getChildNode(element, i);
		if( getNodeType(child) == NODE_TEXT ){
			getNodeValue(child, buffer, BUF_LONG_LEN);
			strncat(buf, buffer, len - strlen(buf) - 1);
		}
	}
}


void clearText(NODE* element){
	int child_len, i;
	NODE* child;
	
	child_len = getChildNodeCount(element);
	for( i=(child_len - 1); i>=0; i--){
		child = getChildNode(element, i);
		if( getNodeType(child) == NODE_TEXT ){
			removeChildNode(element, i);
		}
	}
}
