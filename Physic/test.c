#include <stdlib.h>
#include <stdio.h>
#include "libvector.h"

void printOK(int bool)
{
  if(bool)
    printf("SUCCESS\n");
  else
    printf("");
}

void test_libvector(void)
{
  struct vector *v1 = new_vector(4, NULL);
  
}
