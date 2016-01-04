#include <stdio.h>
#include "simpleElement/nodeCore.h"


int main(void){
	NODE *n1, *n2, *n3;
	
	n1 = createNode(NODE_ELEMENT);
	n2 = createNode(NODE_ATTRIBUTE);
	n3 = createNode(NODE_TEXT);
	
	setNodeName(n1, "test");
	appendChildNode(n1, n2);
	appendChildNode(n1, n3);
	setNodeName(n2, "stuff");
	setNodeValue(n2, "this node is attribute");
	setNodeValue(n3, "This is node core test");
	
	
	traceNodes(n1, 0);

	return 0;
}
