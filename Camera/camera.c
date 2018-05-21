#include <SDL2/SDL.h>
#include <math.h>
#include <stdlib.h>
#include <SDL2/SDL_image.h>
#include <assert.h>
#include "../Physic/physic.h"
#include "../Physic/libvector.h"
#include "camera.h"
#include "libmatrix.h"
#include "../gui/draw_item.h"


struct camera *new_camera(float center_X, float center_Y)
{
	struct camera *camera = calloc(sizeof(struct camera), 1);
	camera->position.size = 3;
	camera->origin.size = 3;
	camera->Vx.size = 3;
	camera->Vy.size = 3;
	camera->depth = 300;

	camera->position.values = calloc(sizeof(float), 3);
	camera->origin.values = calloc(sizeof(float), 3);
	camera->position.values[0] = 400;
	camera->position.values[1] = 0;
	camera->position.values[2] = 0;

	camera->Vx.values = calloc(sizeof(float), 3);
	camera->Vy.values = calloc(sizeof(float), 3);
	camera->Vx.values[1] = 1;
	camera->Vy.values[2] = 1;

	camera->center_X = center_X;
	camera->center_Y = center_Y;

	return camera;
}

struct projection *new_projection(struct item *item)
{
	assert(item != NULL);

	struct projection *projection = calloc(sizeof(struct projection), 1);
	projection->item = item;
	projection->position.size = 2;
	projection->position.values = calloc(sizeof(float), 2);
	item->proj = projection;
	return projection;
}

void push_projection(struct camera *camera, struct projection *projection)
{
	assert(camera != NULL);
	assert(projection != NULL);


	projection->next.next = camera->projections.next;
	if(camera->projections.next != NULL)
		CONTAINER_OF_(struct projection, next, camera->projections.next)->prev.next = &projection->prev;

	projection->prev.next = NULL;
	camera->projections.next = &projection->next;
	camera->nb_proj += 1;
}

int remove_projection(struct camera *camera, struct projection *projection)
{
	struct list *l = &camera->projections;
	while(l != NULL && (l->next != &projection->next))
	{
		l = l->next;
	}
	if(l == NULL)
		return 0;

	l->next = l->next->next;
	
	if(l->next != NULL)
	  {
	    if(l == &camera->projections)
	      CONTAINER_OF_(struct projection, next, l->next)->prev.next = NULL;
	    else
	      CONTAINER_OF_(struct projection, next, l->next)->prev.next =
		&CONTAINER_OF_(struct projection, next, l)->prev;
	  }
	    

	
	
	camera->nb_proj -= 1;

	return 1;
}

void free_camera(struct camera *camera)
{
	assert(camera != NULL);
	assert(camera->position.values != NULL);
	assert(camera->origin.values != NULL);
	assert(camera->Vx.values != NULL);
	assert(camera->Vy.values != NULL);


	free(camera->position.values);
	free(camera->origin.values);
	free(camera->Vx.values);
	free(camera->Vy.values);

	for(struct list *l = camera->projections.next; l != NULL;)
	{
		struct projection *p = CONTAINER_OF_(struct projection, next, l);
		l = l->next;
		free(p);
	}
}

void update_projections(struct camera *camera)
{
	assert(camera != NULL);
	assert(camera->position.size == 3);
	
	struct vector *o = clone_vector(&camera->origin);
	sub_vector(&camera->position, o);
	scalar_product_vector( 1.0f / magnitude_vector(o), o);
	
	for(struct list *l = camera->projections.next; l != NULL; l = l->next)
	{
		struct projection *p = CONTAINER_OF_(struct projection, next, l);
		assert(p->position.size == 2);
		assert(p->position.values != NULL);

		struct vector *new_pos = sub_vector(&camera->position,
				clone_vector(&p->item->position));

		p->position.values[0] = inner_product(new_pos, &camera->Vx);
		p->position.values[1] = inner_product(new_pos, &camera->Vy);


		struct vector *po = scalar_product_vector(inner_product(new_pos, o),
				clone_vector(o));

		float distance = magnitude_vector(po);
		float ratio = camera->depth / (camera->depth + distance);
		scalar_product_vector(ratio, &p->position);

		p->distance = distance;
		p->shown = inner_product(new_pos, o) >= 0;
		p->size = p->item->size * ratio;
		
		free_vector(new_pos);
		free_vector(po);
	}

	free_vector(o);
}

void sort_projections(struct camera *camera)
{
	for(struct list *l = camera->projections.next; l != NULL; l = l->next)
	{
		struct projection *pl = CONTAINER_OF_(struct projection, next, l);
		struct projection *pm = pl;
		struct list *m = camera->projections.next;
		for(; m != l; m= m->next)
		{
			pm = CONTAINER_OF_(struct projection, next, m);
			if(pl->distance > pm->distance)
				break;
		}
		if(m == l) continue;

		CONTAINER_OF_(struct projection, prev, pl->prev.next)->next.next = pl->next.next;
		if(pl->next.next != NULL)
			CONTAINER_OF_(struct projection, next, pl->next.next)->prev.next = pl->prev.next;

		if(pm->prev.next != NULL)
			CONTAINER_OF_(struct projection, prev, pm->prev.next)->next.next = &pl->next;
		else
		  camera->projections.next = &pl->next;
		pl->prev.next = pm->prev.next;

		pl->next.next = &pm->next;
		pm->prev.next = &pl->prev;

	}
}

