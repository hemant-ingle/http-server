g++ -c TMWP.cpp -I ..\include -I ..\..\dataStructures\binarySearchTree\include
ar rcs tmwp.lib *.o
del ..\lib\tmwp.lib
move tmwp.lib ..\lib