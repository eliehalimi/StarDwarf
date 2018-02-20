# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include "libvector.h"
# include "physic.h"
# include <math.h>
# include "forces.h"
# include "collision.h"
void printOK(int bool)
{
  if(bool)
    printf("SUCCESS\n");
  else
    printf("!!! FAILURE !!!\n\n");
}

//#######################
//## TESTING LIBVECTOR ##
//#######################

void test_libvector(void)
{
  struct vector *v1 = new_vector(4, NULL);
  float tab[] = {0, 1, 2, 3, 4};
  struct vector *v2 = new_vector(5, tab);

  printf("\nTESTING LIBVECTOR :\n");

  printf("\tCreating empty vector of size 4 :\n");
  printf("\t\tVector size : %lu : (4 expected) : ", v1->size);
  printOK(v1->size == 4);
  printf("\t\tCorrect values:\n");
  for(size_t i = 0; i < 4; ++i)
    {
      printf("\t\t\tValue is : %f : (0 expected) : ", v1->values[0]);
      printOK(v1->values[0] == 0);
    }

  printf("\n\tCreating vector from array [0, 1, 2, 3, 4] :\n");
  printf("\t\tCorrect size : %lu : (5 expected) : ", v2->size);
  printOK(v2->size == 5);
  printf("\t\tCorrect values :\n");
  for(size_t i = 0;  i < v2->size; ++i)
    {
      printf("\t\t\tValue is : %f : (%lu expected) : ", v2->values[i], i);
      printOK(v2->values[i] == (float) i);
    }

  free_vector(v1);
  v1 = new_vector(5, tab);
  scalar_product_vector(2.0f, v1);
  printf("\n\tScalar product of 2 with [0, 1, 2, 3, 4] :\n");
  printf("\t\tCorrect size : %lu : (5 expected) : ", v1->size);
  printOK(v1->size == 5);
  printf("\t\tCorrect values :\n");
  for(size_t i = 0;  i < v2->size; ++i)
    {
      printf("\t\t\tValue is : %f : (%lu expected) : ", v1->values[i], i * 2);
      printOK(v1->values[i] == (float) i * 2);
    }
  
  printf("\n\tAdding vectors : [0, 1, 2, 3, 4] + [1, 1, 1, 1, 1]\n");
  free_vector(v1);
  float tab2[] = {1, 1, 1, 1, 1};
  v1 = new_vector(5, tab2);
  add_vector(v1, v2);
  printf("\t\tCorrect values :\n");
  for(size_t i = 0;  i < v2->size; ++i)
    {
      printf("\t\t\tValue is : %f : (%lu expected) : ", v2->values[i], i + 1);
      printOK(v2->values[i] == (float) i + 1.0f);
    }

  printf("\n\tlist of vectors:\n\t\tLinking the two vectors :\n");
  v1->list.next = &v2->list;
  printf("\t\tRetrieving the vector : %p (%p expected) : ", (void *)CONTAINER_OF_(struct vector, list, v1->list.next), (void *) v2);
  printOK(v2 == CONTAINER_OF_(struct vector, list, v1->list.next));
  printf("\n");
  free_vector(v1);
  free_vector(v2);
}

//############
//## PHYSIC ##
//############

