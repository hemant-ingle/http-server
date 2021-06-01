#include<stdio.h>
#include<binarySearchTree.h>
int intComparator(void *left,void *right)
{
return (*((int *)left))-(*((int *)right));
}
int main()
{
int x[23]={500,400,600,300,450,550,700,200,350,425,475,525,575,650,750,150,325,430,560,590,555,565,557};
int y;
int s;
int t;
int *q;
int **p;
int req;
p=&q;
q=&t;
req=23;
BinarySearchTree binarySearchTree;
initBinarySearchTree(&binarySearchTree,sizeof(int),intComparator);
for(y=0;y<req;y++)
{
s=insertNode(&binarySearchTree,(void *)&x[y]);
if(s==0)
{
printf("Unable to insert %d in binary search tree\n",x[y]);
break;
}
else
{
printf("%d is inserted successufully\n",x[y]);
}
}
return 0;
}