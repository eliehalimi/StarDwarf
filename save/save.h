#ifndef _SAVE_SYSTEM_H_
#define _SAVE_SYSTEM_H_
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "../Physic/physic.h"

void save_system(struct system *system); 

struct system *load_system(char *path);

#endif
