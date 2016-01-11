#ifndef HTMLITERATOR_H
#define HTMLITERATOR_H

#ifndef NODEITERATOR_H
#	include "../simpleElement/nodeIterator.h"
#endif

struct s_htmliterator {
	HTMLDOC* doc;
	NODETREE_ITR* iterator;
};
typedef struct s_htmliterator HTML_ITR;



NODE* getElementById(HTMLDOC* doc, char* id);

HTML_ITR* createHtmlIterator(HTMLDOC* doc);
void destroyHtmlIterator(HTML_ITR* itr);

NODE* nextElementByClass(HTML_ITR* itr, char* class_name);
NODE* nextElementByAttribute(HTML_ITR* itr, char* name, char* value);
NODE* nextElementByElementName(HTML_ITR* itr, char* element_name);


#endif
