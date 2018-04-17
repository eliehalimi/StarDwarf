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
	float center_X;
	float center_Y;
};

struct projection
{
	struct item *item;
	struct vector position;
	float size;
	float distance;
	int shown;
	struct list next;
	struct list prev;
};

struct camera *new_camera(float center_X, float center_Y);

struct projection *new_projection(struct item *item);

void free_camera(struct camera *camera);

void push_projection(struct camera *camera, struct projection *projection);

int remove_projection(struct camera *camera, struct projection *projection);

void update_projections(struct camera *camera);

void sort_projections(struct camera *camera);

void rotate_camera(struct camera *camera, float alpha, float beta, float gamma);

void move_camera(struct camera *camera, const struct vector *translation);

void Draw_from_camera( struct camera *camera, SDL_Renderer *renderer);

void DrawProj(struct projection *proj, SDL_Renderer *renderer, float offset_X, float offset_Y);

void dolly_rotation(struct camera *camera, float rotZ, float rotX);

# endif
