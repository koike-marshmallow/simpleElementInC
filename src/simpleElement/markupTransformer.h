extern int TRANSFORM_INDENT;
extern int TRANSFORM_LINEFEED;
extern char* TRANSFORM_INDENT_CHAR;


void mtIndent(STRBUF* buffer, int level);
void mtLinefeed(STRBUF* buffer);

void generateAttributeString(STRBUF* buffer, NODE* attr);
void generateTextNodeString(STRBUF* buffer, NODE* text);
int generateElementStartTag(STRBUF* buffer, NODE* element);
void generateElementEndTag(STRBUF* buffer, NODE* element);

void recursiveTransformElement(STRBUF* buffer, NODE* element, int level);

void transform(STRBUF* buffer, NODE* root);
