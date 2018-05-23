#ifndef _DRAW_ITEM_H
#define _DRAW_ITEM_H

#include "SDL.h"
#include <math.h>
#include <assert.h>


# define SCR_WDT 1280
# define SCR_HGT 960

# define RATIO_SIZE_VECTOR 10

# define SCR_CEN_X SCR_WDT / 2
# define SCR_CEN_Y SCR_HGT / 2

# define MAXSIZEITEM 100000
# define SIZESIMPLE 5000



int DrawCircle(struct item *item, SDL_Renderer *renderer);


struct item *init_circle(struct item  *item, SDL_Renderer *renderer);


void Draw_from_camera( struct camera *camera, SDL_Renderer *renderer);

void DrawProj(struct projection *proj, SDL_Renderer *renderer, float offset_X, float offset_Y);

void Draw_vector(const struct camera *camera, const struct vector *origin, const struct vector *relative, SDL_Renderer *renderer);

# endif
