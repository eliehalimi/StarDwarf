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

struct button *new_button, *load_button, *options_button, *quit_button, *credit_button, *volume_button, *back_optionmenu_button, *back_creditmenu_button, *x_button, *start_button, *pause_button, *resume_button, *quit_mainmenu_button;
struct window *startmenu_w, *optionmenu_w, *creditmenu_w, *namemenu_w, *mainmenu_w, *pausemenu_w;
int draw_startmenu = 1, draw_optionmenu = 0, draw_creditmenu = 0, draw_namemenu = 0, draw_mainmenu = 0, draw_pausemenu = 0, input = 0;
char *text;
SDL_Renderer *renderer;

char *intro;
struct system *sys = NULL;


void init_button_window()
{
	new_button = malloc(sizeof(struct button));
	load_button = malloc(sizeof(struct button));
	options_button = malloc(sizeof(struct button));
	quit_button = malloc(sizeof(struct button));
	startmenu_w = malloc(sizeof(struct window));

	credit_button = malloc(sizeof(struct button));
	volume_button = malloc(sizeof(struct button));
	back_optionmenu_button = malloc(sizeof(struct button));
	optionmenu_w = malloc(sizeof(struct window));

	creditmenu_w = malloc(sizeof(struct window));
	back_creditmenu_button = malloc(sizeof(struct button));

	x_button = malloc(sizeof(struct button));
	start_button = malloc(sizeof(struct button));
	namemenu_w = malloc(sizeof(struct window));

	pause_button = malloc(sizeof(struct button));
	mainmenu_w = malloc(sizeof(struct window));

	resume_button = malloc(sizeof(struct button));
	quit_mainmenu_button = malloc(sizeof(struct button));
	pausemenu_w = malloc(sizeof(struct window));

	int window_w = 1280, window_h = 720;

	window_new(startmenu_w, startmenu, 0, 0, window_w, window_h);
	button_new(new_button, new_selected, new_unselected, 400, 320, 450, 90, startmenu_w);
	button_new(load_button, load_selected, load_unselected, 400, 415, 450, 90, startmenu_w);
	button_new(options_button, options_selected, options_unselected, 400, 510, 450, 90, startmenu_w);
	button_new(quit_button, quit_selected, quit_unselected, 400, 605, 450, 90, startmenu_w);

	window_new(optionmenu_w, optionmenu, 0, 0, window_w, window_h);
	button_new(credit_button, credit_selected, credit_unselected, 400, 300, 450, 90, optionmenu_w);
	button_new(volume_button, volume_selected, volume_unselected, 400, 400, 450, 90, optionmenu_w);
	button_new(back_optionmenu_button, back_selected, back_unselected,400,600, 450, 90, optionmenu_w);

	window_new(creditmenu_w, creditmenu, 0, 0, window_w, window_h);
	button_new(back_creditmenu_button, back_selected, back_unselected, 400, 600, 450, 90, creditmenu_w);

	window_new(namemenu_w, namemenu, 260, 200, 739, 300);
	button_new(x_button, x_selected, x_unselected, 945, 205, 54, 52, namemenu_w);
	button_new(start_button, start_selected, start_unselected, 500, 400, 251, 68, namemenu_w);

	window_new(mainmenu_w, mainmenu, 0, 0, window_w, window_h);
	button_new(pause_button, pause_selected, pause_unselected, 0, 0, 47, 49, mainmenu_w);

	window_new(pausemenu_w, pausemenu, 400, 80, 739, 300);
	button_new(resume_button, resume_selected, resume_unselected, 520, 110, 242, 77, pausemenu_w);
	button_new(quit_mainmenu_button, quit_mainmenu_selected, quit_mainmenu_unselected, 520, 560, 242, 77, pausemenu_w);

}


