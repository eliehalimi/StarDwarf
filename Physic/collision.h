# ifndef COLLISION_STARDWARF
# define COLLISION_STARDWARF

#include <stdlib.h>
#include "libvector.h"
#include "physic.h"

int collide(struct system *system, struct item *i1, struct item *i2, struct item **destroyed); 
# endif
