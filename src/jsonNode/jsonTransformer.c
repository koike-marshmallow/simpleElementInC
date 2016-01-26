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
			sprintf(JT_VALUE_BUFFER, VALUEBUF_LEN, "%d", jdataGetInt(data)),
			VALUEBUF_LEN, "jt_transformValueNode"
		);
		sbCatString(dst, JT_VALUE_BUFFER);
		break;
	case JDTYPE_FLOAT:
		SPRINTF_ASSERT(
			sprintf(JT_VALUE_BUFFER, VALUEBUF_LEN, "%f", jdataGetFloat(data)),
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
	
	jt_transformNode(dst, jobjectGetMemberValue(name_node), level + 1);
}:wq
	
	
	
	
	
		
		
		
