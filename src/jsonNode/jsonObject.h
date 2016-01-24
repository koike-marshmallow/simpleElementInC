#ifndef JSONOBJECT_H
#define JSONOBJECT_H

#ifndef NODECORE_H
#	include "../simpleElement/nodeCore.h"
#endif

#ifndef JSONDATA_H
#	include "jsonData.h"
#endif

#ifndef JSONNODE_H
#	include "jsonNode.h"
#endif


NODE* createJsonObject();
NODE* createJsonArray();

void destroyJsonObject(NODE* jobj);
void destroyJsonArray(NODE* jary);

void clearJsonObject(NODE* jobj);
void clearJsonArray(NODE* jary);

/* Object cotrol function */
void jobjectSetMember(NODE* obj, char* name, NODE* node);
void jobjectDeleteMember(NODE* obj, char* name);
int jobjectGetMemberCount(NODE* obj);
int jobjectGgeMemberList(NODE* obj, char* buffer, char* list[], int buf_len, int list_len);
NODE* jobjectGetMember(NODE* obj, char* name);

/* ArrayControl Function */
void jarrayAppend(NODE* ary, NODE* node);
void jarrayInsert(NODE* ary, int idx, NODE* node);
void jarraySet(NODE* ary, int idx, NODE* node);
void jarrayDelete(NODE* ary, int idx);
void jarrayGetLength(NODE* ary);

/* Iterate Function */
NODE* jobjectGetHeadNode(NODE* jobj);
NODE* jobjectGetNextNode(NODE* jobj);
NODE* jarrayGetHeadNode(NODE* jary);
NODE* jarrayGetNextNode(NODE* jary);
char* jobjectGetMemberName(NODE* node);
NODE* jobjectGetMemberData(NODE* node);


