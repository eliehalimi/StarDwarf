#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "../Physic/physic.h"

void save_system(struct system *sytem) //name if several systems in one simulation 
{
	assert(system != NULL);

	FILE *f = fopen("system.txt", "r");
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
	while( (size_t c = fread(&buf, 1, 1, f)) > 0)
	{
		*(s+i);
		i++;
	}
	return s;
}

