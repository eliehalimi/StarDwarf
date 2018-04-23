#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "save.h"
#include "../Physic/physic.h"
/*
void save_system(struct system *system) //name if several systems in one simulation 
{
	//assert(system != NULL);

	FILE *f = fopen("system.txt", "w+");
	assert(f != NULL);
	
	fwrite(&system,sizeof(system), sizeof(char), f);
}*/
/*
struct system *load_system(char *path)
{
	FILE *f = fopen(path, "w+");
	assert(f != NULL);

	struct system *s = malloc(sizeof(struct system));
	
	int i = 0;
	char buf[1];
	size_t c;
	while( (c = fread(&buf, 1, 1, f)) > 0)
	{	
		i++;
	}
	return s;
}
*/
struct system *load_system(char *path, struct system *sys) //ADD SYSTEM SO THAT I CAN ADD CAMERA 
{
	FILE *f = fopen(path, "r");
	assert(f != NULL);
	assert(system != NULL);
	///struct system *sys = new_system(3);
	//sys->delta_time = 0.1f;
	//sys->camera = new_camera(WINDOW_W /2, WINDOW_H /2);
	char line[255];

	while(fgets(line, sizeof(line), f) != NULL)
	{
		char *str;
		str = strtok(line, " ");
		int counter = 1;	
		

		float x = 0;
		float y = 0;
		float z = 0;	
		double mass = 0;
		//double elec_charge = 0;
		double size = 0;
		float val[3] = {0, 0, 0};
		struct vector *position  = NULL;
		struct item *item = NULL;
		while (str != NULL)
		{
			printf("%s\n", str);
			switch(counter)
			{
				case 1:
					x = (float) atoi(str);
					val[0] = x;
					counter++;
					break;
				case 2:
					y = (float) atoi(str);
					val[1] = y;
					counter++;
					break;
				case 3:
					z = (float) atoi(str);
					val[2] = z;
				      	counter++;
					break;
				case 4:
					size = (double) atol(str);
					counter++;
					break;
				case 5:
					mass = (double) atol(str);
					counter++;
					break;
				default:
					break;
			}
		
			str = strtok(NULL, " ");
		}
		printf("val{%f, %f, %f} \n", val[0], val[1], val[2]);
		position = new_vector(3, val);				
		item = new_item(position);
		item->size = size;
		item->mass = mass;
		printf("%f %f", item->size, item->mass);

		push_item(sys, item);
		//str = strtok(NULL, " ");
		free_vector(position);
		printf("%d %d %d %f %f \n", item->position.values[0], item->position.values[1],
			       	item->position.values[2], item->mass, item->size);
		
	}
	return sys;
}
/*
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
	
		const float val[2] = {x, y};
		const float *values = (const float *) val;

		const struct vector *position = new_vector(2, values);
		struct item *item = new_item(position);
		item->size = z;
		item->mass = 100000000000000.0f;
		item->nb_dimension = 2;
		item->mass = 100000000000.0f; // there is an assertion in the update update to check the mass -> you need to initialize it
		push_item(s, item);
		printf("x= %f, y=%f, size=%d\n", x, y, z); 
	}
*/
