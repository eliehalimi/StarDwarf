# include <stdio.h>
# include <stdlib.h>
# include <SDL2/SDL.h>
# include <SDL2/SDL_ttf.h>
# include <SDL2/SDL_image.h>
# include <err.h>
# include <unistd.h>
# include "gui.h"  
void display_text(SDL_Renderer *renderer, char *text, int x, int h, int rgb, int size)
{
  SDL_Rect pos;                                                        
  MakeRect(&pos, x, h, 400, 400);
  SDL_Color fcolor;                  
  fcolor.r = rgb; fcolor.g  = rgb; fcolor.b  =rgb;                    
  TTF_Font *font = TTF_OpenFont ("textfont.ttf", size);        
  SDL_Surface *textSurface = TTF_RenderText_Solid(font, (const char*)text, fcolor);
  SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, textSurface);         
  SDL_QueryTexture(texture, NULL, NULL, &pos.w, &pos.h);                              
  SDL_RenderCopy(renderer, texture, NULL, &pos); 
  TTF_CloseFont(font);             
  SDL_DestroyTexture(texture); 
  
}
void textinput(SDL_Event e, struct text *text, int maxchr)                                          
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
} 
void init_textinput(struct htable *text_list, char *name, int size)
{
  struct text *text = (struct text *)(access_htable(text_list, name)->value);
  free(text -> text);
  text->active = 1;
  text->text = malloc(size*sizeof(char));                                              
  *(text->text) = '\0';                                                                  
  text->nbchar = 0;                                                                      }
