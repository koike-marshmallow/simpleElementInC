#include <stdio.h>
#include "jsonNode/jsonNode.h"
#include "jsonNode/jsonObject.h"
#include "jsonNode/jsonTransformer.h"
#include "stream/outputStream.h"

int main(void){
	NODE *obj0;
	NODE *obj1;
	NODE *ary1, *ary2;
	OUTSTREAM* stream;
	FILE* fp;
	
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
	
	stream = createFileOutputStream(fopen("output.json", "w"));
	JT_LINEFEED = 1;
	JT_INDENT = 1;
	transformJson(stream, obj0);
	printf("\n");
	
	destroyJsonNodeTree(obj0);
	
	return 0;
}
