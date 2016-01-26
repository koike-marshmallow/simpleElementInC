#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../error/error.h"
#include "../simpleElement/nodeCore.h"
#include "jsonData.h"
#include "jsonNode.h"

#define NULL_CHECK(p, fnc) ifassert((p == NULL), fnc, "ノードがNULLです")


NODE* createJsonNode(void){
	NODE* new_node;
	JCONTENT* new_content;
	
	new_node = createNodeCore();
	new_content = malloc(sizeof(JCONTENT));
	ifassert((new_content == NULL), "createJsonNode", "jsonノード生成に失敗しました");
	setNodeContent(new_node, new_content);
	
	new_content->ntype = JNODE_NULL;
	new_content->data = NULL;
	
	return new_node;
}


NODE* createJsonNodeByType(int type){
	NODE* new_node;
	
	new_node = createJsonNode();
	((JCONTENT*)getNodeContent(new_node))->ntype = type;
	
	return new_node;
}


void destroyJsonNode(NODE* jnode){
	JCONTENT* jcontent;
	NULL_CHECK(jnode, "destroyJsonNode");
	
	jcontent = getNodeContent(jnode);
	if( jcontent->data != NULL ){
		destroyJsonData(jcontent->data);
	}
	
	memset(jcontent, 0, sizeof(JCONTENT));
	free(jcontent);
	
	destroyNodeCore(jnode);
}


void destroyJsonNodeTree(NODE* jnode){
	NULL_CHECK(jnode, "destroyJsonNodeTree");
	
	destroyJsonChildNodes(jnode);
	destroyJsonNode(jnode);
}


void destroyJsonChildNodes(NODE* jnode){
	NODE *np, *next_np;
	NULL_CHECK(jnode, "destroyJsonChildNodes");
	
	next_np = getFirstChildNode(jnode);
	while( next_np != NULL ){
		np = next_np;
		next_np = getNextSiblingNode(next_np);
		
		destroyJsonNodeTree(np);
	}
}


int jnodeGetNodeType(NODE* jnode){
	NULL_CHECK(jnode, "jnodeGetNodeType");
	
	return ((JCONTENT*)getNodeContent(jnode))->ntype;
}


NODE* jnodeSetJsonData(NODE* jnode, JSONDATA* jdata){
	int ntype;
	JCONTENT* jcontent;
	NULL_CHECK(jnode, "jnodeSetJsonData");
	ifassert((jdata == NULL), "jnodeSetJsonData", "データがnullです");
	
	ntype = jnodeGetNodeType(jnode);
	if( ntype == JNODE_NULL || ntype == JNODE_VALUE ){
		jcontent = getNodeContent(jnode);
		jcontent->ntype = JNODE_VALUE;
		jcontent->data = jdata;
	}else{
		fnerror("jnodeSetJsonData", "VALUEノードではありません");
	}
	
	return jnode;
}


JSONDATA* jnodeGetJsonData(NODE* jnode){
	NULL_CHECK(jnode, "jnodeGetJsonData");
	ifassert(!checkJsonNodeType(jnode, JNODE_VALUE), 
		"jnodeGetJsonData", "VALUEノードではありません");
	
	return ((JCONTENT*)getNodeContent(jnode))->data;
}


char* jnodeGetDataString(NODE* jnode, char* buf, int blen){
	JSONDATA* data;
	NULL_CHECK(jnode, "jnodeGetDataString");
	ifassert((buf == NULL), 
		"jnodeGetDataString", "宛先バッファがNULLです");
	
	if( checkJsonNodeType(jnode, JNODE_NULL) ){
		sprintf(buf, "null");
		return buf;
	}
	
	ifassert(!checkJsonNodeType(jnode, JNODE_VALUE),
		"jnodeGetDataString", "VALUEノードではありません");
	
	data = jnodeGetJsonData(jnode);
	
	switch( jdataGetType(data) ){
	case JDTYPE_NULL:
		sprintf(buf, "null");
		break;
	case JDTYPE_INTEGER:
		sprintf(buf, "%d", jdataGetInt(data));
		break;
	case JDTYPE_FLOAT:
		sprintf(buf, "%f", jdataGetFloat(data));
		break;
	case JDTYPE_STRING:
		strncpy(buf, "\"", blen - 1);
		strncat(buf, jdataGetString(data), blen - 3);
		strncat(buf, "\"", blen - 2);
		break;
	case JDTYPE_BOOLEAN:
		if( jdataGetBool(data) == FALSE ) sprintf(buf, "false");
		else sprintf(buf, "true");
		break;
	default:
		fnerror("jnodeGetDataString", "JSONDATAが未定義のデータ型です");
		break;
	}
	
	return buf;
}


NODE* jnodeSetName(NODE* jnode, char* str){
	int ntype;
	JCONTENT* jcontent;
	NULL_CHECK(jnode, "jnodeSetName");
	
	ntype = jnodeGetNodeType(jnode);
	if( ntype == JNODE_NULL || ntype == JNODE_NAMENODE ){
		jcontent = getNodeContent(jnode);
		jcontent->ntype = JNODE_NAMENODE;
		jcontent->data = JD_STRING(str);
	}else{
		fnerror("jnodeSetName", "NAMEノードではありません");
	}
	
	return jnode;
}


