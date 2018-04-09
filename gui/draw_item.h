#ifndef _DRAW_ITEM_H
#define _DRAW_ITEM_H

#include "SDL.h"
#include <SDL2/SDL.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL_image.h>
#include <assert.h>
#include "../Physic/physic.h"
//#include "../Camera/camera.h"

int DrawCircle(struct item *item, SDL_Renderer *renderer);

void MoveItem(struct item *item, const struct vector *position);

void MoveItemLinear(struct item *item, const struct vector *position, float *time_arrival, float time_frame);

struct item *init_circle(struct item  *item, SDL_Renderer *renderer);


# endif
