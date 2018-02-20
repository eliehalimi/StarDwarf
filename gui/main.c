# include <stdio.h>
# include <stdlib.h>
# include <SDL2/SDL.h>
# include <SDL2/SDL_ttf.h>
# include <SDL2/SDL_image.h>
# include <err.h>
# include <unistd.h>
# include "gui.h"
#include "../SDL/circle.c"
int main()
{
  SDL_Event e;
  SDL_Renderer *renderer = init("Kurt Kussel's teapot - StarDwarf",1280, 720);
  if (!renderer) return 1;
  
  struct button *new_button = malloc(sizeof(struct button));
  struct button *load_button = malloc(sizeof(struct button));
  struct button *quit_button = malloc(sizeof(struct button));
  struct window *startmenu_w = malloc(sizeof(struct window));
 
   int window_w = 1280, window_h = 720;
  
  window_new(startmenu_w, startmenu, 0, 0, window_w, window_h);
  button_new(new_button, new_selected, new_unselected,400,350);
  button_new(load_button, load_selected, load_unselected,400,450);
  button_new(quit_button, quit_selected, quit_unselected,400,550);
  
  int quit = 0, draw = 1;
  startmenu_w->visible = 1;
  while (!quit)
    {
      SDL_Delay(10);
      while (SDL_PollEvent(&e))
	{
	  if (e.type == SDL_QUIT)
	    quit = 1;
	  
	  window_event(startmenu_w, &e, &draw);
	  button_event(new_button, &e, &draw);
	  button_event(load_button, &e, &draw);
	  button_event(quit_button, &e, &draw);

	  if (quit_button->active)
	    quit = 1;
	
	  if (new_button->active)
	    quit = 1;

	}
      if (!draw) continue;
      SDL_RenderClear(renderer);
      
      window_draw(startmenu_w, renderer);
      button_draw(new_button, renderer);
      button_draw(load_button, renderer);
      button_draw(quit_button, renderer);
      
      SDL_RenderPresent(renderer);
      draw = 0;
    }
  if (new_button->active)
	  init_circle(50);
  else{
  clean();  
  free(startmenu_w);
  free(new_button);
  free(load_button);
  free(quit_button);
  }
  return 0;
}
