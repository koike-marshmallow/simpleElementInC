#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../error/error.h"
#include "../ptrStack/ptrStack.h"
#include "simpleNode.h"

#define ASSERT_NULL(n, fnc) ifassert((n == NULL), fnc, "値がnullです");

/* ************************************************** */

NODE* createNode(int type){
	NODE* new_node;
	
	new_node = malloc(sizeof(NODE));
	ifassert((new_node == NULL), "createNode", "メモリ確保に失敗しました");
	
	initNode(new_node, type);
	
	return new_node;
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

/* ************************************************** */

void destroyNode(NODE* node){
	ASSERT_NULL(node, "destroyNode");

	initNode(node, 0);
	free(node);
}

void recursiveDestroyNode(NODE* node){
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

/* ************************************************** */

void setNodeType(NODE* node, int typec){
	ASSERT_NULL(node, "setNodeType");
	
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

/* ************************************************** */

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

NODE** getLinkedNodeSiblingPNP(NODE* node, int idx){
	int i;
	NODE **pnp;
	pnp = &(node->child);
	for( i=0; i<idx; i++){
		if( *pnp == NULL ) return NULL;
		pnp = &((*pnp)->sibling);
	}
	return pnp;
}

/* ************************************************** */

void appendChildNode(NODE* node, NODE* append){
	NODE **target;
	ASSERT_NULL(node, "appendChildNode");
	
	target = &(node->child);
	while( *target != NULL ){
		target = &((*target)->sibling);
	}
	
	*target = append;
}

void insertChildNode(NODE* node, int idx, NODE* new_node){
	NODE **prev;
	ASSERT_NULL(node, "insertChildNode");
	ASSERT_NULL(new_node, "insertChildNode");
	
	prev = getLinkedNodeSiblingPNP(node, idx);
	ifassert((prev == NULL), "insertChildNode", "挿入位置を特定できません");
	insertLinkedNodeSibling(prev, new_node);
}

NODE* removeChildNode(NODE* node, int idx){
	NODE **prev;
	ASSERT_NULL(node, "deleteChildNode");
	
	prev = getLinkedNodeSiblingPNP(node, idx);
	ifassert((prev == NULL), "deleteChildNode", "削除位置を特定できません");
	return removeLinkedNodeSibling(prev);
}

/* ************************************************** */

NODE* getFirstChildNode(NODE* node){
	ASSERT_NULL(node, "getFirstChildNode");
	
	return node->child;
}

NODE* getNextSiblingNode(NODE* node){
	ASSERT_NULL(node, "getNextSibling");
	
	return node->sibling;
}

/* ************************************************** */

int getChildNodeIndex(NODE* node, NODE* target){
	int idx;
	NODE* np;
	ASSERT_NULL(node, "getChildNodeIndex");
	
	np = getFirstChildNode(node);
	while( np != NULL ){
		if( np == target ) return idx;
		idx++;
		np = getNextSiblingNode(np);
	}
	
	return -1;
}

int getChildNodeCount(NODE* node){
	int cnt;
	NODE* np;
	ASSERT_NULL(node, "getChildNodeCount");
	
	np = getFirstChildNode(node);
	cnt = 0;
	while( np != NULL ) np = getNextSiblingNode(np);
	
	return cnt;
}

/* ************************************************** */

NODETREE_ITR* nodeitrCreate(NODE* root){
	NODETREE_ITR* new_itr;
	ASSERT_NULL(root, "nodeitrCreate");
	
	new_itr = malloc(sizeof(NODETREE_ITR));
	ifassert((new_itr == NULL), "nodeitrCreate", "イテレータの生成に失敗しました");
	
	new_itr->stack = createPtrStack(NODETREE_ITR_STACK_LEN);
	ifassert((new_itr->stack == NULL), "nodeitrCreate", "スタックの生成に失敗しました");
	
	new_itr->ptr = NULL;
	
	return new_itr;
}

void nodeitrDestroy(NODETREE_ITR* itr){
	ASSERT_NULL(itr, "nodeitrDestroy");
	
	destroyPtrStack(itr->stack);
	itr->ptr = (void*)0;
	free(itr);
}

NODE* nodeitrNext(NODETREE_ITR* itr){
	NODE* np;
	ASSERT_NULL(itr, "nodeitrNext");
	ifassert((itr->ptr == NULL), "nodeitrNext", "イテレータは終端に達しています");

	np = getFirstChildNode(itr->ptr);
	if( np != NULL ){
		ifassert((isPtrStackFull(itr->stack)), "nodeitrNext", "スタックオーバーフローです");
		pushPtrStack(itr->stack, itr->ptr);
		itr->ptr = np;
		return np;
	}
	
	np = getNextSiblingNode(np);
	while( np == NULL ){
		if( isPtrStackEmpty(itr->stack) ){
			itr->ptr = NULL;
			return NULL;
		}
		np = popPtrStack(itr->stack);
		np = getNextSiblingNode(np);
	}
	
	itr->ptr = np;
	return np;
}

NODE* nodeitrGet(NODETREE_ITR* itr){
	ASSERT_NULL(itr, "nodeitrNext");
	return itr->ptr;
}

/* ************************************************** */

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























	







