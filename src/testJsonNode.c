#include <stdio.h>
#include "simpleElement/nodeCore.h"
#include "jsonNode/jsonData.h"
#include "jsonNode/jsonNode.h"

int main(void){
	NODE *obj0;
	NODE *obj1;
	NODE *name01, *name02, *name11, *name12;
	NODE *ary1, *ary2;
	NODE *n1, *n2, *n3, *n4, *n5;
	
	obj0 = createJsonNodeByType(JNODE_OBJECT);
	obj1 = createJsonNodeByType(JNODE_OBJECT);
	ary1 = createJsonNodeByType(JNODE_ARRAY);
	ary2 = createJsonNodeByType(JNODE_ARRAY);
	n1 = JN_INTEGER(1);
	n2 = createJsonNodeByType(JNODE_NULL);
	n3 = JN_BOOLEAN(TRUE);
	n4 = JN_STRING("bar");
	n5 = JN_STRING("qux");
	name01 = jnodeSetName(createJsonNode(), "foo");
	name02 = jnodeSetName(createJsonNode(), "baz");
	name11 = jnodeSetName(createJsonNode(), "foo");
	name12 = jnodeSetName(createJsonNode(), "baz");
	
	jnodeAppendChild(obj0, name01);
	jnodeAppendChild(obj0, name02);
	jnodeAppendChild(name01, ary1);
	jnodeAppendChild(ary1, n1);
	jnodeAppendChild(ary1, n2);
	jnodeAppendChild(name02, obj1);
	jnodeAppendChild(obj1, name11);
	jnodeAppendChild(obj1, name12);
	jnodeAppendChild(name11, ary2);
	jnodeAppendChild(ary2, n3);
	jnodeAppendChild(ary2, n4);
	jnodeAppendChild(name12, n5);

	
	traceJsonNodeTree(obj0, 0);
	
	destroyJsonNodeTree(obj0);
	
	return 0;
}
