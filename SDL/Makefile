
## Simple SDL mini code

CC=gcc

CPPFLAGS= `pkg-config --cflags sdl` -MMD
CFLAGS= -fsanitize=address -Wall -Wextra -Werror -Wpedantic -std=c99 -O0 -g
LDFLAGS=
LDLIBS= -fsanitize=address `pkg-config --libs sdl` -lSDL_image

OBJ= main.o
DEP= ${SRC:.o=.d}

all: main

main: ${OBJ}

clean:
	${RM} ${OBJ} ${DEP} *~
	${RM} main

-include ${DEP}

# END
