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

struct vector *sub_vector(const struct vector *in, struct vector *out);

float magnitude_vector(const struct vector *vect);

float inner_product(const struct vector *v1, const struct vector *v2);

struct vector *orthogonal_projection(const struct vector *list_vector, const struct vector *vector);

struct vector *gram_schmidt(const struct vector *basis);

struct  vector *orthonormal_projection(const struct vector *basis, const struct vector *vector);

# endif
