#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<binarySearchTree.h>
#include<queue.h>
#include<stack.h>
int initBinarySearchTree(BinarySearchTree *binarySearchTree,int elementSize,int (*p2f)(void *,void *))
{
if(binarySearchTree==NULL) return 0;
binarySearchTree->root=NULL;
binarySearchTree->elementSize=elementSize;
binarySearchTree->size=0;
binarySearchTree->p2f=p2f;
return 1;
}
int insertNode(BinarySearchTree *binarySearchTree,void *ptr)
{
BinarySearchTreeNode *node,*p,*q;
int w;
if(binarySearchTree==NULL) return 0;
node=(BinarySearchTreeNode *)malloc(sizeof(BinarySearchTreeNode));
if(node==NULL) return 0;
node->left=NULL;
node->right=NULL;
node->ptr=(void *)malloc(binarySearchTree->elementSize);
if(node->ptr==NULL)
{
free(node);
return 0;
}
if(ptr!=NULL)
{
memcpy(node->ptr,(const void *)ptr,binarySearchTree->elementSize);
}
else
{
node->ptr=ptr;
}
if(binarySearchTree->root==NULL)
{
binarySearchTree->root=node;
}
else
{
q=binarySearchTree->root;
while(q!=NULL)
{
w=binarySearchTree->p2f(ptr,q->ptr);
//if(data<(*(q->data))) q=q->left;
//else if(data>(*(q->data))) q=q->right;
//else{}//if(data==(*(q->data))) //right now do nothing assuming that the user won't add duplicate data
if(w==0)
{
// not decided yet
}
else if(w<0)
{
p=q;
q=q->left;
}
else if(w>0)
{
p=q;
q=q->right;
}
}
w=binarySearchTree->p2f(ptr,p->ptr);
//if(data<(*(p->data))) p->left=node;
//else if(data>(*(p->data))) p->right=node;
if(w<0) p->left=node;
else if(w>0) p->right=node;
}
return 1;
}
int removeNode(BinarySearchTree *binarySearchTree,void *ptr)
{
BinarySearchTreeNode *pL,*pR,*pV,*qL,*qR,*qV,*sL,*sR,*sV,*rL,*rR,*rV;
BinarySearchTreeNode *p,*q,*r,*s;
int w,isLeft;
if(binarySearchTree==NULL || ptr==NULL) return 0;
if(binarySearchTree->root==NULL) return 0;
q=binarySearchTree->root;
p=q;
while(q!=NULL)
{
w=binarySearchTree->p2f(ptr,q->ptr);
if(w<0)
{
p=q;
isLeft=1;
q=q->left;
}
else if(w>0)
{
p=q;
isLeft=0;
q=q->right;
}
else break;
}
if(q==NULL) return 0; //not found
if(q->left==NULL && q->right==NULL) //zero children present
{
if(p==q) 
{
binarySearchTree->root=NULL; //root node
}
else if(isLeft)
{
p->left=NULL;
}
else
{
p->right=NULL;
}
}
else if(q->left==NULL) // one child node is present on right side
{
s=q;
r=q->right;
while(r->left!=NULL)
{
s=r;
r=r->left;
}
if(p==q) 
{
if(s!=q)
{
s->left=r->right;
r->right=q->right;
}
r->left=q->left;
binarySearchTree->root=r; //root node
}
else if(isLeft)
{
if(s!=q)
{
s->left=r->right;
r->right=q->right;
}
r->left=q->left;
p->left=r;
}
else
{
if(s!=q)
{
s->left=r->right;
r->right=q->right;
}
r->left=q->left;
p->right=r;
}

}
else if(q->right==NULL) // one child node is present on left side
{
r=q->left;
if(p==q) 
{
binarySearchTree->root=r; //root node
}
else if(isLeft)
{
p->left=r;
}
else
{
p->right=r;
}
}
else // both the children are present
{
s=q;
r=q->right;
while(r->left!=NULL)
{
s=r;
r=r->left;
}
if(p==q) 
{
if(s!=q)
{
s->left=r->right;
r->right=q->right;
}
r->left=q->left;
binarySearchTree->root=r; //root node
}
else if(isLeft)
{
if(s!=q)
{
s->left=r->right;
r->right=q->right;
}
r->left=q->left;
p->left=r;
}
else
{
if(s!=q)
{
s->left=r->right;
r->right=q->right;
}
r->left=q->left;
p->right=r;
}

}
if(q->ptr!=NULL) free(q->ptr);
free(q);
return 1;
}
int searchNode(BinarySearchTree *binarySearchTree,void *ptr)
{
BinarySearchTreeNode *node,*p;
int w;
if(binarySearchTree==NULL) return 0;
if(binarySearchTree->root==NULL) return 0;
node=binarySearchTree->root;
while(node!=NULL)
{
w=binarySearchTree->p2f(ptr,node->ptr);
//if(data<(*(node->data))) node=node->left;
//else if(data>(*(node->data))) node=node->right;
//else break;
if(w<0) node=node->left;
else if(w>0) node=node->right;
else break;
}
if(node==NULL) return 0; //data not found
return 1;
}
int getNodeValue(BinarySearchTree *binarySearchTree,void *ptr,void *nodeValue)
{
BinarySearchTreeNode *t,*p;
int w;
if(binarySearchTree==NULL) return 0;
if(binarySearchTree->root==NULL) return 0;
t=binarySearchTree->root;
while(t!=NULL)
{
w=binarySearchTree->p2f(ptr,t->ptr);
//if(data<(*(t->data))) t=t->left;
//else if(data>(*(t->data))) t=t->right;
//else break;
if(w<0) t=t->left;
else if(w>0) t=t->right;
else break;
}
if(t==NULL) return 0; //data not found
if(nodeValue!=NULL) memcpy(nodeValue,(const void *)t->ptr,binarySearchTree->elementSize);
return 1;
}
int removeAllNodes(BinarySearchTree *binarySearchTree)
{
BinarySearchTreeNode *node,*p;
Stack stack;
Queue queue;
if(binarySearchTree==NULL) return 0;
if(binarySearchTree->root==NULL) return 0;
initStack(&stack,sizeof(BinarySearchTreeNode *));
initQueue(&queue,sizeof(BinarySearchTreeNode *));
p=binarySearchTree->root;
while(!isEmptyStack(&stack) || p!=NULL)
{
if(p!=NULL)
{
push(&stack,(void *)&p);
p=p->left;
}
else
{
pop(&stack,(void *)&p);
enqueue(&queue,(void *)&p);
p=p->right;
}
}
while(!isEmptyQueue(&queue))
{
dequeue(&queue,(void *)&node);
if(node->ptr) free(node->ptr);
free(node);
}
binarySearchTree->size=0;
binarySearchTree->root=NULL;
return 1;
}
int isEmptyBinarySearchTree(BinarySearchTree *binarySearchTree)
{
if(binarySearchTree==NULL) return 0;
if(binarySearchTree->root==NULL) return 1;
return 0;
}


