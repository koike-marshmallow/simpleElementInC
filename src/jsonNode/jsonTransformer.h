#ifndef JSONTRANSFORMER_H
#define JSONTRANSFORMER_H

#ifndef OUTPUTSTREAM_H
#	include "../stream/outputStream.h"
#endif

#ifndef NODECORE_H
#	include "../simpleElement/nodeCore.h"
#endif

extern int JT_INDENT;
extern int JT_LINEFEED;
extern char* JT_INDENT_CHAR;

void jtIndent(OUTSTREAM* dst, int level);
void jtLinefeed(OUTSTREAM* dst);

/* layer1 */
void jt_transformValueNode(OUTSTREAM* dst, NODE* val_node, int level);
/* layer2 */
void jt_transformNameNode(OUTSTREAM* dst, NODE* name_node, int level);
void jt_transformArray(OUTSTREAM* dst, NODE* ary_node, int level);
void jt_transformObject(OUTSTREAM* dst, NODE* obj_node, int level);
void jt_transformDataNode(OUTSTREAM* dst, NODE* j_node, int level);

void transfromJson(OUTSTREAM* dest, NODE* root);

#endif
