# include <stdio.h>
# include <stdlib.h>
# include <SDL2/SDL.h>
# include <SDL2/SDL_ttf.h>
# include <SDL2/SDL_image.h>
# include <err.h>
# include <unistd.h>
# include "gui.h"
# include "hash_table.h"
# include "../save/save.h"

void init_button_window(int w, int h, struct htable *button_list, struct htable *window_list, struct htable *img_list)
{
	add_htable(button_list, "new", malloc(sizeof(struct button)));
	add_htable(button_list, "load", malloc(sizeof(struct button)));
	add_htable(button_list, "option", malloc(sizeof(struct button)));
	add_htable(button_list, "quit", malloc(sizeof(struct button)));
	add_htable(window_list, "startmenu", malloc(sizeof(struct window)));

	add_htable(button_list, "credit", malloc(sizeof(struct button)));
	add_htable(button_list, "volume", malloc(sizeof(struct button)));
	add_htable(button_list, "back_optionmenu", malloc(sizeof(struct button)));
	add_htable(window_list, "optionmenu", malloc(sizeof(struct window)));

	add_htable(window_list, "creditmenu", malloc(sizeof(struct window)));
	add_htable(button_list, "back_creditmenu", malloc(sizeof(struct button)));

	add_htable(button_list, "x", malloc(sizeof(struct button)));
	add_htable(button_list, "start", malloc(sizeof(struct button)));
	add_htable(window_list, "namemenu", malloc(sizeof(struct window)));

	add_htable(button_list, "pause", malloc(sizeof(struct button)));
	add_htable(window_list, "mainmenu", malloc(sizeof(struct window)));

	add_htable(button_list, "resume", malloc(sizeof(struct button)));
	add_htable(button_list, "quit_mainmenu", malloc(sizeof(struct button)));
	add_htable(window_list, "pausemenu", malloc(sizeof(struct window)));

	window_new(access_htable(window_list, "startmenu")->value, access_htable(img_list, "startmenu")->value, 0, 0, w, h);
	button_new(access_htable(button_list, "new")->value, access_htable(img_list,"new_selected")->value, access_htable(img_list, "new_unselected")->value, 400, 320, access_htable(window_list, "startmenu")->value);
	button_new(access_htable(button_list, "load")->value, access_htable(img_list,"load_selected")->value, access_htable(img_list,"load_unselected")->value, 400, 415, access_htable(window_list, "startmenu")->value);
	button_new(access_htable(button_list, "option")->value, access_htable(img_list,"options_selected")->value, access_htable(img_list,"options_unselected")->value, 400, 510, access_htable(window_list, "startmenu")->value);
	button_new(access_htable(button_list, "quit")->value, access_htable(img_list,"quit_selected")->value, access_htable(img_list,"quit_unselected")->value, 400, 605, access_htable(window_list, "startmenu")->value);

	
	window_new(access_htable(window_list, "optionmenu")->value, access_htable(img_list,"optionmenu")->value, 0, 0, w, h);
	button_new(access_htable(button_list, "credit")->value, access_htable(img_list,"credit_selected")->value, access_htable(img_list,"credit_unselected")->value, 400, 300, access_htable(window_list, "optionmenu")->value);
	button_new(access_htable(button_list, "volume")->value, access_htable(img_list,"volume_selected")->value, access_htable(img_list,"volume_unselected")->value, 400, 400, access_htable(window_list, "optionmenu")->value);
	button_new(access_htable(button_list, "back_optionmenu")->value, access_htable(img_list,"back_selected")->value, access_htable(img_list,"back_unselected")->value,400,600, access_htable(window_list, "optionmenu")->value);

	
	window_new(access_htable(window_list, "creditmenu")->value, access_htable(img_list,"creditmenu")->value, 0, 0, w, h);
	button_new(access_htable(button_list, "back_creditmenu")->value, access_htable(img_list,"back_selected")->value, access_htable(img_list,"back_unselected")->value, 400, 600, access_htable(window_list, "creditmenu")->value);

	
	window_new(access_htable(window_list, "namemenu")->value, access_htable(img_list,"namemenu")->value, 260, 200, 739, 300);
	button_new(access_htable(button_list, "x")->value, access_htable(img_list,"x_selected")->value, access_htable(img_list,"x_unselected")->value, 945, 205, access_htable(window_list, "namemenu")->value);
	button_new(access_htable(button_list, "start")->value, access_htable(img_list,"start_selected")->value, access_htable(img_list,"start_unselected")->value, 500, 400, access_htable(window_list, "namemenu")->value);

	
	window_new(access_htable(window_list, "mainmenu")->value, access_htable(img_list,"mainmenu")->value, 0, 0, w, h);
	button_new(access_htable(button_list, "pause")->value, access_htable(img_list,"pause_selected")->value, access_htable(img_list,"pause_unselected")->value, 0, 0, access_htable(window_list, "mainmenu")->value);

	
	window_new(access_htable(window_list, "pausemenu")->value, access_htable(img_list,"pausemenu")->value, 400, 80, 739, 300);
	button_new(access_htable(button_list, "resume")->value, access_htable(img_list,"resume_selected")->value, access_htable(img_list,"resume_unselected")->value, 520, 110, access_htable(window_list, "pausemenu")->value);
	button_new(access_htable(button_list, "quit_mainmenu")->value, access_htable(img_list,"quit_mainmenu_selected")->value, access_htable(img_list,"quit_mainmenu_unselected")->value, 520, 560, access_htable(window_list, "pausemenu")->value);

}

