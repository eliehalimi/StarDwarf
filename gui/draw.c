# include "gui.h"

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
  if (slider->horizontal)
    slider->rect_token.x = slider->curlength + slider->rect_bar.x;
  else
    slider->rect_token.y = slider->curlength + slider->rect_bar.y;
      
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
int palette_draw(struct palette *p, SDL_Renderer *renderer)
{
  p->visible = p->window->visible;
  if (!p || !p->visible || !renderer) return 0;
  p->rect_picker.x = p->pos + p->rect_palette.x;
  int x = p->rect_palette.x, y = p->rect_palette.y, w = p->rect_palette.w, h = p->rect_palette.h;
  for (int i = 0; i < w; ++i)
    {
      SDL_SetRenderDrawColor(renderer, p->color[i].r, p->color[i].g, p->color[i].b, 255);
      SDL_RenderDrawLine(renderer, x + i, y, x + i, y + h);
    }
  int px = p->rect_picker.x, py = p->rect_picker.y, r = p->r;  
  int new_x = 0, new_y = 0, old_x = px + r, old_y = py;
  SDL_SetRenderDrawColor(renderer, p->color[p->pos].r, p->color[p->pos].g, p->color[p->pos].b, 255);
  int square = r * r;
  for (int i = - r; i < r; ++i)
    for (int j = - r; j < r; ++j)
      if (i*i + j*j <= square)
	{
	  new_x = px+i;
	  new_y = py+j;
	  SDL_RenderDrawLine(renderer, old_x, old_y, new_x, new_y);
	  old_x = new_x;
	  old_y = new_y;
	}
  new_x = px + r*cos(0);
  new_y = py - r*sin(0);
  SDL_RenderDrawLine(renderer, old_x, old_y, new_x, new_y);
  
  return 1;
}

void set_volumemusic_position(struct slider *slider)
{
  float ratio = (float) Mix_VolumeMusic(-1)/(float)MIX_MAX_VOLUME;
  slider->curlength = (int)(slider->maxlength*ratio);
}
void set_volumeeffect_position(struct slider *slider)
{
  float ratio = (float) Mix_Volume(-1, -1)/(float)MIX_MAX_VOLUME;
  slider->curlength = (int)(slider->maxlength*ratio);
}


void draw(SDL_Renderer *renderer, struct htable *button_list, struct htable *window_list, struct htable *draw_list, struct htable *text_list, struct htable *slider_list, struct palette *p, struct system *sys, struct list_char *files)
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
  if (*((int *)(access_htable(draw_list, "volumemenu")->value)))
    {
      window_draw(access_htable(window_list, "volumemenu")->value, renderer);
      button_draw(access_htable(button_list, "back_volumemenu")->value, renderer);
      slider_draw(access_htable(slider_list, "music_volumemenu")->value, renderer);
      slider_draw(access_htable(slider_list, "effect_volumemenu")->value, renderer);
    }
  if (*((int *)(access_htable(draw_list, "namemenu")->value)))
    {
      window_draw(access_htable(window_list, "namemenu")->value, renderer);
      button_draw(access_htable(button_list, "start")->value, renderer);
      button_draw(access_htable(button_list, "x")->value, renderer);
      display_text(renderer, text_list, "name", 320, 300, 255, 40);
    }
  if (*((int *)(access_htable(draw_list, "loadmenu")->value)))
    {
      window_draw(access_htable(window_list, "loadmenu")->value, renderer);
      button_draw(access_htable(button_list, "start_loadmenu")->value, renderer);
      slider_draw(access_htable(slider_list, "scrollbar")->value, renderer);

      button_draw(access_htable(button_list, "x_loadmenu")->value, renderer);
      display_files(renderer, files, access_htable(slider_list, "scrollbar")->value);
      display_text(renderer, text_list, "name_loadmenu", 320, 485, 255, 35);
      if (*((int *)(access_htable(draw_list, "warning_loadmenu")->value)))
	display_text(renderer, text_list, "warning_loadmenu", 550, 420, 255, 30);      
    }
  if (*((int *)(access_htable(draw_list, "mainmenu")->value)))
    {
      //window_draw(access_htable(window_list, "mainmenu")->value, renderer);
      window_draw(access_htable(window_list, "mainmenu")->value, renderer);

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
      palette_draw(p, renderer);

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
      slider_draw(access_htable(slider_list, "music_pausemenu")->value, renderer);
      slider_draw(access_htable(slider_list, "effect_pausemenu")->value, renderer);
    }
}


