# include <stdio.h>
# include <stdlib.h>
# include <SDL2/SDL.h>
# include <SDL2/SDL_ttf.h>
# include <SDL2/SDL_image.h>
# include <err.h>
# include <unistd.h>
# include "gui.h"
# include "draw_item.h"
# include "../Physic/physic.h"
# include "../Physic/libvector.h"
# include <string.h>
# include "../save/save.h"
# include "hash_table.h"

# define WINDOW_W 1280
# define WINDOW_H 720

struct system *sys = NULL;
int main()
{
	SDL_Event e;
	struct htable *button_list = create_htable(20);
	struct htable *window_list = create_htable(10);
	struct htable *img_list = create_htable(40);
	struct htable *draw_list = create_htable(10);
	struct htable *text_list = create_htable(10);
	
	SDL_Renderer *renderer = init("Kurt Russel's teapot - StarDwarf",1280, 720, button_list, window_list, img_list, draw_list, text_list);
	if (!renderer) return 1;
	init_lists(WINDOW_W, WINDOW_H, button_list, window_list, img_list, draw_list, text_list);
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
		       
			button_active(WINDOW_W, WINDOW_H, &quit, sys, button_list, window_list, draw_list, text_list);
			if (((struct text *)(access_htable(text_list, "name")->value))->active)  
			  textinput(e,(struct text *)(access_htable(text_list, "name")->value), 25);
			if (((struct text *)(access_htable(text_list, "item_name")->value))->active)  
			  textinput(e,(struct text *)(access_htable(text_list, "item_name")->value), 10);


			
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


			button_event(access_htable(button_list, "pause")->value, &e, access_htable(draw_list, "mainmenu")->value);

			window_event(access_htable(window_list, "pausemenu")->value, &e, access_htable(draw_list, "pausemenu")->value);
			button_event(access_htable(button_list, "quit_mainmenu")->value, &e, access_htable(draw_list, "pausemenu")->value);
			button_event(access_htable(button_list, "resume")->value, &e, access_htable(draw_list, "pausemenu")->value);
			if(sys)
			  camera_event(sys->camera, &e);
			
		}
		draw(renderer, button_list, window_list, draw_list, text_list, sys);
	}
	clean(button_list, window_list, img_list, draw_list, text_list);
	return 0;
}

