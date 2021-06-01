#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stack.h>
void initStack(Stack *stack,int elementSize)
{
stack->top=NULL;
stack->elementSize=elementSize;
stack->size=0;
}
int push(Stack *stack,void *ptr)
{
StackNode *node;
if(stack==NULL) return 0;
node=(StackNode *)malloc(sizeof(StackNode));
if(node==NULL) return 0;
if(ptr!=NULL)
{
node->ptr=(void *)malloc(stack->elementSize);
if(node->ptr==NULL)
{
free(node);
return 0;
}
memcpy(node->ptr,(const void *)ptr,stack->elementSize);
}
else
{
node->ptr=ptr;
}
node->next=stack->top;
stack->top=node;
stack->size++;
return 1;
}
int pop(Stack *stack,void *ptr)
{
int j;
StackNode *node;
if(stack==NULL) return 0;
if(stack->top==NULL) return 0;
if(stack->top->ptr==NULL)
{
for(j=0;j<stack->elementSize;j++)
{
*((char *)(ptr+j))=(char)0;
}
}
else
{
memcpy(ptr,(const void *)stack->top->ptr,stack->elementSize);
}
node=stack->top;
stack->top=stack->top->next;
if(node->ptr!=NULL) free(node->ptr);
free(node);
stack->size--;
return 1;
}
int isEmptyStack(Stack *stack)
{
if(stack==NULL) return 1;
if(stack->size==0) return 1;
return 0;
}
int clearStack(Stack *stack)
{
StackNode *node;
if(stack==NULL) return 0;
if(stack->top==NULL) return 1;
while(stack->top!=NULL)
{
node=stack->top;
stack->top=stack->top->next;
if(node->ptr) free(node->ptr);
free(node);
}
return 1;
}