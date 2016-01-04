#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "nodeCore.h"

#define ASSERT_NULL(p, fnc) ifassert((p == NULL), fnc, "値がNULLです");
#define ASSERT_CHILD_HEAD(p, fnc) ifassert((p->child == NULL), fnc, "childヘッドが見つかりません");
#define ASSERT_NONE (p, fnc) ifassert(( p->node_type == NODE_NONE ), fnc, "空ノードです");
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
	ASSERT_NULL(node, "destroyNode");

	initNode(node, 0);
	free(node);
}

void rdestroyNode(NODE* node){
	int i;
	NODE *np, *next_np;
	ASSERT_NULL(node, "rdestroyNode");
	
	/*子ノードを削除*/
	if( node->child != NULL ){
		np = node->child;
		while( np != NULL ){
			next_np = np->sibling;
			rdestroyNode(np);
			np = next_np;
		}
	}
	
	destroyNode(node);
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
	nullCheck(node, "clearNode", "値がNULLです");

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


void getNodeName(NODE* node, char buf[], int len){
	nullCheck(node, "getNodeName", "値がNULLです");
	
	strncpy(buf, node->node_name, len - 1);
}


void getNodeValue(NODE* node, char buf[], int len){
	nullCheck(node, "getNodeValue", "値がNULLです");
	
	strncpy(buf, node->node_value, len - 1);
}


NODE* getFirstChildNode(NODE* node){
	ASSERT_NULL(node, "getFirstChildNode");
	
	return node->child;
}


NODE* getNextSiblingNode(NODE* node){
	ASSERT_NULL(node, "getNextSibling");
	
	return node->sibling;
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
		np = getNextSiblingNode(np);
	}
}
	
	
