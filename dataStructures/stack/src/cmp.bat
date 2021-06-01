gcc -c stack.c -I ..\include
ar rcs stack.lib stack.o
del ..\lib\stack.lib
move stack.lib ..\lib
