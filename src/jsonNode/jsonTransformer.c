#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../simpleElement/nodeCore.h"
#include "../stream/outputStream.h"
#include "../error/error.h"
#include "jsonData.h"
#include "jsonNode.h"
#include "jsonObject.h"
#include "jsonTransformer.h"

#define VALUEBUF_LEN 32

#define NULL_CHECK(sb, np, fnc) \
	ifassert((sb == NULL), fnc, "出力先ストリームがnullです"); \
	ifassert((np == NULL), fnc, "jsonノードがnullです");
#define SPRINTF_ASSERT(ret, limit, fnc) \
	ifassert((ret >= limit), fnc, "VALUEバッファがオーバーフローしました")

#define STREAM_WRITES(stream, str) \
	outstream_writes(stream, str)
#define STREAM_WRITEC(stream, c) outstream_writec(stream, c)

int JT_INDENT = 0;
int JT_LINEFEED = 0;
char* JT_INDENT_CHAR = "  ";

char JT_VALUE_BUFFER[VALUEBUF_LEN];


void jtIndent(OUTSTREAM* dst, int level){
	int i;
	if( JT_INDENT ){
		for( i=0; i<level; i++){
			STREAM_WRITES(dst, JT_INDENT_CHAR);
		}
	}
}


void jtLinefeed(OUTSTREAM* dst){
	if( JT_LINEFEED ){
		STREAM_WRITEC(dst, '\n');
	}
}


void jt_transformValueNode(OUTSTREAM* dst, NODE* val_node, int level){
	JSONDATA* data;
	NULL_CHECK(dst, val_node, "jt_transformValueNode");
	
	ifassert(!checkJsonNodeType(val_node, JNODE_VALUE),
		"jt_transformValueNode", "VALUEノードではありません");
	
	data = jnodeGetJsonData(val_node);
	switch( jdataGetType(data) ){
	case JDTYPE_NULL:
		STREAM_WRITES(dst, "null");
		break;
	case JDTYPE_INTEGER:
		SPRINTF_ASSERT(
			snprintf(JT_VALUE_BUFFER, VALUEBUF_LEN, "%d", jdataGetInt(data)),
			VALUEBUF_LEN, "jt_transformValueNode"
		);
		STREAM_WRITES(dst, JT_VALUE_BUFFER);
		break;
	case JDTYPE_FLOAT:
		SPRINTF_ASSERT(
			snprintf(JT_VALUE_BUFFER, VALUEBUF_LEN, "%f", jdataGetFloat(data)),
			VALUEBUF_LEN, "jt_transformValueNode"
		);
		STREAM_WRITES(dst, JT_VALUE_BUFFER);
		break;
	case JDTYPE_STRING:
		STREAM_WRITES(dst, "\"");
		STREAM_WRITES(dst, jdataGetString(data));
		STREAM_WRITES(dst, "\"");
		break;
	case JDTYPE_BOOLEAN:
		if( jdataGetBool(data) ) STREAM_WRITES(dst, "true");
		else STREAM_WRITES(dst, "false");
		break;
	default:
		fnerror("jt_transformValueNode", "不正なVALUEノードが検出されました");
		break;
	}
}


void jt_transformNameNode(OUTSTREAM* dst, NODE* name_node, int level){
	NULL_CHECK(dst, name_node, "jt_transformNameNode");
	ifassert(!checkJsonNodeType(name_node, JNODE_NAMENODE),
		"jt_transformNameNode", "NAMEノードではありません");
	
	STREAM_WRITES(dst, "\"");
	STREAM_WRITES(dst, jobjectGetMemberName(name_node));
	STREAM_WRITES(dst, "\": ");
	
	jt_transformDataNode(dst, jobjectGetMemberData(name_node), level);
}


void jt_transformArray(OUTSTREAM* dst, NODE* ary_node, int level){
	int comma;
	NODE* np;
	NULL_CHECK(dst, ary_node, "jt_transformArray");
	ifassert(!checkJsonNodeType(ary_node, JNODE_ARRAY),
		"jt_transformArray", "ARRAYノードではありません");
	
	STREAM_WRITES(dst, "[");
	jtLinefeed(dst);
	jtIndent(dst, level+1);
	comma = FALSE;
	for( np = jsonMemberIteratorGetHead(ary_node);
	np != NULL;
	np = jsonMemberIteratorNext(np) ){
		if( comma ){
			STREAM_WRITES(dst, ", ");
			jtLinefeed(dst);
			jtIndent(dst, level+1);
		}
		jt_transformDataNode(dst, np, level + 1);
		comma = TRUE;
	}
	jtLinefeed(dst);
	jtIndent(dst, level);
	STREAM_WRITES(dst, "]");
}


void jt_transformObject(OUTSTREAM* dst, NODE* obj_node, int level){
	int comma;
	NODE* np;
	NULL_CHECK(dst, obj_node, "jt_transformObject");
	ifassert(!checkJsonNodeType(obj_node, JNODE_OBJECT),
		"jt_transformObject", "OBJECTノードではありません");
	
	STREAM_WRITES(dst, "{");
	jtLinefeed(dst);
	jtIndent(dst, level+1);
	comma = FALSE;
	for( np = jsonMemberIteratorGetHead(obj_node);
	np != NULL;
	np = jsonMemberIteratorNext(np) ){
		if( comma ){
			STREAM_WRITES(dst, ", ");
			jtLinefeed(dst);
			jtIndent(dst, level+1);
		}
		if( checkJsonNodeType(np, JNODE_NAMENODE) ){
			jt_transformNameNode(dst, np, level + 1);
		}else{
			fnerror("jt_transformObject", "メンバでないノードを検出しました");
		}
		comma = TRUE;
	}
	jtLinefeed(dst);
	jtIndent(dst, level);
	STREAM_WRITES(dst, "}");
}


void jt_transformDataNode(OUTSTREAM* dst, NODE* j_node, int level){
	NULL_CHECK(dst, j_node, "jt_transformNode");
	
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
		STREAM_WRITES(dst, "null");
		break;
	}
}


void transformJson(OUTSTREAM* dest, NODE* root){
	NULL_CHECK(dest, root, "transformJson");
	
	jt_transformDataNode(dest, root, 0);
}
