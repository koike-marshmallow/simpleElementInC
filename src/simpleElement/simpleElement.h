NODE* createElement(char* name);
NODE* destroyElement(NODE* element);

NODE* addAttribute(NODE* element, char* name, char* value);
void deleteAttribute(NODE* element, char* name);
void clearAttribute(NODE* element);
int getAttributeNameList(NODE* element, char* list, int l_size, int b_size);
char* getAttributeValue(NODE* element, char* name, char* buf, int len);

NODE* addText(NODE* element, char* text);
char* getText(NODE* element, char* buf, int len);
void clearText(NODE* element);

void appendChildElement(NODE* element);
void destroyChildElements(NODE* element);

