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
	nullCheck(node, "destroyNode", "値がNULLです");

	if( node->child != NULL ){
		destroyNode(node->child);
	}
	initNode(node, 0);
	free(node);
}

void rdestroyNode(NODE* node){
	int i;
	NODE* np, next_np;
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
	
	if( type != NODE_NONE ){
		node->child = createNode(NODE_NONE);
	}
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


NODE* getFirstChildNode(NODE* node){
	NODE* p;
	ASSERT_NULL(node, "getFirstChildNode");
	
	p = node->child;
	while( p != NULL && p->node_type == NODE_NONE ) p = p->sibling;
	return p;
}


NODE* getNextSibling(NODE* node){
	NODE* p;
	ASSERT_NULL(node, "getNextSibling");
	
	p = node->sibling;
	while( p != NULL && p->node_type == NODE_NONE ) p = p->sibling;
	return p;
}


void appendChildNode(NODE* node, NODE* append){
	NODE *np, *pre_np;
	ASSERT_NULL(node, "appendChildNode");
	ASSERT_CHILD_HEAD(node, "appendChildNode");
	
	pre_np = node->child;
	np = pre_np->sibling;
	while( np != NULL ){
		pre_np = np;
		np = np->sibling;
	}
	
	pre_np->sibling = append;
	append->sibling = NULL;
}


void 
		


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
	
	
