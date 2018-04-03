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

int DrawCircle(SDL_Renderer *renderer, struct item *item);

void MoveItem(struct item *item, struct vector *position);

struct item *init_circle(struct item  *item, int radius);


# ENDIF
