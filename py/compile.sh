swig -python r1b.i
gcc -O3 -c ../build/r1b.c r1b_wrap.c -I/usr/local/Cellar/python/3.7.6_1/Frameworks/Python.framework/Versions/3.7/include/python3.7m
gcc $(python3-config --ldflags) -dynamiclib *.o -o _r1b.so -I/usr/local/Cellar/python/3.7.6_1/Frameworks/Python.framework/Versions/3.7/lib/libpython3.7m.dylib
