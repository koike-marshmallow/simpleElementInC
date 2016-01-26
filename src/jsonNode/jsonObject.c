#include <stdlib.h>
#include <string.h>
#include "../error/error.h"
#include "../simpleElement/nodeCore.h"
#include "jsonNode.h"
#include "jsonObject.h"

#define NULL_CHECK(p, fnc) ifassert((p == NULL), fnc, "ノードがnullです")
#define ARG_NULL_CHECK(p, fnc) ifassert((p == NULL), fnc, "引数がnullです")
#define CHECK_OBJECT(p, fnc) \
	ifassert(!checkJsonNodeType(p, JNODE_OBJECT), fnc, "OBJECTノードではありません")
#define CHECK_ARRAY(p, fnc) \
	ifassert(!checkJsonNodeType(p, JNODE_ARRAY), fnc, "ARRAYノードではありません")
#define ARY_ASSERT_NAMENODE(p, fnc) \
	ifassert(checkJsonNodeType(p, JNODE_NAMENODE), fnc, "NAMEノードは追加できません")
#define ARY_ASSERT_INDEX(idx, len, fnc) \
	ifassert((idx < 0 || idx >= len), fnc, "配列の範囲外の参照です")


NODE* createJsonObject(void){
	return createJsonNodeByType(JNODE_OBJECT);
}


NODE* createJsonArray(void){
	return createJsonNodeByType(JNODE_ARRAY);
}


void destroyJsonObject(NODE* jobj){
	destroyJsonNodeTree(jobj);
}


void destroyJsonArray(NODE* jary){
	destroyJsonNodeTree(jary);
}


NODE* jobjectGetMemberNode(NODE* obj, char* name, int *idx){
	int cnt;
	NODE* np;
	NULL_CHECK(obj, "jobjectGetMemberIndex");
	CHECK_OBJECT(obj, "jobjectGetMemberNode");
	
	cnt = 0;
	for( np = getFirstChildNode(obj);
	np != NULL;
	np = getNextSiblingNode(np) ){
		if( jnodeGetNodeType(np) == JNODE_NAMENODE ){
			if( strcmp(jnodeGetName(np), name) == 0 ){
				if( idx != NULL ) *idx = cnt;
				return np;
			}
		}
	}
	
	return NULL;
}


int jobjectMemberExist(NODE* obj, char* name){
	NULL_CHECK(obj, "jobjectMemberExist");
	CHECK_OBJECT(obj, "jobjectMemberExist");
	return jobjectGetMemberNode(obj, name, NULL) != NULL;
}


void jobjectSetMember(NODE* obj, char* name, NODE* node){
	NODE* member_node;
	NULL_CHECK(obj, "jobjectGetMemberIndex");
	CHECK_OBJECT(obj, "jobjectSetMember");
	
	member_node = jobjectGetMemberNode(obj, name, NULL);
	if( member_node == NULL ){
		member_node = JN_NAME(name);
		jnodeAppendChild(obj, member_node);
	}
	
	jnodeClearChild(member_node);
	jnodeAppendChild(member_node, node);
}


NODE* jobjectRemoveMember(NODE* obj, char* name){
	int position;
	NULL_CHECK(obj, "jobjectGetMemberIndex");
	CHECK_OBJECT(obj, "jobjectRemoveMember");
	
	if( jobjectGetMemberNode(obj, name, &position) != NULL ){
		return jnodeRemoveChild(obj, position);
	}
	return NULL;
}


int jobjectGetMemberCount(NODE* obj){
	NULL_CHECK(obj, "jobjectGetMemberCount");
	CHECK_OBJECT(obj, "jobjectGetMemberCount");
	
	return getChildNodeCount(obj);
}


int jobjectGetMemberList(NODE* obj, char* list, int list_len, int buf_len){
	char* cp;
	int cnt;
	NODE* np;
	NULL_CHECK(obj, "jobjectGetMemberList");
	CHECK_OBJECT(obj, "jobjectGetMemberList");
	
	memset(list, 0, sizeof(char) * (list_len * buf_len));
	cp = list;
	cnt = 0;
	for( np = getFirstChildNode(obj);
	(np != NULL) && (cnt < list_len);
	np = getNextSiblingNode(np) ){
		if( jnodeGetNodeType(np) == JNODE_NAMENODE ){
			strncpy(cp, jnodeGetName(np), buf_len - 1);
			cp = cp + buf_len;
			cnt++;
		}
	}
	
	return cnt;
}


