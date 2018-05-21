# include "gui.h"

# define SPEEDROTATION 0.01f
# define SPEEDTRANSLATION 1

int slider_new(struct slider *slider, struct image *bar, struct image *selected, struct image *unselected, int horizontal, int x, int y, int token_pos, struct window *window, void *maxvalue, void *minvalue)
{
  if (!slider) return -1;
  slider->active = 0; slider->prelight = 0; slider->event = window->event; slider->visible = window->visible;
  MakeRect(&slider->rect_bar, x, y, bar->w, bar->h);
  MakeRect(&slider->rect_token, x, y + token_pos, selected->w, selected->h);
  slider->mousedown = 0;
  slider->horizontal = horizontal;
  if (horizontal)
    slider->maxlength = bar->w;
  else
    slider->maxlength = bar->h;
  slider->curlength = 0;
  slider->maxvalue = maxvalue; slider->minvalue = minvalue;
  slider->window = window; slider->bar = bar;
  slider->selected = selected; slider->unselected = unselected;
  return 0;
}
SDL_Color * init_palette_value(int length, int max, int min)                                       
{                                                                                                  
  SDL_Color * values = malloc(sizeof(SDL_Color) * length);                                         
  int i = 0, size = length/6; float ratio;
  for (; i < size; ++i)
    {                  
      ratio = (float)i/(float)size;
      values[i].r = max;
      values[i].g = min +(Uint8) (max-min)*ratio;
      values[i].b = min;     
    }                                                                                       
  for (; i < 2*size; ++i)                                                                   
    {                                                                                       
      ratio = (float)(i-size)/(float)size;
      values[i].r = max - (Uint8)(max-min)*ratio;
      values[i].g = max ;
      values[i].b = min;
    }                                                                                       
  for (; i < 3*size; ++i)                                                                   
    {                                                                                       
      ratio = (float)(i-2*size)/(float)size;                                                
      values[i].r = min;
      values[i].g = max;
      values[i].b = min + (Uint8)(max-min)*ratio;
    }                                                                                      
  for (; i < 4*size; ++i)                                                                  
    {                                                                                      
      ratio = (float)(i-3*size)/(float)size;                                               
      values[i].r = min;
      values[i].g = max - (Uint8)(max-min)*ratio;
      values[i].b = max;
    }                                                                                      
  for (; i < 5*size; ++i)                                                                  
    {                                                                                      
      ratio = (float)(i-4*size)/(float)size;                                               
      values[i].r = min + (Uint8)(max-min)*ratio;
      values[i].g = min;
      values[i].b = max;
    }                                                                                      
  for (; i < length; ++i)                                                                  
    {                                                                                      
      ratio = (float)(i-5*size)/(float)size;                                               
      values[i].r = max;
      values[i].g = min;
      values[i].b = max - (Uint8)(max-min)*ratio;
    }                                                                                              
  return values;
}

int palette_new(struct palette *p, struct window *window, int x, int y, int w, int h, int r, int picker_pos)  
{
  if (!p) return -1;
  p->active = 0; p->event = window->event; p->visible = window->visible;

  p->r = r; p->pos = 0;
  p->color = init_palette_value(w, 255, 0);
 
  MakeRect(&p->rect_palette, x, y, w, h);
  MakeRect(&p->rect_picker, x, y+picker_pos, 2*r, 2*r);
    
  p->mousedown = 0; p->mousepos = 0; p->window = window;
  return 0;
}

int palette_event(struct palette *p, SDL_Event *event, int *draw)
{
  p->event = p->window->event;
  if (!p || !p->event || !event) return 0;
  if (event->type == SDL_WINDOWEVENT && event->window.event == SDL_WINDOWEVENT_EXPOSED)
    *draw = 1;
  if (event->type == SDL_MOUSEBUTTONDOWN && PointInRect_Circle(event->button.x, event->button.y, &p->rect_picker))
    {
      p->mousepos = event->button.x;
      p->mousedown = 1; p->active = 1; *draw = 1;
    }
  else if (event->type == SDL_MOUSEMOTION && p->mousedown && PointInRect_Circle(event->button.x, event->button.y, &p->rect_picker))
	{
	  *draw = 1;
	  int x = p->rect_picker.x + event->button.x - p->mousepos;
	  if (x >= p->rect_palette.x && x <= p->rect_palette.x + p->rect_palette.w - p->r)
	    {  
	      p->rect_picker.x = x; p->mousepos = event->button.x; 
	      p->pos = p->rect_picker.x - p->rect_palette.x;
	    }
	}
  else if (event->type == SDL_MOUSEBUTTONUP && PointInRect_Circle(event->motion.x, event->motion.y, &p->rect_picker))
    {
      p->mousedown = 0; *draw = 1;
    }
  else if (!PointInRect_Circle(event->motion.x, event->motion.y, &p->rect_picker))
    {
      p->mousedown = 0; p->active = 0; *draw = 1;  
    }
  return 1;

}

