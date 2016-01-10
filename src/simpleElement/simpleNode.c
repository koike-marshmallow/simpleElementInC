#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../error/error.h"
#include "nodeCore.h"
#include "nodeIterator.h"
#include "simpleNode.h"

#define ASSERT_NULL(n, fnc) ifassert((n == NULL), fnc, "値がnullです");
#define ASSERT_CONTENT_NULL(cp, fnc) ifassert((cp == NULL), fnc, "ノードにデータがありません");
#define PRINTINDENT(a) for( i=0; i<a; i++) printf("  ");
#define PRINTNODECORE(np) printf("NODE CORE(%p, %p, %p)\n", np->content, np->child, np->sibling);

NODE* createNode(int type){
	NODE* new_node;
	NCONTENT* new_content;
	
	new_node = createNodeCore();
	
	new_content = malloc(sizeof(NCONTENT));
	ifassert((new_content == NULL),
		"createNode", "ノードの生成に失敗しました");
	setNodeContent(new_node, new_content);
	
	initNode(new_node, type);
	
	return new_node;
}


void initNode(NODE* node, int type){
	int i;
	NCONTENT* content;
	ASSERT_NULL(node, "initNode");

	content = getNodeContent(node);
	initNodeCore(node);
	setNodeContent(node, content);
	
	content->type = type;
	memset(content->name, 0, NODE_NAME_LEN);
	memset(content->value, 0, NODE_VALUE_LEN);
}


void destroyNode(NODE* node){
	NCONTENT* content;
	ASSERT_NULL(node, "destroyNode");

	content = getNodeContent(node);
	ASSERT_CONTENT_NULL(content, "destroyNode");
	
	initNode(node, 0);
	free(content);
	destroyNodeCore(node);
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


void setNodeType(NODE* node, int typec){
	NCONTENT* content;
	ASSERT_NULL(node, "setNodeType");
	
	content = getNodeContent(node);
	ASSERT_CONTENT_NULL(content, "setNodeType");
	content->type = typec;
}

void setNodeName(NODE* node, char* name){
	NCONTENT* content;
	ASSERT_NULL(node, "setNodeName");

	content = getNodeContent(node);
	ASSERT_CONTENT_NULL(content, "setNodeName");
	
	strncpy(content->name, name, NODE_NAME_LEN - 1);
}

void setNodeValue(NODE* node, char* value){
	NCONTENT* content;
	ASSERT_NULL(node, "setNodeValue");

	content = getNodeContent(node);
	ASSERT_CONTENT_NULL(content, "setNodeValue");
	
	strncpy(content->value, value, NODE_VALUE_LEN - 1);
}

int getNodeType(NODE* node){
	NCONTENT* content;
	ASSERT_NULL(node, "getNodeType");

	content = getNodeContent(node);
	ASSERT_CONTENT_NULL(content, "getNodeType");
	
	return content->type;
}

char* getNodeName(NODE* node, char* buf, int len){
	NCONTENT* content;
	ASSERT_NULL(node, "getNodeName");

	content = getNodeContent(node);
	ASSERT_CONTENT_NULL(content, "getNodeName");
	
	if( buf != NULL ){
		strncpy(buf, content->name, len - 1);
	}
	return content->name;
}

char* getNodeValue(NODE* node, char* buf, int len){
	NCONTENT* content;
	ASSERT_NULL(node, "getNodeValue");

	content = getNodeContent(node);
	ASSERT_CONTENT_NULL(content, "getNodeValue");
	
	if( buf != NULL ){
		strncpy(buf, content->value, len - 1);
	}
	return content->value;
}


void appendChildNode(NODE* node, NODE* apnd){
	NODE** pnp;
	ASSERT_NULL(node, "appendChildNode");
	ASSERT_NULL(apnd, "appendChildNode");
	
	pnp = getLinkedNodeSibtailPNP(node);
	ifassert((pnp == NULL), "appendChildNode", "予期せぬエラーが発生しました");
	insertLinkedNodeSibling(pnp, apnd);
}


void insertChildNode(NODE* node, int idx, NODE* new_node){
	NODE **prev;
	ASSERT_NULL(node, "insertChildNode");
	ASSERT_NULL(new_node, "insertChildNode");
	
	prev = getLinkedNodeSibidxPNP(node, idx);
	ifassert((prev == NULL), "insertChildNode", "挿入位置を特定できません");
	insertLinkedNodeSibling(prev, new_node);
}


NODE* removeChildNode(NODE* node, int idx){
	NODE **prev;
	ASSERT_NULL(node, "deleteChildNode");
	
	prev = getLinkedNodeSibidxPNP(node, idx);
	ifassert((prev == NULL), "deleteChildNode", "削除位置を特定できません");
	return removeLinkedNodeSibling(prev);
}


void printNodeInfo(NODE* node, int indent){
	int i;
	NCONTENT* content;
	ASSERT_NULL(node, "printNodeInfo");
	
	content = getNodeContent(node);
	ASSERT_CONTENT_NULL(content, "printNodeInfo");
	
	PRINTINDENT(indent);
	printf("node type: %d\n", content->type);
	PRINTINDENT(indent);
	printf("node name: %s\n", content->name);
	PRINTINDENT(indent);
	printf("node value: %s\n", content->value);
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
