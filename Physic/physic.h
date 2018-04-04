# ifndef PHYSIC_STARDWARF
# define PHYSIC_STARDWARF

# include <stdlib.h>
# include "libvector.h"
//# include "SDL.h"
# include <SDL2/SDL.h>

struct item
{
  size_t nb_dimension;
  float mass, elec_charge, size;
  char label[16];
  char color[4];
  struct vector position, velocity, force;
  struct list user_force;                       //VECTOR LIST (sentinel)
  struct list list;                             //ITEM LIST (pointer to next)
  //SDL_Renderer *renderer;
  SDL_Texture *texture;
  SDL_Rect *rect;
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

// Update the velocity and position vector of the object
// Based on the force it is set with
void update_item(struct item *item, float delta_time);

// Update every item of the system, then update the forces
// they apply to one another
void update_system(struct system *system);

// Add an item to the system
void push_item(struct system *system, struct item *item);

// Remove an item to the system
struct item *remove_item(struct system *system, struct item *item);

# endif
