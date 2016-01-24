#ifndef JSONOBJECT_H
#define JSONOBJECT_H

#ifndef NODECORE_H
# include "../simpleElement/nodeCore.h"
#endif

#ifndef JSONNODE_H
# include "jsonNode.h"
#endif


NODE* createJsonObject();
NODE* createJsonArray();

void destroyJsonNodeTree(NODE* jnode);
void destroyJsonChildNodes(NODE* jnode);
void destroyJsonObject(NODE* jobj);
void destroyJsonArray(NODE* jary);

void addJsonObjectMember(char* name, JCONTENT content);

