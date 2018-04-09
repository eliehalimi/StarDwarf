#ifndef _CAMERA_H
#define _CAMERA_H

#include "SDL.h"
#include <SDL2/SDL.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL_image.h>
#include <assert.h>
#include "../Physic/physic.h"
#include "../Physic/libvector.h"

struct camera
{
	struct vector position;
	struct vector origin;
	struct vector Vx;
	struct vector Vy;
	float depth;
	size_t nb_proj;
	struct list projections;
};

struct projection
{
	struct item *item;
	struct vector position;
	float size;
	float distance;
  int shown;
  struct list next;
};

struct camera *new_camera(void);

struct projection *new_projection(const struct item *item);

void free_camera(struct camera *camera);

void push_projection(struct camera *camera, struct projection *projection);

int remove_projection(struct camera *camera, struct projection *projection);

void update_projections(struct camera *camera);

void sort_projections(struct camera *camera);

void rotate_camera(struct camera *camera, float alpha, float beta);

void move_camera(struct camera *camera, const struct vector *translation);

void Draw_from_camera(const struct camera *camera);

# endif
