#include <stdio.h>
#include "simpleElement/nodeCore.h"
#include "simpleElement/nodeIterator.h"
#include "simpleElement/simpleNode.h"

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
	
	printf("\n");
	testNodeIterator(n0);
	
	
	
#if 0
	removeChildNode(n4, n5);
	insertChildNode(n1, n5, n2);
	
	traceNodes(n0, 0);
	
	rdestroyNode(n0);
#endif
	

	return 0;
}


void printNode(NODE* node, char* tail){
	printf("(%d, %s, \"%s\")%s", 
		getNodeType(node),
		getNodeName(node, NULL, 0),
		getNodeValue(node, NULL, 0),
		tail);
}


void testNodeIterator(NODE* root){
	NODETREE_ITR* itr;
	int i;
	
	for( itr = createNodeIterator(root);
	nodeitrGetNode(itr) != NULL;
	nodeitrNext(itr)){
		PRINTINDENT(nodeitrGetLevel(itr));
		printNode(nodeitrGetNode(itr), "\n");
	}
}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