void test_Physic(void)
{
  printf("\nTESTING PHYSIC :\n");
  printf("\tSystem performing two updates on two objects at a distance of 10, and with mass of 10 and 100, in 3D : \n");
  struct system *s = new_system(3);
  s->delta_time = 1.0f;
  struct vector *p = new_vector(3, NULL);
  struct item *item = new_item(p);
  struct item *item2 = new_item(p);
  
  item->mass = 10.0f;
  item2->mass = 100.0f;
  item->position.values[2] = -10.0f;
  
  push_item(s, item);
  push_item(s, item2);

  update_system(s);
  update_system(s);

  printf("\t\tItem 1 :\n");
  //float checkp[] = {0.0f, -10.0f, 0.0f};
  printf("\t\t\tNew force values are : \n");
  for(size_t i = 0;  i < item->nb_dimension; ++i)
    {
      printf("\t\t\t\tValue is : %f\n", item->velocity.values[i]);
      //printOK(item->velocity.values[i] == check[i]);
    }
  printf("\t\t\tNew velocity values are : \n");
  for(size_t i = 0;  i < item->nb_dimension; ++i)
    {
      printf("\t\t\t\tValue is : %f\n", item->velocity.values[i]);
      //printOK(item->velocity.values[i] == check[i]);
    }
  printf("\n\t\t\tNew position values are : \n");
  for(size_t i = 0;  i < item->nb_dimension; ++i)
    {
      printf("\t\t\t\tValue is : %f\n", item->position.values[i]);
      //printOK(item->position.values[i] == check[i]);
    }

  printf("\t\tItem 2 :\n");

  printf("\t\t\tNew force values are : \n");
  for(size_t i = 0;  i < item2->nb_dimension; ++i)
    {
      printf("\t\t\t\tValue is : %f\n", item2->velocity.values[i]);
      //printOK(item->velocity.values[i] == check[i]);
    }
  printf("\t\t\tNew velocity values are : \n");
  for(size_t i = 0;  i < item2->nb_dimension; ++i)
    {
      printf("\t\t\t\tValue is : %f\n", item2->velocity.values[i]);
      //printOK(item->velocity.values[i] == check[i]);
    }
  printf("\n\t\t\tNew position values are : \n");
  for(size_t i = 0;  i < item2->nb_dimension; ++i)
    {
      printf("\t\t\t\tValue is : %f\n", item2->position.values[i]);
      //printOK(item->position.values[i] == check[i]);
    }
  
  
  free_vector(p);
  free_item(remove_item(s, item));
  free_item(remove_item(s, item2));
  free_system(s);
  printf("\n");
}

//#######################
//## TESTING FORCES ##
//#######################

void test_forces(void)
{
  float tab1[] = {5,4,-4,4,4};
  float tab2[] = {1,1,1,-1,-1};
  struct vector *v1 = new_vector(5, tab1);
  struct vector *v2 = new_vector(5, tab2);
  struct item *i1 = new_item(v1);
  struct item *i2 = new_item(v2);
  i1->mass = 5*powf(10,7);
  i2->mass = 1*powf(10,7);
  struct vector *f1 = gra_force(i1,i2);// i2 acts on i1
  struct vector *f2 = gra_force(i2,i1);//i1 acts on i2
  size_t k = 0;
  while (k < f1->size && f1->values[k] == -1*(f2->values[k]))
    ++k;

  printf("\nTESTING GRAVITATIONAL FORCE : ");
  printOK(k==f1->size);
  printf("\tCreate new item 1 at position : \n");
  printf("\t\t");
  for(size_t i = 0;  i < v1->size; ++i)
    {
      printf(" % 4.0f ", v1->values[i]);
    }
  printf("\n\tCreate new item 2 at position : \n");
  printf("\t\t");
  for(size_t i = 0;  i < v2->size; ++i)
    {
      printf(" %4.0f ", v2->values[i]);
    }
  printf("\n\tF1 (i2 acts on i1) : \n");
  printf("\t\t");
  for(size_t i = 0;  i < f1->size; ++i)
    {
      printf(" %4.0f  ", f1->values[i]);
    } 
  printf("\n\tF2 (i1 acts on i2) : \n");
  printf("\t\t");
  for(size_t i = 0;  i < f2->size; ++i)
    {
      printf(" %4.0f ", f2->values[i]);
    } 
  free_vector(v1);
  free_vector(v2);
  free_item(i1);
  free_item(i2);
  free_vector(f1);
  free_vector(f2);
}

//############
//## TESTING COLLISION ##
//############