void draw(struct system *sys)
{
	SDL_RenderClear(renderer);
	if (draw_startmenu)
	{
		window_draw(startmenu_w, renderer);
		button_draw(new_button, renderer);
		button_draw(load_button, renderer);
		button_draw(options_button, renderer);
		button_draw(quit_button, renderer);
	}
	if (draw_optionmenu)
	{
		window_draw(optionmenu_w, renderer);
		button_draw(credit_button, renderer);
		button_draw(volume_button, renderer);
		button_draw(back_optionmenu_button, renderer);
	}

	if (draw_creditmenu)
	{
		window_draw(creditmenu_w, renderer);
		button_draw(back_creditmenu_button, renderer);
	}
	if (draw_namemenu)
	{
		window_draw(namemenu_w, renderer);
		button_draw(start_button, renderer);
		button_draw(x_button, renderer);
	}

	if (draw_mainmenu)
	{
		window_draw(mainmenu_w, renderer);
		button_draw(pause_button, renderer);

		if(!draw_pausemenu)
			update_system(sys, renderer);
		else
			for(struct list *l = sys->items.next; l != NULL; l = l->next)
				DrawCircle(CONTAINER_OF_(struct item, list, l), renderer);


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
		window_draw(pausemenu_w, renderer);
		button_draw(resume_button, renderer);
		button_draw(quit_mainmenu_button, renderer);
	}
	SDL_RenderPresent(renderer);
}


void button_active(int *quit)
{
	if (quit_button->active)
		*quit = 1;
	else if (new_button->active)
	{
		new_button->active = 0;
		new_button->prelight = 0;
		namemenu_w->visible = 1, namemenu_w->event = 1;
		startmenu_w->event = 0;
		draw_namemenu = 1;
		input = 1;
	}
	else if (options_button->active)
	{
		options_button->active = 0;
		options_button->prelight = 0;
		startmenu_w->visible = 0, startmenu_w->event = 0;
		optionmenu_w->visible = 1, optionmenu_w->event = 1;
		draw_startmenu = 0;
		draw_optionmenu = 1;
	}
	else if (back_optionmenu_button->active)
	{
		back_optionmenu_button->active = 0;
		back_optionmenu_button->prelight = 0;
		startmenu_w->visible = 1, startmenu_w->event = 1;
		optionmenu_w->visible = 0, optionmenu_w->event = 0;
		draw_optionmenu = 0;
	}
	else if (credit_button->active)
	{
		credit_button->active = 0;	     
		credit_button->prelight = 0;
		optionmenu_w->visible = 0, optionmenu_w->event = 0;
		creditmenu_w->visible = 1, creditmenu_w->event = 1;
		draw_creditmenu = 1;
		draw_startmenu = 0;
		draw_optionmenu = 0;
	}
	else if (back_creditmenu_button->active)
	{
		back_creditmenu_button->active = 0;
		back_creditmenu_button->prelight = 0;
		optionmenu_w->visible = 1, optionmenu_w->event = 1;
		creditmenu_w->visible = 0, creditmenu_w->event = 0;
		draw_creditmenu = 0;
		draw_optionmenu = 1;
	}
	else if (pause_button->active)
	{
		pause_button->active = 0;
		pause_button->prelight = 0;
		mainmenu_w->event = 0;
		pausemenu_w->visible = 1, pausemenu_w->event = 1;
		draw_pausemenu = 1;
		//pause system
	}

	//for these 2, maybe add an event for when click 
	else if (resume_button->active)
	{
		resume_button->active = 0;
		resume_button->prelight = 1;
		pausemenu_w->visible = 0, pausemenu_w->event = 0;
		mainmenu_w->event = 1;
		draw_pausemenu = 0;
	}
	else if (quit_mainmenu_button->active)
	{
		quit_mainmenu_button->active = 0;
		quit_mainmenu_button->prelight = 0;
		pausemenu_w->visible = 0, pausemenu_w->event = 0;
		mainmenu_w->visible = 0;
		startmenu_w->visible = 1, startmenu_w->event = 1;
		draw_startmenu = 1;
		draw_mainmenu = 0;
		free_system(sys);
		draw_pausemenu = 0;
	}
}


