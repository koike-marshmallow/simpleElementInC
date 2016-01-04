#define NODE_NONE 0
#define NODE_ELEMENT 1
#define NODE_ATTRIBUTE 2
#define NODE_TEXT 3

#define NODE_NAME_LEN 64
#define NODE_VALUE_LEN 256

#define MAX_CHILDS_LEN 32


struct s_node {
	int node_type;
	char node_name[NODE_NAME_LEN];
	char node_value[NODE_VALUE_LEN];
	struct s_node* child;
	struct s_node* sibling;
};

typedef struct s_node NODE;


NODE* createNode(int type);
void destroyNode(NODE* node);
void recursiveDestroyNode(NODE* node);

void initNode(NODE* node, int type);
void clearNode(NODE* node);

void seNodeType(NODE* node, int typec);
void setNodeName(NODE* node, char* name);
void setNodeValue(NODE* node, char* value);
int getNodeType(NODE* node);
void getNodeName(NODE* node, char buf[], int len);
void getNodeValue(NODE* node, char buf[], int len);

void appendChildNode(NODE* node, NODE* append);

NODE* getFirstChildNode(NODE* node);
NODE* getNextSibling(NODE* node);

void clearChildNodeList(NODE* node);
void destroyChildNodeList(NODE* node);
void getChildNodeList(NODE* node, NODE* list[], int len);

void printNodeInfo(NODE* node, int indent);
void traceNodes(NODE* node, int indent);
