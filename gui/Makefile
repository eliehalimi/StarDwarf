
## Simple SDL mini code

CC=gcc

CPPFLAGS= `pkg-config --cflags sdl2` -MMD
CFLAGS= -Wall -Wextra -std=c99 -g #-fsanitize=address  #-Werror 
LDFLAGS=
LDLIBS= -lm `pkg-config --libs sdl2` -lSDL2 -lSDL2_image -lSDL2_ttf #-fsanitize=address

OBJ= general.o draw.o event.o list.o textinput.o draw_item.o main_manipulation.o hash_table.o ../Physic/libvector.o ../Physic/physic.o ../Physic/collision.o ../Physic/forces.o ../save/save.o main.o ../Camera/camera.o ../Camera/libmatrix.o 
DEP= ${OBJ:.o=.d}

all: main

main: ${OBJ}

clean:
	${RM} ${OBJ} 
	${RM} ${DEP} 
	${RM} *~
	${RM} main

-include ${DEP}

# END
