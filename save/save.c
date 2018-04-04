#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "save.h"
#include "../Physic/physic.h"

void save_system(struct system *system) //name if several systems in one simulation 
{
	//assert(system != NULL);

	FILE *f = fopen("system.txt", "w+");
	assert(f != NULL);
	
	fwrite(&system,sizeof(system), sizeof(char), f);
}

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
	//	*(s+i);
		i++;
	}
	return s;
}

