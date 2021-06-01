gcc -c queue.c -I ..\include
ar rcs queue.lib queue.o
del ..\lib\queue.lib
move queue.lib ..\lib