int slider_event(struct slider *slider, SDL_Event *event, int *draw)
{
  slider->event = slider->window->event;
  if (!slider || !slider->event || !event) return 0;
 
  if (event->type == SDL_WINDOWEVENT && event->window.event == SDL_WINDOWEVENT_EXPOSED)
    *draw = 1;
  if (event->type == SDL_MOUSEBUTTONDOWN&& PointInRect(event->button.x, event->button.y, &slider->rect_token))
    {
      if (slider->horizontal)
	slider->mousepos = event->button.x;
      else
	slider->mousepos = event->button.y;
      slider->mousedown = 1; slider->active = 1; slider->prelight = 1; *draw = 1;
    }
  else if (event->type == SDL_MOUSEMOTION && slider->mousedown && PointInRect(event->button.x, event->button.y, &slider->rect_token))
	{
          slider->prelight = 1;
	  *draw = 1;
	  if (slider->horizontal)
	    {
	      int x = slider->rect_token.x + event->button.x - slider->mousepos;
	      if (x >= slider->rect_bar.x && x <= slider->rect_bar.x + slider->rect_bar.w - slider->rect_token.w)
		{  
		  slider->rect_token.x = x; slider->mousepos = event->button.x; 
		  slider->curlength = slider->rect_token.x - slider->rect_bar.x;
		}
	    }
	  else
	    {
	      int y = slider->rect_token.y + event->button.y - slider->mousepos;
	      if (y >= slider->rect_bar.y && y <= slider->rect_bar.y + slider->rect_bar.h - slider->rect_token.h)
		{
		  slider->rect_token.y = y; slider->mousepos = event->button.y;
		  slider->curlength = slider->rect_token.y - slider->rect_bar.y;
		}
	    }
	}
      else if (event->type == SDL_MOUSEBUTTONUP && PointInRect(event->motion.x, event->motion.y, &slider->rect_token))
	{
	  slider->mousedown = 0; slider->prelight = 1; *draw = 1;
	}
      else if (!PointInRect(event->motion.x, event->motion.y, &slider->rect_token))
	{
	  slider->mousedown = 0; slider->prelight = 0; slider->active = 0; *draw = 1;  
	}
  return 1;
}
int window_new(struct window *window, struct image *bg, int x, int y, int w, int h, struct window *parent)
{
  if (!window) return -1;
  window->parent = parent;
  window->bg = bg;
  MakeRect(&window->rect, x, y, w, h);
  window->visible = 0;
  if (window->parent)
    window->event = window->parent->event;
  else
    window->event = 0;
  return 0;
}

int window_event(struct window *window, SDL_Event *event, int *draw)
{
  if (!window || !window->event || !event) return 0;
  if (window->parent)
    window->event = window->parent->event;
  if (event->type == SDL_WINDOWEVENT && event->window.event == SDL_WINDOWEVENT_EXPOSED)
    *draw = 1;
  if (event->type == SDL_MOUSEBUTTONDOWN && PointInRect(event->button.x, event->button.y, &window->rect))
    return 1;
  return 0;
}

int button_new(struct button *button, struct image *selected, struct image *unselected, int x, int y, struct window *window)
{
  if (!button) return -1;
  button->window = window; button->event = window->event; button->visible = window->visible;
  button->active = 0; button->prelight = 0;
  button->selected = selected; button->unselected = unselected;
  button->textbox = 0; button->input = 0;
  MakeRect(&button->rect, x, y, selected->w, selected->h);
  return 0;
}

