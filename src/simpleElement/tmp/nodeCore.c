#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "nodeCore.h"
#include "../error/error.h"

#define ASSERT_NULL(p, fnc) ifassert((p == NULL), fnc, "値がNULLです");
#define PRINTINDENT(a) for( i=0; i<a; i++) printf("  ");


NODE* createNode(int type){
	NODE* new_node;
	
	new_node = malloc(sizeof(NODE));
	ifassert((new_node == NULL), "createNode", "メモリ確保に失敗しました");
	
	initNode(new_node, type);
	
	return new_node;
}


NODE* createCopyNode(NODE* node){
	NODE* clone_node;
	
	clone_node = createNode(node->node_type);
	setNodeName(clone_node, node->node_name);
	setNodeValue(clone_node, node->node_value);
	
	return clone_node;
}	


void destroyNode(NODE* node){
	ASSERT_NULL(node, "destroyNode");

	initNode(node, 0);
	free(node);
}

void rdestroyNode(NODE* node){
	ASSERT_NULL(node, "rdestroyNode");
	
	destroyChildNodes(node);
	destroyNode(node);
}


void destroyChildNodes(NODE* node){
	NODE *np, *next_np;
	
	np = node->child;
	while( np != NULL ){
		next_np = np->sibling;
		rdestroyNode(np);
		np = next_np;
	}
	node->child = NULL;
}


void initNode(NODE* node, int type){
	int i;
	ASSERT_NULL(node, "initNode");

	node->node_type = type;
	memset(node->node_name, 0, NODE_NAME_LEN);
	memset(node->node_value, 0, NODE_VALUE_LEN);
	node->child = NULL;
	node->sibling = NULL;
}


void clearNode(NODE* node){
	ASSERT_NULL(node, "clearNode");

	setNodeName(node, "");
	setNodeValue(node, "");
}


void setNodeType(NODE* node, int typec){
	nullCheck(node, "setNodeType", "値がNULLです");
	
	node->node_type = typec;
}


void setNodeName(NODE* node, char* name){
	nullCheck(node, "setNodeName", "値がNULLです");
	
	strncpy(node->node_name, name, NODE_NAME_LEN - 1);
}


void setNodeValue(NODE* node, char* value){
	nullCheck(node, "setNodeValue", "値がNULLです");
	
	strncpy(node->node_value, value, NODE_VALUE_LEN - 1);
}


int getNodeType(NODE* node){
	nullCheck(node, "getNodeType", "値がNULLです");
	
	return node->node_type;
}


char* getNodeName(NODE* node, char* buf, int len){
	nullCheck(node, "getNodeName", "値がNULLです");
	
	if( buf != NULL ){
		strncpy(buf, node->node_name, len - 1);
	}
	return node->node_name;
}


char* getNodeValue(NODE* node, char* buf, int len){
	nullCheck(node, "getNodeValue", "値がNULLです");
	
	if( buf != NULL ){
		strncpy(buf, node->node_value, len - 1);
	}
	return node->node_value;
}


NODE* getFirstChildNode(NODE* node){
	ASSERT_NULL(node, "getFirstChildNode");
	
	return node->child;
}


NODE* getNextSiblingNode(NODE* node){
	ASSERT_NULL(node, "getNextSibling");
	
	return node->sibling;
}


void insertLinkedNodeSibling(NODE **pre_np, NODE *new_node){
	NODE *tmp;
	tmp = *pre_np;
	*pre_np = new_node;
	new_node->sibling = tmp;
}


NODE* removeLinkedNodeSibling(NODE **pre_np){
	NODE *tmp;
	tmp = *pre_np;
	*pre_np = tmp->sibling;
	tmp->sibling = NULL;
}	


void appendChildNode(NODE* node, NODE* append){
	NODE **target;
	ASSERT_NULL(node, "appendChildNode");
	
	target = &(node->child);
	while( *target != NULL ){
		target = &((*target)->sibling);
	}
	
	*target = append;
}


void insertChildNode(NODE* node, NODE* new_node, NODE* pos){
	NODE **target;
	ASSERT_NULL(node, "insertChildNode");
	ASSERT_NULL(new_node, "insertChildNode");
	ifassert((pos == NULL), "insertChildNode", "posがNULLです");
	
	target = &(node->child);
	while( *target != NULL ){
		if( *target == pos ){
			insertLinkedNodeSibling(target, new_node);
			break;
		}
		target = &((*target)->sibling);
	}
}


void removeChildNode(NODE* node, NODE* pos){
	NODE **pre;
	ASSERT_NULL(node, "insertChildNode");
	
	pre = &(node->child);
	while( *pre != NULL ){
		if( *pre == pos ){
			removeLinkedNodeSibling(pre);
			break;
		}
		pre = &((*pre)->sibling);
	}
}
		

int getChildNodeCount(NODE* node){
	int cnt;
	NODE* np;
	ASSERT_NULL(node, "getChildNodeCount");
	
	np = node->child;
	while( np != NULL ){
		cnt++;
		np = np->sibling;
	}
	
	return cnt;
}
	

int getChildNodeList(NODE* node, NODE* list[], int len){
	int cnt = 0;
	NODE* np;
	ASSERT_NULL(node, "getChildNodeList");
	
	np = node->child;
	while( np != NULL ){
		list[cnt] = np;
		cnt++;
		np = np->sibling;
	}
	
	return cnt;
}
	
	
void printNodeInfo(NODE* node, int indent){
	int i;
	nullCheck(node, "printNodeInfo", "値がnullです");
	
	PRINTINDENT(indent);
	printf("node type: %d\n", node->node_type);
	PRINTINDENT(indent);
	printf("node name: %s\n", node->node_name);
	PRINTINDENT(indent);
	printf("node value: %s\n", node->node_value);
}
	
	
void traceNodes(NODE* node, int indent){
	NODE* np;
	ASSERT_NULL(node, "traceNodes");
	
	printNodeInfo(node, indent);
	
	np = getFirstChildNode(node); /* np = node->child */
	while( np != NULL ){
		traceNodes(np, indent + 2);
		np = getNextSiblingNode(np); /* np = np->sibling */
	}
}
	
	
