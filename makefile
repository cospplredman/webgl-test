#Building requires the emscripten compiler and associated headers

SRC := $(shell echo src/*.c)
OBJ := $(SRC:.c=.o)
INC := src

CC = emcc
CFLAGS = -g0 -O2 -Wall -pedantic

default: all
all: main.js

clean:
	rm -f main.js main.wasm main.worker.js ${OBJ}

%.o: %.c
	${CC} ${CFLAGS} -c $< -o $@

main.js: main.c ${OBJ}
	$(CC) ${CFLAGS} $^ -o $@ -sALLOW_MEMORY_GROWTH -sEXPORTED_FUNCTIONS=_main -lGL -lGLU -s USE_GLFW=3 -s USE_WEBGL2=1 #--proxy-to-worker

.PHONY: all clean
