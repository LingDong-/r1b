# swig -python r1b.i
gcc -O3 -fpic -I/usr/include/python3.4 -c r1b_wrap.c ../build/r1b.c -std=c99
gcc -shared r1b_wrap.o r1b.o -o _r1b.so