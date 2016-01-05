#define NODE_ELEMENT 1
#define NODE_ATTRIBUTE 2
#define NODE_TEXT 3

#define NODE_NAME_LEN 64
#define NODE_VALUE_LEN 256


struct s_node {
	int node_type;
	char node_name[NODE_NAME_LEN];
	char node_value[NODE_VALUE_LEN];
	struct s_node* child;
	struct s_node* sibling;
};

typedef struct s_node NODE;


NODE* createNode(int type);
NODE* createCopyNode(NODE* node);
void destroyNode(NODE* node);
void destroyChildNodes(NODE* node);
void recursiveDestroyNode(NODE* node);

void initNode(NODE* node, int type);
void clearNode(NODE* node);

void seNodeType(NODE* node, int typec);
void setNodeName(NODE* node, char* name);
void setNodeValue(NODE* node, char* value);
int getNodeType(NODE* node);
char* getNodeName(NODE* node, char* buf, int len);
char* getNodeValue(NODE* node, char* buf, int len);

NODE* getFirstChildNode(NODE* node);
NODE* getNextSiblingNode(NODE* node);

/*void insertLinkedNodeSibling(NODE **pre_np, NODE *new_node);*/
/*NODE* removeLinkedNodeSibling(NODE **pre_np);*/
void appendChildNode(NODE* node, NODE* append);
void insertChildNode(NODE* node, NODE* new_node, NODE* pos);
void removeChildNode(NODE* node, NODE* pos);

int getChildNodeIndex(NODE* node, NODE* target);
int getChildNodeCount(NODE* node);
int getChildNodeList(NODE* node, NODE* list[], int len);

void printNodeInfo(NODE* node, int indent);
void traceNodes(NODE* node, int indent);
