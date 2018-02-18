
## Simple SDL mini code

CC=gcc

CPPFLAGS= `pkg-config --cflags sdl2` -MMD
CFLAGS= -fsanitize=address -std=c99 -Wall -Wextra -Werror -std=c99 -O0 -g
LDFLAGS=
LDLIBS= -fsanitize=address -lm `pkg-config --libs sdl2` -lSDL_image #-lSDL_gfx -lSDL_ttf

SRC= circle.o 
OBJ= ${SRC:.c=.o}
DEP= ${SRC:.o=.d}

all: circle

#main: ${OBJ}

clean:
	${RM} ${OBJ} 
	${RM} ${DEP} 
	${RM} *~
	${RM} main circle

-include ${DEP}

# END
