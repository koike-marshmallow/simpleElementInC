#include <stdio.h>
#include "nodeCore.h"
#include "simpleNode.h"
#include "simpleElement.h"
#include "../stringBuffer/stringBuffer.h"

int TRANSFORM_INDENT = 0;
int TRANSFORM_LINEFEED = 0;
char* TRANSFORM_INDENT_CHAR = " ";


void mtIndent(STRBUF* buffer, int level){
	int i;
	for( i=0; i<(TRANSFORM_INDENT * level); i++)
		sbCatString(buffer, TRANSFORM_INDENT_CHAR);
}


void mtLinefeed(STRBUF* buffer){
	if( TRANSFORM_LINEFEED )
		sbCatString(buffer, "\n");
}


void generateAttributeString(STRBUF* buffer, NODE* attr){
	if( getNodeType(attr) != NODE_ATTRIBUTE ) return;
	
	sbCatString(buffer, getNodeName(attr, NULL, 0));
	sbCatString(buffer, "=\"");
	sbCatString(buffer, getNodeValue(attr, NULL, 0));
	sbCatString(buffer, "\"");
}


void generateTextNodeString(STRBUF* buffer, NODE* text){
	if( getNodeType(text) != NODE_TEXT ) return;
	
	sbCatString(buffer, getNodeValue(text, NULL, 0));
}


int generateElementStartTag(STRBUF* buffer, NODE* element){
	char* e_name;
	int child, cn_type;
	NODE* np;
	
	e_name = getNodeName(element, NULL, 0);
	sbCatString(buffer, "<");
	sbCatString(buffer, e_name);
	
	child = 0;
	for( np = getFirstChildNode(element);
	np != NULL;
	np = getNextSiblingNode(np) ){
		cn_type = getNodeType(np);
		switch( cn_type ){
		case NODE_ATTRIBUTE:
			sbCatString(buffer, " ");
			generateAttributeString(buffer, np);
			break;
		case NODE_ELEMENT:
		case NODE_TEXT:
			child = 1;
			break;
		}
	}
	
	if( child ){
		sbCatString(buffer, ">");
	}else{
		sbCatString(buffer, " />");
	}
	
	return child;
}


void generateElementEndTag(STRBUF* buffer, NODE* element){
	sbCatString(buffer, "</");
	sbCatString(buffer, getNodeName(element, NULL, 0));
	sbCatString(buffer, ">");
}


void recursiveTransformElement(STRBUF* buffer, NODE* element, int level){
	NODE* np;
	int cn_type, end_lf;
	
	if( getNodeType(element) != NODE_ELEMENT ) return;
	
	mtIndent(buffer, level);
	if( generateElementStartTag(buffer, element) ){
	
		/*子ノードのトランスフォーム*/
		end_lf = 0;
		for( np = getFirstChildNode(element);
		np != NULL;
		np = getNextSiblingNode(np) ){
			cn_type = getNodeType(np);
			
			switch( cn_type ){
			case NODE_ELEMENT: 
				mtLinefeed(buffer);
				recursiveTransformElement(buffer, np, level + 1);
				end_lf = 1;
				break;
			case NODE_TEXT:
				generateTextNodeString(buffer, np);
				break;
			}
		}
		
		if( end_lf ){
			mtLinefeed(buffer);
			mtIndent(buffer, level);
		}
		generateElementEndTag(buffer, element);
	}
}


void transform(STRBUF* buffer, NODE* root){
	if( buffer == NULL || root == NULL ) return;
	
	recursiveTransformElement(buffer, root, 0);
}
