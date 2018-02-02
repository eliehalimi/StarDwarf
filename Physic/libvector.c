# include <assert.h>
# include <math.h>
# include "libvector.h"

struct vector *new_vector(const size_t size, const float *values)
{
  struct vector *res = calloc(sizeof(struct vector), 1);
  res->size = size;
  res->values = calloc(sizeof(float), size);
  if(values != NULL)
    for(size_t i = 0; i < size; ++i)
      res->values[i] = values[i];
  return res;
}

void free_vector(struct vector *vect)
{
  assert(vect != NULL);
  assert(vect->values != NULL);
  
  free(vect->values);
  free(vect);
}

struct vector * add_vector(const struct vector *in, struct vector *out)
{
  assert(in != NULL);
  assert(out != NULL);
  assert(in->values != NULL);
  assert(out->values != NULL);
  assert(in->size == out->size);
  
  for(size_t i = 0; i < in->size; ++i)
    out->values[i] += in->values[i];
  
  return out;
}


struct vector * sub_vector(const struct vector *in, struct vector *out)
{
  assert(in != NULL);
  assert(out != NULL);
  assert(in->values != NULL);
  assert(out->values != NULL);
  assert(in->size == out->size);
  
  for(size_t i = 0; i < in->size; ++i)
    out->values[i] -= in->values[i];
  
  return out;
}


struct vector *scalar_product_vector(float scalar, struct vector *out)
{
  assert(out != NULL);
  assert(out->values != NULL);

  for(size_t i = 0; i < out->size; ++i)
    out->values[i] *= scalar;

  return out;
}

struct vector *clone_vector(const struct vector *vect)
{
  return new_vector(vect->size, vect->values);
}

float magnitude_vector (const struct vector *vect)
{
  float sum; // = sqrt(x^2 + y^2 + z^2+....)
  for (size_t i = 0; i < vect->size; ++i)
    sum += vect->values[i] * vect->values[i];
  return sqrt(sum);
}
