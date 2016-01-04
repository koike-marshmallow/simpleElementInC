#include <stdio.h>
#include <stdlib.h>
#include "nodeCore.h"

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

	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
