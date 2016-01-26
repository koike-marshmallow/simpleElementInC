#include <stdio.h>
#include "jsonNode/jsonNode.h"
#include "jsonNode/jsonObject.h"

int main(void){
	NODE *obj0;
	NODE *obj1;
	NODE *ary1, *ary2;
	
	obj0 = createJsonObject();
	obj1 = createJsonObject();
	ary1 = createJsonArray();
	ary2 = createJsonArray();
	
	jobjectSetMember(obj0, "foo", ary1);
	jobjectSetMember(obj0, "baz", obj1);
	jobjectSetMember(obj1, "foo", ary2);
	jobjectSetMember(obj1, "baz", JN_STRING("qux"));
	jarrayAppend(ary1, JN_INTEGER(1));
	jarrayAppend(ary1, JN_NULL);
	jarrayAppend(ary2, JN_BOOLEAN(TRUE));
	jarrayAppend(ary2, JN_STRING("bar"));
	
	traceJsonNodeTree(obj0, 0);
	
	destroyJsonNodeTree(obj0);
	
	return 0;
}
