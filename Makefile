CC = clang 

CFLAGS = -Wall -Wpointer-arith -Wno-unused-parameter -g --std=c99 -Isrc

default: build

build:
	$(CC) $(CFLAGS) -o objs/sipc-text \
		src/sipc.c \
		src/s_user.c \
		src/s_msg.c \
		src/s_sys_config.c \
		src/s_sign_in.c \
		src/s_log.c
