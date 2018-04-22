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

char *text;
char *intro;
struct system *sys = NULL;

int main()
{
	SDL_Event e;
	struct htable *button_list = create_htable(20);
	struct htable *window_list = create_htable(10);
	struct htable *img_list = create_htable(40);
	struct htable *draw_list = create_htable(10);
	SDL_Renderer *renderer = init("Kurt Russel's teapot - StarDwarf",1280, 720, button_list, window_list, img_list, draw_list);
	text = malloc(30*sizeof(char));
	*text = '\0'; 
	if (!renderer) return 1;
	printf("1\n");

	init_button_window(WINDOW_W, WINDOW_H, button_list, window_list, img_list, draw_list);

	int quit = 0;
	intro = malloc(200*sizeof(char));
	*intro = '\0';
	TTF_Init();
	
	((struct window *)(access_htable(window_list, "startmenu")->value))->visible = 1;
	((struct window *)(access_htable(window_list, "startmenu")->value))->event = 1;

	struct item *item = NULL;
	struct item *item2 = NULL;
	struct item *item3 = NULL;

	while (!quit)
	{
		SDL_Delay(10);
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
				quit = 1;	  
			button_active(&quit, sys, button_list, window_list, draw_list);

			window_event(access_htable(window_list, "startmenu")->value, &e, access_htable(draw_list, "startmenu")->value);
			button_event(access_htable(button_list, "new")->value, &e, access_htable(draw_list, "startmenu")->value);
			button_event(access_htable(button_list, "load")->value, &e, access_htable(draw_list, "startmenu")->value);
			button_event(access_htable(button_list, "option")->value, &e, access_htable(draw_list, "startmenu")->value);
			button_event(access_htable(button_list, "quit")->value, &e, access_htable(draw_list, "startmenu")->value);

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


			button_event(access_htable(button_list, "pause")->value, &e, access_htable(draw_list, "mainmenu")->value);

			window_event(access_htable(window_list, "pausemenu")->value, &e, access_htable(draw_list, "pausemenu")->value);
			button_event(access_htable(button_list, "quit_mainmenu")->value, &e, access_htable(draw_list, "pausemenu")->value);
			button_event(access_htable(button_list, "resume")->value, &e, access_htable(draw_list, "pausemenu")->value);
			if(sys)
			  camera_event(sys->camera, &e);
			
		}
		draw(renderer, button_list, window_list, draw_list, sys);
		if (*((int *)(access_htable(draw_list, "input")->value)))
		{
			free(intro);
			intro = malloc(200*sizeof(char));
			textinput(renderer, button_list, window_list, draw_list);
			if (*text)
				sprintf(intro, "welcome to %s's world", text);
			else
				sprintf(intro, "welcome to StarDwarf's Kurt Russel's teapot");
			if(!strcmp(text, "Russel") &&  *((int *)(access_htable(draw_list, "input")->value))< 2)
			{
				//system created
				sys = new_system(3);
				sys->camera = new_camera(WINDOW_W / 2, WINDOW_H / 2);
				sys->delta_time = 0.1f;

				//values for position vector                                       
				float val[3] = {0, 0, 0};
				float val2[3] = {150, 150, 150};
				float val3[3] = {0, 250, 0};

				//vector postion and creation of item                             
				struct vector *position = new_vector(3, val);
				struct vector *position2 = new_vector(3, val2);
				struct vector *position3 = new_vector(3, val3);

				item = new_item(position);
				item->size = 100;
				item->mass  = 100000000000000.0f;
				item->color[1] = 0;
				item->color[2] = 0;
				item->velocity.values[0] = 10;

				item2 = new_item(position2);
				item2->size = 100;
				item2->mass = 100000000000000.0f;

				item3 = new_item(position3);
				item3->size = 100;
				item3->mass = 100000000000000.0f;
				item3->color[0] = 0;

				//adding item to list of items in system                           
				push_item(sys, item);
				push_item(sys, item2);
				push_item(sys, item3);

				free_vector(position);
				free_vector(position2);
				free_vector(position3);
			}
			else if(*((int *)(access_htable(draw_list, "input")->value)) < 2)
			{
				//system created

				sys = new_system(3);
				sys->camera = new_camera(WINDOW_W / 2, WINDOW_H / 2);
				sys->delta_time = 0.1f;

				//values for position vector
				float val[3] = {150, 150, 0};
				float val2[3] = {0, 300, 0};
				float val3[3] = {0, 0, 300};

				//vector postion and creation of item
				struct vector *position = new_vector(3, val);
				struct vector *position2 = new_vector(3, val2);
				struct vector *position3 = new_vector(3, val3);

				item = new_item(position);
				item->size = 100;
				item->mass  = 200000000000000.0f;
				item->color[1] = 0;
				item->color[2] = 0;

				item2 = new_item(position2);
				item2->size = 10;
				item2->mass = 1000000000000.0f;
				item2->color[0] = 0;
				item2->color[2] = 0;

				item3 = new_item(position3);
				item3->size = 100;
				item3->mass = 100000000000000.0f;
				item3->color[0] = 0;

				//adding item to list of items in system
				push_item(sys, item);
				push_item(sys, item2);
				push_item(sys, item3);

				free_vector(position);
				free_vector(position2);
				free_vector(position3);
			}
			item->rect = NULL;
		        puts("Finished Drawing");
		}

	}
	clean(button_list, window_list, img_list, draw_list);
	return 0;
}

