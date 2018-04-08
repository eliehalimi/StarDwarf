#include "SDL.h"
#include <SDL2/SDL.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL_image.h>
#include <assert.h>
#include "../Physic/physic.h"
#include "../Physic/libvector.h"
#include "camera.h"


struct camera *new_camera(struct system)
{
	struct camera *camera = calloc(sizeof(struct camera), 1);
	camera->position.size = 3;
	camera->origin.size = 3;
	camera->depth = 1.0f;
	return camera;
}

struct projection *new_projection(struct item *item)
{
	assert(item != NULL);

	struct projection *projection = calloc(sizeof(struct projection), 1);
	projecction->item = item;
	projection->position.size = 2;
	return projection;
}

void push_projection(struct camera *camera, struct projection *projection)
{
	projection->next.next = camera->projections.next;
	camera->next.next = &projection>next;
}

int remove_projection(struct camera *camera, struct projection *projection);
{
	struct list *l = camera->projections.next;
	while(l != projection && l != NULL)
	{
	  l = l->next;
	}
	if(l == NULL)
	  return 0;

	
	
	return 1;
}

void free_camera(struct camera *camera)
{
	assert(camera != NULL);
	assert(camera->position.values != NULL);
	assert(camera->origin.values != NULL);


	free(camera->position.values);
	free(camera->origin.values);

	for(struct list *l = camera->projections.next; l != NULL;)
	{
		struct projection *p = CONTAINER_OF_(struct projection, list, l);
		l = l->next;
		free(p);
	}
}

void update_projection(struct projection *projection, struct camera *camera);

void sort_projections(struct camera *camera);

void rotate_camera(struct camera *camera, float alpha, float beta);

void move_camera(struct camera *camera, struct vector *translation);

void Draw_from_camera(struct camera *camera);
