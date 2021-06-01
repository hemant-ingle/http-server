typedef struct __stack_node
{
void *ptr;
struct __stack_node *next;
}StackNode;
typedef struct __stack
{
StackNode *top;
int elementSize;
int size;
}Stack;
void initStack(Stack *stack,int elementSize);
int push(Stack *stack,void *ptr);
int pop(Stack *stack,void *ptr);
int isEmptyStack(Stack *stack);
int clearStack(Stack *stack);