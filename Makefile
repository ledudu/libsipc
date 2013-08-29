CC = gcc

CFLAGS_THIRD_PARTY = `pkg-config --cflags libcurl`
LIBS_THIRD_PARTY = `pkg-config --libs libcurl`

CFLAGS = -Wall -Wpointer-arith -Wno-unused-parameter -g --std=c99 $(CFLAGS_THIRD_PARTY)

LIBS = $(LIBS_THIRD_PARTY)

OBJS = objs/s_user.o \
	objs/s_msg.o \
	objs/s_sys_config.o \
	objs/s_sign_in.o \
	objs/s_log.o

default: build

build: objs/sipc-text

objs/sipc-text: ${OBJS} objs/sipc-text.o
	$(CC) $(CFLAGS) $(LIBS) -o objs/sipc-text objs/sipc-text.o ${OBJS} 

objs/sipc-text.o: src/sipc-text.c
	$(CC) $(CFLAGS) $(LIBS) -c -o objs/sipc-text.o src/sipc-text.c

objs/s_user.o: src/s_user.c src/s_user.h
	$(CC) $(CFLAGS) $(LIBS) -c -o objs/s_user.o src/s_user.c

objs/s_msg.o: src/s_msg.c src/s_msg.h
	$(CC) $(CFLAGS) $(LIBS) -c -o objs/s_msg.o src/s_msg.c

objs/s_sys_config.o: src/s_sys_config.c src/s_sys_config.h
	$(CC) $(CFLAGS) $(LIBS) -c -o objs/s_sys_config.o src/s_sys_config.c

objs/s_sign_in.o: src/s_sign_in.c src/s_sign_in.h
	$(CC) $(CFLAGS) $(LIBS) -c -o objs/s_sign_in.o src/s_sign_in.c

objs/s_log.o: src/s_log.c src/s_log.h
	$(CC) $(CFLAGS) $(LIBS) -c -o objs/s_log.o src/s_log.c


.PHONY: clean

clean:
	rm objs/sipc-text ${OBJS}
