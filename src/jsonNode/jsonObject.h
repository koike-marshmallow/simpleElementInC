#ifndef JSONOBJECT_H
#define JSONOBJECT_H

#ifndef NODECORE_H
#	include "../simpleElement/nodeCore.h"
#endif

#ifndef JSONNODE_H
#	include "jsonNode.h"
#endif

#define JN_MEMBER(name, node) jnodeAppendChild(JN_NAME(name), node)

NODE* createJsonObject(void);
NODE* createJsonArray(void);

void destroyJsonObject(NODE* jobj);
void destroyJsonArray(NODE* jary);

/*void clearJsonObject(NODE* jobj);*/
/*void clearJsonArray(NODE* jary);*/

/* Object cotrol function */
int jobjectGetMembeNode(NODE* obj, char* name, int* idx);
int jobjectMemberExist(NODE* obj, char* name);
void jobjectSetMember(NODE* obj, char* name, NODE* node);
NODE* jobjectRemoveMember(NODE* obj, char* name);
int jobjectGetMemberCount(NODE* obj);
int jobjectGetMemberList(NODE* obj, char* buffer, char* list[], int buf_len, int list_len);
NODE* jobjectGetMember(NODE* obj, char* name);

/* ArrayControl Function */
void jarrayAppend(NODE* ary, NODE* node);
void jarrayInsert(NODE* ary, int idx, NODE* node);
void jarraySet(NODE* ary, int idx, NODE* node);
NODE* jarrayRemove(NODE* ary, int idx);
NODE* jarrayGet(NODE* ary, int idx);
int jarrayGetLength(NODE* ary);

/* Iterate Function */
NODE* jobjectGetHeadNode(NODE* jobj);
NODE* jobjectGetNextNode(NODE* jobj);
NODE* jarrayGetHeadNode(NODE* jary);
NODE* jarrayGetNextNode(NODE* jary);
char* jobjectGetMemberName(NODE* node);
NODE* jobjectGetMemberData(NODE* node);

#endif
