# include <stdlib.h>
# include "libvector.h"
# include "physic.h"
# include "forces.h"
# include "math.h"
float distance(struct item *i1, struct item *i2)
{
  struct vector *sum = sub_vector(&(i2->position),clone_vector(&(i1->position)));
  float d =  magnitude_vector(sum);
  free_vector(sum);
  return d;
}


//calcutate gravitational force of i2 acts on i1 (i2 -> i1)
struct vector* gra_force(struct item *i1, struct item *i2)
{
  /* F= (G*m1*m2)/(r*r)           : N
     G = 6.67 * 10^(-11)
     m1,m2: mass of i1,i2         : kg
     r: distance bwt m1 and m2    : m
   */
  float G = 6.672 * powf(10,-11);
  float m1 = i1->mass, m2 = i2->size;
  float r = distance(i1,i2);
  float F_magnitude = (G*m1*m2)/powl(r,2);
  struct vector *F = sub_vector(&(i2->position), clone_vector(&(i1->position))); 
  F = scalar_product_vector(1/r,F); //finding vector unit
  F = scalar_product_vector(F_magnitude, F);
  return F; 
}
