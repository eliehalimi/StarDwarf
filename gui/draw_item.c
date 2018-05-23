# include "SDL.h"
# include "../Camera/camera.h"
# include "draw_item.h"
# include <math.h>

struct item *init_circle(struct item *item, SDL_Renderer *renderer)
{

  SDL_Texture *background = NULL;

  int w, h;

  //SDL_Renderer *renderer = item->renderer;
  // Loading image
  background = IMG_LoadTexture(renderer, NULL);
  SDL_QueryTexture(background, NULL, NULL, &w, &h);
  SDL_SetRenderTarget(renderer, background);

  // Scaling image
  SDL_Rect texr;
  item->rect = &texr;
  texr.x = SCR_WDT/2048;
  texr.y = SCR_HGT/2048;
  texr.w = w;// *2;
  texr.h = h;// *2;

  //SDL_RenderClear(renderer);
  SDL_RenderCopy(renderer, background, NULL, &texr);

  DrawCircle(item, renderer);
  return item;
}


int DrawCircle(struct item *item, SDL_Renderer *renderer)
{
  struct vector *position = &item->position;
  int x = position->values[0];
  int y = position->values[1];

  float size = item->size;
  
  if(size > MAXSIZEITEM)
    size = MAXSIZEITEM;

  
  int new_x = 0;
  int new_y = 0;
  int old_x = x + size / 2;
  int old_y = y;

  /* SETS COLOR*/

  
  SDL_SetRenderDrawColor(renderer, item->color[0], item->color[1], item->color[2],item->color[3]);

  if(size < SIZESIMPLE)
    {
      float square = size * size / 4;
      
      for(int i = -size / 2; i < size / 2; i++)
	{
	  for(int j = -size / 2; j < size / 2; j++)
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
	
      new_x = x + (item->size / 2 * cos(0));
      new_y = y - (item->size / 2 * sin(0));

      SDL_RenderDrawLine(renderer, old_x, old_y, new_x, new_y);
    }
  else
    { 
      for(int i = -size / 2; i < size / 2; i++)
	{
	  for(int j = -size / 2; j < size / 2; j++)
	    {
	      if(abs(i + j) < size / 2)
		{
		  new_x = x + i;
		  new_y = y +j;
		  SDL_RenderDrawLine(renderer, old_x, old_y, new_x, new_y);
		  old_x = new_x;
		  old_y = new_y;		
		}
	    }
	}
	
      new_x = x + (item->size / 2 * cos(0));
      new_y = y - (item->size / 2 * sin(0));

      SDL_RenderDrawLine(renderer, old_x, old_y, new_x, new_y);
    }

  
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

  return old_x;
}


void DrawProj(struct projection *proj, SDL_Renderer *renderer, float offset_X, float offset_Y)
{

  int x = proj->position.values[0] + offset_X;
  int y = proj->position.values[1]  + offset_Y;

  struct item *item = proj->item;

  // SETS COLOR

	
  float size = proj->size;
 
  if(size > MAXSIZEITEM)
    size = MAXSIZEITEM;

  
  int new_x = x;
  int new_y = y;
  int old_x = x + size / 2;
  int old_y = y;

  /* SETS COLOR*/

  
  SDL_SetRenderDrawColor(renderer, item->color[0], item->color[1], item->color[2],item->color[3]);

  if(size < SIZESIMPLE)
    {
      float square = size * size / 4;
      
      for(int i = -size / 2; i < size / 2; i++)
	{
	  for(int j = -size / 2; j < size / 2; j++)
	    {
	      new_x = x + i;
	      new_y = y +j;
	      if(i * i + j * j <= square)
		{
		  SDL_RenderDrawLine(renderer, old_x, old_y, new_x, new_y);
		}
	      old_x = new_x;
	      old_y = new_y;	        
	    }
	}
	
      new_x = x + (item->size / 2 * cos(0));
      new_y = y - (item->size / 2 * sin(0));

      //SDL_RenderDrawLine(renderer, old_x, old_y, new_x, new_y);
    }
  else
    { 
      for(int i = -size / 2; i < size / 2; i++)
	{
	  SDL_RenderDrawLine(renderer, -size/2 + x, y + i, size/2 + x, y + i);
	}
	
      new_x = x + (item->size / 2 * cos(0));
      new_y = y - (item->size / 2 * sin(0));

      //SDL_RenderDrawLine(renderer, old_x, old_y, new_x, new_y);
    }

  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}

void Draw_from_camera(struct camera *camera, SDL_Renderer *renderer)
{
  update_projections(camera);
  sort_projections(camera);


  struct vector *or = sub_vector(&camera->position, clone_vector(&camera->origin));
  float dist_or = magnitude_vector(or);
  free_vector(or);
  
  for(struct list *l = camera->projections.next; l != NULL; l = l->next)
    {
      struct projection *p = CONTAINER_OF_(struct projection, next, l);
      
      if(p->shown && p->distance > dist_or)
	{
	  DrawProj(p, renderer, camera->center_X, camera->center_Y);
	  Draw_vector(camera, &p->item->position, &p->item->velocity, renderer);
	}
    }

  float x[] = {10, 0, 0};
  float y[] = {0, 10, 0};
  float z[] = {0, 0, 10};
  
  struct vector *Ux = new_vector(3, x);
  struct vector *Uy = new_vector(3, y);
  struct vector *Uz = new_vector(3, z);

  Draw_vector(camera, &camera->origin, Ux, renderer);
  Draw_vector(camera, &camera->origin, Uy, renderer);
  Draw_vector(camera, &camera->origin, Uz, renderer);
  
  free_vector(Ux);
  free_vector(Uy);
  free_vector(Uz);

  
  
  for(struct list *l = camera->projections.next; l != NULL; l = l->next)
    {
      struct projection *p = CONTAINER_OF_(struct projection, next, l);
      
      if(p->shown && p->distance <= dist_or)
	{
	  DrawProj(p, renderer, camera->center_X, camera->center_Y);
	  Draw_vector(camera, &p->item->position, &p->item->velocity, renderer);
	}
    }
}

void Draw_vector(const struct camera *camera, const struct vector *origin, const struct vector *relative, SDL_Renderer *renderer)
{
  assert(camera != NULL);
  assert(origin != NULL);
  assert(relative != NULL);
  assert(renderer != NULL);
  assert(origin->size == 3);
  assert(relative->size == 3);

  struct vector *or = sub_vector(&camera->position, clone_vector(origin));
  struct vector *absolue = add_vector(or, scalar_product_vector(RATIO_SIZE_VECTOR, clone_vector(relative)));

  const struct vector *Vx = &camera->Vx;
  const struct vector *Vy = &camera->Vy;
  struct vector *Vz = sub_vector(&camera->position, clone_vector(&camera->origin));
  scalar_product_vector(1.0f / magnitude_vector(Vz), Vz);
  
  struct vector *po = scalar_product_vector(inner_product(or, Vz),
					    clone_vector(Vz));
  
  float x1 = inner_product(or, Vx);
  float y1 = inner_product(or, Vy);
  
  float distanceO = magnitude_vector(po);
  float ratioO = camera->depth / (camera->depth + distanceO);

  x1 *= ratioO;
  y1 *= ratioO;

  float x2 = inner_product(absolue, Vx);
  float y2 = inner_product(absolue, Vy);
  
  struct vector *pa = scalar_product_vector(-inner_product(absolue, Vz),
					    clone_vector(Vz));
  
  float distanceA = magnitude_vector(pa);
  float ratioA = camera->depth / (camera->depth + distanceA);

  x2 *= ratioA;
  y2 *= ratioA;
  
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

  SDL_RenderDrawLine(renderer, x1 + camera->center_X, y1 + camera->center_Y, x2 + camera->center_X, y2 + camera->center_Y);
  
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  
  free_vector(pa);
  free_vector(po);
  free_vector(Vz);
  free_vector(or);
  free_vector(absolue);
}

