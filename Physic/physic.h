# ifndef PHYSIC_STARDWARF
# define PHYSIC_STARDWARF

# include <stdlib.h>
# include "libvector.h"

struct item
{
  size_t nb_dimension;
  float mass, elec_charge, size;
  char label[16];
  char color[3];
  struct vector position, velocity, force;
  struct list user_force;                       //VECTOR LIST (sentinel)
  struct list list;                             //ITEM LIST (pointer to next)
};

struct system
{
  struct list items;                            //ITEM LIST (sentinel)
  size_t nb_dimension;
  float timelapse, delta_time;
};

struct item *new_item(const struct vector *postion);

struct system *new_system(size_t nb_dimension);

void free_item(struct item *item);

void free_system(struct system *system);

void update_item(struct item *item, float delta_time);

void update_system(struct system *system);

# endif
