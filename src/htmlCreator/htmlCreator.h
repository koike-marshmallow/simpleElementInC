#ifndef HTMLCREATOR_H
#define HTMLCREATOR_H

#ifndef NODECORE_H
#	include "../simpleElement/nodeCore.h"
#endif

struct s_htmldoc{
	NODE* e_html;
	NODE* e_head;
	NODE* e_body;
};
typedef struct s_htmldoc HTMLDOC;

HTMLDOC* createHtmlDocument(void);
void initHtmlDocument(HTMLDOC* doc);
void destroyHtmlDocument(HTMLDOC* doc);

NODE* getHtmlHeadElement(HTMLDOC* doc);
NODE* getHtmlBodyElement(HTMLDOC* doc);

#endif
