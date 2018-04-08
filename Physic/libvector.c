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
	/*r (size_t i = 0; i < vect->size; ++i)
	  {
	  sum += powl(vect->values[i],2);
	  }*/
	sum = inner_product(vect, vect);
	return sqrt(sum);
}

float inner_product(const struct vector *v1, const struct vector *v2)
{
	assert(v1 != NULL);
	assert(v2 != NULL);
	assert(v1->size == v2->size);

	float res = 0;
	for(size_t i = 0; i < v1->size; i++)
		res += v1->values[i] * v2->values[i];
	return res;
}


struct vector *orthogonal_projection(const struct vector *list_vector, const struct vector *vector)
{
	assert(list_vector != NULL);
	assert(vector != NULL);

	struct vector *res = new_vector(vector->size, NULL);

	for(struct list *l = &list_vector->next; l != NULL; l = l->next)
	{
		struct vector *b = CONTAINER_OF_(struct vector, list, l);
		assert(b->size == vector->size);

		struct vecotr *e = scalar_product_vector(inner_product(vector, b), clone_vector(b));

		add_vector(e, res);
		free_vector(e);
	}
}


struct vector *gram_schmidt(const struct vector *basis)
{
  assert(basis != NULL);
  
  struct vector *res = clone_vector(basis);
  struct vector *current = res;
  
  for(struct list *lk = basis->list.next; lk != NULL; lk = lk->next)
    {
      struct vector *sub = new_vector(res->size, NULL);
      struct vector *e = clone_vector(CONTAINER_OF_(struct vector, list, lk));
      
      for(struct list *li = &res->list; li != lk; li = li->next)
	{
	  struct vecotr *eps = clone_vector(CONTAINER_OF_(struct vector, list, li));
	  float ratio = inner_product(e, eps) / inner_product(eps, eps);
	  add_vector(scalar_product_vector(ratio, eps), sub);

	  free_vector(eps);
	}

      sub_vector(sub, e);
      free_vector(sub);
      current->next.next = e;
      current = e;
    }

  return res;
}
