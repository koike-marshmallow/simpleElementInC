typedef void* STACK_TYPE;

struct s_ptrstack {
	STACK_TYPE* stack;
	int stack_size;
	int datanum;
};
typedef struct s_ptrstack PTR_STACK;


PTR_STACK* createPtrStack(int s);
void destroyPtrStack(PTR_STACK* ns);

void pushPtrStack(PTR_STACK* ns, STACK_TYPE data);
STACK_TYPE popPtrStack(PTR_STACK* ns);
STACK_TYPE retrievePtrStack(PTR_STACK* ns);

int getPtrStackCount(PTR_STACK* ns);
int isPtrStackFull(PTR_STACK* ns);
int isPtrStackEmpty(PTR_STACK* ns);
