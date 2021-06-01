gcc -c binarySearchTree.c -I ..\include -I ..\..\queue\include -I ..\..\stack\include
ar rcs binarySearchTree.lib binarySearchTree.o
del ..\lib\binarySearchTree.lib
move binarySearchTree.lib ..\lib