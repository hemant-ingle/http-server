typedef struct __queue_node
{
void *ptr;
struct __queue_node *next;
}QueueNode;
typedef struct __queue
{
QueueNode *start,*end;
int elementSize;
int size;
}Queue;
void initQueue(Queue *queue,int elementSize);
int enqueue(Queue *queue,void *ptr);
int dequeue(Queue *queue,void *ptr);
int isEmptyQueue(Queue *queue);
int clearQueue(Queue *queue);