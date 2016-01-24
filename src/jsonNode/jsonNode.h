#ifndef JSONNODE_H
#define JSONNODE_H

#ifndef NODECORE_H
#	include "../simpleElement/nodeCore.h"
#endif

#ifndef JSONDATA_H
#	include "jsonData.h"
#endif

#define JNODE_VALUE 1
#define JNODE_NAMENODE 2
#define JNODE_ARRAY 3
#define JNODE_OBJECT 4
#define JNODE_NULL 5

extern int DATAGET_CONVERT_STRICT;

struct s_jsoncontent{
	int ntype;
	JSONDATA* data;
};
typedef struct s_jsoncontent JCONTENT;


NODE* createJsonNode(void);
NODE* createJsonNodeByType(int type);

void destroyJsonNode(NODE* jnode);

void destroyJsonNodeTree(NODE* jnode);
void destroyJsonChildNodes(NODE* jnode);

/*node controls*/
int jnodeGetNodeType(NODE* jnode);
/*value node*/
NODE* jnodeSetJsonData(NODE* jnode, JSONDATA* jdata);
JSONDATA* jnodeGetJsonData(NODE* jnode);
char* jnodeGetDataString(NODE* jnode, char* buf, int blen);
/*name node*/
NODE*  jnodeSetName(NODE* jnode, char* str);
char* jnodeGetName(NODE* jnode);
/*array/object node*/
void jnodeAppendChild(NODE* jnode, NODE* apnd);
void jnodeInsertChild(NODE* jnode, int idx, NODE* apnd);
NODE* jnodeRemoveChild(NODE* jnode, int idx);
/* getChildNodeCount(NODE* node); nodecore function */

int checkJsonNodeType(NODE* jnode, int type);
void printJsonNode(NODE* jnode, int indent);
void traceJsonNodeTree(NODE* root, int level);

#define JN_INTEGER(val) jnodeSetJsonData(createJsonNode(), JD_INTEGER(val))
#define JN_FLOAT(val) jnodeSetJsonData(createJsonNode(), JD_FLOAT(val))
#define JN_STRING(str) jnodeSetJsonData(createJsonNode(), JD_STRING(str))
#define JN_BOOLEAN(val) jnodeSetJsonData(createJsonNode(), JD_BOOLEAN(val))

#endif
