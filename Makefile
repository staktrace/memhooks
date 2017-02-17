memhooks-host.so: memhooks.c rtsym.c rtsym.h Makefile
	gcc -shared -fPIC -g -o memhooks-host.so memhooks.c rtsym.c -ldl

memhooks-arm.so: memhooks.c rtsym.c rtsym.h Makefile
	$(HOME)/android/ndk/toolchains/arm-linux-androideabi-4.6.3/prebuilt/linux-x86/bin/arm-linux-androideabi-gcc -shared -fPIC -g -o memhooks-arm.so memhooks.c rtsym.c

parser: HookOutputParser.java
	javac HookOutputParser.java
