# include <stdlib.h>
# include <SDL2/SDL.h>
# include <SDL2/SDL_image.h>
# include <SDL2/SDL_ttf.h>
# include <err.h>
# include <unistd.h>
# include "gui.h"
# include "hash_table.h"
# include "draw_item.h" 
# include "../save/save.h" 

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
int slider_draw(struct slider *slider, SDL_Renderer *renderer)
{
  slider->visible = slider->window->visible;
  if (!slider || !slider->visible || !renderer) return 0;
  RenderImage(renderer, slider->bar, slider->rect_bar.x, slider->rect_bar.y, NULL);
  if (!slider->selected)
    printf("image is NULL \n");
  if (!slider->unselected)
    printf("image is NULL \n");
  if (!slider->bar)
    printf("image is NULL \n");
  
  if (slider->prelight)
    RenderImage(renderer, slider->selected, slider->rect_token.x, slider->rect_token.y, NULL);
  else
    RenderImage(renderer, slider->unselected, slider->rect_token.x, slider->rect_token.y, NULL);
  return 1;
}



void draw(SDL_Renderer *renderer, struct htable *button_list, struct htable *window_list, struct htable *draw_list, struct htable *text_list, struct htable *slider_list, struct system *sys)
{
  
  if (*((int *)(access_htable(draw_list, "startmenu")->value)))
    {
      window_draw(access_htable(window_list, "startmenu")->value, renderer);
      button_draw(access_htable(button_list, "new")->value, renderer);
      button_draw(access_htable(button_list, "load")->value, renderer);
      button_draw(access_htable(button_list, "option")->value, renderer);
      button_draw(access_htable(button_list, "quit")->value, renderer);
    }
  
  if (*((int *)(access_htable(draw_list, "optionmenu")->value)))
    {
      window_draw(access_htable(window_list, "optionmenu")->value, renderer);
      button_draw(access_htable(button_list, "credit")->value, renderer);
      button_draw(access_htable(button_list, "volume")->value, renderer);
      button_draw(access_htable(button_list, "back_optionmenu")->value, renderer);
    }
  
  if (*((int *)(access_htable(draw_list, "creditmenu")->value)))
    {
      window_draw(access_htable(window_list, "creditmenu")->value, renderer);
      button_draw(access_htable(button_list, "back_creditmenu")->value, renderer);
    }
  if (*((int *)(access_htable(draw_list, "namemenu")->value)))
    {
      window_draw(access_htable(window_list, "namemenu")->value, renderer);
      button_draw(access_htable(button_list, "start")->value, renderer);
      button_draw(access_htable(button_list, "x")->value, renderer);
      display_text(renderer, text_list, "name", 320, 300, 255, 40);
    }
  
  if (*((int *)(access_htable(draw_list, "mainmenu")->value)))
    {
      
      //window_draw(access_htable(window_list, "mainmenu")->value, renderer);
      if (sys)
	Draw_from_camera(sys->camera, renderer);
      window_draw(access_htable(window_list, "itemsmenu")->value, renderer);

      button_draw(access_htable(button_list, "item_name")->value, renderer);
      button_draw(access_htable(button_list, "item_x")->value, renderer);
      button_draw(access_htable(button_list, "item_y")->value, renderer);
      button_draw(access_htable(button_list, "item_z")->value, renderer);
      button_draw(access_htable(button_list, "pause")->value, renderer);
      button_draw(access_htable(button_list, "item_vx")->value, renderer);
      button_draw(access_htable(button_list, "item_vy")->value, renderer);
      button_draw(access_htable(button_list, "item_vz")->value, renderer);
      button_draw(access_htable(button_list, "item_mass")->value, renderer);
      button_draw(access_htable(button_list, "item_radius")->value, renderer);
      button_draw(access_htable(button_list, "delete")->value, renderer);
      button_draw(access_htable(button_list, "add")->value, renderer);
      button_draw(access_htable(button_list, "start_mainmenu")->value, renderer);
      button_draw(access_htable(button_list, "reset")->value, renderer);


      slider_draw(access_htable(slider_list, "timelapse")->value, renderer);


      display_text(renderer, text_list, "intro", 60, 0, 255, 31);
      display_text(renderer, text_list, "item_name", 1080, 70, 0, 25);
      display_text(renderer, text_list, "item_x", 1100, 132, 0, 17);
      display_text(renderer, text_list, "item_y", 1100, 160, 0, 17);
      display_text(renderer, text_list, "item_z", 1100, 188, 0, 17);
      display_text(renderer, text_list, "item_mass", 1095, 242, 0, 17);
      display_text(renderer, text_list, "item_radius", 1095, 291, 0, 17);
      display_text(renderer, text_list, "item_vx", 1095, 342, 0, 17);
      display_text(renderer, text_list, "item_vy", 1095, 370, 0, 17);
      display_text(renderer, text_list, "item_vz", 1095, 399, 0, 17);

    }
  if (*((int *)(access_htable(draw_list, "pausemenu")->value)))
    {
      window_draw(access_htable(window_list, "pausemenu")->value, renderer);
      button_draw(access_htable(button_list, "resume")->value, renderer);
      button_draw(access_htable(button_list, "quit_mainmenu")->value, renderer);
      button_draw(access_htable(button_list, "saveandquit")->value, renderer);

    }
}