int initInorderForwardIterator(InorderForwardIterator *inorderForwardIterator,int elementSize)
{
if(inorderForwardIterator==NULL || elementSize<=0) return 0;
inorderForwardIterator->start=NULL;
inorderForwardIterator->end=NULL;
inorderForwardIterator->elementSize=elementSize;
inorderForwardIterator->size=0;
return 1;
}
int nextElementOfInorderForwardIterator(InorderForwardIterator *inorderForwardIterator,void *ptr)
{
InorderForwardIteratorNode *node;
BinarySearchTreeNode *b;
int j;
if(inorderForwardIterator==NULL || ptr==NULL) return 0;
if(inorderForwardIterator->start==NULL) return 0;
node=inorderForwardIterator->start;
if(inorderForwardIterator->start->ptr==NULL)
{
for(j=0;j<inorderForwardIterator->elementSize;j++)
{
(*((char *)(ptr+j)))=(char)0;
}
inorderForwardIterator->size--;
return 1;
}
memcpy(&b,(const void *)inorderForwardIterator->start->ptr,sizeof(BinarySearchTreeNode *));
memcpy(ptr,(const void *)b->ptr,inorderForwardIterator->elementSize);
if(inorderForwardIterator->start==inorderForwardIterator->end)
{
inorderForwardIterator->start=NULL;
inorderForwardIterator->end=NULL;
}
else
{
inorderForwardIterator->start=inorderForwardIterator->start->next;
}
inorderForwardIterator->size--;
if(node->ptr!=NULL) free(node->ptr);
free(node);
return 1;
}
int inorderForwardIteratorHasNextElement(InorderForwardIterator *inorderForwardIterator)
{
if(inorderForwardIterator==NULL) return 0;
if(inorderForwardIterator->size>0) return 1;
return 0;
}
int destroyInorderForwardIterator(InorderForwardIterator *inorderForwardIterator)
{
InorderForwardIteratorNode *node;
if(inorderForwardIterator==NULL) return 0;
node=inorderForwardIterator->start;
while(node!=NULL)
{
inorderForwardIterator->start=inorderForwardIterator->start->next;
if(node->ptr!=NULL) free(node->ptr);
free(node);
node=inorderForwardIterator->start;
}
inorderForwardIterator->start=NULL;
inorderForwardIterator->end=NULL;
inorderForwardIterator->size=0;
return 1;
}
int inorderTraversal(BinarySearchTree *binarySearchTree,InorderForwardIterator *inorderForwardIterator)
{
Stack stack;
InorderForwardIteratorNode *iteratorNode;
BinarySearchTreeNode *p,*q;
if(binarySearchTree==NULL || inorderForwardIterator==NULL) return 0;
initInorderForwardIterator(inorderForwardIterator,binarySearchTree->elementSize);
if(binarySearchTree->root==NULL) return 0;
initStack(&stack,sizeof(BinarySearchTreeNode *));
p=binarySearchTree->root;
while(!isEmptyStack(&stack) || p!=NULL)
{
if(p!=NULL)
{
push(&stack,(void *)&p);
//verification is required if failed clear the stack
//destory (clear) the inorderForwardIterator and return 0;
p=p->left;
}
else
{
pop(&stack,(void *)&p);
iteratorNode=(InorderForwardIteratorNode *)malloc(sizeof(InorderForwardIteratorNode));
if(iteratorNode==NULL)
{
clearStack(&stack);
destroyInorderForwardIterator(inorderForwardIterator);
inorderForwardIterator->start=NULL;
inorderForwardIterator->end=NULL;
inorderForwardIterator->size=0;
return 0; 
}
iteratorNode->ptr=(void *)malloc(sizeof(BinarySearchTreeNode *));
if(iteratorNode->ptr==NULL)
{
free(iteratorNode);
clearStack(&stack);
destroyInorderForwardIterator(inorderForwardIterator);
inorderForwardIterator->start=NULL;
inorderForwardIterator->end=NULL;
inorderForwardIterator->size=0;
return 0; 
}
memcpy(iteratorNode->ptr,(const void *)&p,sizeof(BinarySearchTree *));
iteratorNode->next=NULL;
if(inorderForwardIterator->start==NULL)
{
inorderForwardIterator->start=iteratorNode;
inorderForwardIterator->end=iteratorNode;
}
else
{
inorderForwardIterator->end->next=iteratorNode;
inorderForwardIterator->end=inorderForwardIterator->end->next;
}
inorderForwardIterator->size++;
p=p->right;
}
}
return 1;
}
/*
void inorder(BinarySearchTreeNode *binarySearchTreeNode)
{
if(binarySearchTreeNode==NULL) return;
inorder(binarySearchTreeNode->left);
inorder(binarySearchTreeNode->right);
}
void inorderTraversal(BinarySearchTree *binarySearchTree)
{
inorder(binarySearchTree->root);
}*/
int preorderTraversal(BinarySearchTree *binarySearchTree)
{
printf("preorderTraversal is not implemented yet\n");
}
int postorderTraversal(BinarySearchTree *binarySearchTree)
{
printf("postorderTraversal is not implemented yet\n");
}
/*
void levelorderTraversal(BinarySearchTree *binarySearchTree)
{
BinarySearchTreeNode *node,*p;
Queue queue;
init(&queue,sizeof(BinarySearchTreeNode));
enqueue(&queue,(void *)binarySearchTree->root);
p=binarySearchTree->root;
while(!isEmptyQueue(&queue))
{
dequeue(&queue,(void *)node);
if((*(p->data))==(*(node->data)))
{
if(node->right!=NULL) p=node->right;
else if(node->left!=NULL) p=node->left;
}
if(node->left!=NULL)
{
enqueue(&queue,(void *)node->left);
}
if(node->right!=NULL)
{
enqueue(&queue,(void *)node->right);
}
}
}
*/
int levelorderTraversal(BinarySearchTree *binarySearchTree)
{
BinarySearchTreeNode *node,*p;
Queue queue;
if(binarySearchTree==NULL) return 0;
if(binarySearchTree->root==NULL) return 0;
initQueue(&queue,sizeof(BinarySearchTreeNode *));
enqueue(&queue,(void *)&(binarySearchTree->root));
p=binarySearchTree->root;
while(!isEmptyQueue(&queue))
{
dequeue(&queue,(void *)&node);
if(p==node)
{
if(node->right!=NULL) p=node->right;
else if(node->left!=NULL) p=node->left;
}
if(node->left!=NULL)
{
enqueue(&queue,(void *)&(node->left));
}
if(node->right!=NULL)
{
enqueue(&queue,(void *)&(node->right));
}
}
return 1;
}