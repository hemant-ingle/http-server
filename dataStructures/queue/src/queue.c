#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<queue.h>
void initQueue(Queue *queue,int elementSize)
{
queue->start=NULL;
queue->end=NULL;
queue->elementSize=elementSize;
queue->size=0;
}
int enqueue(Queue *queue,void *ptr)
{
QueueNode *node;
if(queue==NULL) return 0;
node=(QueueNode *)malloc(sizeof(QueueNode *));
if(node==NULL) return 0;
node->ptr=(void *)malloc(queue->elementSize);
if(ptr!=NULL)
{
memcpy(node->ptr,(const void *)ptr,queue->elementSize);
node->next=NULL;
}
else
{
node->ptr=NULL;
}
if(queue->start==NULL)
{
queue->start=node;
queue->end=node;
}
else
{
queue->end->next=node;
queue->end=queue->end->next;
}
queue->size++;
return 1;
}
int dequeue(Queue *queue,void *ptr)
{
int j;
QueueNode *node;
if(queue==NULL || ptr==NULL) return 0;
if(queue->start==NULL) return 0;
node=queue->start;
if(queue->start==queue->end)
{
queue->start=NULL;
queue->end=NULL;
}
else
{
queue->start=queue->start->next;
}
if(node->ptr!=NULL)
{
memcpy(ptr,(const void *)node->ptr,queue->elementSize);
}
else
{
for(j=0;j<queue->elementSize;j++)
{
*((char *)(ptr+j))=(char)0;
}
}
if(node->ptr!=NULL) free(node->ptr);
free(node);
queue->size--;
return 1;
}
int isEmptyQueue(Queue *queue)
{
if(queue==NULL) return 1;
if(queue->size==0) return 1;
return 0;
}
int clearQueue(Queue *queue)
{
QueueNode *node;
if(queue==NULL) return 0;
if(queue->start==NULL) return 0;
while(queue->start!=NULL)
{
node=queue->start;
queue->start=queue->start->next;
if(node->ptr) free(node->ptr);
free(node);
}
queue->end=NULL;
queue->size=0;
return 1;
}