void button_active(int w, int h, int *quit, struct system **sys, struct system **reset_sys, struct htable *button_list, struct htable *window_list, struct htable *draw_list, struct htable *text_list, int *state)
{
  if (((struct button *)(access_htable(button_list, "quit")->value))->active)
    *quit = 1;
  else if (((struct button *)(access_htable(button_list, "new")->value))->active)
    {
      ((struct button *)(access_htable(button_list, "new")->value))->active = 0;
      ((struct button *)(access_htable(button_list, "new")->value))->prelight = 0;
      ((struct window *)(access_htable(window_list, "namemenu")->value))->visible = 1;
      ((struct window *)(access_htable(window_list, "namemenu")->value))->event = 1;
      ((struct window *)(access_htable(window_list, "startmenu")->value))->event = 0;
      *((int *)(access_htable(draw_list, "namemenu")->value)) = 1;
      init_textinput(text_list, "name", 30);
    }
  else if (((struct button *)(access_htable(button_list, "x")->value))->active)        
    {                                                                             
      ((struct button *)(access_htable(button_list, "x")->value))->active = 0;    
      ((struct button *)(access_htable(button_list, "x")->value))->prelight = 0;  
      ((struct window *)(access_htable(window_list, "namemenu")->value))->visible = 0;
      ((struct window *)(access_htable(window_list, "namemenu")->value))->event = 0;
      ((struct window *)(access_htable(window_list, "startmenu")->value))->event = 1;
      *((int *)(access_htable(draw_list, "namemenu")->value)) = 0;
      ((struct text *)(access_htable(text_list, "name")->value))->active = 0;
    }
  else if (((struct button *)(access_htable(button_list, "start")->value))->active)
    {                                                                             
      ((struct button *)(access_htable(button_list, "start")->value))->active = 0;
      ((struct button *)(access_htable(button_list, "start")->value))->prelight = 0;
      ((struct window *)(access_htable(window_list, "mainmenu")->value))->visible = 1;
      ((struct window *)(access_htable(window_list, "mainmenu")->value))->event = 1;
      ((struct window *)(access_htable(window_list, "startmenu")->value))->visible = 0;
      ((struct window *)(access_htable(window_list, "startmenu")->value))->event = 0;
      ((struct window *)(access_htable(window_list, "namemenu")->value))->visible = 0; 
      ((struct window *)(access_htable(window_list, "namemenu")->value))->event = 0;
      ((struct window *)(access_htable(window_list, "itemsmenu")->value))->visible = 1;
      ((struct window *)(access_htable(window_list, "itemsmenu")->value))->event = 1;

      init_textinput(text_list, "intro", 200);
      struct text *intro = (struct text *)(access_htable(text_list, "intro")->value);
      struct text *name = (struct text *)(access_htable(text_list, "name")->value);
      if (name->nbchar > 0)                                             
	sprintf(intro->text, "welcome to %s's world", name->text);   
      else                                                              
	sprintf(intro->text, "welcome to StarDwarf's Kurt Russel's teapot");               
      *((int *)(access_htable(draw_list, "mainmenu")->value)) = 1;
      *((int *)(access_htable(draw_list, "namemenu")->value)) = 0;
      ((struct text *)(access_htable(text_list, "name")->value))->active = 0;

      //initialize system here
      *sys = init_system(w, h, text_list);
    }
  else if (((struct button *)(access_htable(button_list, "item_name")->value))->active)
    init_textinput(text_list, "item_name", 15);
  else if (((struct button *)(access_htable(button_list, "item_x")->value))->active)
    init_textinput(text_list, "item_x", 15);
  else if (((struct button *)(access_htable(button_list, "item_y")->value))->active)
    init_textinput(text_list, "item_y", 15);
  else if (((struct button *)(access_htable(button_list, "item_z")->value))->active)
    init_textinput(text_list, "item_z", 15);
  else if (((struct button *)(access_htable(button_list, "item_mass")->value))->active)
    init_textinput(text_list, "item_mass", 15);
  else if (((struct button *)(access_htable(button_list, "item_radius")->value))->active)
    init_textinput(text_list, "item_radius", 15);
  else if (((struct button *)(access_htable(button_list, "item_vx")->value))->active)
    init_textinput(text_list, "item_vx", 15);
  else if (((struct button *)(access_htable(button_list, "item_vy")->value))->active)
    init_textinput(text_list, "item_vy", 15);
  else if (((struct button *)(access_htable(button_list, "item_vz")->value))->active)
    init_textinput(text_list, "item_vz", 15);
  else if (((struct button *)(access_htable(button_list, "option")->value))->active)
    {
      ((struct button *)(access_htable(button_list, "option")->value))->active = 0;
      ((struct button *)(access_htable(button_list, "option")->value))->prelight = 0;
      ((struct window *)(access_htable(window_list, "startmenu")->value))->visible = 0;
      ((struct window *)(access_htable(window_list, "startmenu")->value))->event = 0;
      ((struct window *)(access_htable(window_list, "optionmenu")->value))->visible = 1;
      ((struct window *)(access_htable(window_list, "optionmenu")->value))->event = 1;
      *((int *)(access_htable(draw_list, "startmenu")->value)) = 0;
      *((int *)(access_htable(draw_list, "optionmenu")->value)) = 1;
    }
  else if (((struct button *)(access_htable(button_list, "back_optionmenu")->value))->active)
    {
      ((struct button *)(access_htable(button_list, "back_optionmenu")->value))->active = 0;
      ((struct button *)(access_htable(button_list, "back_optionmenu")->value))->prelight = 0;
      ((struct window *)(access_htable(window_list, "startmenu")->value))->visible = 1;
      ((struct window *)(access_htable(window_list, "startmenu")->value))->event = 1;
      ((struct window *)(access_htable(window_list, "optionmenu")->value))->visible = 0;
      ((struct window *)(access_htable(window_list, "optionmenu")->value))->event = 0;
      *((int *)(access_htable(draw_list, "optionmenu")->value)) = 0;
    }
  else if (((struct button *)(access_htable(button_list, "credit")->value))->active)
    {
      ((struct button *)(access_htable(button_list, "credit")->value))->active = 0;	     
      ((struct button *)(access_htable(button_list, "credit")->value))->prelight = 0;
      ((struct window *)(access_htable(window_list, "optionmenu")->value))->visible = 0;
      ((struct window *)(access_htable(window_list, "optionmenu")->value))->event = 0;
      ((struct window *)(access_htable(window_list, "creditmenu")->value))->visible = 1;
      ((struct window *)(access_htable(window_list, "creditmenu")->value))->event = 1;
      *((int *)(access_htable(draw_list, "creditmenu")->value)) = 1;
      *((int *)(access_htable(draw_list, "startmenu")->value)) = 0;
      *((int *)(access_htable(draw_list, "optionmenu")->value)) = 0;
    }
  else if (((struct button *)(access_htable(button_list, "back_creditmenu")->value))->active)
    {
      ((struct button *)(access_htable(button_list, "back_creditmenu")->value))->active = 0;
      ((struct button *)(access_htable(button_list, "back_creditmenu")->value))->prelight = 0;
      ((struct window *)(access_htable(window_list, "optionmenu")->value))->visible = 1;
      ((struct window *)(access_htable(window_list, "optionmenu")->value))->event = 1;
      ((struct window *)(access_htable(window_list, "creditmenu")->value))->visible = 0;
      ((struct window *)(access_htable(window_list, "creditmenu")->value))->event = 0;
      *((int *)(access_htable(draw_list, "creditmenu")->value)) = 0;
      *((int *)(access_htable(draw_list, "optionmenu")->value)) = 1;
    }
  else if (((struct button *)(access_htable(button_list, "pause")->value))->active)
    {
      ((struct button *)(access_htable(button_list, "pause")->value))->active = 0;
      ((struct button *)(access_htable(button_list, "pause")->value))->prelight = 0;
      ((struct window *)(access_htable(window_list, "pausemenu")->value))->visible = 1;
      ((struct window *)(access_htable(window_list, "pausemenu")->value))->event = 1;
      ((struct window *)(access_htable(window_list, "itemsmenu")->value))->event = 0;
 
      *((int *)(access_htable(draw_list, "pausemenu")->value)) = 1;
      if(*state == SIMULATION_PROGRESS)
	*state = SIMULATION_PAUSE;
    }
  else if (((struct button *)(access_htable(button_list, "reset")->value))->active && *state != SIMULATION_EDIT)
    {
      ((struct button *)(access_htable(button_list, "reset")->value))->active = 0;
      ((struct button *)(access_htable(button_list, "reset")->value))->prelight = 0;
      
      struct list *l = (*sys)->camera->projections.next;  
      (*sys)->camera->projections.next = (*reset_sys)->camera->projections.next;
      (*reset_sys)->camera->projections.next = l;

      struct camera *c = (*sys)->camera;
      (*sys)->camera = (*reset_sys)->camera;
      (*reset_sys)->camera = c;

      free_system(*sys);
      *sys = *reset_sys;

      *state = SIMULATION_EDIT;
    }
  else if (((struct button *)(access_htable(button_list, "start_mainmenu")->value))->active && *state == SIMULATION_EDIT)
    {
      ((struct button *)(access_htable(button_list, "start_mainmenu")->value))->active = 0;
      ((struct button *)(access_htable(button_list, "start_mainmenu")->value))->prelight = 0;
      *reset_sys = clone_system(*sys);
      *state = SIMULATION_PROGRESS;
    }

  //for these 2, maybe add an event for when click 
  else if (((struct button *)(access_htable(button_list, "resume")->value))->active && *state == SIMULATION_PAUSE)
    {
      ((struct button *)(access_htable(button_list, "resume")->value))->active = 0;
      ((struct button *)(access_htable(button_list, "resume")->value))->prelight = 1;
      ((struct window *)(access_htable(window_list, "pausemenu")->value))->visible = 0;
      ((struct window *)(access_htable(window_list, "pausemenu")->value))->event = 0;
      ((struct window *)(access_htable(window_list, "mainmenu")->value))->event = 1;
      ((struct window *)(access_htable(window_list, "itemsmenu")->value))->event = 1;
 
      *((int *)(access_htable(draw_list, "pausemenu")->value)) = 0;
      *state = SIMULATION_PROGRESS;
    }

  
  else if (((struct button *)(access_htable(button_list, "quit_mainmenu")->value))->active)
    {
      ((struct button *)(access_htable(button_list, "quit_mainmenu")->value))->active = 0;
      ((struct button *)(access_htable(button_list, "quit_mainmenu")->value))->prelight = 0;
      ((struct window *)(access_htable(window_list, "pausemenu")->value))->visible = 0;
      ((struct window *)(access_htable(window_list, "pausemenu")->value))->event = 0;
      ((struct window *)(access_htable(window_list, "mainmenu")->value))->visible = 0;
      ((struct window *)(access_htable(window_list, "startmenu")->value))->visible = 1;
      ((struct window *)(access_htable(window_list, "startmenu")->value))->event = 1;

      ((struct window *)(access_htable(window_list, "mainmenu")->value))->visible = 0;
      ((struct window *)(access_htable(window_list, "mainmenu")->value))->event = 0;
      ((struct window *)(access_htable(window_list, "itemsmenu")->value))->visible = 0;
      ((struct window *)(access_htable(window_list, "itemsmenu")->value))->event = 0;
      *((int *)(access_htable(draw_list, "startmenu")->value))= 1;
      *((int *)(access_htable(draw_list, "mainmenu")->value)) = 0;
      free_system(*sys);
      *sys = NULL;
      *((int *)(access_htable(draw_list, "pausemenu")->value)) = 0;
    }

  
  else if (((struct button *)(access_htable(button_list, "saveandquit")->value))->active)
    {
      ((struct button *)(access_htable(button_list, "quit_mainmenu")->value))->active = 0;
      ((struct button *)(access_htable(button_list, "quit_mainmenu")->value))->prelight = 0;
      ((struct window *)(access_htable(window_list, "pausemenu")->value))->visible = 0;
      ((struct window *)(access_htable(window_list, "pausemenu")->value))->event = 0;
      ((struct window *)(access_htable(window_list, "mainmenu")->value))->visible = 0;
      ((struct window *)(access_htable(window_list, "startmenu")->value))->visible = 1;
      ((struct window *)(access_htable(window_list, "startmenu")->value))->event = 1;

      ((struct window *)(access_htable(window_list, "mainmenu")->value))->visible = 0;
      ((struct window *)(access_htable(window_list, "mainmenu")->value))->event = 0;
      ((struct window *)(access_htable(window_list, "itemsmenu")->value))->visible = 0;
      ((struct window *)(access_htable(window_list, "itemsmenu")->value))->event = 0;
      *((int *)(access_htable(draw_list, "startmenu")->value))= 1;
      *((int *)(access_htable(draw_list, "mainmenu")->value)) = 0;
      *((int *)(access_htable(draw_list, "pausemenu")->value)) = 0;
      //save here

      free_system(*sys);
      *sys = NULL;
    }
  else if (((struct button *)(access_htable(button_list, "load")->value))->active)
    {
      ((struct button *)(access_htable(button_list, "load")->value))->active = 0;
      ((struct button *)(access_htable(button_list, "load")->value))->prelight = 1;
      ((struct window *)(access_htable(window_list, "mainmenu")->value))->visible = 1;
      ((struct window *)(access_htable(window_list, "mainmenu")->value))->event = 1;
      ((struct window *)(access_htable(window_list, "itemsmenu")->value))->visible = 1;
      ((struct window *)(access_htable(window_list, "itemsmenu")->value))->event = 1;
		
      ((struct window *)(access_htable(window_list, "startmenu")->value))->visible = 0;
      ((struct window *)(access_htable(window_list, "startmenu")->value))->event = 0;   
      *sys = load_system("../save/system.txt");
      *((int *)(access_htable(draw_list, "mainmenu")->value)) = 1;

    }
  else if (((struct button *)(access_htable(button_list, "add")->value))->active)
    {
      ((struct button *)(access_htable(button_list, "add")->value))->active = 0;
      ((struct button *)(access_htable(button_list, "add")->value))->prelight = 1;
      (*sys)->camera->event_type = CREATING;
    }
}