void button_active(int *quit, struct system *sys, struct htable *button_list, struct htable *window_list)
{
	if (((struct button *)(access_htable(button_list, "quit")->value))->active)
		*quit = 1;
	else if (((struct button *)(access_htable(button_list, "new")->value))->active)
	{
		((struct button *)(access_htable(button_list, "new")->value))->active = 0;
		((struct button *)(access_htable(button_list, "new")->value))->prelight = 0;
		((struct window *)(access_htable(window_list, "namemenu")->value))->visible = 1;
		((struct window *)(access_htable(window_list, "namemenu")->value))->event = 1;
		((struct window *)(access_htable(window_list, "startmenu")->value))->event = 0;
		draw_namemenu = 1;
		input = 1;
	}
	else if (((struct button *)(access_htable(button_list, "option")->value))->active)
	{
	        ((struct button *)(access_htable(button_list, "option")->value))->active = 0;
		((struct button *)(access_htable(button_list, "option")->value))->prelight = 0;
		((struct window *)(access_htable(window_list, "startmenu")->value))->visible = 0;
		((struct window *)(access_htable(window_list, "startmenu")->value))->event = 0;
	        ((struct window *)(access_htable(window_list, "optionmenu")->value))->visible = 1;
		((struct window *)(access_htable(window_list, "optionmenu")->value))->event = 1;
		draw_startmenu = 0;
		draw_optionmenu = 1;
	}
	else if (((struct button *)(access_htable(button_list, "back_optionmenu")->value))->active)
	{
		((struct button *)(access_htable(button_list, "back_optionmenu")->value))->active = 0;
		((struct button *)(access_htable(button_list, "back_optionmenu")->value))->prelight = 0;
		((struct window *)(access_htable(window_list, "startmenu")->value))->visible = 1;
		((struct window *)(access_htable(window_list, "startmenu")->value))->event = 1;
		((struct window *)(access_htable(window_list, "optionmenu")->value))->visible = 0;
		((struct window *)(access_htable(window_list, "optionmenu")->value))->event = 0;
		draw_optionmenu = 0;
	}
	else if (((struct button *)(access_htable(button_list, "credit")->value))->active)
	{
		((struct button *)(access_htable(button_list, "credit")->value))->active = 0;	     
		((struct button *)(access_htable(button_list, "credit")->value))->prelight = 0;
		((struct window *)(access_htable(window_list, "optionmenu")->value))->visible = 0;
		((struct window *)(access_htable(window_list, "optionmenu")->value))->event = 0;
		((struct window *)(access_htable(window_list, "creditmenu")->value))->visible = 1;
		((struct window *)(access_htable(window_list, "creditmenu")->value))->event = 1;
		draw_creditmenu = 1;
		draw_startmenu = 0;
		draw_optionmenu = 0;
	}
	else if (((struct button *)(access_htable(button_list, "back_creditmenu")->value))->active)
	{
		((struct button *)(access_htable(button_list, "back_creditmenu")->value))->active = 0;
		((struct button *)(access_htable(button_list, "back_creditmenu")->value))->prelight = 0;
		((struct window *)(access_htable(window_list, "optionmenu")->value))->visible = 1;
		((struct window *)(access_htable(window_list, "optionmenu")->value))->event = 1;
		((struct window *)(access_htable(window_list, "creditmenu")->value))->visible = 0;
		((struct window *)(access_htable(window_list, "creditmenu")->value))->event = 0;
		draw_creditmenu = 0;
		draw_optionmenu = 1;
	}
	else if (((struct button *)(access_htable(button_list, "pause")->value))->active)
	{
		((struct button *)(access_htable(button_list, "pause")->value))->active = 0;
		((struct button *)(access_htable(button_list, "pause")->value))->prelight = 0;
		((struct window *)(access_htable(window_list, "startmenu")->value))->event = 0;
		((struct window *)(access_htable(window_list, "pausemenu")->value))->visible = 1;
		((struct window *)(access_htable(window_list, "pausemenu")->value))->event = 1;
		draw_pausemenu = 1;
		//pause system
	}

	//for these 2, maybe add an event for when click 
	else if (((struct button *)(access_htable(button_list, "resume")->value))->active)
	{
		((struct button *)(access_htable(button_list, "resume")->value))->active = 0;
		((struct button *)(access_htable(button_list, "resume")->value))->prelight = 1;
		((struct window *)(access_htable(window_list, "pausemenu")->value))->visible = 0;
		((struct window *)(access_htable(window_list, "pausemenu")->value))->event = 0;
		((struct window *)(access_htable(window_list, "mainmenu")->value))->event = 1;
		draw_pausemenu = 0;
	}
	else if (((struct button *)(access_htable(button_list, "quit_mainmenu")->value))->active)
	{
		((struct button *)(access_htable(button_list, "quit_mainmenu")->value))->active = 0;
		((struct button *)(access_htable(button_list, "quit_mainmenu")->value))->prelight = 0;
		((struct window *)(access_htable(window_list, "pausemenu")->value))->visible = 0;
		((struct window *)(access_htable(window_list, "pausemenu")->value))->event = 0;
		((struct window *)(access_htable(window_list, "mainmenu")->value))->visible = 0;
		((struct window *)(access_htable(window_list, "startmenu")->value))->visible = 1;
		((struct window *)(access_htable(window_list, "startmenu")->value))->event = 1;
		draw_startmenu = 1;
		draw_mainmenu = 0;
		free_system(sys);
		draw_pausemenu = 0;
	}
	else if (((struct button *)(access_htable(button_list, "load")->value))->active)
	{
		((struct button *)(access_htable(button_list, "load")->value))->active = 0;
		((struct button *)(access_htable(button_list, "load")->value))->prelight = 1;
		((struct window *)(access_htable(window_list, "mainmenu")->value))->visible = 1;
		((struct window *)(access_htable(window_list, "mainmenu")->value))->event = 1;           
		((struct window *)(access_htable(window_list, "startmenu")->value))->visible = 0;
		((struct window *)(access_htable(window_list, "startmenu")->value))->event = 0;   
		sys = load_system("../save/system.txt");
		draw_mainmenu = 1;

	}
}
