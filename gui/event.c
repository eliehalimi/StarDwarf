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
	MakeRect(&button->rect, x, y, selected->w, selected->h);
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

int camera_event(struct camera *camera, SDL_Event *event)
{
	if(!camera || !event) return 0;
	
	if(event->type == SDL_MOUSEBUTTONDOWN)
	{
		camera->event_type = ROTATING;
	}
	else if(event->type == 768)
	{
		camera->event_type = TRANSLATING;
	}
	else if(event->type == SDL_MOUSEBUTTONUP || event->type == 769)
	{
		camera->event_type = NOTMOVING;
	}
	else if(camera->event_type == ROTATING && event->type == SDL_MOUSEMOTION)
	{
		dolly_rotation(camera, -(event->button.x - camera->mouse_x) * SPEEDROTATION,
				-(event->button.y - camera->mouse_y) * SPEEDROTATION);
	}
	else if(camera->event_type == TRANSLATING && event->type == SDL_MOUSEMOTION)
	{
		struct vector *trans = new_vector(2, NULL);
		trans->values[0] = -(event->button.x - camera->mouse_x) * SPEEDTRANSLATION;
		trans->values[1] = -(event->button.y - camera->mouse_y) * SPEEDTRANSLATION;

		move_camera(camera, trans);
		free_vector(trans);
	}

	if(event->type == SDL_MOUSEMOTION)
	{
		camera->mouse_x = event->button.x;
		camera->mouse_y = event->button.y;
	}
	//printf("%i, %d, %d\n", event->type, event->button.x, event->button.y);
	return 1;
}
