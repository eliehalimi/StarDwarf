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
	return 0;
}


int window_event(struct window *window, SDL_Event *event, int *draw)
{
  if (!window || !window->visible || !event) return 0;
  if (event->type == SDL_WINDOWEVENT && event->window.event == SDL_WINDOWEVENT_EXPOSED)
    *draw = 1;
  if (event->type == SDL_MOUSEBUTTONDOWN && PointInRect(event->button.x, event->button.y, &window->rect))
    return 1;
  return 0;
}

int window_draw(struct window *window, SDL_Renderer *renderer)
{
  if (!window || !window->visible || !renderer) return 0;
  RenderImage(renderer, window->bg, 0, 0, NULL);
  return 1;
}

int button_new(struct button *button, struct image *selected, struct image *unselected, int x, int y)
{
  if (!button) return -1;
  button->active = 0;
  button->prelight = 0;
  button->visible = 1;
  button->selected = selected;
  button->unselected = unselected;
  MakeRect(&button->rect, x, y, 450, 90);
  return 0;
}


int button_event(struct button *button, SDL_Event *event, int *draw)
{
  if (!button || !button-> visible || !event) return 0;
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

int button_draw(struct button *button, SDL_Renderer *renderer)
{
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

