# include <stdio.h>
# include <stdlib.h>
# include <SDL2/SDL.h>
# include <SDL2/SDL_ttf.h>
# include <SDL2/SDL_image.h>
# include <err.h>
# include <unistd.h>
# include "gui.h"
struct button *new_button, *load_button, *options_button, *quit_button, *credit_button, *volume_button, *back_optionmenu_button, *back_creditmenu_button;
struct window *startmenu_w, *optionmenu_w, *creditmenu_w;

void init_button_window()
{
  new_button = malloc(sizeof(struct button));
  load_button = malloc(sizeof(struct button));
  options_button = malloc(sizeof(struct button));
  quit_button = malloc(sizeof(struct button));
  startmenu_w = malloc(sizeof(struct window));

  credit_button = malloc(sizeof(struct button));
  volume_button = malloc(sizeof(struct button));
  back_optionmenu_button = malloc(sizeof(struct button));
  optionmenu_w = malloc(sizeof(struct window));

  creditmenu_w = malloc(sizeof(struct window));
  back_creditmenu_button = malloc(sizeof(struct button));
  int window_w = 1280, window_h = 720;
  
  window_new(startmenu_w, startmenu, 0, 0, window_w, window_h);
  button_new(new_button, new_selected, new_unselected, 400, 320, startmenu_w);
  button_new(load_button, load_selected, load_unselected, 400, 415, startmenu_w);
  button_new(options_button, options_selected, options_unselected, 400, 510, startmenu_w);
  button_new(quit_button, quit_selected, quit_unselected, 400, 605, startmenu_w);

  window_new(optionmenu_w, optionmenu, 0, 0, window_w, window_h);
  button_new(credit_button, credit_selected, credit_unselected, 400, 300, optionmenu_w);
  button_new(volume_button, volume_selected, volume_unselected, 400, 400, optionmenu_w);
  button_new(back_optionmenu_button, back_selected, back_unselected,400,600, optionmenu_w);
  
  window_new(creditmenu_w, creditmenu, 0, 0, window_w, window_h);
  button_new(back_creditmenu_button, back_selected, back_unselected, 400, 600, creditmenu_w);
  

}

void button_active(int *quit, int *draw_startmenu, int *draw_optionmenu, int *draw_creditmenu)
{
  if (quit_button->active)
    *quit = 1;
  
  if (options_button->active)
    {
      options_button->active = 0;
      options_button->prelight = 0;
      startmenu_w->visible = 0;
      optionmenu_w->visible = 1;
      *draw_startmenu = 0;
      *draw_optionmenu = 1;
    }
  if (back_optionmenu_button->active)
    {
      back_optionmenu_button->active = 0;
      back_optionmenu_button->prelight = 0;
      startmenu_w->visible = 1;
      optionmenu_w->visible = 0;
      *draw_optionmenu = 0;
    }
  if (credit_button->active)
    {
      credit_button->active = 0;	     
      credit_button->prelight = 0;
      optionmenu_w->visible = 0;
      creditmenu_w->visible = 1;
      *draw_creditmenu = 1;
      *draw_startmenu = 0;
      *draw_optionmenu = 0;
    }
  if (back_creditmenu_button->active)
    {
      back_creditmenu_button->active = 0;
      back_creditmenu_button->prelight = 0;
      optionmenu_w->visible = 1;
      creditmenu_w->visible = 0;
      *draw_creditmenu = 0;
      *draw_optionmenu = 1;
    }
}

int main()
{
  SDL_Event e;
  SDL_Renderer *renderer = init("Kurt Kussel's teapot - StarDwarf",1280, 720);
  if (!renderer) return 1;
  init_button_window();
  int quit = 0, draw_startmenu = 1, draw_optionmenu = 0, draw_creditmenu = 0;
  startmenu_w->visible = 1;
  while (!quit)
    {
      SDL_Delay(10);
      while (SDL_PollEvent(&e))
	{
	  if (e.type == SDL_QUIT)
	    quit = 1;	  
	  button_active(&quit, &draw_startmenu, &draw_optionmenu, &draw_creditmenu);
	  
	  window_event(startmenu_w, &e, &draw_startmenu);
	  button_event(new_button, &e, &draw_startmenu);
	  button_event(load_button, &e, &draw_startmenu);
	  button_event(options_button, &e, &draw_startmenu);
	  button_event(quit_button, &e, &draw_startmenu);
	  
	  window_event(optionmenu_w, &e, &draw_optionmenu);
	  button_event(credit_button, &e, &draw_optionmenu);
	  button_event(volume_button, &e, &draw_optionmenu);
	  button_event(back_optionmenu_button, &e, &draw_optionmenu);

	  window_event(creditmenu_w, &e, &draw_creditmenu);
	  button_event(back_creditmenu_button, &e, &draw_creditmenu);

	}
      if (!draw_startmenu && !draw_optionmenu && !draw_creditmenu) continue;
      SDL_RenderClear(renderer);
      if (draw_startmenu)
	{
	  window_draw(startmenu_w, renderer);
	  button_draw(new_button, renderer);
	  button_draw(load_button, renderer);
	  button_draw(options_button, renderer);
	  button_draw(quit_button, renderer);
	  draw_startmenu = 0;
	}
      if (draw_optionmenu)
	{
	  window_draw(optionmenu_w, renderer);
	  button_draw(credit_button, renderer);
	  button_draw(volume_button, renderer);
	  button_draw(back_optionmenu_button, renderer);
	  draw_optionmenu = 0;
	}
      
      if (draw_creditmenu)
	{
	  window_draw(creditmenu_w, renderer);
	  button_draw(back_creditmenu_button, renderer);
	  draw_creditmenu = 0;
	}

      
      SDL_RenderPresent(renderer);
	
    }
  clean();  
  free(startmenu_w);
  free(new_button);
  free(load_button);
  free(options_button);
  free(quit_button);

  free(optionmenu_w);
  free(credit_button);
  free(volume_button);
  free(back_optionmenu_button);

  free(creditmenu_w);
  free(back_creditmenu_button);

  return 0;
}
