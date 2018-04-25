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

# define NOTMOVING 0
# define ROTATING 1
# define TRANSLATING 2
# define CREATING 3
# define SELECTED 4


# define WINDOW_W 1280
# define WINDOW_H 720

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
  float mouse_x, mouse_y;
  int event_type;
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

void dolly_rotation(struct camera *camera, float rotZ, float rotX);

struct item *selecting_item(struct camera *camera);

struct vector *selecting_position(struct camera *camera);

# endif
