#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "nodeCore.h"
#include "simpleNode.h"
#include "simpleElement.h"

#define BUF_SHORT_LEN 32
#define BUF_LONG_LEN 256

#define PRINTNODECORE(np) printf("NODE CORE(%p, %p, %p)\n", np->content, np->child, np->sibling);


NODE* createElement(char* name){
	NODE *new_element;
	
	new_element = createNode(NODE_ELEMENT);
	setNodeName(new_element, name);
	
	return new_element;
}


void destroyElement(NODE* element){
	rdestroyNode(element);
}


NODE* addAttribute(NODE* element, char* name, char* value){
	NODE *np;
	
	for( np = getFirstChildNode(element);
	np != NULL;
	np = getNextSiblingNode(np) ){
		if( getNodeType(np) == NODE_ATTRIBUTE 
		&& strcmp(getNodeName(np, NULL, 0), name) == 0 ){
			break;
		}
	}
	
	if( np == NULL ){
		np = createNode(NODE_ATTRIBUTE);
		appendChildNode(element, np);
		setNodeName(np, name);
	}
	setNodeValue(np, value);
	
	return np;
}


void deleteAttribute(NODE* element, char* name){
	NODE *itr, *next_itr;
	
	itr = getFirstChildNode(element);
	while( itr != NULL ){
		next_itr = getNextSiblingNode(itr);
		if( strcmp(getNodeName(itr, NULL, 0), name) == 0 ){
			removeChildNode(element, getChildNodeIndex(element, itr));
			destroyNode(itr);
		}
		itr = next_itr;
	}
}


void clearAttribute(NODE* element){
	NODE *itr, *next_itr;
	
	itr = getFirstChildNode(element);
	while( itr != NULL ){
		next_itr = getNextSiblingNode(itr);
		if( getNodeType(itr) == NODE_ATTRIBUTE ){
			removeChildNode(element, getChildNodeIndex(element, itr));
			destroyNode(itr);
		}
		itr = next_itr;
	}
}


int getAttributeNameList(NODE* element, char* list, int l_size, int b_size){
	int cnt;
	char* list_pt;
	NODE* itr;
	
	list_pt = list;
	cnt = 0;
	for( itr=getFirstChildNode(element); 
	(itr != NULL) && (cnt < l_size);
	itr = getNextSiblingNode(itr)){
		if( getNodeType(itr) == NODE_ATTRIBUTE ){
			getNodeName(itr, list_pt, b_size);
			list_pt += b_size;
			cnt++;
		}
	}
	
	return cnt;
}


char* getAttributeValue(NODE* element, char* name, char* buf, int len){
	NODE* itr;
	
	for( itr = getFirstChildNode(element);
	itr != NULL;
	itr = getNextSiblingNode(itr) ){
		if( getNodeType(itr) == NODE_ATTRIBUTE ){
			if( strcmp(getNodeName(itr, NULL, 0), name) == 0 ){
				if( buf != NULL ){
					getNodeValue(itr, buf, len);
				}
				return getNodeValue(itr, NULL, 0);
			}
		}
	}
}
		
	
NODE* addText(NODE* element, char* text){
	NODE* new_text;
	
	new_text = createNode(NODE_TEXT);
	setNodeValue(new_text, text);
	
	appendChildNode(element, new_text);
	
	return new_text;
}


char* getText(NODE* element, char* buf, int len){
	int child_len, i;
	NODE* itr;
	
	memset(buf, 0, len);
	for( itr = getFirstChildNode(element);
	(itr != NULL) && (strlen(buf) < len - 1);
	itr = getNextSiblingNode(itr) ){
		if( getNodeType(itr) == NODE_TEXT ){
			strncat(buf, getNodeValue(itr, NULL, 0), len - strlen(buf) - 1);
		}
	}
	
	return buf;
}


void clearText(NODE* element){
	NODE *itr, *next_itr;
	
	itr = getFirstChildNode(element);
	while( itr != NULL ){
		next_itr = getNextSiblingNode(itr);
		if( getNodeType(itr) == NODE_TEXT ){
			removeChildNode(element, getChildNodeIndex(element, itr));
			destroyNode(itr);
		}
		itr = next_itr;
	}
}


void appendChildElement(NODE* element, NODE* apnd){
	if( getNodeType(apnd) == NODE_ELEMENT ){
		appendChildNode(element, apnd);
	}
}


void destroyChildElements(NODE* element){
	NODE *itr, *next_itr;
	
	itr = getFirstChildNode(element);
	while( itr != NULL ){
		next_itr = getNextSiblingNode(itr);
		if( getNodeType(itr) == NODE_ELEMENT ){
			removeChildNode(element, getChildNodeIndex(element, itr));
			rdestroyNode(itr);
		}
		itr = next_itr;
	}
}
