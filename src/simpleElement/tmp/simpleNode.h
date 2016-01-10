#define NODE_ELEMENT 1
#define NODE_ATTRIBUTE 2
#define NODE_TEXT 3

#define NODE_NAME_LEN 64
#define NODE_VALUE_LEN 256

#define NODETREE_ITR_STACK_LEN 16

struct s_node {
	int node_type;
	char node_name[NODE_NAME_LEN];
	char node_value[NODE_VALUE_LEN];
	struct s_node* child;
	struct s_node* sibling;
};
typedef struct s_node NODE;

struct s_nodeitr {
	PTR_STACK* stack;
	struct s_node* ptr;
};
typedef struct s_nodeitr NODETREE_ITR;


/* Node creator */
NODE* createNode(int type);
void initNode(NODE* node, int type);

/* Node destroyer */
void destroyNode(NODE* node);
void recursiveDestroyNodes(NODE* node);
void destroyChildNodes(NODE* node);

/* Node content controller */
void setNodeType(NODE* node, int typec);
void setNodeName(NODE* node, char* name);
void setNodeValue(NODE* node, char* value);
int getNodeType(NODE* node);
char* getNodeName(NODE* node, char* buf, int len);
char* getNodeValue(NODE* node, char* buf, int len);

/* Nodetree insert/delete core */
void insertLinkedNodeSibling(NODE **pre_np, NODE *new_node);
NODE* removeLinkedNodeSibling(NODE **pre_np);
NODE** getLinkedNodeSiblingPNP(NODE* node, int idx);

/* Node childnode controller */
void appendChildNode(NODE* node, NODE* apnd);
void insertChildNode(NODE* node, int idx, NODE* isrt);
NODE* removeChildNode(NODE* node, int idx);

/* Node child/sibling iterator */
NODE* getFirstChildNode(NODE* node);
NODE* getNextSiblingNode(NODE* node);

/* Node childnode profile */
int getChildNodeIndex(NODE* node, NODE* target);
int getChildNodeCount(NODE* node);

/* Nodetree recursive iterator */
NODETREE_ITR* nodeitrCreate(NODE* root);
NODE* nodeitrNext(NODETREE_ITR* itr);
NODE* nodeitrGet(NODETREE_ITR* itr);
void nodeitrDestroy(NODETREE_ITR* itr);

/* debug */
void printNodeInfo(NODE* node, int indent);
void traceNodes(NODE* node, int indent);
