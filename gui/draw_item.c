# include "SDL.h"
# include "../Camera/camera.h"
# include "draw_item.h"


#define SCR_WDT 1280
#define SCR_HGT 960
#define M_PI	3.14159265358979323846264338327950288

const int SCR_CEN_X = SCR_WDT / 2;
const int SCR_CEN_Y = SCR_HGT / 2;

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

  int new_x = 0;
  int new_y = 0;
  int old_x = x + item->size / 2;
  int old_y = y;

  /* SETS COLOR*/

  SDL_SetRenderDrawColor(renderer, item->color[0], item->color[1], item->color[2],item->color[3]);
  float square = item->size * item->size / 4;
	
  for(int i = -item->size / 2; i < item->size / 2; i++)
    {
      for(int j = -item->size / 2; j < item->size / 2; j++)
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
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

  return old_x;
}


void DrawProj(struct projection *proj, SDL_Renderer *renderer, float offset_X, float offset_Y)
{

  int x = proj->position.values[0] + offset_X;
  int y = proj->position.values[1]  + offset_Y;

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
	{
	  DrawProj(p, renderer, camera->center_X, camera->center_Y);
	  //Draw_vector(camera, &p->item->position, &p->item->velocity, renderer);
	}
    }
}

void Draw_vector(struct camera *camera, struct vector *origin, struct vector *relative, SDL_Renderer *renderer)
{
  assert(camera != NULL);
  assert(origin != NULL);
  assert(relative != NULL);
  assert(renderer != NULL);
  assert(origin->size == 3);
  assert(relative->size == 3);

  struct vector *or = sub_vector(&camera->position, clone_vector(origin));
  struct vector *absolue = add_vector(or, clone_vector(relative));

  struct vector *Vx = &camera->Vx;
  struct vector *Vy = &camera->Vy;
  struct vector *Vz = sub_vector(&camera->position, clone_vector(&camera->origin));
  scalar_product_vector(1.0f / magnitude_vector(Vz), Vz);

  float x1 = inner_product(or, Vx);
  float y1  = inner_product(or, Vy);
  
  float x2  = inner_product(absolue, Vx);
  float y2  = inner_product(absolue, Vy);

  struct vector *po = scalar_product_vector(inner_product(or, Vz),
					    clone_vector(or));
 
  // struct vector *pa = scalar_product_vector(inner_product(absolue, Vz), clone_vector(absolue));
 
  float distance = magnitude_vector(po);
  float ratioO = camera->depth / (camera->depth + distance);

  printf("%f\n", ratioO);
  float ratioA = 0.0f;

  x1 *= ratioO;
  y1 *= ratioO;
  
  x2 *= ratioA;
  y2 *= ratioA;
  
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

  SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
  
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

}

