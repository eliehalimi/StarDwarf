# EPITA Practical Programming S3 - 2016/2017
# Makefile
# Marwan Burelle
 
# Compilers and options
CC=gcc -fsanitize=address
CPPFLAGS= `pkg-config --cflags sdl` -MMD
CFLAGS= -Werror -Wall -Wextra -std=c99 -pedantic -O0 -g
LDFLAGS=
LDLIBS=`pkg-config --libs sdl` -lSDL_image
 
SRC = libvector.c
OBJ = ${SRC:.c=.o}
DEP = ${SRC:.c=.d}
 
all: physic
 
physic: ${OBJ}
 
test : ${OBJ}
 
-include ${DEP}
 
clean:
	rm -f ${OBJ} ${DEP}
	rm -f physic test
	rm -f test.d test.o
	rm -f \#*\#
	rm -f *~
 
# END
