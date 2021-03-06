#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../error/error.h"
#include "nodeCore.h"
#include "nodeIterator.h"

#define DEFAULT_INIT_STACKLEN 16

#define ASSERT_NULL(p, fnc) ifassert((p == NULL), fnc, "引数がNULLです");

int NODEITERATOR_INIT_STACKLEN = DEFAULT_INIT_STACKLEN;


NODESTACK* createNodeStack(int s){
	NODESTACK* new_stack;
	
	ifassert((s <= 0), "createNodeStack", "スタックの大きさ指定が不正です");
	
	new_stack = malloc(sizeof(NODESTACK));
	ifassert((new_stack == NULL), "createNodeStack", "スタックを生成できませんでした");
	
	new_stack->stack = malloc(sizeof(NODE*) * s);
	ifassert((new_stack->stack == NULL),
		"createNodeStack", "スタック領域を生成できませんでした");
	
	new_stack->size = s;
	initNodeStack(new_stack);
	
	return new_stack;
}


void initNodeStack(NODESTACK* ns){
	ASSERT_NULL(ns, "initNodeStack");
	
	memset(ns->stack, 0, sizeof(NODE*)*ns->size);
	ns->cnt = 0;
}


void destroyNodeStack(NODESTACK* ns){
	ASSERT_NULL(ns, "destroyNodeStack");
	
	initNodeStack(ns);
	free(ns->stack);
	free(ns);
}


void nodeStackPush(NODESTACK* ns, NODE* node){
	ASSERT_NULL(ns, "nodeStackPush");
	ifassert(isNodeStackFull(ns), "nodeStackPush", "スタックがいっぱいです");
	
	ns->stack[ns->cnt] = node;
	ns->cnt++;
}


NODE* nodeStackPop(NODESTACK* ns){
	ASSERT_NULL(ns, "nodeStackPop");
	ifassert(isNodeStackEmpty(ns), "nodeStackPop", "スタックが空です");
	
	ns->cnt--;
	return ns->stack[ns->cnt];
}


NODE* nodeStackRetrieve(NODESTACK* ns){
	ASSERT_NULL(ns, "nodeStackRetrieve");
	ifassert(isNodeStackEmpty(ns), "nodeStackRetrieve", "スタックが空です");
	
	return ns->stack[ns->cnt - 1];
}


int getNodeStackCount(NODESTACK* ns){
	ASSERT_NULL(ns, "getNodeStackCount");
	
	return ns->cnt;
}


int isNodeStackFull(NODESTACK* ns){
	ASSERT_NULL(ns, "getNodeStackFull");
	
	return ns->cnt >= ns->size;
}


int isNodeStackEmpty(NODESTACK* ns){
	ASSERT_NULL(ns, "getNodeStackEmpty");
	
	return ns->cnt <= 0;
}


NODETREE_ITR* createNodeIterator(NODE* root){
	NODETREE_ITR* new_itr;
	
	new_itr = malloc(sizeof(NODETREE_ITR));
	ifassert((new_itr == NULL), 
		"createNodeIterator", "メモリを確保できませんでした");
	
	new_itr->stack = createNodeStack(NODEITERATOR_INIT_STACKLEN);
	
	initNodeIterator(new_itr, root);
	
	return new_itr;
}


void initNodeIterator(NODETREE_ITR* itr, NODE* root){
	ASSERT_NULL(itr, "initNodeIterator");
	
	initNodeStack(itr->stack);
	nodeStackPush(itr->stack, root);
}


void destroyNodeIterator(NODETREE_ITR* itr){
	ASSERT_NULL(itr, "destroyNodeStack");
	
	initNodeIterator(itr, (void*)0);
	destroyNodeStack(itr->stack);
	free(itr);
}


NODE* nodeitrNext(NODETREE_ITR* itr){
	NODE* np;
	ASSERT_NULL(itr, "nodeitrNext");
	ifassert((isNodeStackEmpty(itr->stack)), "nodeitrNext", "イテレータは終端に達しています");
	
	np = nodeStackRetrieve(itr->stack);
	if( getFirstChildNode(np) != NULL ){
		ifassert((isNodeStackFull(itr->stack)), "nodeitrNext", "スタックオーバーフローです");
		nodeStackPush(itr->stack, getFirstChildNode(np));
		return nodeStackRetrieve(itr->stack);
	}
	
	nodeStackPop(itr->stack);
	while( getNextSiblingNode(np) == NULL ){
		if( isNodeStackEmpty(itr->stack) ){
			return NULL;
		}
		np = nodeStackPop(itr->stack);
	}
	
	nodeStackPush(itr->stack, getNextSiblingNode(np));
	return nodeStackRetrieve(itr->stack);
}
	


NODE* nodeitrGetNode(NODETREE_ITR* itr){
	ASSERT_NULL(itr, "nodeitrGetNode");
	
	if( isNodeStackEmpty(itr->stack) ) return NULL;
	
	return nodeStackRetrieve(itr->stack);
}


int nodeitrGetLevel(NODETREE_ITR* itr){
	ASSERT_NULL(itr, "nodeitrGetLevel");
	
	return getNodeStackCount(itr->stack) - 1;
}
