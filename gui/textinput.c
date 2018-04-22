# include <stdio.h>
# include <stdlib.h>
# include <SDL2/SDL.h>
# include <SDL2/SDL_ttf.h>
# include <SDL2/SDL_image.h>
# include <err.h>
# include <unistd.h>
# include "gui.h"  
//char *text;
char *composition;
Sint32 cursor;
Sint32 selection_len;
void drawtextinput(SDL_Renderer *renderer, struct htable *button_list, struct htable *window_list, struct htable *draw_list)
{
  SDL_RenderClear(renderer);
  if (*((int *)(access_htable(draw_list, "startmenu")->value)))
    {
      window_draw(access_htable(window_list, "startmenu")->value, renderer);
      button_draw(access_htable(button_list, "new")->value, renderer);                                                 
      button_draw(access_htable(button_list, "load")->value, renderer);                                               
      button_draw(access_htable(button_list, "option")->value, renderer);                                             
      button_draw(access_htable(button_list, "quit")->value, renderer);                                                
    }                                                                                    
  if (*((int *)(access_htable(draw_list, "namemenu")->value)))                                                                     
    {
      window_draw(access_htable(window_list, "namemenu")->value, renderer);                                            
      button_draw(access_htable(button_list, "start")->value, renderer);                                               
      button_draw(access_htable(button_list, "x")->value, renderer);                                                   
    }                                                                                    
  if (*text)                                                                             
    {
      SDL_Rect pos;                                                                      
      MakeRect(&pos,320,300,400,400);                                                   
      SDL_Color fcolor;                                                                  
      fcolor.r = 255;                                                                    
      fcolor.g  = 255;                                                                   
      fcolor.b  = 255;                                                                   
      TTF_Font *font = TTF_OpenFont ("textfont.ttf", 40);                                
      SDL_Surface *textSurface = TTF_RenderText_Solid(font, (const char*) text, fcolor); 
      SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, textSurface);        
      SDL_QueryTexture(texture, NULL, NULL, &pos.w, &pos.h);                             
      SDL_RenderCopy(renderer, texture, NULL, &pos);                                     
      TTF_CloseFont(font);
      SDL_DestroyTexture(texture);
    }                                                                                    
     
  SDL_RenderPresent(renderer);

}

void textinput(SDL_Renderer *renderer, struct htable *button_list, struct htable *window_list, struct htable *draw_list)
{
  free(text);
  text = malloc(30*sizeof(char));
  *text = '\0';
  SDL_bool done = SDL_FALSE;
  SDL_Event e;
  int nbchar = 0;
  SDL_StartTextInput();

  while (!done)
    {
      SDL_Delay(10);
      while (SDL_PollEvent(&e))
	{
	  if (((struct button *)(access_htable(button_list, "x")->value))->active)
	    {
	      ((struct button *)(access_htable(button_list, "x")->value))->active = 0;
	      ((struct button *)(access_htable(button_list, "x")->value))->prelight = 0;
	      ((struct window *)(access_htable(window_list, "namemenu")->value))->visible = 0;
	      ((struct window *)(access_htable(window_list, "namemenu")->value))->event = 0;
	      ((struct window *)(access_htable(window_list, "startmenu")->value))->event = 1;
	      *((int *)(access_htable(draw_list, "namemenu")->value)) = 0; 
	      done = SDL_TRUE;  
	    }
	  else if (((struct button *)(access_htable(button_list, "start")->value))->active)
	    {
	      ((struct button *)(access_htable(button_list, "start")->value))->active = 0;
	      ((struct button *)(access_htable(button_list, "start")->value))->prelight = 0;
	      ((struct window *)(access_htable(window_list, "mainmenu")->value))->visible = 1;
	      ((struct window *)(access_htable(window_list, "mainmenu")->value))->event = 1;
	      ((struct window *)(access_htable(window_list, "startmenu")->value))->visible = 0;
	      ((struct window *)(access_htable(window_list, "startmenu")->value))->event = 0;
	      ((struct window *)(access_htable(window_list, "namemenu")->value))->visible = 0;
	      ((struct window *)(access_htable(window_list, "namemenu")->value))->event = 0;
	      ((struct window *)(access_htable(window_list, "itemsmenu")->value))->visible = 1;   
	      ((struct window *)(access_htable(window_list, "itemsmenu")->value))->event = 1;    
	      *((int *)(access_htable(draw_list, "mainmenu")->value)) = 1; 
	      done = SDL_TRUE;
	      
	    }

	  window_event(access_htable(window_list, "namemenu")->value, &e, access_htable(draw_list, "namemenu")->value);                          
	  button_event(access_htable(button_list, "x")->value, &e, access_htable(draw_list, "namemenu")->value);
	  button_event(access_htable(button_list, "start")->value, &e, access_htable(draw_list, "namemenu")->value); 
	  drawtextinput(renderer, button_list, window_list, draw_list);

	  
	  if (e.type ==  SDL_QUIT)
	    {
	      *((int *)(access_htable(draw_list, "input")->value)) = 0;
	      done = SDL_TRUE;
	    }
	  else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_BACKSPACE && nbchar > 0)
		{
		  text[nbchar - 1] = '\0';
		  nbchar -= 1;
		}
	  else if (e.type == SDL_TEXTINPUT && nbchar < 25)
	    {
	     
	      strcat(text, e.text.text);
	      nbchar += 1;
	    }
	}      
    }
  SDL_StopTextInput();
  *((int *)(access_htable(draw_list, "input")->value)) = 0;
}     
