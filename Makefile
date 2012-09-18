memhooks-host.so: memhooks.c rtsym.c rtsym.h Makefile
	gcc -shared -fPIC -g -o memhooks-host.so memhooks.c rtsym.c

memhooks-arm.so: memhooks.c rtsym.c rtsym.h Makefile
	$(HOME)/android/ndk/toolchains/arm-linux-androideabi-4.6.3/prebuilt/linux-x86/bin/arm-linux-androideabi-gcc -shared -fPIC -g -o memhooks-arm.so memhooks.c rtsym.c

parser: HookOutputParser.java
	javac HookOutputParser.java

arm-stack: main.c
	$(HOME)/android/ndk-r8/toolchains/arm-linux-androideabi-4.4.3/prebuilt/linux-x86/bin/arm-linux-androideabi-gcc -I$(HOME)/android/ndk-r8/platforms/android-5/arch-arm/usr/include -O2 -g -Wall -Wmissing-prototypes -Wshadow -Wpointer-arith -Wstrict-prototypes -Wmissing-declarations -Wno-format-zero-length -fno-strict-aliasing -fno-builtin -marm -mcpu=cortex-a8 -static -Wno-long-long --sysroot=$(HOME)/android/ndk-r8/platforms/android-3/arch-arm -Wno-pointer-sign -fno-stack-protector -Wl,-z,noexecstack -o arm-stack main.c
