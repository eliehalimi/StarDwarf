IFNDEF VECTOR_STARDWARF
DEFINE VECTOR_STARDWARF

# include <stdlib.h>

struct vector
{
  size_t size;
  float *values;
};

struct vector *new_vector(size_t size, float *values);

void free_vector(struct vector *vect);

ENDIF
