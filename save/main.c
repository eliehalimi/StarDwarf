#include <stdio.h>
#include <stdlib.h>

#include "save.h"
#include "../Physic/physic.h"
#include "../Physic/libvector.h"

int main()
{

	struct system *system = new_system(2);

	const float val[2] = {500, 500};
	const float *values = (const float *) val;

	const struct vector *position = new_vector(2, values);
	struct item *item = new_item(position);
	item->size = 200;

	push_item(system, item);

	item->rect = NULL;
	puts("Drawing");
	printf("x = %f, y = %f\n", item->position.values[0], item->position.values[1]);
	puts("Finished Drawing");

	//save_system(system);
	load_system("system.txt");
	
	puts("saved");


}
