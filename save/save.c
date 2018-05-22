#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <err.h>

#include "save.h"
#include "../Physic/physic.h"

void save_system(struct system *system, char *name) 
{
	assert(system != NULL);
	assert(system->delta_time > 0.0f);
	assert(system->nb_dimension == 3);

	char path[18+strlen(name)+1];
	strcpy(path, "../save/save_files/");
	strcat(path, name);
	strcat(path, ".txt");
	FILE *f = fopen(path, "w+");
	assert(f != NULL);
	puts(path);

       	double mass, size;
	//char label[16];
	unsigned char *color;
	struct vector *pos, *velocity;
	
	int xpos = 0, ypos = 0, zpos = 0;
	int xvelocity = 0, yvelocity = 0, zvelocity = 0;
	int r = 0, g = 0, b = 0; 
	
	char safe[1024];
	int counter = 1;
	for (struct list *l = system->items.next; l != NULL; l = l->next)
	{
		struct item *i = CONTAINER_OF_(struct item, list, l);
		
		mass = i->mass;
		size = i->size;
		pos = &i->position;

		//label = i->label;
		color = &i->color;
		pos = &i->position;
		velocity = &i->velocity;
		
		for (int i = 0; i < 3; i++)
		{
			if (i == 0)
			{
				xpos = pos->values[i];
				xvelocity = velocity->values[i];
				r = color[i];
			}
			if (i == 1)
			{
				ypos = pos->values[i];
				yvelocity = velocity->values[i];
				g = color[i];
			}
			if (i == 2)
			{
				zpos = pos->values[i];
				zvelocity = velocity->values[i];
				b = color[i];
			}
		}
		
		if ((r == 0 && g != 255) || (r != 255 && g == 0))
			assert(b == 255);
		if ((r == 0 && b != 255) || (b == 0 && r != 255))
			assert(g == 255);
		if ((b != 255 && g == 0) || (b == 0 && g != 255))
			assert(r == 255);

		char item[255];
		fprintf(f, "%d %d %d %f %f %d %d %d %d %d %d\n",
			xpos, ypos, zpos, size, mass, r, g, b, xvelocity, yvelocity, zvelocity);	
		
		sprintf(item, "%d %d %d %f %f %d %d %d %d %d %d\n",
			xpos, ypos, zpos, size, mass, r, g, b, xvelocity, yvelocity, zvelocity);	
		if (counter == 1)
		{
			strcpy(safe, item);
			counter = 0;
		}
		else
			strcat(safe, item);	
		//strcpy(safe, item);
		puts(item);
		printf("%d %d %d %f %f %d %d %d %d %d %d\n"
		,xpos, ypos, zpos, size, mass, r, g, b, xvelocity, yvelocity, zvelocity);	

		//char *charitem = 
		//printf("%f, %f, %f\n pos = %f %f %f\nvel = %f %f %f", size, mass, nb_dimension,
		  //     pos->values[0], pos->values[1], pos->values[2],
		    //   velocity->values[0], velocity->values[1], velocity->values[2]); 
	}
	//fprintf(f,"%s",safe);

	fclose(f);
	puts("closed");
}


struct system *load_system(char *path)
{
	FILE *f = fopen(path, "r");
	assert(f != NULL);

	struct system *sys = new_system(3);
	sys->delta_time = 0.1f;
	char line[255];
	sys->camera = new_camera(WINDOW_W / 2, WINDOW_H / 2);
	
	while(fgets(line, sizeof(line), f) != NULL)
	{
		char *str;
		str = strtok(line, " ");
		int counter = 1;
		
		float x = 0;
		float y = 0;
		float z = 0;
		double mass = 0;
		double size = 0;
		float val[3] = {0,0,0};
		struct vector *position = NULL;
		struct item *item = NULL;
		int color0 = 0;
		int color1 = 0;
		int color2 = 0;
		int velocity0 = 0;
		int velocity1 = 0;
		int velocity2 = 0;
		char *label = "";

		while(str != NULL)
		{
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
				case 6:
					color0 = atoi(str);
					counter++;
					break;
				case 7:
					color1 = atoi(str);
					counter++;
					break;
				case 8:
					color2 = atoi(str);
					counter++;
					break;
				case 9:
					velocity0 = atoi(str);
					counter++;
					break;
				case 10:
					velocity1 = atoi(str);
					counter++;
					break;
				case 11:
					velocity2 = atoi(str);
					counter++;
					break;
				
				case 12:
					label = str;
					break;
				default:
					break;
			}
			
			str = strtok(NULL, " ");
		
		}
		assert(size != 0);
		assert(mass != 0);
		if (color0 == 0 && color1 == 0 && color2 == 0)
			err(1, "can't see planet");

		printf("%f, %f, %f\n%f, %f\n%d, %d, %d\n%d, %d, %d\n",
				x, y, z, size, mass, color0, color1, color2, velocity0, velocity1, velocity2);
		position = new_vector(3, val);
		item = new_item(position);
		item->size = size;
		item->mass = mass;
		item->rect = NULL;
		item->color[0] = color0;
		item->color[1] = color1;
		item->color[2] = color2;
		item->velocity.values[0] = velocity0;
		item->velocity.values[1] = velocity1;
		item->velocity.values[2] = velocity2;
		strcpy(item->label, label);
		push_item(sys, item);
		free_vector(position);
	}
	return sys;
}
