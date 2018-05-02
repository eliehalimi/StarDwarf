# include <stdio.h>
# include <stdlib.h>
# include <SDL2/SDL.h>
# include <SDL2/SDL_ttf.h>
# include <SDL2/SDL_image.h>
# include <err.h>
# include <unistd.h>
# include "gui.h"
# include "draw_item.h"
# include "hash_table.h"
# include "../save/save.h"

struct system *init_system(int w, int h, struct htable *text_list)
{
  struct system *sys;
  struct item *item = NULL;
  struct item *item2 = NULL;
  struct item *item3 = NULL;
  if(!strcmp(((struct text *)(access_htable(text_list,"name")->value))->text, "Russel"))
    {
      //system created
      sys = new_system(3);
      sys->camera = new_camera(w / 2, h / 2);
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
  else
    {
      //system created
      sys = new_system(3);
      sys->camera = new_camera(w / 2, h / 2);
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
      strncpy(item->label, "test", 16);
      
      item2 = new_item(position2);
      item2->size = 10;
      item2->mass = 1000000000000.0f;
      item2->color[0] = 0;
      item2->color[2] = 0;
      strncpy(item2->label, "asteroid", 16);
      
      item3 = new_item(position3);
      item3->size = 100;
      item3->mass = 100000000000000.0f;
      item3->color[0] = 0;
      strncpy(item3->label, "cyan planet", 16);
      
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
  return sys;
}

void init_draw_list(struct htable *draw_list)
{
  add_htable(draw_list, "startmenu", malloc(sizeof(int)));  
  add_htable(draw_list, "optionmenu", malloc(sizeof(int)));
  add_htable(draw_list, "creditmenu", malloc(sizeof(int)));
  add_htable(draw_list, "namemenu", malloc(sizeof(int)));
  add_htable(draw_list, "mainmenu", malloc(sizeof(int)));
  add_htable(draw_list, "pausemenu", malloc(sizeof(int)));
  
  *((int *)(access_htable(draw_list, "startmenu")->value)) = 1;
  *((int *)(access_htable(draw_list, "creditmenu")->value)) = 0;
  *((int *)(access_htable(draw_list, "namemenu")->value)) = 0;
  *((int *)(access_htable(draw_list, "mainmenu")->value)) = 0;
  *((int *)(access_htable(draw_list, "pausemenu")->value)) = 0;
  *((int *)(access_htable(draw_list, "optionmenu")->value)) = 0;  
}

void init_text(struct htable *text_list, char *name, int size, int item)
{
  add_htable(text_list, name, malloc(sizeof(struct text)));
  struct text *text = (struct text *)(access_htable(text_list, name)->value);
  text->text = malloc(size*sizeof(char));
  *(text->text) = '\0';
  text->nbchar = 0;
  text->active = 0;
  text->item = item;
}
void init_text_list(struct htable *text_list)
{
  init_text(text_list, "name", 30, 0);
  init_text(text_list, "intro", 200, 0);
  init_text(text_list, "item_name", 20, 1);
  init_text(text_list, "item_x", 20, 1);
  init_text(text_list, "item_y", 20, 1);
  init_text(text_list, "item_z", 20, 1);
  init_text(text_list, "item_mass", 20, 1);
  init_text(text_list, "item_radius", 20, 1);
  init_text(text_list, "item_vx", 20, 1);
  init_text(text_list, "item_vy", 20, 1);
  init_text(text_list, "item_vz", 20, 1);
}
void init_lists(int w, int h, struct htable *button_list, struct htable *window_list, struct htable *img_list, struct htable *draw_list, struct htable *text_list)
{
  
        init_draw_list(draw_list);
        init_text_list(text_list);

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
	add_htable(button_list, "item_name", malloc(sizeof(struct button)));
	add_htable(button_list, "item_x", malloc(sizeof(struct button)));
	add_htable(button_list, "item_y", malloc(sizeof(struct button)));
	add_htable(button_list, "item_z", malloc(sizeof(struct button)));
	add_htable(button_list, "item_mass", malloc(sizeof(struct button)));
	add_htable(button_list, "item_radius", malloc(sizeof(struct button)));
	add_htable(button_list, "item_vx", malloc(sizeof(struct button)));
	add_htable(button_list, "item_vy", malloc(sizeof(struct button)));
	add_htable(button_list, "item_vz", malloc(sizeof(struct button)));
	add_htable(button_list, "add", malloc(sizeof(struct button)));
	add_htable(button_list, "delete", malloc(sizeof(struct button)));

	add_htable(window_list, "mainmenu", malloc(sizeof(struct window)));
	add_htable(window_list, "itemsmenu", malloc(sizeof(struct window)));
	
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
	window_new(access_htable(window_list, "itemsmenu")->value, access_htable(img_list,"itemsmenu")->value, 1053, 44, 227,676);
	button_new(access_htable(button_list, "pause")->value, access_htable(img_list,"pause_selected")->value, access_htable(img_list,"pause_unselected")->value, 0, 0, access_htable(window_list, "mainmenu")->value);
	button_new(access_htable(button_list, "item_name")->value, access_htable(img_list,"item_namebox_selected")->value, access_htable(img_list,"item_namebox_unselected")->value, 1073, 68, access_htable(window_list, "mainmenu")->value);
	button_new(access_htable(button_list, "item_x")->value, access_htable(img_list,"item_posbox_selected")->value, access_htable(img_list,"item_posbox_unselected")->value, 1095, 130, access_htable(window_list, "mainmenu")->value);
	button_new(access_htable(button_list, "item_y")->value, access_htable(img_list,"item_posbox_selected")->value, access_htable(img_list,"item_posbox_unselected")->value, 1095, 158, access_htable(window_list, "mainmenu")->value);
	button_new(access_htable(button_list, "item_z")->value, access_htable(img_list,"item_posbox_selected")->value, access_htable(img_list,"item_posbox_unselected")->value, 1095, 186, access_htable(window_list, "mainmenu")->value);
	button_new(access_htable(button_list, "item_mass")->value, access_htable(img_list,"item_posbox_selected")->value, access_htable(img_list,"item_posbox_unselected")->value, 1090, 239, access_htable(window_list, "mainmenu")->value);
	button_new(access_htable(button_list, "item_radius")->value, access_htable(img_list,"item_posbox_selected")->value, access_htable(img_list,"item_posbox_unselected")->value, 1090, 289, access_htable(window_list, "mainmenu")->value);
	button_new(access_htable(button_list, "item_vx")->value, access_htable(img_list,"item_posbox_selected")->value, access_htable(img_list,"item_posbox_unselected")->value, 1090, 340, access_htable(window_list, "mainmenu")->value);
	button_new(access_htable(button_list, "item_vy")->value, access_htable(img_list,"item_posbox_selected")->value, access_htable(img_list,"item_posbox_unselected")->value, 1090, 368, access_htable(window_list, "mainmenu")->value);
	button_new(access_htable(button_list, "item_vz")->value, access_htable(img_list,"item_posbox_selected")->value, access_htable(img_list,"item_posbox_unselected")->value, 1090, 396, access_htable(window_list, "mainmenu")->value);
	button_new(access_htable(button_list, "add")->value, access_htable(img_list,"add_selected")->value, access_htable(img_list,"add_unselected")->value, 1090, 610, access_htable(window_list, "mainmenu")->value);
	button_new(access_htable(button_list, "delete")->value, access_htable(img_list,"delete_selected")->value, access_htable(img_list,"delete_unselected")->value, 1090, 660, access_htable(window_list, "mainmenu")->value);
	
	
	window_new(access_htable(window_list, "pausemenu")->value, access_htable(img_list,"pausemenu")->value, 400, 80, 739, 300);
	button_new(access_htable(button_list, "resume")->value, access_htable(img_list,"resume_selected")->value, access_htable(img_list,"resume_unselected")->value, 520, 110, access_htable(window_list, "pausemenu")->value);
	button_new(access_htable(button_list, "quit_mainmenu")->value, access_htable(img_list,"quit_mainmenu_selected")->value, access_htable(img_list,"quit_mainmenu_unselected")->value, 520, 560, access_htable(window_list, "pausemenu")->value);


	((struct button *)(access_htable(button_list, "item_name")->value))->textbox = 1;
	((struct button *)(access_htable(button_list, "item_x")->value))->textbox = 1;
	((struct button *)(access_htable(button_list, "item_y")->value))->textbox = 1;
	((struct button *)(access_htable(button_list, "item_z")->value))->textbox = 1;
	((struct button *)(access_htable(button_list, "item_mass")->value))->textbox = 1;
	((struct button *)(access_htable(button_list, "item_radius")->value))->textbox = 1;
	((struct button *)(access_htable(button_list, "item_vx")->value))->textbox = 1;
	((struct button *)(access_htable(button_list, "item_vy")->value))->textbox = 1;
	((struct button *)(access_htable(button_list, "item_vz")->value))->textbox = 1;

}

