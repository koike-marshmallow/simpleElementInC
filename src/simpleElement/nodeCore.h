#ifndef NODECORE_H
#define NODECORE_H	

struct s_node {
	void* content;
	struct s_node* child;
	struct s_node* slibong;
};
typedef struct s_node NODE;


NODE* createNodeCore(void);
void initNodeCore(NODE* node);
void destroyNodeCore(NODE* node);

void* getNodeContent(NODE* node);

NODE* getFirstChildNode(NODE* node);
NODE* getNextSiblingNode(NODE* node);

void insertLinkedNodeSibling(NODE** prev_sibling_ptr, NODE* new_node);
NODE* removeLinkedNodeSibling(NODE** prev_sibling_ptr);

NODE** getLinkedNodeSibidxPNP(NODE* node, int idx);
NODE** getLinkedNodeSibtailPNP(NODE* node);

int getChildNodeIdx(NODE* node, NODE* target);
int getChildNodeCount(NODE* node);

#endif
