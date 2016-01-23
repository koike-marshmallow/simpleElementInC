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
	void* value;
}
typedef struct s_jsoncontent JCONTENT;

typedef int JSON_DT_INT;
typedef double JSON_DT_FLOAT;
typedef char JSON_DT_STRING;
typedef int JSON_DT_BOOLEAN;


NODE* createJsonNode();
void initJsonNode(NODE* jnode);
void destroyJsonNode(NODE* jnode);

void json_setInt(NODE* jnode, JSON_DT_INT val);
void json_setFloat(NODE* jnode, JSON_DT_FLOAT val);
void json_setString(NODE* jnode, char* str);
void json_setBool(NODE* jnode, JSON_DT_BOOLEAN val);

void json_setNull(NODE* jnode);
void json_setObject(NODE* jnode, NODE* obj);
void json_arrayAppendNode(NODE* jnode, NODE* apnd);