void button_active(int w, int h, int *quit, struct system **sys, struct system **reset_sys, struct htable *button_list, struct htable *window_list, struct htable *draw_list, struct htable *text_list,struct htable *slider_list,  struct list_char* files, int *state, struct palette *p)
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
      set_volumemusic_position(access_htable(slider_list, "music_pausemenu")->value);
      set_volumeeffect_position(access_htable(slider_list, "effect_pausemenu")->value);
      
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
      ((struct slider *)(access_htable(slider_list, "timelapse")->value))->curlength = 0;
      p->pos = 0;
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
      *((int *)(access_htable(draw_list, "optionmenu")->value)) = 0;
    }
  else if (((struct button *)(access_htable(button_list, "volume")->value))->active)
    {
      set_volumemusic_position(access_htable(slider_list, "music_volumemenu")->value);
      set_volumeeffect_position(access_htable(slider_list, "effect_volumemenu")->value);
      ((struct button *)(access_htable(button_list, "volume")->value))->active = 0;	 
      ((struct button *)(access_htable(button_list, "volume")->value))->prelight = 0;
      ((struct window *)(access_htable(window_list, "optionmenu")->value))->visible = 0;
      ((struct window *)(access_htable(window_list, "optionmenu")->value))->event = 0;
      ((struct window *)(access_htable(window_list, "volumemenu")->value))->visible = 1;
      ((struct window *)(access_htable(window_list, "volumemenu")->value))->event = 1;
      *((int *)(access_htable(draw_list, "volumemenu")->value)) = 1;
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
  else if (((struct button *)(access_htable(button_list, "back_volumemenu")->value))->active)
    {
      ((struct button *)(access_htable(button_list, "back_volumemenu")->value))->active = 0;
      ((struct button *)(access_htable(button_list, "back_volumemenu")->value))->prelight = 0;
      ((struct window *)(access_htable(window_list, "optionmenu")->value))->visible = 1;
      ((struct window *)(access_htable(window_list, "optionmenu")->value))->event = 1;
      ((struct window *)(access_htable(window_list, "volumemenu")->value))->visible = 0;
      ((struct window *)(access_htable(window_list, "volumemenu")->value))->event = 0;
      *((int *)(access_htable(draw_list, "volumemenu")->value)) = 0;
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
      ((struct slider *)(access_htable(slider_list, "timelapse")->value))->curlength = 0;
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
  else if (((struct button *)(access_htable(button_list, "resume")->value))->active) //&& *state == SIMULATION_PAUSE)
    {
      ((struct button *)(access_htable(button_list, "resume")->value))->active = 0;
      ((struct button *)(access_htable(button_list, "resume")->value))->prelight = 0;
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
      ((struct button *)(access_htable(button_list, "load")->value))->prelight = 0;
      ((struct window *)(access_htable(window_list, "loadmenu")->value))->visible = 1;
      ((struct window *)(access_htable(window_list, "loadmenu")->value))->event = 1;
      ((struct window *)(access_htable(window_list, "startmenu")->value))->event = 0;
      *((int *)(access_htable(draw_list, "loadmenu")->value)) = 1;
      init_textinput(text_list, "name_loadmenu", 30);
      removeall_list(files);
      get_files(files);
      ((struct slider *)(access_htable(slider_list, "scrollbar")->value))->curlength = 0;
    }
  else if (((struct button *)(access_htable(button_list, "x_loadmenu")->value))->active)        
    {                                                                             
      ((struct button *)(access_htable(button_list, "x_loadmenu")->value))->active = 0;    
      ((struct button *)(access_htable(button_list, "x_loadmenu")->value))->prelight = 0;  
      ((struct window *)(access_htable(window_list, "loadmenu")->value))->visible = 0;
      ((struct window *)(access_htable(window_list, "loadmenu")->value))->event = 0;
      ((struct window *)(access_htable(window_list, "startmenu")->value))->event = 1;
      *((int *)(access_htable(draw_list, "loadmenu")->value)) = 0;
    }

  else if (((struct button *)(access_htable(button_list, "start_loadmenu")->value))->active)
    {
      ((struct button *)(access_htable(button_list, "start_loadmenu")->value))->active = 0;
      ((struct button *)(access_htable(button_list, "start_loadmenu")->value))->prelight = 0;
      if (list_find(files, ((struct text *)access_htable(text_list, "name_loadmenu")->value)->text))
	{
	  ((struct window *)(access_htable(window_list, "mainmenu")->value))->visible = 1;
	  ((struct window *)(access_htable(window_list, "mainmenu")->value))->event = 1;
	  ((struct window *)(access_htable(window_list, "itemsmenu")->value))->visible = 1;
	  ((struct window *)(access_htable(window_list, "itemsmenu")->value))->event = 1;
	  ((struct window *)(access_htable(window_list, "loadmenu")->value))->visible = 0;
	  ((struct window *)(access_htable(window_list, "loadmenu")->value))->event = 0;   
	  ((struct window *)(access_htable(window_list, "startmenu")->value))->visible = 0;
	  ((struct window *)(access_htable(window_list, "startmenu")->value))->event = 0;
	  *((int *)(access_htable(draw_list, "loadmenu")->value)) = 0;

	 // char *text = (char*) ((struct text *)access_htable(text_list, "name_loadmenu")->value)->text;
	  //char *path = strcat("../save/save_files/", text);
	  //puts(path);
	 // fflush(NULL);
	 // *sys = load_system(path);
	  *sys = load_system("../save/save_files/system.txt");
	  *reset_sys = NULL;
	  *((int *)(access_htable(draw_list, "mainmenu")->value)) = 1;
	  p->pos = 0;
	  ((struct slider *)(access_htable(slider_list, "timelapse")->value))->curlength = 0;
	  set_volumemusic_position(access_htable(slider_list, "music_pausemenu")->value);
	  set_volumeeffect_position(access_htable(slider_list, "effect_pausemenu")->value);
      
	}
      else
	{
	  *((int *)(access_htable(draw_list, "warning_loadmenu")->value)) = 1;
	  init_textinput(text_list, "warning_loadmenu", 200);
	  struct text *warning = (struct text *)(access_htable(text_list, "warning_loadmenu")->value);
	    sprintf(warning->text, "invalid name");
	}
    }
  
  else if (((struct button *)(access_htable(button_list, "add")->value))->active)
    {
      ((struct button *)(access_htable(button_list, "add")->value))->active = 0;
      ((struct button *)(access_htable(button_list, "add")->value))->prelight = 1;
      (*sys)->camera->event_type = CREATING;
    }   
}
