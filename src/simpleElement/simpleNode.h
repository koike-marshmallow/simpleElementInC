#ifndef SIMPLENODE_H
#define SIMPLENODE_H

#ifndef NODECORE_H
#	include "nodeCore.h"
#endif

#ifndef NODEITERATOR_H
#	include "nodeIterator.h"
#endif


#define NODE_ELEMENT 1
#define NODE_ATTRIBUTE 2
#define NODE_TEXT 3

#define NODE_NAME_LEN 64
#define NODE_VALUE_LEN 256


/* Node creator */
NODE* createNode(int type);
void initNode(NODE* node, int type);

/* Node destroyer */
void destroyNode(NODE* node);
void recursiveDestroyNodes(NODE* node);
void destroyChildNodes(NODE* node);

/* Node content controller */
void setNodeType(NODE* node, int typec);
void setNodeName(NODE* node, char* name);
void setNodeValue(NODE* node, char* value);
int getNodeType(NODE* node);
char* getNodeName(NODE* node, char* buf, int len);
char* getNodeValue(NODE* node, char* buf, int len);

/* Node childnode controller */
void appendChildNode(NODE* node, NODE* apnd);
void insertChildNode(NODE* node, int idx, NODE* isrt);
NODE* removeChildNode(NODE* node, int idx);

/* debug */
void printNodeInfo(NODE* node, int indent);
void traceNodes(NODE* node, int indent);
