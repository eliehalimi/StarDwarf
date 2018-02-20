# ifndef FORCES_STARDWARF
# define FORCES_STARDWARF

#include <stdlib.h>
#include "libvector.h"
#include "physic.h"

float distance(struct item *i1, struct item *i2);

struct vector* gra_force(struct item *i1, struct item *i2); //i2 acts on i1
//struct vector* mag_force(struct item *i1, struct item *i2);

# endif
  