char* jnodeGetName(NODE* jnode){
	NULL_CHECK(jnode, "jnodeGetName");
	ifassert(!checkJsonNodeType(jnode, JNODE_NAMENODE), 
		"jnodeGetName", "NAMENODEではありません");
	
	return jdataGetString(((JCONTENT*)getNodeContent(jnode))->data);
}


void jnodeAppendChild(NODE* jnode, NODE* apnd){
	NULL_CHECK(jnode, "jnodeAppendChild");
	ifassert((apnd == NULL), "jnodeAppendChild", "NULLの追加は許可されていません");
	
	switch( jnodeGetNodeType(jnode) ){
	case JNODE_ARRAY:
	case JNODE_OBJECT:
	case JNODE_NAMENODE:
		insertLinkedNodeSibling(getLinkedNodeSibtailPNP(jnode), apnd);
		break;
	default:
		fnerror("jnodeAppendChild", "OBJECT/ARRAY/NAMENODEではありません");
		break;
	}
}


void jnodeInsertChild(NODE* jnode, int idx, NODE* apnd){
	NODE** pnp;
	NULL_CHECK(jnode, "jnodeInsertChild");
	ifassert((apnd == NULL), "jnodeInsertChild", "NULLの追加は許可されていません");
	
	switch( jnodeGetNodeType(jnode) ){
	case JNODE_ARRAY:
	case JNODE_OBJECT:
		pnp = getLinkedNodeSibidxPNP(jnode, idx);
		ifassert((pnp == NULL), "jnodeInsertChild", "挿入位置を特定できません");
		insertLinkedNodeSibling(pnp, apnd);
		break;
	default:
		fnerror("jnodeInsertChild", "OBJECT/ARRAYノードではありません");
		break;
	}
}


NODE* jnodeRemoveChild(NODE* jnode, int idx){
	NODE** pnp;
	NULL_CHECK(jnode, "jnodeRemoveChild");
	
	switch( jnodeGetNodeType(jnode) ){
	case JNODE_ARRAY:
	case JNODE_OBJECT:
	case JNODE_NAMENODE:
		pnp = getLinkedNodeSibidxPNP(jnode, idx);
		ifassert((pnp == NULL), "jnodeRemoveChild", "削除位置を特定できません");
		return removeLinkedNodeSibling(pnp);
	default:
		fnerror("jnodeRemoveChild", "OBJECT/ARRAY/NAMENODEではありません");
		break;
	}
	return NULL;
}


void jnodeClearChild(NODE* jnode){
	NODE** pnp;
	NULL_CHECK(jnode, "jnodeClearChild");
	
	switch( jnodeGetNodeType(jnode) ){
	case JNODE_ARRAY:
	case JNODE_OBJECT:
	case JNODE_NAMENODE:
		pnp = getLinkedNodeSibidxPNP(jnode, 0);
		while( *pnp != NULL ){
			removeLinkedNodeSibling(pnp);
		}
		break;
	default:
		fnerror("jnodeClearChild", "OBJECT/ARRAY/NAMENODEではありません");
		break;
	}
}
			


int checkJsonNodeType(NODE* jnode, int type){
	NULL_CHECK(jnode, "checkJsonNodeType");
	
	return jnodeGetNodeType(jnode) == type;
}


#define PRINT_INDENT(n) for( i=0; i<n; i++) printf(" ");

void printJsonNode(NODE* jnode, int indent){
	int i;
	JCONTENT* jcontent;
	char type[32], data[128];
	NULL_CHECK(jnode, "printJsonNode");
	
	jcontent = getNodeContent(jnode);
	switch( jnodeGetNodeType(jnode) ){
	case JNODE_VALUE:
		strcpy(type, "VALUE");
		jnodeGetDataString(jnode, data, 128);
		break;
	case JNODE_NAMENODE:
		strcpy(type, "NAME NODE");
		strncpy(data, jnodeGetName(jnode), 127);
		break;
	case JNODE_ARRAY:
		strcpy(type, "ARRAY");
		sprintf(data, "(NODE COUNT (%d))", getChildNodeCount(jnode));
		break;
	case JNODE_OBJECT:
		strcpy(type, "OBJECT");
		sprintf(data, "(NODE COUNT (%d))", getChildNodeCount(jnode));
		break;
	case JNODE_NULL:
		strcpy(type, "NULL NODE");
		strcpy(data, "");
		break;
	}
	
	PRINT_INDENT(indent);
	printf("node type  : %s[%d]\n", type, jnodeGetNodeType(jnode));
	PRINT_INDENT(indent);
	printf("node value : %s\n", data);
	
}


void traceJsonNodeTree(NODE* root, int level){
	NODE* np;
	NULL_CHECK(root, "traceJsonNodeTree");
	
	printJsonNode(root, level * 2);
	
	for( np = getFirstChildNode(root);
	np != NULL;
	np = getNextSiblingNode(np) ){
		traceJsonNodeTree(np, level + 1);
	}
}
	
	
	
	
	
		










	
	
	
