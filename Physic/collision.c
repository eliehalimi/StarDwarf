# include <stdlib.h>
# include "libvector.h"
# include "physic.h"
# include "collide.h"
# include "math.h"
# include "forces.h"
void collide(struct item i1, struct item i2)
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
  if (ratio <=  100) //collision bwt a asteriod and a planet
    {
      if (m1 > m2) //i1 is a planet
	{
	  //m1v1 + m2v2 = (m1+m2)v1'
	  i1->velocity = (m1*i1->velocity + m2*i2->velocity)/(m1+m2);
	  free_item(i2);
	}
      else
	{
	  i2->velocity = (m1*i1->velocity + m2*i2->velocity)/(m1+m2);
	  free_item(i1);
	}
    }
  else //collision bwt 2 planets or 2 asteroids
    {
      //m1v1+m2v2 = m1v1'+m2v2'
      //m1(v1^2) + m2(v2)^2 = m1(v1')^2 + m2(v2')^2
      
    }
}
