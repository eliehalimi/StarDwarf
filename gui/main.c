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

int draw_startmenu = 1, draw_optionmenu = 0, draw_creditmenu = 0, draw_namemenu = 0, draw_mainmenu = 0, draw_pausemenu = 0, input = 0;
char *text;
SDL_Renderer *renderer;

char *intro;
struct system *sys = NULL;


void draw(struct htable *button_list, struct htable *window_list)
{
	SDL_RenderClear(renderer);
	if (draw_startmenu)
	{
	        window_draw(access_htable(window_list, "startmenu")->value, renderer);
		button_draw(access_htable(button_list, "new")->value, renderer);
		button_draw(access_htable(button_list, "load")->value, renderer);
		button_draw(access_htable(button_list, "option")->value, renderer);
		button_draw(access_htable(button_list, "quit")->value, renderer);
	}
	if (draw_optionmenu)
	{
	        window_draw(access_htable(window_list, "optionmenu")->value, renderer);
		button_draw(access_htable(button_list, "credit")->value, renderer);
		button_draw(access_htable(button_list, "volume")->value, renderer);
		button_draw(access_htable(button_list, "back_optionmenu")->value, renderer);
	}

	if (draw_creditmenu)
	{
	        window_draw(access_htable(window_list, "creditmenu")->value, renderer);
		button_draw(access_htable(button_list, "back_creditmenu")->value, renderer);
	}
	if (draw_namemenu)
	{
	        window_draw(access_htable(window_list, "namemenu")->value, renderer);
		button_draw(access_htable(button_list, "start")->value, renderer);
		button_draw(access_htable(button_list, "x")->value, renderer);
	}

	if (draw_mainmenu)
	{
	        window_draw(access_htable(window_list, "mainmenu")->value, renderer);
		button_draw(access_htable(button_list, "pause")->value, renderer);

		if(!draw_pausemenu)
		{
		  update_system(sys);
		  //dolly_rotation(sys->camera, 0.01f, 0.01f);
		  //sys->camera->position.values[0] += 10;
		}
		Draw_from_camera(sys->camera, renderer);

		float tab[] = {0, 0};
		struct vector *trans = new_vector(2, tab);

		move_camera(sys->camera, trans);

		SDL_Rect pos;                                                     
		MakeRect(&pos,60,0,400,400);                                 
		SDL_Color fcolor;                                                           
		fcolor.r = 255;                                                   
		fcolor.g  = 255;                                                  
		fcolor.b  = 255;                                                  
		TTF_Font *font = TTF_OpenFont ("textfont.ttf", 25);               
		SDL_Surface *textSurface = TTF_RenderText_Solid(font, (const char*)intro, fcolor);       
		SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, textSurface); 
		SDL_QueryTexture(texture, NULL, NULL, &pos.w, &pos.h);                   
		SDL_RenderCopy(renderer, texture, NULL, &pos);               
		TTF_CloseFont(font);
		SDL_DestroyTexture(texture);
	}

	if (draw_pausemenu)
	{
	        window_draw(access_htable(window_list, "pausemenu")->value, renderer);
		button_draw(access_htable(button_list, "resume")->value, renderer);
		button_draw(access_htable(button_list, "quit_mainmenu")->value, renderer);
	}

	SDL_RenderPresent(renderer);
}




int main()
{
	SDL_Event e;
	
	struct htable *button_list = create_htable(20);
	struct htable *window_list = create_htable(10);
	struct htable *img_list = create_htable(40);

	renderer = init("Kurt Russel's teapot - StarDwarf",1280, 720, button_list, window_list, img_list);
	text = malloc(30*sizeof(char));
	*text = '\0'; 
	if (!renderer) return 1;

	init_button_window(WINDOW_W, WINDOW_H, button_list, window_list, img_list);

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
			button_active(&quit, sys, button_list, window_list);

			window_event(access_htable(window_list, "startmenu")->value, &e, &draw_startmenu);
			button_event(access_htable(button_list, "new")->value, &e, &draw_startmenu);
			button_event(access_htable(button_list, "load")->value, &e, &draw_startmenu);
			button_event(access_htable(button_list, "option")->value, &e, &draw_startmenu);
			button_event(access_htable(button_list, "quit")->value, &e, &draw_startmenu);

			window_event(access_htable(window_list, "optionmenu")->value, &e, &draw_optionmenu);
			button_event(access_htable(button_list, "credit")->value, &e, &draw_optionmenu);
			button_event(access_htable(button_list, "volume")->value, &e, &draw_optionmenu);
			button_event(access_htable(button_list, "back_optionmenu")->value, &e, &draw_optionmenu);

			window_event(access_htable(window_list, "creditmenu")->value, &e, &draw_creditmenu);
			button_event(access_htable(button_list, "back_creditmenu")->value, &e, &draw_creditmenu);

			window_event(access_htable(window_list, "mainmenu")->value, &e, &draw_mainmenu);
			button_event(access_htable(button_list, "pause")->value, &e, &draw_mainmenu);

			window_event(access_htable(window_list, "pausemenu")->value, &e, &draw_pausemenu);
			button_event(access_htable(button_list, "quit_mainmenu")->value, &e, &draw_pausemenu);
			button_event(access_htable(button_list, "resume")->value, &e, &draw_pausemenu);
			if(sys)
			  camera_event(sys->camera, &e);
			
		}
		draw(button_list, window_list);
		if (input)
		{

			free(intro);
			intro = malloc(200*sizeof(char));
			textinput(button_list, window_list);
			if (*text)
				sprintf(intro, "welcome to %s's world", text);
			else
				sprintf(intro, "welcome to StarDwarf's Kurt Russel's teapot");

			if(!strcmp(text, "Russel") && input < 2)
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
			else if(input < 2)
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
			//adding textures, renderer... to item
			//item->renderer = renderer;
			//item->texture = text;
			item->rect = NULL;
			//init_circle(item);
			//draw_cricle(item);
			puts("Finished Drawing");


		}

	}
	clean(button_list, window_list, img_list);
	return 0;
}

