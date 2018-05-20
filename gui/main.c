# include "gui.h"

void text_event(SDL_Event e, struct htable *text_list, struct htable *button_list, char *name, int size)
{
  if (((struct text *)(access_htable(text_list, name)->value))->active)  
    textinput(e,(struct text *)(access_htable(text_list, name)->value), size, access_htable(button_list, name)->value);
}

void timelapse( struct slider *slider, struct system *sys)
{
  if (slider->mousedown)
    {
      float minv = *(float *)slider->minvalue;                         
      float maxv = *(float *)slider->maxvalue;                         
      float ratio = (float )slider->curlength/slider->maxlength;       
      sys->delta_time = minv + (maxv-minv)*ratio; 
    }

}
int main()
{
  SDL_Event e;
  struct system *sys = NULL;
  struct item *selected = NULL;
  struct system *reset_sys = NULL;
  struct htable *button_list = create_htable(20);
  struct htable *slider_list = create_htable(3);	
  struct htable *window_list = create_htable(10);
  struct htable *img_list = create_htable(40);
  struct htable *draw_list = create_htable(10);
  struct htable *text_list = create_htable(10);
  struct list_char *files = list_create();
  struct palette *p = malloc(sizeof(struct palette));
  struct music *music = malloc(sizeof(struct music));

  int simulation_state = SIMULATION_EDIT;

  SDL_Renderer *renderer = init("Kurt Russel's teapot - StarDwarf",1280, 720, button_list, window_list, img_list, draw_list, text_list, slider_list, music);
  if (!renderer) return 1;
  init_lists(WINDOW_W, WINDOW_H, button_list, window_list, img_list, draw_list, text_list, slider_list, p);
  int quit = 0;
  TTF_Init();
  ((struct window *)(access_htable(window_list, "startmenu")->value))->visible = 1;
  ((struct window *)(access_htable(window_list, "startmenu")->value))->event = 1;
	
  SDL_StartTextInput();
  while (!quit)
    {
      SDL_Delay(10);
      while (SDL_PollEvent(&e))
	{
	  if (e.type == SDL_QUIT)
	    quit = 1;
	  button_active(WINDOW_W, WINDOW_H, &quit, &sys, &reset_sys, button_list, window_list, draw_list, text_list, slider_list, files, &simulation_state, p);

	  if (((struct text *)(access_htable(text_list, "name")->value))->active)  
	    textinput(e,(struct text *)(access_htable(text_list, "name")->value), 25, NULL);
	  text_event(e, text_list, button_list, "item_name", 10);
	  text_event(e, text_list, button_list, "item_x", 10);
	  text_event(e, text_list, button_list, "item_y", 10);
	  text_event(e, text_list, button_list, "item_z", 10);
	  text_event(e, text_list, button_list, "item_mass", 10);
	  text_event(e, text_list, button_list, "item_radius", 10);
	  text_event(e, text_list, button_list, "item_vx", 10);
	  text_event(e, text_list, button_list, "item_vy", 10);
	  text_event(e, text_list, button_list, "item_vz", 10);

	  window_event(access_htable(window_list, "startmenu")->value, &e, access_htable(draw_list, "startmenu")->value);
	  button_event(access_htable(button_list, "new")->value, &e, access_htable(draw_list, "startmenu")->value);
	  button_event(access_htable(button_list, "load")->value, &e, access_htable(draw_list, "startmenu")->value);
	  button_event(access_htable(button_list, "option")->value, &e, access_htable(draw_list, "startmenu")->value);
	  button_event(access_htable(button_list, "quit")->value, &e, access_htable(draw_list, "startmenu")->value);


	  window_event(access_htable(window_list, "namemenu")->value, &e, access_htable(draw_list, "namemenu")->value);
	  button_event(access_htable(button_list, "x")->value, &e, access_htable(draw_list, "namemenu")->value);
	  button_event(access_htable(button_list, "start")->value, &e, access_htable(draw_list, "namemenu")->value);

	  window_event(access_htable(window_list, "optionmenu")->value, &e, access_htable(draw_list, "optionmenu")->value);
	  button_event(access_htable(button_list, "credit")->value, &e, access_htable(draw_list, "optionmenu")->value);
	  button_event(access_htable(button_list, "volume")->value, &e, access_htable(draw_list, "optionmenu")->value);
	  button_event(access_htable(button_list, "back_optionmenu")->value, &e, access_htable(draw_list, "optionmenu")->value);

	  window_event(access_htable(window_list, "creditmenu")->value, &e, access_htable(draw_list, "creditmenu")->value);
	  button_event(access_htable(button_list, "back_creditmenu")->value, &e, access_htable(draw_list, "creditmenu")->value);

	  window_event(access_htable(window_list, "mainmenu")->value, &e, access_htable(draw_list, "mainmenu")->value);
	  button_event(access_htable(button_list, "item_name")->value, &e, access_htable(draw_list, "mainmenu")->value);
	  button_event(access_htable(button_list, "item_x")->value, &e, access_htable(draw_list, "mainmenu")->value);
	  button_event(access_htable(button_list, "item_y")->value, &e, access_htable(draw_list, "mainmenu")->value);
	  button_event(access_htable(button_list, "item_z")->value, &e, access_htable(draw_list, "mainmenu")->value);
	  button_event(access_htable(button_list, "item_vx")->value, &e, access_htable(draw_list, "mainmenu")->value);
	  button_event(access_htable(button_list, "item_vy")->value, &e, access_htable(draw_list, "mainmenu")->value);
	  button_event(access_htable(button_list, "item_vz")->value, &e, access_htable(draw_list, "mainmenu")->value);
	  button_event(access_htable(button_list, "item_mass")->value, &e, access_htable(draw_list, "mainmenu")->value);
	  button_event(access_htable(button_list, "item_radius")->value, &e, access_htable(draw_list, "mainmenu")->value);
	  button_event(access_htable(button_list, "add")->value, &e, access_htable(draw_list, "mainmenu")->value);
	  button_event(access_htable(button_list, "delete")->value, &e, access_htable(draw_list, "mainmenu")->value);
	  button_event(access_htable(button_list, "start_mainmenu")->value, &e, access_htable(draw_list, "mainmenu")->value);

	  slider_event(access_htable(slider_list, "timelapse")->value, &e, access_htable(draw_list, "mainmenu")->value);
	  timelapse(access_htable(slider_list, "timelapse")->value, sys);
	  palette_event(p, &e, access_htable(draw_list, "mainmenu")->value);
			
	  button_event(access_htable(button_list, "pause")->value, &e, access_htable(draw_list, "mainmenu")->value);

	  window_event(access_htable(window_list, "pausemenu")->value, &e, access_htable(draw_list, "pausemenu")->value);
	  button_event(access_htable(button_list, "quit_mainmenu")->value, &e, access_htable(draw_list, "pausemenu")->value);
	  button_event(access_htable(button_list, "resume")->value, &e, access_htable(draw_list, "pausemenu")->value);
	  button_event(access_htable(button_list, "reset")->value, &e, access_htable(draw_list, "pausemenu")->value);
	  button_event(access_htable(button_list, "saveandquit")->value, &e, access_htable(draw_list, "pausemenu")->value);

	  window_event(access_htable(window_list, "loadmenu")->value, &e, access_htable(draw_list, "loadmenu")->value);
	  button_event(access_htable(button_list, "x_loadmenu")->value, &e, access_htable(draw_list, "loadmenu")->value);
	  button_event(access_htable(button_list, "start_loadmenu")->value, &e, access_htable(draw_list, "loadmenu")->value);
	  slider_event(access_htable(slider_list, "scrollbar")->value, &e, access_htable(draw_list, "loadmenu")->value);
	  if (((struct text *)(access_htable(text_list, "name_loadmenu")->value))->active)  
	    textinput(e,(struct text *)(access_htable(text_list, "name_loadmenu")->value), 25, NULL);
	  if(sys)
	    camera_event(sys->camera, &e, &selected);
	    
	}
		
      SDL_RenderClear(renderer);
      draw(renderer, button_list, window_list, draw_list, text_list, slider_list, p, sys, files);

      if(sys != NULL)
	{
	  if(reset_sys == sys)
	    {
	      if(sys->selected != NULL)
		item_to_input(text_list, p, sys->selected);
	      reset_sys = NULL;
	    }
	  
	  if(selected != NULL)
	    {
	      sys->selected = selected;
	      selected = NULL;
	      item_to_input(text_list, p, sys->selected);
	    }

	  if(simulation_state == SIMULATION_EDIT && sys->selected != NULL)
	    input_to_item(text_list, p, sys->selected);
	   
	  if(simulation_state == SIMULATION_PROGRESS)
	    {
	      update_system(sys);
	      if(sys->selected != NULL)
		item_to_input(text_list, p, sys->selected);
	    }
			
	  if(simulation_state == SIMULATION_EDIT)
	    {
	      struct vector *v = selecting_position(sys->camera);
			    
	      if(v != NULL)
		{
		  struct item *i = new_item(v);
		  free_vector(v);
			      
		  i->size = 100;
		  i->mass  = 100000000000000.0f;
			      
		  push_item(sys, i);
		}
	    }
	}
      SDL_RenderPresent(renderer);
    }
  clean(renderer, button_list, window_list, img_list, draw_list, text_list, slider_list, music);
  if (files)
    free_list(files);
  free(p->color);
  free(p);
  return 0;
}

