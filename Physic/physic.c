# include <stdlib.h>
# include <string.h>
# include <assert.h>
# include "physic.h"
# include "forces.h"
# include "collision.h"
# include "../gui/draw_item.h"

struct item *new_item(const struct vector *position)
{
	assert(position != NULL);
	assert(position->size > 0);

	struct item *i = calloc(sizeof(struct item), 1);
	i->nb_dimension = position->size;
	i->position.values = malloc(sizeof(float) * i->nb_dimension);
	memcpy(i->position.values, position->values, sizeof(float) * i->nb_dimension);
	i->position.size = i->nb_dimension;
	struct vector *v = new_vector(i->nb_dimension, NULL); 
	memcpy(&i->velocity, v, sizeof(struct vector));
	free(v);
	v = new_vector(i->nb_dimension, NULL);
	memcpy(&i->force, v, sizeof(struct vector));
	free(v);

	for(size_t index = 0; index < 4; index++)
		i->color[index] = 255;
	//i->color[3] = 255;

	return i;
}

struct system *new_system(size_t nb_dimension)
{
	assert(nb_dimension > 0);

	struct system *s = calloc(sizeof(struct system), 1);
	s->nb_dimension = nb_dimension;
	return s;
}

void free_item(struct item *item)
{
	assert(item != NULL);
	assert(item->list.next == NULL);
	//assert(item->renderer == NULL);
	assert(item->texture == NULL);
	assert(item->rect == NULL);

	free(item->position.values);
	free(item->velocity.values);
	free(item->force.values);
	for(struct list *l = item->user_force.next; l != NULL;)
	{
		struct list *next = l->next;
		free_vector(CONTAINER_OF_(struct vector, list, l));
		l = next;
	}
	free(item);
}

void free_system(struct system *system)
{
	assert(system != NULL);

	for(struct list *l = system->items.next; l != NULL;)
	{
		struct list *next = l->next;
		struct item *i = CONTAINER_OF_(struct item, list, l);
		i->list.next = NULL;
		free_item(i);
		l = next;
	}
	free(system);
}

void update_item(struct item *item, float delta_time)
{
	assert(delta_time > 0);
	assert(item != NULL);
	assert(item->nb_dimension == item->position.size);
	assert(item->nb_dimension == item->velocity.size);
	assert(item->nb_dimension == item->force.size);
	assert(item->position.values != NULL);
	assert(item->velocity.values != NULL);
	assert(item->force.values != NULL);

	struct vector *totalForce = clone_vector(&item->force);

	for(struct list *l = item->user_force.next; l != NULL; l = l->next)
		add_vector(CONTAINER_OF_(struct vector, list, l), totalForce);

	scalar_product_vector(delta_time, totalForce);
	sub_vector(totalForce, &item->velocity);

	struct vector *totalVelocity = clone_vector(&item->velocity);
	scalar_product_vector(delta_time, totalVelocity);
	add_vector(totalVelocity, &item->position);

	free_vector(totalForce);
	free_vector(totalVelocity);
}

void update_system(struct system *system, SDL_Renderer *renderer)
{
	assert(system != NULL);
	assert(system->delta_time > 0.0f);
	assert(system->nb_dimension > 0);


	//UPDATE ITEMS AND GET THEIR NEW POS
	for(struct list *l = system->items.next; l != NULL; l = l->next)
	{
		struct item *i = CONTAINER_OF_(struct item, list, l);
		update_item(i, system->delta_time);
		DrawCircle(i, renderer);

	}
	//RESET FORCE APPLIED BY SYSTEM
	for(struct list *l = system->items.next; l != NULL; l = l->next)
		for(size_t i = 0; i < system->nb_dimension; ++i)
			CONTAINER_OF_(struct item, list, l)->force.values[i] = 0.0f;

	//APPLY GRAVITY
	for(struct list *l1 = system->items.next; l1 != NULL; l1 = l1->next)
	{
		for(struct list *l2 = system->items.next; l2 != NULL; l2 = l2->next)
		{
			struct item *i1 = CONTAINER_OF_(struct item, list, l1);
			struct item *i2 = CONTAINER_OF_(struct item, list, l2);

			if(i1 == i2)
				continue;

			struct vector *g = gra_force(i1, i2);
			scalar_product_vector(1/i1->mass, g);
			add_vector(g, &i1->force);
			free_vector(g);
			collide(i1, i2);
		}
	}
}

void push_item(struct system *system, struct item *item)
{
	assert(system != NULL);
	assert(item != NULL);

	item->list.next = system->items.next;
	system->items.next = &item->list;
	system->nb_item += 1;
}

struct item *remove_item(struct system *system, struct item *item)
{
	assert(system != NULL);
	assert(item != NULL);

	for(struct list *l = &system->items; l != NULL; l = l->next)
	{
		if(CONTAINER_OF_(struct item, list, l->next) == item)
		{
			struct item *i = CONTAINER_OF_(struct item, list, l->next);
			struct list *u = i->list.next;
			i->list.next = NULL;
			l->next = u;
			return i;
		}
	}

	return NULL;
}
