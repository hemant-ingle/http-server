#include<stdio.h>
#include<binarySearchTree.h>
int nameComparator(void *left,void *right)
{
char **a,**b;
char *p,*q;
a=(char **)left;
b=(char **)right;
p=*a;
q=*b;
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
char *t;
InorderForwardIterator inorderForwardIterator;
int req;
req=10;
char **a;
char *b,*c;
BinarySearchTree binarySearchTree;
initBinarySearchTree(&binarySearchTree,sizeof(char *),nameComparator);
for(y=0;y<req;y++)
{
a=&x[y];
s=insertNode(&binarySearchTree,(void *)a);
}
printf("-------Inserted Data----------\n");
inorderTraversal(&binarySearchTree,&inorderForwardIterator);
while(inorderForwardIteratorHasNextElement(&inorderForwardIterator))
{
nextElementOfInorderForwardIterator(&inorderForwardIterator,(void *)&b);
printf("%s\n",b);
}
printf("------------------------------\n");

printf("Enter a name : ");
scanf("%s",name);
b=&name[0];
getNodeValue(&binarySearchTree,(void *)&b,(void *)&c);
printf("Fetched name : %s\n",c);
return 0;
}