NODE* jobjectGetMember(NODE* obj, char* name){
	NODE* member_node;
	NULL_CHECK(obj, "jobjectGetMember");
	CHECK_OBJECT(obj, "jobjectGetMember");
	
	member_node = jobjectGetMemberNode(obj, name, NULL);
	if( member_node != NULL ){
		return getFirstChildNode(member_node);
	}
	return NULL;
}


void jarrayAppend(NODE* ary, NODE* node){
	NULL_CHECK(ary, "jarrayAppend");
	CHECK_ARRAY(ary, "jarrayAppend");
	
	ARY_ASSERT_NAMENODE(node, "jarrayAppend");
	jnodeAppendChild(ary, node);
}


void jarrayInsert(NODE* ary, int idx, NODE* node){
	NULL_CHECK(ary, "jarrayInsert");
	CHECK_ARRAY(ary, "jarrayInsert");
	
	ARY_ASSERT_NAMENODE(node, "jarrayInsert");
	ARY_ASSERT_INDEX(idx, getChildNodeCount(ary), "jarrayInsert");
	jnodeInsertChild(ary, idx, node);
}


void jarraySet(NODE* ary, int idx, NODE* node){
	NULL_CHECK(ary, "jarraySet");
	CHECK_ARRAY(ary, "jarraySet");
	
	ARY_ASSERT_NAMENODE(node, "jarraySet");	
	ARY_ASSERT_INDEX(idx, getChildNodeCount(ary), "jarraySet");
	jnodeRemoveChild(ary, idx);
	jnodeInsertChild(ary, idx, node);
}


NODE* jarrayRemove(NODE* ary, int idx){
	NULL_CHECK(ary, "jarrayRemove");
	CHECK_ARRAY(ary, "jarrayRemove");
	
	ARY_ASSERT_INDEX(idx, getChildNodeCount(ary), "jarrayRemove");
	return jnodeRemoveChild(ary, idx);
}


NODE* jarrayGet(NODE* ary, int idx){
	int cnt;
	NODE* np;
	NULL_CHECK(ary, "jarrayGet");
	CHECK_ARRAY(ary, "jarrayGet");
	
	ARY_ASSERT_INDEX(idx, getChildNodeCount(ary), "jarrayGet");
	cnt = 0;
	for( np = getFirstChildNode(ary);
	np != NULL && cnt < idx;
	np = getNextSiblingNode(np) ){
		idx++;
	}
	return np;
}


int jarrayGetLength(NODE* ary){
	NULL_CHECK(ary, "jarrayGetLength");
	CHECK_ARRAY(ary, "jarrayGetLength");
	
	return getChildNodeCount(ary);
}
	
	
NODE* jsonMemberIteratorGetHead(NODE* jobj){
	int ntype;
	NULL_CHECK(jobj, "jsonMemberIteratorGetHead");
	ntype = jnodeGetNodeType(jobj);
	if( ntype != JNODE_ARRAY && ntype != JNODE_OBJECT ) return NULL;
	return getFirstChildNode(jobj);
}


NODE* jsonMemberIteratorNext(NODE* ch){
	NULL_CHECK(ch, "jsonMemberIteratorNext");
	return getNextSiblingNode(ch);
}


char* jobjectGetMemberName(NODE* node){
	NULL_CHECK(node, "jobjectGetMemberName");
	ifassert(!checkJsonNodeType(node, JNODE_NAMENODE),
		"jobjectGetMemberName", "NAMEノードではありません");
	
	return jnodeGetName(node);
}


NODE* jobjectGetMemberData(NODE* node){
	NULL_CHECK(node, "jobjectGetMemberValue");
	
	if( checkJsonNodeType(node, JNODE_NAMENODE) ){
		return getFirstChildNode(node);
	}
	return node;
}
	
	



		
	
	
























	
	
