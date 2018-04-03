#include "SDL.h"
#include <SDL2/SDL.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL_image.h>
#include <assert.h>
#include "../Physic/physic.h"

#include "draw_item.h"


#define SCR_WDT 1280
#define SCR_HGT 960
#define M_PI	3.14159265358979323846264338327950288

const int SCR_CEN_X = SCR_WDT / 2;
const int SCR_CEN_Y = SCR_HGT / 2;

struct item *init_circle(struct item *item)
{

	//assert radius

	DrawCircle(item);
	return item;
}


int DrawCircle(struct item *item)
{
	SDL_Renderer *renderer = item->renderer;
	struct vector *position = &item->position;
	int radius = item->size / 2;
	int x = position->values[0];
	int y = position->values[1];

	int new_x = 0;
	int new_y = 0;
	int old_x = x +radius;
	int old_y = y;
	float step = (M_PI *2) /50;

	/* SETS COLOR
	 *  WILL ADD A WAY TO CHANGE THE COLOR LATER ON*/
	SDL_SetRenderDrawColor (renderer, 255, 255, 255, 255);

	for (float theta = 0; theta <= (M_PI *2); theta += step)
	{
		new_x = x + (radius * cos(theta));
		new_y = y - (radius * sin (theta));
		SDL_RenderDrawLine(renderer, old_x, old_y, new_x, new_y);
		old_x = new_x;
		old_y = new_y;
	}

	new_x = x + (radius * cos(0));
	new_y = y - (radius * sin(0));

	SDL_RenderDrawLine(renderer, old_x, old_y, new_x, new_y);
	return old_x;
}

void MoveItem(struct item *item, const struct vector *position)
{
	assert(item != NULL);
	assert(position != NULL);
	assert(item->renderer != NULL);
	assert(item->texture != NULL);
	assert(item->rect != NULL);
	assert(position->size == item->nb_dimension);
	assert(position->size ==2); //might change in the future, but we stick with 2D for now

	item->position.values[0] = position->values[0];
	item->position.values[1] = position->values[1];


	SDL_RenderClear(item->renderer);
	SDL_RenderCopy(item->renderer, item->texture, NULL, item->rect);
	DrawCircle(item);
	SDL_SetRenderDrawColor(item->renderer, 0,0,0,255);
	SDL_RenderPresent(item->renderer);

	return;
}

void MoveItemLinear(struct item *item, const struct vector *position, float *time_arrival, float time_frame)
{
	assert(item != NULL);
	assert(position != NULL);
	assert(time_arrival != NULL);

	if(*time_arrival <= time_frame)
	{
		MoveItem(item, position);
		*time_arrival = 0;
		return;
	}

	struct vector *pos = clone_vector(position);
	
	sub_vector(&item->position, pos);
	scalar_product_vector(time_frame / *time_arrival, pos);
	add_vector(&item->position, pos);
	MoveItem(item, pos);
	*time_arrival -= time_frame;
}
