#ifndef JSONTRANSFORMER_H
#define JSONTRANSFORMER_H

#ifndef STRINGBUFFER_H
#	include "../stringBuffer/stringBuffer.h"
#endif

#ifndef NODECORE_H
#	include "../simpleElement/nodeCore.h"
#endif

/* layer1 */
/*void jt_transformNullNode(STRBUF* dst, NODE* null_node, int level);*/
void jt_transformValueNode(STRBUF* dst, NODE* val_node, int level);
/* layer2 */
void jt_transformNameNode(STRBUF* dst, NODE* name_node, int level);
void jt_transformArray(STRBUF* dst, NODE* ary_node, int level);
void jt_transformObject(STRBUF* dst, NODE* obj_node, int level);
void jt_tranformDataNode(STRBUF* dst, NODE* j_node, int level);

void transfromJson(STRBUF* dest, NODE* root);