int main()
{
	SDL_Event e;
	renderer = init("Kurt Kussel's teapot - StarDwarf",1280, 720);
	text = malloc(30*sizeof(char));
	*text = '\0'; 
	if (!renderer) return 1; 
	init_button_window();
	int quit = 0;
	intro = malloc(200*sizeof(char));
	*intro = '\0';
	TTF_Init();
	startmenu_w->visible = 1, startmenu_w->event = 1;

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
			button_active(&quit);

			window_event(startmenu_w, &e, &draw_startmenu);
			button_event(new_button, &e, &draw_startmenu);
			button_event(load_button, &e, &draw_startmenu);
			button_event(options_button, &e, &draw_startmenu);
			button_event(quit_button, &e, &draw_startmenu);

			window_event(optionmenu_w, &e, &draw_optionmenu);
			button_event(credit_button, &e, &draw_optionmenu);
			button_event(volume_button, &e, &draw_optionmenu);
			button_event(back_optionmenu_button, &e, &draw_optionmenu);

			window_event(creditmenu_w, &e, &draw_creditmenu);
			button_event(back_creditmenu_button, &e, &draw_creditmenu);

			window_event(mainmenu_w, &e, &draw_mainmenu);
			button_event(pause_button, &e, &draw_mainmenu);

			window_event(pausemenu_w, &e, &draw_pausemenu);
			button_event(quit_mainmenu_button, &e, &draw_pausemenu);
			button_event(resume_button, &e, &draw_pausemenu);

		}
		draw(sys);
		if (input)
		{

			free(intro);
			intro = malloc(200*sizeof(char));
			textinput();
			if (*text)
				sprintf(intro, "welcome to %s's world", text);
			else
				sprintf(intro, "welcome to StarDwarf's Kurt Russel's teapot");

			if(!strcmp(text, "Russel"))
			  {
			    
			    //system created
			
			    sys = new_system(2);
			    sys->delta_time = 0.1f;
			
			    //values for position vector
			    float val[2] = {250, 250};
			    float val2[2] = {250, 400};

			    //vector postion and creation of item
			    struct vector *position = new_vector(2, val);
			    struct vector *position2 = new_vector(2, val2);

			    struct vector *force = new_vector(2, NULL);
			    force->values[0] = -1;
			    force->values[1] = -1;
			    
			    item = new_item(position);
			    item->size = 50;
			    item->mass  = 1000000000000000.0f;
			    item->color[1] = 0;
			    item->color[2] = 0;
			    item->velocity.values[0] = 10;
			    item->user_force.next = &force->list;
			    
			    item2 = new_item(position2);
			    item2->size = 50;
			    item2->mass = 1000000000000000.0f;

			    //adding item to list of items in system
			    push_item(sys, item);
			    push_item(sys, item2);

			    free_vector(position);
			    free_vector(position2);
			  }
			else
			  {
			    //system created
			
			    sys = new_system(2);
			    sys->delta_time = 0.1f;
			
			    //values for position vector
			    float val[2] = {250, 250};
			    float val2[2] = {350, 350};
			    float val3[2] = {750, 500};

			    //vector postion and creation of item
			    struct vector *position = new_vector(2, val);
			    struct vector *position2 = new_vector(2, val2);
			    struct vector *position3 = new_vector(2, val3);

			    item = new_item(position);
			    item->size = 100;
			    item->mass  = 100000000000000.0f;
			    item->color[1] = 0;
			    item->color[2] = 0;
			    item->velocity.values[0] = 10;

			    item2 = new_item(position2);
			    item2->size = 50;
			    item2->mass = 100000000000000.0f;

			    item3 = new_item(position3);
			    item3->size = 50;
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
			puts("Drawing");
			printf("x = %f, y = %f\n", item->position.values[0], item->position.values[1]);
			//init_circle(item);
			//draw_cricle(item);
			puts("Finished Drawing");


		}

	}
	clean();
	free(text);
	free(startmenu_w);
	free(new_button);
	free(load_button);
	free(options_button);
	free(quit_button);

	free(optionmenu_w);
	free(credit_button);
	free(volume_button);
	free(back_optionmenu_button);

	free(creditmenu_w);
	free(back_creditmenu_button);

	free(namemenu_w);
	free(x_button);
	free(start_button);
	return 0;
}