void test_collision(void)
{

  
  float tab1[] = {1,2,3}; //tab2[] = {4,5,6};  
  float tabpos1[] = {1,1,1}, tabpos2[] = {1,1,1}, tabpos3[] = {1,1,1}, tabpos4[] ={1,1,1};
  struct vector *p1 = new_vector(3, tabpos1);
  struct vector *p2 = new_vector(3, tabpos2);
  struct vector *p3 = new_vector(3, tabpos3);
  struct vector *p4 = new_vector(3, tabpos4);
  struct item *i1 = new_item(p1);
  struct item *i2 = new_item(p2);
  struct item *i3 = new_item(p3);
  struct item *i4 = new_item(p4);

  
  struct vector *v1 = new_vector(3, tab1);
  memcpy(i1->velocity.values, &v1->values, sizeof(float) * 3);
  free_vector(v1);

  /*
  i1->mass = 150*powf(10,7);
  i2->mass = 1*powf(10,7);
  printf("\nTESTING COLLISION :\n");
  printf("\tCollision between a planet and a asteroid: \n");
  printf("\t\t m1: planet ; m2 : asteriod and m1=150m2\n");
  printf("\t\t\t velocity of m1 before colliding with m2: ");
  for(size_t i = 0;  i < i1->velocity.size; ++i)
    {
      printf(" %2.0f ", i1->velocity.values[i]);
    }
  printf("\n ");
  
  collide(i1,i2);
  
  printf("\t\t\t velocity of m1 after colliding with m2 (m2 is destroyed and  merged with m1): ");
  for(size_t i = 0;  i < i1->velocity.size; ++i)
    {
      printf(" %2.0f ", i1->velocity.values[i]);
    }


  i3->mass = 2*powf(10,7);
  i4->mass = 1*powf(10,7);
  
  printf("\tCollision between 2 planets or 2 asteroid : \n");
  printf("\t\t After colliding each other, m1v1' = m2v2, m2v2' = m1v1 \n");
  printf("\t\t Assume m1 = 2m2, v1' = v2/2 and v2' = 2v1\n");
  printf("\t\t\t velocity of m1 before colliding with m2: ");
  for(size_t i = 0;  i < i3->velocity.size; ++i)
    {
      printf(" %f ", i3->velocity.values[i]);
    }
  printf("\t\t\t velocity of m2 before colliding with m1: ");
  for(size_t i = 0;  i < i4->velocity.size; ++i)
    {
      printf(" %f ", i4->velocity.values[i]);
    }

  printf("\n");
  collide(i3, i4);
  printf("\t\t\t velocity of m1 after collision: ");
  for(size_t i = 0;  i < i3->velocity.size; ++i)
    {
      printf(" %f ", i3->velocity.values[i]);
    }
  printf("\t\t\t velocity of m2 after collision: ");
  for(size_t i = 0;  i < i4->velocity.size; ++i)
    {
      printf(" %f ", i4->velocity.values[i]);
    }
  printf("\n");
  */
  free_item(i1);
  free_item(i2);
  free_item(i3);
  free_item(i4);
  free_vector(p1);
  free_vector(p2);
  free_vector(p3);
  free_vector(p4);

}


//##########
//## MAIN ##
//##########


int main(int argc, char *argv[])
{
  int test_vector = 0;
  int test_physic = 0;
  int test_force = 0;
  int test_Collision = 0;
  if(argc == 1)
    {
      test_vector = 1;
      test_physic = 1;
      test_force = 1;
      test_Collision = 1;
    }

  for(size_t i = 1; i < (size_t)argc; ++i)
    {
      if(*argv[i] == 'v')
	{
	  test_vector = 1;
	  continue;
	}
      if(*argv[i] == 'p')
	{
	  test_physic = 1;
	  continue;
	}
      if(*argv[i] == 'f')
	{
	  test_force = 1;
	  continue;
	}
      
      if(*argv[i] == 'c')
	{
	  test_Collision = 1;
	  continue;
	}
      
      printf("%c : Unknown letter\n", *argv[i]);
    }

  if(test_vector)
    test_libvector();
  
  if(test_physic)
    test_Physic();
  
  if(test_force)
    test_forces();

  
  if(test_Collision)
    test_collision();
  return 0;
}
