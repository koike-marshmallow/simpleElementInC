#ifndef JSONNODE_H
#define JSONNODE_H

#ifndef NODECORE_H
#	include "../nodeCore.h"
#endif

#define DTYPE_INTEGER 1
#define DTYPE_FLOAT 2
#define DTYPE_STRING 3
#define DTYPE_BOOLEAN 4
#define DTYPE_ARRAY 5
#define DTYPE_OBJECT 6
#define DTYPE_NULL 7

#define JSON_STRBUF 256

struct s_jsoncontent{
	int dtype;
	char* name;
	void* value;
}
typedef struct s_jsoncontent JCONTENT;

typedef int JNODE_DT_INT;
typedef double JNODE_DT_FLOAT;
typedef char JNODE_DT_STRING;
typedef int JNODE_DT_BOOLEAN;


NODE* createJsonNode();
void initJsonNode(NODE* jnode);
void destroyJsonNode(NODE* jnode);

void jnode_setName(NODE* jnode char* str);
char* jnode_getNmae(NODE* jnode);

void jnode_setInt(NODE* jnode, JNODE_DT_INT val);
void jnode_setFloat(NODE* jnode, JNODE_DT_FLOAT val);
void jnode_setString(NODE* jnode, char* str);
void jnode_setBool(NODE* jnode, JNODE_DT_BOOLEAN val);

void jnode_setNull(NODE* jnode);
void jnode_setObject(NODE* jnode, NODE* obj);
void jnode_setArray(NODE*: jnode, NODE* ary);

int jnode_getType(NODE* jnode);
JSON_DT_INT jnode_getInt(NODE* jnode);
JSON_DT_FLOAT jnode_getFloat(NODE* jnode);
char* jnode_getString(NODE* jnode);
JSON_DT_BOOLEAN jnode_getBool(NODE* jnode);

NODE* jnode_getObject(NODE* jnode);
NODE* jnode_getArray(NODE* jnode);

void jnode_insertChild(NODE* jnode, int idx, NODE* child);
void jnode_appendChild(NODE* jnode, NODE* child);
NODE* jnode_removeChild(NODE* jnode, int idx);

void clearValue(NODE* jnode);
