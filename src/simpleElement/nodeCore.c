#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "nodeCore.h"

#define ASSERT_NULL(p, fnc) ifassert((p == NULL), fnc, "値がNULLです");
#define PRINTINDENT(a) for( i=0; i<a; i++) printf("  ");


/*
NODE* createNode(int type);
void destroyNode(NODE* node);

void initNode(NODE* node, int type);
void clearNode(NODE* node);

void setType(NODE* node, int typec);
void setName(NODE* node, char* name);
void setValue(NODE* node, char* value);
int getType(NODE* node);
void getName(NODE* node, char buf[], int len);
void getValue(NODE* node, char buf[], int len);

void appendChildNode(NODE* node, NODE* append);
NODE* getChildNode(NODE* node, int idx);
int getChildNodeCount(NODE* node);

void clearChildNodeList(NODE* node);
void destroyChildNodeList(NODE* node);
void getChildeNodeList(NODE* node, NODE* list[], int len);
*/


NODE* createNode(int type){
	NODE* new_node;
	
	new_node = malloc(sizeof(NODE));
	ifassert((new_node == NULL), "createNode", "メモリ確保に失敗しました");
	
	initNode(new_node, type);
	
	return new_node;
}


void destroyNode(NODE* node){
	nullCheck(node, "destroyNode", "値がNULLです");

	initNode(node, 0);
	free(node);
}

void recursiveDestroyNode(NODE* node){
	int i;
	nullCheck(node, "recursiveDestoryNode", "値がNULLです");
	
	for( i=0; i<node->c_childs; i++){
		recursiveDestroyNode(getChildNode(node, i));
	}
	
	destroyNode(node);
}


void initNode(NODE* node, int type){
	int i;

	nullCheck(node, "initNode", "値がNULLです");

	node->node_type = type;
	memset(node->node_name, 0, NODE_NAME_LEN);
	memset(node->node_value, 0, NODE_VALUE_LEN);
	for( i=0; i<MAX_CHILDS_LEN; i++) node->childs[i] = NULL;
	node->c_childs = 0;
}


void clearNode(NODE* node){
	nullCheck(node, "clearNode", "値がNULLです");

	setNodeName(node, "");
	setNodeValue(node, "");
	clearChildNodeList(node);
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


void getNodeName(NODE* node, char buf[], int len){
	nullCheck(node, "getNodeName", "値がNULLです");
	
	strncpy(buf, node->node_name, len - 1);
}


void getNodeValue(NODE* node, char buf[], int len){
	nullCheck(node, "getNodeValue", "値がNULLです");
	
	strncpy(buf, node->node_value, len - 1);
}


void appendChildNode(NODE* node, NODE* append){
	nullCheck(node, "appendChildNode", "値がNULLです");
	
	if( node->c_childs >= MAX_CHILDS_LEN ){
		fnerror("appendChildNode", "子ノードリストがいっぱいです");
	}
	
	node->childs[node->c_childs] = append;
	node->c_childs++;
}



void insertChildNode(NODE* node, int idx, NODE* insert){
	int i;
	ASSERT_NULL(node, "insertChildNode");
	
	if( idx < 0 || idx >= node->c_childs ){
		fnerror("getChildNode", "子ノードがありません");
	}
	if( node->c_childs >= MAX_CHILDS_LEN ){
		fnerror("insertChildNode", "子ノードリストがいっぱいです");
	}
	
	i = node->c_childs;
	while( i > idx ){
		node->childs[i] = node->childs[i - 1];
	}
	node->childs[idx] = insert;
	node->c_childs++;
}


void deleteChildNode(NODE* node, int idx){
	int i;
	ASSERT_NULL(node, "deleteChildNode");
	
	if( idx < 0 || idx >= node->c_childs ){
		fnerror("deleteChildNode", "子ノードがありません");
	}
	
	i = idx;
	while( i < node->c_childs - 1 ){
		node->childs[i] = node->childs[i + 1];
	}
	node->c_childs--;
}			


NODE* getChildNode(NODE* node, int idx){
	nullCheck(node, "getChildNode", "値がNULLです");
	
	if( idx < 0 || idx >= node->c_childs ){
		fnerror("getChildNode", "子ノードがありません");
	}
	
	return node->childs[idx];
}


int getChildNodeCount(NODE* node){
	nullCheck(node, "getChildNodeCount", "値がNULLです");
	
	return node->c_childs;
}


void clearChildNodeList(NODE* node){
	nullCheck(node, "clearChildNodeList", "値がNULLです");
	
	node->c_childs = 0;
}

void getChildNodeList(NODE* node, NODE* list[], int len){
	int i;
	nullCheck(node, "getChildNodeList", "値がNULLです");
	
	i = 0;
	while( i < node->c_childs && i < len ){
		list[i] = node->childs[i];
		i++;
	}
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
	int i, cc;
	nullCheck(node, "traceNodes", "値がnullです");
	
	printNodeInfo(node, indent);
	cc = getChildNodeCount(node);
	for( i=0; i<cc; i++){
		traceNodes(getChildNode(node, i), indent + 2);
	}
}
	
	