int button_event(struct button *button, SDL_Event *event, int *draw)
{
  button->event = button->window->event;
  if (!button || !button->event || !event) return 0;
  if (event->type == SDL_WINDOWEVENT && event->window.event == SDL_WINDOWEVENT_EXPOSED)
    *draw = 1;
  if (!button->textbox)
    {
      if (event->type == SDL_MOUSEBUTTONDOWN && PointInRect(event->button.x, event->button.y,&button->rect))
	{
	  button->active = 1; button->prelight = 1;*draw = 1;
	}
      else if (event->type == SDL_MOUSEMOTION && PointInRect(event->motion.x, event->motion.y, &button->rect))
	{
	  button->prelight = 1; *draw = 1;
	}
      else if (!PointInRect(event->motion.x, event->motion.y, &button->rect))
	{
	  button->prelight = 0; button->active = 0; *draw = 1;  
	}
    }
  else
    {
      if (event->type == SDL_MOUSEBUTTONDOWN && PointInRect(event->button.x, event->button.y,&button->rect))
	{
	  button->active = 1; button->prelight = 1; button->input = 1; *draw = 1;
	}
      else if (button->input && event->type == SDL_MOUSEBUTTONDOWN && !PointInRect(event->button.x, event->button.y,&button->rect))
	{
	  button->active = 0; button->prelight = 0; button->input = 0; *draw = 1;
	}
      else if (button->input && !PointInRect(event->button.x, event->button.y,&button->rect))
	{
	  button->active = 0; button->prelight = 1; button->input = 1; *draw = 1;
	}
      else if (PointInRect(event->button.x, event->button.y,&button->rect))
	{
	  button->prelight = 1;
	}
      else if (event->type == SDL_MOUSEMOTION)
	{
	  button->prelight = 0; button->active = 0; button->input = 0; *draw = 1;  
	}
    }
  return 1;
}

int camera_event(struct camera *camera, SDL_Event *event, struct item **selected)
{
	if(!camera || !event) return 0;

	if(event->type == SDL_MOUSEBUTTONDOWN && event->button.button == SDL_BUTTON_RIGHT)
	{
		camera->event_type = ROTATING;
	}
	else if(event->type == SDL_MOUSEBUTTONDOWN && event->button.button == SDL_BUTTON_MIDDLE)
	{
		camera->event_type = TRANSLATING;
	}
	else if(event->type == SDL_MOUSEBUTTONUP && camera->event_type != CREATING)
	{
		camera->event_type = NOTMOVING;
	}
	else if(camera->event_type == ROTATING && event->type == SDL_MOUSEMOTION  && event->button.button == 4)
	{
		dolly_rotation(camera, -(event->button.x - camera->mouse_x) * SPEEDROTATION,
				-(event->button.y - camera->mouse_y) * SPEEDROTATION);
	}
	else if(camera->event_type == TRANSLATING && event->type == SDL_MOUSEMOTION&& event->button.button == 2)
	{
		struct vector *trans = new_vector(2, NULL);
		trans->values[0] = -(event->button.x - camera->mouse_x) * SPEEDTRANSLATION;
		trans->values[1] = -(event->button.y - camera->mouse_y) * SPEEDTRANSLATION;

		move_camera(camera, trans);
		free_vector(trans);
	}
	else if(camera->event_type == CREATING && event->type == SDL_MOUSEBUTTONDOWN)
	  {
	    camera->event_type = SELECTED;
	  }
	
	else if(camera->event_type == NOTMOVING && event->type == SDL_MOUSEBUTTONDOWN && event->button.button == SDL_BUTTON_LEFT
		&& camera->mouse_x < WINDOW_W - ITEM_MENU_WIDTH)
	  {
	    struct item *i = selecting_item(camera);
	    *selected = i;
	    camera->event_type = MOVING_ITEM;
	  }

	else if(camera->event_type == MOVING_ITEM && event->type == SDL_MOUSEBUTTONUP && event->button.button == SDL_BUTTON_LEFT)
	  camera->event_type = NOTMOVING;
	
	else if(camera->event_type == MOVING_ITEM && event->type == SDL_MOUSEMOTION && *selected != NULL)
	  {
	    struct vector *pos = &(*selected)->position;
	    struct vector *Vz = sub_vector(&camera->position, clone_vector(&camera->origin));
	    scalar_product_vector(1.0f / magnitude_vector(Vz), Vz);

	    sub_vector(&camera->position, pos);

	    float ratio = camera->depth / (camera->depth + inner_product(Vz, pos));

	    struct vector *Vmx = scalar_product_vector((event->button.x - camera->mouse_x) / ratio, clone_vector(&camera->Vx));
	    struct vector *Vmy = scalar_product_vector((event->button.y - camera->mouse_y) / ratio, clone_vector(&camera->Vy));


	    add_vector(Vmx, pos);
	    add_vector(Vmy, pos);

	    add_vector(&camera->position, pos);
	    
	    free_vector(Vmy);
	    free_vector(Vmx);
	    free_vector(Vz);
	  }
	else if(camera->event_type == NOTMOVING && event->type == SDL_MOUSEBUTTONDOWN && event->button.button == 4)
	  zoom_camera(camera, 30);

	if(event->type == SDL_MOUSEBUTTONDOWN)
	  printf("%i\n", event->button.button);
	
	if(event->type == SDL_MOUSEMOTION)
	{
		camera->mouse_x = event->button.x;
		camera->mouse_y = event->button.y;
	}
	//printf("%i, %d, %d\n", event->type, event->button.x, event->button.y);
	return 1;
}
