#include<stdio.h>
#include<binarySearchTree.h>
int intComparator(void *left,void *right)
{
return (*((int *)left))-(*((int *)right));
}
int nameComparator(void *left,void *right)
{
char **a,**b;
char *p,*q;
a=(char **)left;
b=(char **)right;
p=*a;
q=*b;
printf("Comparing : %s and %s\n",p,q);
while(*p && *q && *p==*q)
{
p++;
q++;
}
return (*p)-(*q);
}
int main()
{
char name[22];
char fetchedName[22];

char *x[10]={
"Ramu",
"Ram",
"Ramesh",
"Sam",
"John",
"Peter",
"Bobby",
"Amit",
"Sita",
"Tony"
};
int y;
int s;
InorderForwardIterator inorderForwardIterator;
int req;
req=10;
char **a;
char *b;
BinarySearchTree binarySearchTree;
initBinarySearchTree(&binarySearchTree,sizeof(char *),nameComparator);
for(y=0;y<req;y++)
{
b=x[y];
a=&b;
printf("eg1 a : %d\n",a);
printf("eg1 *a : %d\n",*a);
insertNode(&binarySearchTree,(void *)a);
}
printf("-------Inserted Data----------\n");
inorderTraversal(&binarySearchTree,&inorderForwardIterator);
while(inorderForwardIteratorHasNextElement(&inorderForwardIterator))
{
a=&b;
nextElementOfInorderForwardIterator(&inorderForwardIterator,(void *)a);
printf("%s\n",b);
}
printf("------------------------------\n");
int xx[23]={500,400,600,300,450,550,700,200,350,425,475,525,575,650,750,150,325,430,560,590,555,565,557};
int yy;
int ss;
int tt;
int *qq;
int **pp;
int reqq;
pp=&qq;
qq=&tt;
reqq=23;
BinarySearchTree binarySearchTreee;
initBinarySearchTree(&binarySearchTreee,sizeof(int),intComparator);
for(yy=0;yy<reqq;yy++)
{
qq=&xx[yy];
printf("eg1 qq : %d\n",qq);
printf("eg1 *qq : %d\n",*qq);
ss=insertNode(&binarySearchTreee,(void *)qq);
}
printf("-------Inserted Data----------\n");
inorderTraversal(&binarySearchTreee,&inorderForwardIterator);
while(inorderForwardIteratorHasNextElement(&inorderForwardIterator))
{
qq=&tt;
nextElementOfInorderForwardIterator(&inorderForwardIterator,(void *)qq);
printf("%d\n",tt);
}
printf("------------------------------\n");
return 0;
}