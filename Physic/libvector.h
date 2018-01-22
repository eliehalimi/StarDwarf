IFNDEF VECTOR_STARDWARF
DEFINE VECTOR_STARDWARF

# include <stdlib.h>

struct vector
{
  size_t size;
  float *values;
};

struct vector *newvector(size_t size, float *values);

void freevector(struct vector *vect);

ENDIF