void rotate_camera(struct camera *camera, float alpha, float beta, float gamma)
{
	assert(camera != NULL);

	float tabZ[] = {cosf(alpha), -sinf(alpha), 0,
		sinf(alpha), cos(alpha), 0,
		0, 0, 1};

	struct matrix *linappZ = newMat(3, 3);
	fill(linappZ, tabZ, 9);

	float tabY[] = {cosf(beta), 0, sinf(beta),
		0, 1, 0,
		-sinf(beta), 0, cos(beta)};

	struct matrix *linappY = newMat(3, 3);
	fill(linappY, tabY, 9);

	float tabX[] = {1, 0, 0,
		0, cosf(gamma), -sinf(gamma),
		0, sinf(gamma), cos(gamma)};

	struct matrix *linappX = newMat(3, 3);
	fill(linappX, tabX, 9);

	struct matrix *m = mult(linappZ, linappY);
	struct matrix *linapp = mult(m, linappX);
	freeMat(m);
	
	add_vector(&camera->origin, mult_vector(linapp, sub_vector(&camera->origin, &camera->position)));
	mult_vector(linapp, &camera->Vx);
	mult_vector(linapp, &camera->Vy);

	freeMat(linappX);
	freeMat(linappY);
	freeMat(linappZ);
	freeMat(linapp);
}

void move_camera(struct camera *camera, const struct vector *translation)
{
	assert(camera != NULL);
	assert(translation != NULL);
	assert(translation->size == 2);

	struct vector *X = clone_vector(&camera->Vx);
	struct vector *Y = clone_vector(&camera->Vy);

	add_vector(scalar_product_vector(translation->values[0], X), &camera->position);
	add_vector(scalar_product_vector(translation->values[1], Y), &camera->position);

	add_vector(X, &camera->origin);
	add_vector(Y, &camera->origin);

	free_vector(X);
	free_vector(Y);
}

void zoom_camera(struct camera *camera, float dist)
{
  assert(camera != NULL);

  struct vector *v = sub_vector(&camera->origin, clone_vector(&camera->position));

  if(dist < magnitude_vector(v) || dist > 0)
    {
      scalar_product_vector(dist/magnitude_vector(v), v);
      add_vector(v, &camera->position);
    }
  
  free_vector(v);
}

void dolly_rotation(struct camera *camera, float rotZ, float rotX)
{
  	assert(camera != NULL);

	float tabZ[] = {cosf(rotZ), -sinf(rotZ), 0,
			sinf(rotZ), cos(rotZ), 0,
			0, 0, 1};

	struct matrix *linappZ = newMat(3, 3);
	fill(linappZ, tabZ, 9);

	
	float tabX[] = {1, 0, 0,
			0, cosf(rotX), -sinf(rotX),
			0, sinf(rotX), cos(rotX),};


	struct matrix *linappX = newMat(3, 3);
	fill(linappX, tabX, 9);


	struct vector *Vx = scalar_product_vector(1.0f / magnitude_vector(&camera->Vx), &camera->Vx);

	
	struct vector *sub = scalar_product_vector(inner_product(&camera->Vy, Vx), clone_vector(Vx));
	struct vector *Vy = sub_vector(sub, &camera->Vy);
	free_vector(sub);
	scalar_product_vector(1.0f / magnitude_vector(&camera->Vy), &camera->Vy);

	
	struct vector *Vz = sub_vector(&camera->origin, clone_vector(&camera->position));
	sub = scalar_product_vector(inner_product(Vz, Vx), clone_vector(Vx));
	sub_vector(sub, Vz);
	free_vector(sub);
	sub = scalar_product_vector(inner_product(Vz, Vy), clone_vector(Vy));
	sub_vector(sub, Vz);
	scalar_product_vector(1.0f / magnitude_vector(Vz), Vz);
	
	
	float tabT[] = {Vx->values[0], Vx->values[1], Vx->values[2],
			Vy->values[0], Vy->values[1], Vy->values[2],
			Vz->values[0], Vz->values[1], Vz->values[2]};

	struct matrix *T = newMat(3,3);
	fill(T, tabT, 9);

	struct matrix *invT = transpose(T);

	struct matrix *m = mult(linappX, T);
	freeMat(linappX);
	linappX = mult(invT, m);
	freeMat(m);

	struct matrix *linapp = mult(linappX, linappZ);
	
	add_vector(&camera->origin, mult_vector(linapp,
						sub_vector(&camera->origin, &camera->position)));
	mult_vector(linapp, &camera->Vx);
	mult_vector(linapp, &camera->Vy);


	freeMat(linapp);
	freeMat(linappX);
	freeMat(linappZ);
	freeMat(T);
	freeMat(invT);
}

struct item *selecting_item(struct camera *camera)
{
  struct item *selected = NULL;
  for(struct list *l = camera->projections.next; l != NULL; l = l->next)
    {
      struct projection *p = CONTAINER_OF_(struct projection, next, l);
      float x = camera->mouse_x - p->position.values[0] - camera->center_X;
      float y = camera->mouse_y - p->position.values[1] - camera->center_Y;
      if(x * x + y * y <= p->size * p->size / 4)
	selected = p->item;
    }
  
  return selected;
}


struct vector *selecting_position(struct camera *camera)
{
  if(camera->event_type != SELECTED)
    return NULL;

  camera->event_type =  NOTMOVING;

  struct vector *o = sub_vector(&camera->position, clone_vector(&camera->origin));
  float ratio = (camera->depth + magnitude_vector(o)) / camera->depth;
  free_vector(o);
  
  
  float x = (camera->mouse_x - camera->center_X) * ratio;
  float y = (camera->mouse_y - camera->center_Y) * ratio;

  struct vector *Vx = scalar_product_vector(x, clone_vector(&camera->Vx));
  struct vector *Vy = scalar_product_vector(y, clone_vector(&camera->Vy));

  add_vector(Vy, Vx);
  free_vector(Vy);
  add_vector(&camera->origin, Vx);
  return Vx;
}
