#include "SDL.h"
#include <SDL2/SDL.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL_image.h>
#include <assert.h>
#include "../Physic/physic.h"

#define SCR_WDT 1280
#define SCR_HGT 960
#define M_PI	3.14159265358979323846264338327950288

const int SCR_CEN_X = SCR_WDT / 2;
const int SCR_CEN_Y = SCR_HGT / 2;

struct item *init_circle(struct item  *item, int radius)
{
	assert(radius>0);
	
	DrawCircle(renderer, item, radius);
	return item;
}


int DrawCircle(SDL_Renderer *renderer, struct item *item, int radius)
{
	assert(item->position->size ==2);
	struct vector *position = item->position;
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

void MoveCircle(SDL_Renderer *renderer, struct item *item, struct vector *position, SDL_Texture *bg, SDL_Rect *tex)
{
	assert (item->position->size == 2);
	//int x = item->position->values[0];
	//int y = item->position->values[1];

	int a = position->values[0];
	int b = position->values[1];

	if (a<0 || a > SCR_WDT)
		return -1;
	if (b<0 || b > SCR_HGT)
		return -1;
	
	SDL_Event event;
	int is_running = 1;

	while(is_running)
	{
		SDL_WaitEvent(&event);
		if (event.type == SDL_QUIT)
			is_running = 0;
		if (event.type == SDL_KEYDOWN)
		{
			switch(event.key.keysym.sym)
			{
				case SDLK_RETURN:
					is_running = 0;
					break;
				case SDLK_LEFT:
					if (item->position->values[0] > radius)
						item->position->values[0] -=1;
					break;
				case SDLK_RIGHT:
					if (item->position->values[0] < a -radius)
						item->position->values[0] +=1;
					break;
				case SDLK_UP:
					if (item->position->values[1] > radius)
						item->position->values[1] -=1;
					break;
				case SDLK_DOWN:
					if (item->position->values[1] < b-radius)
						item->position->values[1] +=1;
					break;
				default:
					break;
			}
		 }

		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, bg, NULL, tex);
		DrawCircle(renderer, item->position->values[0], item->position->values[1], radius);
		SDL_SetRenderDrawColor(renderer, 0,0,0,255);
		SDL_RenderPresent(renderer);
	}	
	return 1;
}



