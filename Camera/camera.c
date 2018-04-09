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


struct camera *new_camera()
{
	struct camera *camera = calloc(sizeof(struct camera), 1);
	camera->position.size = 3;
	camera->origin.size = 3;
	camera->Vx.size = 3;
	camera->Vy.size = 3;
	camera->depth = 1.0f;

	camera->position.values = calloc(sizeof(float), 3);
	camera->origin.values = calloc(sizeof(float), 3);
	camera->origin.values[2] = 1;
	
	camera->Vx.values = calloc(sizeof(float), 3);
	camera->Vy.values = calloc(sizeof(float), 3);
	camera->Vx.values[0] = 1;
	camera->Vy.values[1] = 1;


	return camera;
}

struct projection *new_projection(struct item *item)
{
	assert(item != NULL);

	struct projection *projection = calloc(sizeof(struct projection), 1);
	projection->item = item;
	projection->position.size = 2;
	return projection;
}

void push_projection(struct camera *camera, struct projection *projection)
{
	projection->next.next = camera->projections.next;
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

	l->next = projection->next.next;
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


	for(struct list *l = camera->projections.next; l != NULL; l = l->next)
	{
		struct projection *p = CONTAINER_OF_(struct projection, next, l);
		assert(p->position.size == 2);
		
		p->position.values[0] = inner_product(&p->item->position, &camera->Vx);
		p->position.values[1] = inner_product(&p->item->position, &camera->Vy);

		struct vector *po = scalar_product_vector(inner_product(&p->item->position, o),
				clone_vector(o));

		float ratio = camera->depth / (camera->depth + magnitude_vector(po));
		scalar_product_vector(ratio, &p->position);

		p->shown = ratio <= 1;

		free_vector(po);
	}

	free_vector(o);
}

void sort_projections(struct camera *camera)
{
	for(struct list *l = camera->projections.next; l != NULL; l = l->next)
	{
		struct projection *pl = CONTAINER_OF_(struct projection, next, l->next);
		struct projection *pm = pl;
		for(struct list *m = camera->projections.next; m != l; m= m->next)
		{
			pm = CONTAINER_OF_(struct projection, next, m);
			if(pl->distance > pm->distance)
				break;
		}
		if(pm == pl) continue;

		pl->prev->next.next = pl->next.next;
		CONTAINER_OF_(struct projection, next, pl->next.next)->prev = pl->prev;

		pm->prev->next.next = &pl->next;
		pl->prev = pm->prev;

		pl->next.next = &pm->next;
		pm->prev = pl;

	}
}

void rotate_camera(struct camera *camera, float alpha, float beta)
{
	assert(camera != NULL);

	float tab[] = {cosf(alpha) * cosf(beta), -sinf(beta) * cosf(alpha), 0,
		sinf(beta) * cosf(alpha), cos(beta) * cosf(alpha), 0,
		sin(alpha), sin(alpha), 1};

	struct matrix *linapp = newMat(3, 3);

	fill(linapp, tab, 9);
	
	add_vector(&camera->origin, mult_vector(linapp, sub_vector(&camera->origin, &camera->position)));
	mult_vector(linapp, &camera->Vx);
	mult_vector(linapp, &camera->Vy);

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
}


void DrawProj(struct projection *proj, SDL_Renderer *renderer)
{
        int x = proj->position.values[0];
        int y = proj->position.values[1];

        int new_x = 0;
        int new_y = 0;
        int old_x = x + proj->size / 2;
        int old_y = y;

        struct item *item = proj->item;

        // SETS COLOR                                                                                                                                         

        SDL_SetRenderDrawColor(renderer, item->color[0], item->color[1], item->color[2],item->color[3]);
        float square = proj->size * proj->size / 4;

        for(int i = -proj->size / 2; i < proj->size / 2; i++)
          {
            for(int j = -proj->size / 2; j < proj->size / 2; j++)
              {
                if(i * i + j * j <= square)
                  {
                    new_x = x + i;
                        new_y = y +j;
                        SDL_RenderDrawLine(renderer, old_x, old_y, new_x, new_y);
                        old_x = new_x;
                        old_y = new_y;

                  }
              }
          }

        new_x = x + (proj->size / 2 * cos(0));
        new_y = y - (proj->size / 2 * sin(0));

        SDL_RenderDrawLine(renderer, old_x, old_y, new_x, new_y);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}

void Draw_from_camera(struct camera *camera, SDL_Renderer *renderer)
{
  update_projections(camera);
  sort_projections(camera);

  for(struct list *l = camera->projections.next; l != NULL; l = l->next)
    {
      struct projection *p = CONTAINER_OF_(struct projection, next, l);

      if(p->shown)
	DrawProj(p, renderer);
    }
}
