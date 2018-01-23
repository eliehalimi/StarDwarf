# include "libvector.h"

struct vector *new_vector(const size_t size, const float *values)
{
  struct vector *res = malloc(sizeof(struct vector));
  res->size = size;
  res->values = calloc(sizeof(float), size);
  if(values != NULL)
    for(size_t i = 0; i < size; ++i)
      res->values[i] = values[i];
  return res;
}

void free_vector(struct vector *vect)
{
  free(vect->values);
  free(vect);
}
