SRC_FILES = src/main.c
CC_FLAGS = -Wall -Wextra -g -std=c11
CC = gcc
RM = rm -f
TARGET = virtualmachine

all:
	${CC} ${SRC_FILES} ${CC_FLAGS} -o ${TARGET}

clean:
	${RM} ${TARGET}
