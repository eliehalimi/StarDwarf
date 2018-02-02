# include <stdlib.h>
# include <stdio.h>
# include "libvector.h"
# include "physic.h"

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
  printf("\tSingle update on an object falling at -10 Newton, with no initial velocity, in 3D : \n");
  struct vector *p = new_vector(3, NULL);
  struct item *item = new_item(p);
  item->force.values[1] = - 10.0f;
  update_item(item, 1.0f);
  float check[] = {0.0f, -10.0f, 0.0f};
  printf("\t\tNew velocity values are : \n");
  for(size_t i = 0;  i < item->nb_dimension; ++i)
    {
      printf("\t\t\tValue is : %f : (%f expected) : ", item->velocity.values[i], check[i]);
      printOK(item->velocity.values[i] == check[i]);
    }
  printf("\n\t\tNew position values are : \n");
  for(size_t i = 0;  i < item->nb_dimension; ++i)
    {
      printf("\t\t\tValue is : %f : (%f expected) : ", item->position.values[i], check[i]);
      printOK(item->position.values[i] == check[i]);
    }  
  free_vector(p);
  free_item(item);
  printf("\n");
}



//##########
//## MAIN ##
//##########


int main(int argc, char *argv[])
{
  int test_vector = 0;
  int test_physic = 0;
  if(argc == 1)
    {
      test_vector = 1;
      test_physic = 1;
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
      printf("%c : Unknown letter\n", *argv[i]);
    }

  if(test_vector)
    test_libvector();
  
  if(test_physic)
    test_Physic();
  
  return 0;
}
