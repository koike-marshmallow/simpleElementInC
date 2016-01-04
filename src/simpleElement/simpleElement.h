NODE* createElement(char* name);
NODE* createTextNode(char* text);
void destroyElement(NODE* element);
void recursiveDestroyElement(NODE* element);

void initElement(NODE* element);
void clearElement(NODE* element);

void addAttribute(NODE* element, char* name, char* value);
void deleteAttribute(NODE* element, char* name);
void clearAttribute(NODE* element);
int getAttributeNameList(NODE* element, char* list[], int l_size, int b_size);
void getAttributeValue(NODE* element, char* name, char buf[], int len);

void addText(NODE* element, char* text);
void getText(NODE* element, char buf[], int len);
void clearText(NODE* element);

//void appendChildNode(NODE* node, NODE* append);
//NODE* getChildNode(NODE* node, int idx);
//int getChildNodeCount(NODE* node);

//void clearChildNodeList(NODE* node);
//void destroyChildNodeList(NODE* node);
//void getChildNodeList(NODE* node, NODE* list[], int len);


