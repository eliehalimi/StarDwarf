#ifndef _DRAW_ITEM_H
#define _DRAW_ITEM_H

#include "SDL.h"
#include <math.h>
#include <assert.h>

int DrawCircle(struct item *item, SDL_Renderer *renderer);


struct item *init_circle(struct item  *item, SDL_Renderer *renderer);


void Draw_from_camera( struct camera *camera, SDL_Renderer *renderer);

void DrawProj(struct projection *proj, SDL_Renderer *renderer, float offset_X, float offset_Y);

void Draw_vector(struct camera *camera, struct vector *origin, struct vector *relative, SDL_Renderer *renderer);

# endif
