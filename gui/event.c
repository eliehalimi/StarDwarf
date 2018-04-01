# include <stdio.h>
# include <stdlib.h>
# include <SDL2/SDL.h>
# include <SDL2/SDL_ttf.h>
# include <SDL2/SDL_image.h>
# include <err.h>
# include <unistd.h>
# include "gui.h"

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
  MakeRect(&button->rect, x, y, 450, 90);
  return 0;
}


int button_event(struct button *button, SDL_Event *event, int *draw)
{
  button->event = button->window->event;
  if (!button || !button->event || !event) return 0;
  if (event->type == SDL_WINDOWEVENT && event->window.event == SDL_WINDOWEVENT_EXPOSED)
    *draw = 1;
  if (event->type == SDL_MOUSEBUTTONDOWN && PointInRect(event->button.x, event->button.y,&button->rect))
    {
      button->active = 1;
      //button->prelight = 1;
      *draw = 1;
    }
  else if  (PointInRect(event->button.x, event->button.y, &button->rect))
    {
      button->active  = 0;
      button->prelight = 1;
      *draw = 1;
      return 1;
    }
  else if (event->type == SDL_MOUSEMOTION && PointInRect(event->motion.x, event->motion.y, &button->rect))
    {
      button->prelight = 1;
      *draw = 1;
    }
  else if (event->type == SDL_MOUSEMOTION && !PointInRect(event->motion.x, event->motion.y, &button->rect))
    {
      button->prelight = 0;
      *draw = 1;
      if (button->active) {
	button->active = 0;
	return 1;
      }
    }
	return 0;
}

