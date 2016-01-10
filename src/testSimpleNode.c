#include <stdio.h>
#include "simpleElement/nodeCore.h"
#include "simpleElement/nodeIterator.h"
#include "simpleElement/simpleNode.h"

#define STACK_TRACE 0

#define PRINTINDENT(a) for( i=0; i<a; i++) printf("  ");

void testNodeIterator(NODE* root);

int main(void){
	NODE *n0, *n1, *n2, *n3, *n4, *n5;
	
	n0 = createNode(NODE_ELEMENT);
	n1 = createNode(NODE_ELEMENT);
	n2 = createNode(NODE_ATTRIBUTE);
	n3 = createNode(NODE_TEXT);
	n4 = createNode(NODE_ELEMENT);
	n5 = createNode(NODE_ATTRIBUTE);
	
	setNodeName(n0, "root");
	appendChildNode(n0, n1);
	appendChildNode(n0, n4);
	setNodeName(n1, "test");
	appendChildNode(n1, n2);
	appendChildNode(n1, n3);
	setNodeName(n2, "stuff");
	setNodeValue(n2, "this node is attribute");
	setNodeValue(n3, "This is node core test");
	setNodeName(n4, "ext");
	appendChildNode(n4, n5);
	setNodeName(n5, "myname");
	setNodeValue(n5, "taka");
	
	traceNodes(n0, 0);
	
	NODEITERATOR_INIT_STACKLEN = 8;
	testNodeIterator(n0);
	
	removeChildNode(n4, getChildNodeIndex(n4, n5));
	testNodeIterator(n0);
	
	insertChildNode(n1, getChildNodeIndex(n1, n2), n5);
	testNodeIterator(n0);
	
	rdestroyNode(n0);
	

	return 0;
}


void printNode(NODE* node, char* tail){
	printf("(%d, %s, \"%s\")[%d]%s", 
		getNodeType(node),
		getNodeName(node, NULL, 0),
		getNodeValue(node, NULL, 0),
		getChildNodeCount(node),
		tail);
}

void printNode2(NODE* node){
	switch( getNodeType(node) ){
	case NODE_ELEMENT:
		printf("<%s>\n", getNodeName(node, NULL, 0)); break;
	case NODE_ATTRIBUTE:
		printf("%s=\"%s\"\n", 
			getNodeName(node, NULL, 0),
			getNodeValue(node, NULL, 0)); break;
	case NODE_TEXT:
		printf("\"%s\"\n", getNodeValue(node, NULL, 0)); break;
	}
}

void printNodeStack(NODESTACK* stk){
#if STACK_TRACE
	int i;
	printf("--NODE STACK (%d/%d) [", stk->cnt, stk->size);
	for( i=0; i<stk->cnt; i++){
		printf("%p", stk->stack[i]);
		if( i != (stk->cnt - 1) ) printf(" ");
	}
	printf("]\n");
#endif
}

void testNodeIterator(NODE* root){
	NODETREE_ITR* itr;
	int i;
	
	printf("\n");
	
	for( itr = createNodeIterator(root);
	nodeitrGetNode(itr) != NULL;
	nodeitrNext(itr)){
		printNodeStack(itr->stack);
		PRINTINDENT(nodeitrGetLevel(itr));
		printNode(nodeitrGetNode(itr), "\n");
	}
}


