memhooks.so: memhooks.c rtsym.c rtsym.h Makefile
	gcc -shared -fPIC -g -o memhooks.so memhooks.c rtsym.c
