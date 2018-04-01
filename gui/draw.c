#include "gui.h"
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <err.h>
#include <unistd.h>

struct image *quit_selected, *quit_unselected, *new_selected, *new_unselected, *load_selected, *load_unselected, *startmenu, *options_selected, *options_unselected, *optionmenu, *back_selected, *back_unselected, *credit_selected, *credit_unselected, *volume_selected, *volume_unselected, *creditmenu, *namemenu, *start_selected, *start_unselected, *x_selected, *x_unselected;

SDL_Window *window;
SDL_Renderer *renderer;

int window_draw(struct window *window, SDL_Renderer *renderer)
{
  if (!window || !window->visible || !renderer) return 0;
  RenderImage(renderer, window->bg, window->rect.x, window->rect.y, NULL);
  return 1;
}

int button_draw(struct button *button, SDL_Renderer *renderer)
{
  button->visible = button->window->visible;
  if (!button || !button->visible || !renderer) return 0;
  if (button->active)
    RenderImage(renderer, button->selected, button->rect.x,
		button->rect.y, NULL);
  else if (button->prelight)
    {
      RenderImage(renderer, button->selected, button->rect.x, button->rect.y, NULL);
    }
  else
    RenderImage(renderer, button->unselected, button->rect.x, button->rect.y, NULL);
  return 1;
}

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
  optionmenu = malloc(sizeof(struct image));
  creditmenu = malloc(sizeof(struct image));
  namemenu = malloc(sizeof(struct image));
  
  new_selected = malloc(sizeof(struct image));
  new_unselected = malloc(sizeof(struct image));
  load_selected = malloc(sizeof(struct image));
  load_unselected = malloc(sizeof(struct image));
  quit_selected = malloc(sizeof(struct image));
  quit_unselected = malloc(sizeof(struct image));
  options_selected = malloc(sizeof(struct image));
  options_unselected = malloc(sizeof(struct image));
  credit_selected = malloc(sizeof(struct image));
  credit_unselected = malloc(sizeof(struct image));  
  back_selected = malloc(sizeof(struct image));
  back_unselected = malloc(sizeof(struct image));
  volume_selected = malloc(sizeof(struct image));
  volume_unselected = malloc(sizeof(struct image));
  x_selected = malloc(sizeof(struct image));
  x_unselected = malloc(sizeof(struct image));
  start_selected = malloc(sizeof(struct image));
  start_unselected = malloc(sizeof(struct image));

  int r = 0;
  r += image_new(startmenu, "startmenu.png", renderer);
  r += image_new(new_selected, "new_selected.png", renderer);
  r += image_new(new_unselected, "new_unselected.png", renderer);
  r += image_new(load_selected, "load_selected.png", renderer);
  r += image_new(load_unselected, "load_unselected.png", renderer);
  r += image_new(quit_selected, "quit_selected.png", renderer);
  r += image_new(quit_unselected, "quit_unselected.png", renderer);
  r += image_new(options_selected, "options_selected.png", renderer);
  r += image_new(options_unselected, "options_unselected.png", renderer);

  r += image_new(optionmenu, "optionmenu.png", renderer);
  r += image_new(credit_selected, "credit_selected.png", renderer);
  r += image_new(credit_unselected, "credit_unselected.png", renderer);
  r += image_new(back_selected, "back_selected.png", renderer);
  r += image_new(back_unselected, "back_unselected.png", renderer);
  r += image_new(volume_selected, "volume_selected.png", renderer);
  r += image_new(volume_unselected, "volume_unselected.png", renderer);

  r += image_new(creditmenu, "creditmenu.png", renderer);

  r += image_new(namemenu, "namemenu.png", renderer);
  r += image_new(x_selected, "x_selected.png", renderer);
  r += image_new(x_unselected, "x_unselected.png", renderer);
  r += image_new(start_selected, "start_selected.png", renderer);
  r += image_new(start_unselected, "start_unselected.png", renderer);


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
  SDL_DestroyTexture(options_selected->texture);
  SDL_DestroyTexture(options_unselected->texture);

  SDL_DestroyTexture(credit_selected->texture);
  SDL_DestroyTexture(credit_unselected->texture);
  SDL_DestroyTexture(back_selected->texture);
  SDL_DestroyTexture(back_unselected->texture);
  SDL_DestroyTexture(volume_selected->texture);
  SDL_DestroyTexture(volume_unselected->texture);
 
  
  SDL_DestroyTexture(startmenu->texture);
  SDL_DestroyTexture(optionmenu->texture);
  SDL_DestroyTexture(creditmenu->texture);

  SDL_DestroyTexture(namemenu->texture);
  SDL_DestroyTexture(x_selected->texture);
  SDL_DestroyTexture(x_unselected->texture);
  SDL_DestroyTexture(start_selected->texture);
  SDL_DestroyTexture(start_unselected->texture);
  
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);  

  free(new_selected);
  free(new_unselected);
  free(load_selected);
  free(load_unselected);
  free(options_selected);
  free(options_unselected);
  free(quit_selected);
  free(quit_unselected);
  free(startmenu);

  free(credit_selected);
  free(credit_unselected);
  free(volume_selected);
  free(volume_unselected);
  free(back_selected);
  free(back_unselected);
  free(optionmenu);

  free(creditmenu);

  free(x_selected);
  free(x_unselected);
  free(start_selected);
  free(start_unselected);
  free(namemenu);

  IMG_Quit();
  SDL_Quit();

  SDL_RenderClear(renderer);
}
