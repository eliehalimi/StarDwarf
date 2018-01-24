# ifndef VECTOR_STARDWARF
# define VECTOR_STARDWARF

# include <stddef.h>

# define CONTAINER_OF_(TYPENAME_, FIELDNAME_, PTR_)\
  ((TYPENAME_ *)(((char*)PTR_ - offsetof(TYPENAME_, FIELDNAME_))))

# include <stdlib.h>

struct list
{
  struct list *next;
};

struct vector
{
  size_t size;
  float *values;
  struct list list;
};

struct vector *new_vector(size_t size, const float *values);

void free_vector(struct vector *vect);

struct vector*scalar_product_vector(float scalar, struct vector *out);

struct vector *add_vector(const struct vector *in, struct vector *out);

struct vector *clone_vector(const struct vector *vect);

# endif
