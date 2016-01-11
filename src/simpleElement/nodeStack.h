typedef STACK_TYPE void*;

struct s_ptrstack {
	STACK_TYPE* stack;
	int stack_size;
	int datanum;
};
typedef struct s_ptrstack PTR_STACK;


NODE_STACK* createPtrStack(int s);
void destroyPtrStack(NODE_STACK* ns);

void pushPtrStack(NODE_STACK* ns, STACK_TYPE data);
STACK_TYPE popPtrStack(NODE_STACK* ns);
STACK_TYPE retrievePtrStack(NODE_STACK* ns);

int getPtrStackCount(NODE_STACK* ns);
int isPtrStackFull(NODE_STACK* ns);
int isPtrStackEmpty(NODE_STACK* ns);
