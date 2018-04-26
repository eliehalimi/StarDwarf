#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "save.h"
#include "../Physic/physic.h"

void save_system(struct system *system) 
{
	assert(system != NULL);
	assert(system->delta_time > 0.0f);
	assert(system->nb_dimension == 3);

	FILE *f = fopen("system.txt", "w+");
	assert(f != NULL);
	
	char *str;
	
	float size;
	float mass;
	float nbdimension;
	struct vector *pos; 
	struct vector *velocity; //WILL ADD IT TO THE LOAD_SYSTEM function


	for (struct list *l = system->items.next; l != NULL; l = l->next)
	{
		struct item *i = CONTAINER_OF_(struct item, list, l);
		size = i->size;
		mass = i->mass;
		nbdimension = i->nb_dimension;
		pos = &i->position;
		velocity = &i->velocity;
	
		printf("%f, %f, %f\n pos = %f %f %f\nvel = %f %f %f", size, mass, nbdimension,
		       pos->values[0], pos->values[1], pos->values[2],
		       velocity->values[0], velocity->values[1], velocity->values[2]); 
		
		//WILL MAKE IT PRINT INTO FILE DESCRIPTOR (system.txt);
	}
}


struct system *load_system(char *path)
{
	FILE *f = fopen(path, "r");
	assert(f != NULL);

	struct system *s = new_system(2);
	s->delta_time = 0.1f;
	char line[255];
	s->camera = new_camera(WINDOW_H / 2, WINDOW_W / 2);
	
	while(fgets(line, sizeof(line), f) != NULL)
	{
		char val1[16] ,val2[9], val3[10];

		char *tok1 = strtok(line, " ");
		char *tok;
		int v1 = 1;
		while ((tok = strtok(NULL, " ")) != NULL)
		{
			if (v1)
			{
				strcpy(val1, tok1);
				v1 = 0;
			}
			else
				strcpy(val2, tok1);
			tok1 = tok;
		}
		if (tok1 != NULL)
			 strcpy(val3,tok1);


		float x = (float) atoi(val1);
		float y = (float) atoi(val2);
		int z = atoi(val3);
	
		const float val[3] = {x, y, 0};
		const float *values = (const float *) val;

		const struct vector *position = new_vector(3, values);
		struct item *item = new_item(position);
		item->size = z;
		item->mass = 100000000000000.0f;
		item->mass = 100000000000.0f; // there is an assertion in the update update to check the mass -> you need to initialize it
		push_item(s, item);
		printf("x= %f, y=%f, size=%d\n", x, y, z); 
	}
	return s;
	
}

