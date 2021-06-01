typedef struct __binary_search_tree_node
{
void *ptr;
struct __binary_search_tree_node *left,*right;
}BinarySearchTreeNode;
typedef struct __binary_search_tree
{
BinarySearchTreeNode *root;
int elementSize;
int size;
int (*p2f)(void *left,void *right);
}BinarySearchTree;
int initBinarySearchTree(BinarySearchTree *binarySearchTree,int elementSize,int (*p2f)(void *,void *));
int insertNode(BinarySearchTree *binarySearchTree,void *ptr);
int removeNode(BinarySearchTree *binarySearchTree,void *ptr);
int searchNode(BinarySearchTree *binarySearchTree,void *ptr);
int getNodeValue(BinarySearchTree *binarySearchTree,void *ptr,void *nodeValue);
int removeAllNodes(BinarySearchTree *binarySearchTree);
int isEmptyBinarySearchTree(BinarySearchTree *binarySearchTree);
typedef struct __inorder_forward_iterator_node
{
void *ptr;
struct __inorder_forward_iterator_node *next;
}InorderForwardIteratorNode;
typedef struct __inorder_forward_iterator
{
InorderForwardIteratorNode *start,*end;
int elementSize;
int size;
}InorderForwardIterator;
int nextElementOfInorderForwardIterator(InorderForwardIterator *inorderForwardIterator,void *ptr);
int inorderForwardIteratorHasNextElement(InorderForwardIterator *inorderForwardIterator);
int destroyInorderForwardIterator(InorderForwardIterator *inorderForwardIterator);
int inorderTraversal(BinarySearchTree *binarySearchTree,InorderForwardIterator *inorderForwardIterator);
int preorderTraversal(BinarySearchTree *binarySearchTree);
int postorderTraversal(BinarySearchTree *binarySearchTree);
int levelorderTraversal(BinarySearchTree *binarySearchTree);


