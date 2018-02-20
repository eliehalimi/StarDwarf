
## Simple SDL mini code

CC=gcc

CPPFLAGS= `pkg-config --cflags sdl2` -MMD
CFLAGS=  -fsanitize=address -Wall -Wextra -Werror -std=c99 #-fsanitize=address 
LDFLAGS=
LDLIBS=  -fsanitize=address -lm `pkg-config --libs sdl2` -lSDL2 -lSDL2_image -lSDL2_ttf #-fsanitize=address

SRC= general.o draw.o event.o main.o
OBJ= ${SRC:.c=.o}
DEP= ${SRC:.o=.d}

all: main

main: ${OBJ}

clean:
	${RM} ${OBJ} 
	${RM} ${DEP} 
	${RM} *~
	${RM} main

-include ${DEP}

# END
