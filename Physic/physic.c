# include <stdlib.h>
# include <assert.h>
# include "physic.h"

void free_item(struct item *item)
{
  assert(item->list.next = NULL);
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
  for(struct list l = item->user_force.next; l != NULL; l = l->next)
    add_vector(CONTAINER_OF_(struct vector, list, l), totalForce);
  scalar_product_vector(delta_time, totalForce);
  add_vector(totalForce, &item->velocity);
  struct vector *totalVelocity = clone_vector(&item->velocity);
  scalar_product_vector(delta_time, totalVelocity);
  add_vector(totalVelocity, &item->position);
}

void update_system(struct system *system);
