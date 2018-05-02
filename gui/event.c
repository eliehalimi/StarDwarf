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

int window_new(struct window *window, struct image *bg, int x, int y, int w, int h)
{
  if (!window) return -1;
  window->bg = bg;
  MakeRect(&window->rect, x, y, w, h);
  window->visible = 0;
  window->event = 0;
  return 0;
}

int window_event(struct window *window, SDL_Event *event, int *draw)
{
  if (!window || !window->event || !event) return 0;
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
