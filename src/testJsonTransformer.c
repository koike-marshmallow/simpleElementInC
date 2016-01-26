#include <stdio.h>
#include "jsonNode/jsonNode.h"
#include "jsonNode/jsonObject.h"
#include "stringBuffer/stringBuffer.h"

int main(void){
	NODE *obj0;
	NODE *obj1;
	NODE *ary1, *ary2;
	STRBUF* strb;
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
	
	strb = createStringBuffer(4096);
	transformJson(strb, obj0);
	printStringBufferInfo(strb);
	
	if( (fp = fopen("output.json", "w")) != NULL ){
		fprintf(fp, "%s", sbGetString(strb, NULL, 0));
		fclose(fp);
	}
	
	destroyJsonNodeTree(obj0);
	
	return 0;
}
