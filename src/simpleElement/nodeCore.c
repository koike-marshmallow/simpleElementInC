#include <stdlib.h>
#include "../error/error.h"
#include "nodeCore.h"

#define ASSERT_NULL(np, fnc) ifassert((np == NULL), fnc, "node pointer is NULL");


NODE* createNodeCore(void){
	NODE* new_node;
	
	new_node = malloc(sizeof(NODE));
	ifassert((new_node == NULL), "createNodeCore", "failed create node");
	
	initNodeCore(new_node);
	
	return new_node;
}


void initNodeCore(NODE* node){
	ASSERT_NULL(node, "initNodeCore");
	
	node->content = NULL;
	node->child = NULL;
	node->sibling = NULL;
}


void destroyNodeCore(NODE* node){
	ASSERT_NULL(node, "destroyNodeCore");
	
	node->content = (void*)0;
	node->child = (void*)0;
	node->sibling = (void*)0;
	free(node);
}


void* getNodeContent(NODE* node){
	ASSERT_NULL(node, "getNodeContent");
	
	return node->content;
}


void setNodeContent(NODE* node, void* ptr){
	ASSERT_NULL(node, "setNodeContent");
	
	node->content = ptr;
}


NODE* getFirstChildNode(NODE* node){
	ASSERT_NULL(node, "getFirstChildNode");
	
	return node->child;
}


NODE* getNextSiblingNode(NODE* node){
	ASSERT_NULL(node, "getNextSiblingNode");
	
	return node->sibling;
}


void insertLinkedNodeSibling(NODE** prev_np, NODE* new_node){
	NODE* tmp;
	ifassert((prev_np == NULL),
		"insertLinkedNodeSibling", "Previous Node Pointer is NULL");
	ifassert((new_node == NULL),
		"insertLinkedNodeSibling", "Insert Node Pointer is NULL");
	
	tmp = *prev_np;
	*prev_np = new_node;
	new_node->sibling = tmp;
}


NODE* removeLinkedNodeSibling(NODE** prev_np){
	NODE* tmp;
	ifassert((prev_np == NULL),
		"removeLinkedNodeSibling", "Previous Node Pointer is NULL");
	
	tmp = *prev_np;
	*prev_np = tmp->sibling;
	tmp->sibling = NULL;
}


NODE** getLinkedNodeSibidxPNP(NODE* node, int idx){
	NODE** pnp;
	int i;
	ASSERT_NULL(node, "getLinkedNodeSibidxPNP");
	
	pnp = &(node->child);
	for( i=0; i<idx; i++){
		if( *pnp == NULL ) return NULL;
		pnp = &((*pnp)->sibling);
	}
	
	return pnp;
}


NODE** getLinkedNodeSibtailPNP(NODE* node){
	NODE** pnp;
	ASSERT_NULL(node, "getLinkedNodeSibtailPNP");
	
	pnp = &(node->child);
	while( *pnp != NULL ){
		pnp = &((*pnp)->sibling);
	}
	
	return pnp;
}


int getChildNodeIndex(NODE* node, NODE* target){
	NODE* np;
	int cnt;
	ASSERT_NULL(node, "getChildNodeIndex");
	ifassert((target == NULL), "getChildNodeIndex", "target node pointer is NULL");
	
	np = getFirstChildNode(node);
	cnt = 0;
	while( np != NULL ){
		if( np == target ) return cnt;
		np = getNextSiblingNode(np);
		cnt++;
	}
	
	return -1;
}


int getChildNodeCount(NODE* node){
	NODE* np;
	int cnt;
	ASSERT_NULL(node, "getChildNodeCount");
	
	np = getFirstChildNode(node);
	cnt = 0;
	while( np != NULL ){
		cnt++;
		np = getNextSiblingNode(np);
	}
	
	return cnt;
}
