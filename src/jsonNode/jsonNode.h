#ifndef JSONNODE_H
#define JSONNODE_H

#ifndef NODECORE_H
#	include "../simpleElement/nodeCore.h"
#endif

#define JNODE_VALUE 1
#define JNODE_ARRAY 2
#define JNODE_OBJECT 3
#define JNODE_NULL 4

extern int DATAGET_CONVERT_STRICT;

struct s_jsoncontent{
	int ntype;
	char* name;
	JSONDATA* data;
}
typedef struct s_jsoncontent JCONTENT;


NODE* createJsonNode();
void initJsonNode(NODE* jnode);
void destroyJsonNode(NODE* jnode);
void clearJsonNode(NODE* jnode);

void jnodeSetName(NODE* jnode char* str);
char* jnodeSetName(NODE* jnode);

NODE* jnodeSetJsonData(NODE* jnode, JSONDATA* data);
NODE* jnodeSetNull(NODE* jnode);
NODE* jnodeSetObject(NODE* jnode, NODE* obj);
NODE* jnodeSetArray(NODE* jnode, NODE* ary);

int jnodeGetDataType(NODE* jnode);
JSONDATA* jnodeGetJsonData(NODE* jnode);
char* jnodeGetDataString(NODE* jnode, char* buf, int blen);

NODE* jnodeGetObject(NODE* jnode);
NODE* jnodeGetArray(NODE* jnode);

/*
void jnodeInsertChild(NODE* jnode, int idx, NODE* child);
void jnodeAppendChild(NODE* jnode, NODE* child);
NODE* jnodeRemoveChild(NODE* jnode, int idx);
*/
