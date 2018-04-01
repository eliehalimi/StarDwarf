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
void drawtextinput()
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
  if (draw_namemenu)                                                                     
    {
      window_draw(namemenu_w, renderer);                                                 
      button_draw(start_button, renderer);                                               
      button_draw(x_button, renderer);                                                   
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

void textinput()
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
	  if (x_button->active)
	    {
	      x_button->active = 0;
	      x_button->prelight = 0;
	      namemenu_w->visible = 0, namemenu_w->event = 0;
	      startmenu_w->event = 1;
	      draw_namemenu = 0; 
	      done = SDL_TRUE;  
	    }
	  else if (start_button->active)
	    {
	      start_button->active = 0;
	      start_button->prelight = 0;
	      mainmenu_w->visible = 1, mainmenu_w->event = 1;                           
	      startmenu_w->visible = 0, startmenu_w->event = 0;                         
	      namemenu_w->visible = 0, namemenu_w->event = 0;
	      draw_mainmenu = 1; 
	      done = SDL_TRUE;
	    }

	  window_event(namemenu_w, &e, &draw_namemenu);                          
	  button_event(x_button, &e, &draw_namemenu);
	  button_event(start_button, &e, &draw_namemenu); 
	  drawtextinput();

	  
	  if (e.type ==  SDL_QUIT)
	    {
	      input = 0;
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
  input = 0;
}     
