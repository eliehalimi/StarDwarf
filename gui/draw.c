#include "gui.h"
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <err.h>
#include <unistd.h>

struct image *quit_selected, *quit_unselected, *new_selected, *new_unselected, *load_selected, *load_unselected, *startmenu;

SDL_Window *window;
SDL_Renderer *renderer;

int RenderImage(SDL_Renderer *renderer, struct image *img, int x, int y, SDL_Rect *rect)
{
  SDL_Rect dst;
  if (!renderer || !img->texture) return -1;
  MakeRect(&dst, x, y, img->w, img->h);
  if (rect) dst.w = rect->w;
  if (rect) dst.h = rect->h;
  SDL_RenderCopy(renderer, img->texture, rect, &dst);
  return 0;
}
/*
  load texture from an image through its name
  return 0 (use 0 b/c of later usage) when succeed, -1 when fail 
*/
int image_new(struct image *img, char *fname, SDL_Renderer* renderer)
{
  if (!img || !fname) return -1;
  char path[100] = "img/";
  strcat(path, fname);
  img->texture = IMG_LoadTexture(renderer, path);
  if (!img->texture)
    {
      errx(1,"Could not load image: %s\n", SDL_GetError());
      return -1;
    }
    
  SDL_QueryTexture(img->texture, NULL, NULL, &img->w, &img->h);
  return 0;
}

SDL_Renderer* init (char *title, int w, int h)
{
  SDL_Rect srect;
  SDL_Init(SDL_INIT_EVERYTHING);
  // get the desktop area represented by a display, with the primary display located at 0,0.
  SDL_GetDisplayBounds(0, &srect);
  if  (w > srect.w || h > srect.h)
    {
      SDL_Quit();
      return NULL;
    }
  // load support for the JPG and PNG image formats
  IMG_Init(IMG_INIT_JPG|IMG_INIT_PNG);
  
  //create a window with the specified position, dimensions, and flags. 
  window = SDL_CreateWindow(title, srect.w/2 - w/2, srect.h/2-h/2,w,h,SDL_WINDOW_SHOWN);
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  
  startmenu = malloc(sizeof(struct image));
  new_selected = malloc(sizeof(struct image));
  new_unselected = malloc(sizeof(struct image));
  load_selected = malloc(sizeof(struct image));
  load_unselected = malloc(sizeof(struct image));
  quit_selected = malloc(sizeof(struct image));
  quit_unselected = malloc(sizeof(struct image));
  
  int r = 0;
  r += image_new(startmenu, "bg.png", renderer);
  r += image_new(new_selected, "new_selected.png", renderer);
  r += image_new(new_unselected, "new_unselected.png", renderer);
  r += image_new(load_selected, "load_selected.png", renderer);
  r += image_new(load_unselected, "load_unselected.png", renderer);
  r += image_new(quit_selected, "quit_selected.png", renderer);
  r += image_new(quit_unselected, "quit_unselected.png", renderer);

  if (r)
    {
      clean();
      return NULL;
    }
  return renderer;
}

void clean()
{
  SDL_DestroyTexture(new_selected->texture);
  SDL_DestroyTexture(new_unselected->texture);
  SDL_DestroyTexture(load_selected->texture);
  SDL_DestroyTexture(load_unselected->texture);
  SDL_DestroyTexture(quit_selected->texture);
  SDL_DestroyTexture(quit_unselected->texture);
  SDL_DestroyTexture(startmenu->texture);
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);  

  free(new_selected);
  free(new_unselected);
  free(load_selected);
  free(load_unselected);
  free(quit_selected);
  free(quit_unselected);
  free(startmenu);
  
  IMG_Quit();
  SDL_Quit();

  SDL_RenderClear(renderer);
}
