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
  TTF_Init();                                                                            
  if (*text)                                                                             
    {
      SDL_Rect pos;                                                                      
      MakeRect(&pos, 400,300,400,400);                                                   
      SDL_Color fcolor;                                                                  
      fcolor.r = 255;                                                                    
      fcolor.g  = 255;                                                                   
      fcolor.b  = 255;                                                                   
      TTF_Font *font = TTF_OpenFont ("textfont.ttf", 30);                                
      SDL_Surface *textSurface = TTF_RenderText_Solid(font, (const char*) text, fcolor); 
      SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, textSurface);        
      SDL_QueryTexture(texture, NULL, NULL, &pos.w, &pos.h);                             
      SDL_RenderCopy(renderer, texture, NULL, &pos);                                     
      TTF_CloseFont(font);
    }                                                                                    
  TTF_Quit();                                                                            
  SDL_RenderPresent(renderer);

}

void textinput()
{
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

	  
	  switch (e.type)
	    {
	    case SDL_QUIT:
	      input = 0;
	      done = SDL_TRUE;
	      break;
	    case SDL_TEXTINPUT:
	      if (nbchar < 30)
		{
		  strcat(text, e.text.text);
		  nbchar += 1;
		}
	      break;
	    case SDL_TEXTEDITING:
	      /*    
		Update the composition text.
		Update the cursor position.
		Update the selection length (if any).
	      */
	      composition = e.edit.text;
	      cursor = e.edit.start;
	      selection_len = e.edit.length;
	      break;
	    }
     
	}      
    }
  SDL_StopTextInput();
  input = 0;
}     
