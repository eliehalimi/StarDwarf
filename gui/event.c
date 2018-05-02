# include <stdio.h>
# include <stdlib.h>
# include <SDL2/SDL.h>
# include <SDL2/SDL_ttf.h>
# include <SDL2/SDL_image.h>
# include <err.h>
# include <unistd.h>
# include "gui.h"

# define SPEEDROTATION 0.01f
# define SPEEDTRANSLATION 1

int slider_new(struct slider *slider, struct image *bar, struct image *selected, struct image *unselected, int horizontal, int x, int y, struct window *window, void *maxvalue, void *minvalue)
{
  if (!slider) return -1;
  slider->active = 0;
  slider->prelight = 0;
  slider->event = window->event;
  slider->visible = window->visible;
 
  MakeRect(&slider->rect_bar, x, y, bar->w, bar->h);
  MakeRect(&slider->rect_token, x, y+7, selected->w, selected->h);

  slider->mousedown = 0;
  slider->horizontal = horizontal;
  if (horizontal)
    slider->maxlength = bar->w;
  else
    slider->maxlength = bar->h;
  slider->curlength = 0;
  slider->maxvalue = maxvalue;
  slider->minvalue = minvalue;
  
  slider->window = window;
  slider->bar = bar;
  slider->selected = selected;
  slider->unselected = unselected;
  return 0;
}


int slider_event(struct slider *slider, SDL_Event *event, int *draw, struct system *sys)
{
  slider->event = slider->window->event;
  if (!slider || !slider->event || !event) return 0;
 
  if (event->type == SDL_WINDOWEVENT && event->window.event == SDL_WINDOWEVENT_EXPOSED)
    *draw = 1;
  if (event->type == SDL_MOUSEBUTTONDOWN&& PointInRect(event->button.x, event->button.y, &slider->rect_token))
    {
      slider->mousepos = event->button.x;
      slider->mousedown = 1;
      slider->active = 1;
      slider->prelight = 1;
      *draw = 1;
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
		  slider->rect_token.x = x; 
		  slider->curlength = slider->rect_token.x - slider->rect_bar.x;
		  
		  slider->mousepos = event->button.x;
		}
	    }
	  else
	      if (event->button.y - slider->rect_bar.y > 0 && event->button.y - slider->rect_bar.y < slider->maxlength)
		{
		  slider->rect_token.y = slider->rect_token.y + event->button.y - slider->mousepos;
		  slider->curlength = slider->rect_token.y - slider->rect_bar.y;
		  slider->mousepos = event->button.y;

		}
	  float minv = *(float *)slider->minvalue;
	  float maxv = *(float *)slider->maxvalue;
	  float ratio = (float )slider->curlength/slider->maxlength;
	  sys->delta_time = minv + (maxv-minv)*ratio;	  
	}
      else if (event->type == SDL_MOUSEBUTTONUP && PointInRect(event->motion.x, event->motion.y, &slider->rect_token))
	{
	  slider->mousedown = 0;
	  slider->prelight = 1;
	  *draw = 1;
	}
      else if (!PointInRect(event->motion.x, event->motion.y, &slider->rect_token))
	{
	  slider->mousedown = 0;
	  slider->prelight = 0;
	  slider->active = 0;
	  *draw = 1;  
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
  button->window = window;
  button->active = 0;
  button->prelight = 0;
  button->event = window->event;
  button->visible = window->visible;
  button->selected = selected;
  button->unselected = unselected;
  button->textbox = 0;
  button->input = 0;
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
	  button->active = 1;
	  button->prelight = 1;
	  *draw = 1;
	}
      else if (event->type == SDL_MOUSEMOTION && PointInRect(event->motion.x, event->motion.y, &button->rect))
	{
	  button->prelight = 1;
	  *draw = 1;
	}
      else if (!PointInRect(event->motion.x, event->motion.y, &button->rect))
	{
	  button->prelight = 0;
	  button->active = 0;
	  *draw = 1;  
	}
    }
  else
    {
      if (event->type == SDL_MOUSEBUTTONDOWN && PointInRect(event->button.x, event->button.y,&button->rect))
	{
	  button->active = 1;
	  button->prelight = 1;
	  button->input = 1;
	  *draw = 1;
	}
      else if (button->input && event->type == SDL_MOUSEBUTTONDOWN && !PointInRect(event->button.x, event->button.y,&button->rect))
	{
	  button->active = 0;
	  button->prelight = 0;
	  button->input = 0;
	  *draw = 1;
	}
      else if (button->input && !PointInRect(event->button.x, event->button.y,&button->rect))
	{
	  button->active = 0;
	  button->prelight = 1;
	  button->input = 1;
	  *draw = 1;
	}
      else if (PointInRect(event->button.x, event->button.y,&button->rect))
	{
	  button->prelight = 1;
	}
      else if (event->type == SDL_MOUSEMOTION)
	{
	  button->prelight = 0;
	  button->active = 0;
	  button->input = 0;
	  *draw = 1;  
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
	
	else if(camera->event_type == NOTMOVING && event->type == SDL_MOUSEBUTTONDOWN && event->button.button == SDL_BUTTON_LEFT)
	  {
	    struct item *i = selecting_item(camera);
	    *selected = i;
	  }
	
	
	if(event->type == SDL_MOUSEMOTION)
	{
		camera->mouse_x = event->button.x;
		camera->mouse_y = event->button.y;
	}
	//printf("%i, %d, %d\n", event->type, event->button.x, event->button.y);
	return 1;
}
