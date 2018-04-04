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
struct system *load_system(char *path)
{
	FILE *f = fopen(path, "r");
	assert(f != NULL);

	struct system *s = new_system(2);
	s->delta_time = 0.1f;
	char line[255];

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
	
		const float val[2] = {x, y};
		const float *values = (const float *) val;

		const struct vector *position = new_vector(2, values);
		struct item *item = new_item(position);
		item->size = z;
		item->nb_dimension = 2;
		push_item(s, item);
		printf("x= %f, y=%f, size=%d\n", x, y, z); 
	}
	return s;
	
}

