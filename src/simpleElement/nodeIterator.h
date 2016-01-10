#ifndef NODEITERATOR_H
#define NODEITERATOR_H

#ifndef NODECORE_H
#	include "nodeCore.h"
#endif

struct s_nodestack {
	NODE** stack;
	int size;
	int cnt;
};
typedef struct s_nodestack NODESTACK;

struct s_nodeiterator {
	NODESTACK* stack;
	NODE* ptr;
};
typedef struct s_nodeiterator NODETREE_ITR;


extern int NODEITERATOR_INIT_STACKLEN;


NODESTACK* createNodeStack(int s);
void initNodeStack(NODESTACK* ns);
void destroyNodeStack(NODESTACK* ns);

void nodeStackPush(NODESTACK* ns, NODE* node);
NODE* nodeStackPop(NODESTACK* ns);
NODE* nodeStackRetrieve(NODESTACK* ns);

int getNodeStackCount(NODESTACK* ns);
int isNodeStackFull(NODESTACK* ns);
int isNodeStackEmpty(NODESTACK* ns);


NODETREE_ITR* createNodeIterator(NODE* root);
void initNodeIterator(NODETREE_ITR* itr, NODE* root);
void destroyNodeIterator(NODETREE_ITR* itr);

NODE* nodeitrNext(NODETREE_ITR* itr);
NODE* nodeitrGet(NODETREE_ITR* itr);

#endif
