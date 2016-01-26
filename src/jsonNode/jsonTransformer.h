#ifndef JSONTRANSFORMER_H
#define JSONTRANSFORMER_H

#ifndef STRINGBUFFER_H
#	include "../stringBuffer/stringBuffer.h"
#endif

#ifndef NODECORE_H
#	include "../simpleElement/nodeCore.h"
#endif

extern int JT_INDENT;
extern int JT_LINEFEED;
extern char* JT_INDENT_CHAR;

void jtIndent(STRBUF* dst, int level);
void jtLinefeed(STRBUF* dst);

/* layer1 */
void jt_transformValueNode(STRBUF* dst, NODE* val_node, int level);
/* layer2 */
void jt_transformNameNode(STRBUF* dst, NODE* name_node, int level);
void jt_transformArray(STRBUF* dst, NODE* ary_node, int level);
void jt_transformObject(STRBUF* dst, NODE* obj_node, int level);
void jt_transformDataNode(STRBUF* dst, NODE* j_node, int level);

void transfromJson(STRBUF* dest, NODE* root);

#endif
