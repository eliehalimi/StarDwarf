# define _DEFAULT_SOURCE
# include <stdio.h>
# include <stdlib.h>
# include <SDL2/SDL.h>
# include <SDL2/SDL_ttf.h>
# include <SDL2/SDL_image.h>
# include <err.h>
# include <unistd.h>
# include "gui.h"
# include "../Physic/physic.h"
struct text *get_text(struct htable *text_list, char *name)
{
  return (struct text *)(access_htable(text_list, name)->value);
}
void text_to_input(struct text *input, char * text)
{
  //free(input->text); 
  //input->text = malloc(20*sizeof(char));                                
  *(input->text) = '\0';
  size_t i = 0;
  for (; i < 15 && text[i] != '\0'; i++)
    input->text[i] = text[i];
  input->nbchar = i;
  for (; i < 25; i++)
    input->text[i] = '\0';
}
void item_to_input(struct htable *text_list, struct item *item)
{
  text_to_input(get_text(text_list, "item_name"), item->label);
  gcvt(item->mass, 15, get_text(text_list, "item_mass")->text);
  gcvt(item->size, 15, get_text(text_list, "item_radius")->text);

  gcvt(item->position.values[0], 15, get_text(text_list, "item_x")->text);
  gcvt(item->position.values[1], 15, get_text(text_list, "item_y")->text);
  gcvt(item->position.values[2], 15, get_text(text_list, "item_z")->text);

  gcvt(item->velocity.values[0], 15, get_text(text_list, "item_vx")->text);
  gcvt(item->velocity.values[1], 15, get_text(text_list, "item_vy")->text);
  gcvt(item->velocity.values[2], 15, get_text(text_list, "item_vz")->text);
}

void input_to_item(struct htable *text_list, struct item *item)
{
  strncpy(item->label, get_text(text_list, "item_name")->text, 15);
  
  item->mass = atof(get_text(text_list, "item_mass")->text);
  item->size = atof(get_text(text_list, "item_radius")->text);
 
  float x = atof(get_text(text_list, "item_x") -> text);
  float y = atof(get_text(text_list, "item_y") -> text);
  float z = atof(get_text(text_list, "item_z") -> text);

  float pos_val[3] = {x,y,z};
  struct vector *position = new_vector(3, pos_val);
  memcpy(item->position.values, position->values, sizeof(float)*position->size);
  free_vector(position);
  
  float vx = atof(get_text(text_list, "item_vx") -> text);
  float vy = atof(get_text(text_list, "item_vy") -> text);
  float vz = atof(get_text(text_list, "item_vz") -> text);
  float v_val[3] = {vx,vy,vz};
  struct vector *v = new_vector(3, v_val);
  memcpy(item->velocity.values, v->values, sizeof(float)*v->size);
  free_vector(v);
}

void display_text(SDL_Renderer *renderer, struct htable *text_list, char *name, int x, int h, int rgb, int size)
{
  struct text *text = (struct text *)(access_htable(text_list, name)->value);
  if (!text->item || text->nbchar > 0)
    {
      SDL_Rect pos;                                                        
      MakeRect(&pos, x, h, 400, 400);
      SDL_Color fcolor;                  
      fcolor.r = rgb; fcolor.g  = rgb; fcolor.b  =rgb;                    
      TTF_Font *font;
      if (size > 26)
	font = TTF_OpenFont ("textfont.ttf", size);
      else
	font = TTF_OpenFont("Lato-Medium.ttf", size);
      
      SDL_Surface *textSurface = TTF_RenderText_Solid(font, (const char*)text->text, fcolor);
      SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, textSurface);         
      SDL_QueryTexture(texture, NULL, NULL, &pos.w, &pos.h);                              
      SDL_RenderCopy(renderer, texture, NULL, &pos); 
      TTF_CloseFont(font);             
      SDL_DestroyTexture(texture); 
    }
}
void textinput(SDL_Event e, struct text *text, int maxchr, struct button *button)
{                                                     
  if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_BACKSPACE && text->nbchar > 0)   
    {                                                                           
      text->text[text->nbchar - 1] = '\0';                                     
      text->nbchar -= 1;                                                    
    }                                                    
  else if (e.type == SDL_TEXTINPUT && text->nbchar < maxchr)                   
    {                                                            
      strcat(text->text, e.text.text);                                 
      text->nbchar += 1;                                                   
    }
  if (button != NULL && button->input == 0)
    text->active = 0;
} 
void init_textinput(struct htable *text_list, char *name, int size)
{
  struct text *text = (struct text *)(access_htable(text_list, name)->value);
  if (!text->item)
    {
      free(text -> text); 
      text->text = malloc(size*sizeof(char));                                           
      *(text->text) = '\0';
      text->nbchar = 0;
    }
  text->active = 1;
}
