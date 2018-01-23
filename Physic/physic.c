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

void update_item(struct item *item, float delta_time);

void update_system(struct system *system);
