# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include "libvector.h"
# include "physic.h"
# include "collision.h"
# include "math.h"
# include "forces.h"


int collide(struct system *system, struct item *i1, struct item *i2, struct item **destroyed)
{
	if (distance(i1,i2) < (i1->size / 2 + i2->size / 2))
	{
		//printf("collide\n");
		//rintf("distance:%f   r1:%f   r2:%f \n", distance(i1,i2), i1->size, i2->size);
		//smallest mass of a planet : 3.301 x 10^23 kg 
		//biggest mass of a asteroid : 939.3 X 10^18 kg
		//assume that the mass input is under unit quadrillion kg (10^15)
		*destroyed = NULL;
		float ratio = 0;
		float m1 = i1->mass, m2 = i2->mass;
		if (m1>m2)
			ratio = m1/m2;
		else
			ratio = m2/m1;
		if (ratio >=  100) //collision bwt a asteriod and a planet
		{

			struct vector *v = add_vector(scalar_product_vector(m1/(m1+m2), &(i1->velocity)), scalar_product_vector(m2/(m1+m2), &(i2->velocity)));

			if (m1 > m2) //i1 is a planet
			{
				if(system->selected == i2)
					system->selected = NULL;
				//m1v1 + m2v2 = (m1+m2)v1'
				memcpy(i1->velocity.values, v->values, sizeof(float)* v->size);
				i1->mass += i2->mass;

				add_vector(scalar_product_vector(m2/m1, &i2->velocity), &i1->velocity);
				free_item(remove_item(system, i2));
				*destroyed = i2;
			}
			else
			{
				if(system->selected == i1)
					system->selected = NULL;
				memcpy(i2->velocity.values, v->values, sizeof(float)*v->size);
				i2->mass += i1->mass;

				add_vector(scalar_product_vector(m1/m2, &i1->velocity), &i2->velocity);
				free_item(remove_item(system, i1));
				*destroyed = i1;
			}
			return 0;
		}
		else //collision bwt 2 planets or 2 asteroids
		{
			//m1v1+m2v2 = m1v1'+m2v2'
			//m1v1 = m2v2' and m2v2 = m1v1'
			struct vector *v1 = clone_vector(&(i1->velocity));
			struct vector *v2 = clone_vector(&(i2->velocity));

			memcpy(i2->velocity.values, scalar_product_vector((m1/m2), v1)->values, sizeof(float)*v1->size);
			memcpy(i1->velocity.values, scalar_product_vector((m2/m1), v2)->values, sizeof(float)*v2->size);

			free_vector(v1);
			free_vector(v2);
		}
		return 1;
	}
	return 0;
}
