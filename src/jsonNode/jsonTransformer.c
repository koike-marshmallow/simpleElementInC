#include <stdio.h>
#include <stdlib.h>
#include "../stringBuffer/stringBuffer.h"
#include "../error/error.h"
#include "jsonData.h"
#include "jsonNode.h"
#include "jsonObject.h"

#define VALUEBUF_LEN 32

#define STRBUF_REARNULL_LEN(strbuf) \
	(sbGetLimitStringLength(strbuf) - sbGetStringLength(strbuf) + 1)
#define NULL_CHECK(sb, np, fnc) \
	ifassert((sb == NULL), fnc, "出力先バッファがnullです"); \
	ifassert((np == NULL), fnc, "jsonノードがnullです");
#define SPRINTF_ASSERT(ret, limit, fnc) \
	ifassert((ret >= limit), fnc, "VALUEバッファがオーバーフローしました")

char JT_VALUE_BUFFER[VALUEBUF_LEN];

void jt_transformValueNode(STRBUF* dst, NODE* val_node, int level){
	JSONDATA* data;
	NULL_CHECK(dst, val_node, "jt_transformValueNode");
	
	ifassert(!checkJsonNodeType(val_node, JNODE_VALUE),
		"jt_transformValueNode", "VALUEノードではありません");
	
	data = jnodeGetJsonData(val_node);
	switch( jdataGetType(data) ){
	case JDTYPE_NULL:
		sbCatString(dst, "null");
		break;
	case JDTYPE_INTEGER:
		SPRINTF_ASSERT(
			snprintf(JT_VALUE_BUFFER, VALUEBUF_LEN, "%d", jdataGetInt(data)),
			VALUEBUF_LEN, "jt_transformValueNode"
		);
		sbCatString(dst, JT_VALUE_BUFFER);
		break;
	case JDTYPE_FLOAT:
		SPRINTF_ASSERT(
			snprintf(JT_VALUE_BUFFER, VALUEBUF_LEN, "%f", jdataGetFloat(data)),
			VALUEBUF_LEN, "jt_transformValueNode"
		);
		sbCatString(dst, JT_VALUE_BUFFER);
		break;
	case JDTYPE_STRING:
		sbCatString(dst, "\"");
		sbCatString(dst, jdataGetString(data));
		sbCatString(dst, "\"");
		break;
	case JDTYPE_BOOLEAN:
		if( jdataGetBool(data) ) sbCatString(dst, "true");
		else sbCatString(dst, "false");
		break;
	default:
		fnerror("jt_transformValueNode", "不正なVALUEノードが検出されました");
		break;
	}
}


void jt_transformNameNode(STRBUF* dst, NODE* name_node, int level){
	NULL_CHECK(dst, name_node, "jt_transformNameNode");
	ifassert(!checkJsonNodeType(name_node, JNODE_NAMENODE),
		"jt_transformNameNode", "NAMEノードではありません");
	
	sbCatString(dst, "\"");
	sbCatString(dst, jobjectGetMemberName(name_node));
	sbCatString(dst, "\": ");
	
	jt_transformDataNode(dst, jobjectGetMemberValue(name_node), level);
}


void jt_transformArray(STRBUF* dst, NODE* ary_node, int level){
	int comma;
	NODE* np;
	NULL_CHECK(dst, ary_node, "jt_transformArray");
	ifassert(!checkJsonNodeType(ary_node, JNODE_ARRAY),
		"jt_transformArray", "ARRAYノードではありません");
	
	sbCatString(dst, "[");
	comma = FALSE;
	for( np = jsonMemberIteratorGetHead(ary_node);
	np != NULL;
	np = jsonMemberIteratorNext(np) ){
		if( comma ) sbCatString(dst, ", ");
		jt_transformDataNode(dst, np, level + 1);
		comma = TRUE;
	}
	sbCatString(dst, "]");
}


void jt_transformObject(STRBUF* dst, NODE* obj_node, int level){
	int comma;
	NODE* np;
	NULL_CHECK(dst, obj_node, "jt_transformObject");
	ifassert(!checkJsonNodeType(obj_node, JNODE_OBJECT),
		"jt_transformObject", "OBJECTノードではありません");
	
	sbCatString(dst, "{");
	for( np = jsonMemberIteratorGetHead(obj_node);
	np != NULL;
	np = jsonMemberIteratorNext(np) ){
		if( comma ) sbCatString(dst, ", ");
		if( checkJsonNodeType(np, JNODE_NAMENODE) ){
			jt_transformNameNode(dst, np, level + 1);
		}else{
			fnerror("jt_transformObject", "メンバでないノードを検出しました");
		}
		comma = TRUE;
	}
	sbCatString(dst, "}");
}


void jt_transformDataNode(STRBUF* dst, NODE* j_node, int level){
	NULL_CHECK(dst, obj_node, "jt_transformNode");
	
	switch( jnodeGetNodeType(j_node) ){
	case JNODE_VALUE:
		jt_transformValueNode(dst, j_node, level);
		break;
	case JNODE_NAMENODE:
		fnerror("jt_transformNode", "NAMEノードはオブジェクトの中でのみ有効です");
		break;
	case JNODE_ARRAY:
		jt_transformArray(dst, j_node, level);
		break;
	case JNODE_OBJECT:
		jt_transformObject(dst, j_node, level);
		break;
	case JNODE_NULL:
		sbCatString(dst, "null");
		break;
	}
}


void transformJson(STRBUF* dest, NODE* root){
	NULL_CHECK(dest, root, "transformJson");
	
	jt_transformDataNode(dest, root, 0);
}
