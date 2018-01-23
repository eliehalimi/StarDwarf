IFNDEF PHYSIC_STARDWARF
DEFINE PHYSIC_STARDWARF

# include <stdlib.h>
# include "libvector.h"

struct item
{
  size_t nb_dimension;
  float mass, elec_charge, size;
  char label[16];
  char color[3];
  struct vector position, velocity, force;
  size_t nb_user_force;
  vector *user_force;
};

struct system
{
  size_t nb_item;
  struct item *items;
  size_t nb_dimension;
  float timelapse, delta_time;
};

struct item *new_item(struct vector *postion);

struct system *new_system(size_t nb_dimension);

void free_item(struct item *item);

void free_system(struct system *system);

void update_item(struct item *item, float delta_time);

void update_system(struct system *system

ENDIF
