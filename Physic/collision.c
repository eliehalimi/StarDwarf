# include <stdlib.h>
# include <stdio.h>
# include "libvector.h"
# include "physic.h"
# include "collision.h"
# include "math.h"
# include "forces.h"
void collide(struct item *i1, struct item *i2)
{
  //smallest mass of a planet : 3.301 x 10^23 kg 
  //biggest mass of a asteroid : 939.3 X 10^18 kg
  //assume that the mass input is under unit quadrillion kg (10^15)
  float ratio = 0;
  float m1 = i1->mass, m2 = i2->mass;
  if (m1>m2)
    ratio = m1/m2;
  else
    ratio = m2/m1;
  if (ratio >=  100) //collision bwt a asteriod and a planet
    {
      if (m1 > m2) //i1 is a planet
	{
	  //m1v1 + m2v2 = (m1+m2)v1'
	  printf("%f \n", ratio);
	  i1->velocity =*(clone_vector(add_vector(scalar_product_vector(m1/(m1+m2), &(i1->velocity)), scalar_product_vector(m2/(m1+m2), &(i2->velocity)))));
	  i1->mass += i2->mass;
	  free_item(i2);
	}
      else
	{
	  i2->velocity = *add_vector(scalar_product_vector(m1/(m1+m2), &(i1->velocity)), scalar_product_vector(m2/(m1+m2), &(i2->velocity)));
	  i2->mass += i1->mass;
	  free_item(i1);
	}
    }
  else //collision bwt 2 planets or 2 asteroids
    {
      //m1v1+m2v2 = m1v1'+m2v2'
      //m1v1 = m2v2' and m2v2 = m1v1'
      struct vector *v1 = clone_vector(&(i1->velocity));
      struct vector *v2 = clone_vector(&(i2->velocity));
      
      i2->velocity = *scalar_product_vector((m1/m2), v1);
      i1->velocity = *scalar_product_vector((m2/m1), v2);

      free_vector(v1);
      free_vector(v2);
    }
}
