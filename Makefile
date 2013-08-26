CC = clang

CFLAGS = -Wall -Wpointer-arith -Wno-unused-parameter -g --std=c99 -Isrc

CLIBS = 

OBJS = objs/sipc.o \
	objs/s_user.o \
	objs/s_msg.o \
	objs/s_sys_config.o \
	objs/s_sign_in.o \
	objs/s_log.o

default: build

objs/sipc.o:
	$(CC) $(CFLAGS) $(CLIBS) -c -o objs/sipc.o src/sipc.c

objs/s_user.o:
	$(CC) $(CFLAGS) $(CLIBS) -c -o objs/s_user.o src/s_user.c

objs/s_msg.o:
	$(CC) $(CFLAGS) $(CLIBS) -c -o objs/s_msg.o src/s_msg.c

objs/s_sys_config.o:
	$(CC) $(CFLAGS) $(CLIBS) -c -o objs/s_sys_config.o src/s_sys_config.c

objs/s_sign_in.o:
	$(CC) $(CFLAGS) $(CLIBS) -c -o objs/s_sign_in.o src/s_sign_in.c

objs/s_log.o:
	$(CC) $(CFLAGS) $(CLIBS) -c -o objs/s_log.o src/s_log.c


objs/sipc_text: ${OBJS}
	$(CC) $(CFLAGS) $(CLIBS)-o objs/sipc_text ${OBJS}


build: objs/sipc_text

clean:
	rm ${OBJS}