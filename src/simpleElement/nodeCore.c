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



