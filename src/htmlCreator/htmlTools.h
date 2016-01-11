#ifndef HTMLTOOLS_H
#define HTMLTOOLS_H

#ifndef HTMLCREATOR_H
#	include "htmlCreator.h"
#endif


NODE* createIdElement(char* name, char* id);
NODE* createTextElement(char* name, char* text);

NODE* addHtmlTitle(HTMLDOC* doc, char* title);
NODE* addHtmlMeta(HTMLDOC* doc, char* equiv, char* content);


NODE* addElementId(NODE* element, char* id);
NODE* addElementClass(NODE* element, char* class_name);


#endif

