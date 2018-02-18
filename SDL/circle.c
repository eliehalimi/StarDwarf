#include "SDL.h"
#include <SDL2/SDL.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL_image.h>

#define SCR_WDT 1280
#define SCR_HGT 960
#define M_PI	3.14159265358979323846264338327950288

const int SCR_CEN_X = SCR_WDT / 2;
const int SCR_CEN_Y = SCR_HGT / 2;


int DrawCircle( SDL_Renderer *r, int x, int y, int radius);

int main ()
{
	SDL_Texture *background = NULL;
	
      	SDL_Init ( SDL_INIT_VIDEO ); 

    	SDL_Window *window = SDL_CreateWindow ( "Drawing a Circle", SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, SCR_WDT, SCR_HGT, 0 );
    	SDL_Renderer *renderer = SDL_CreateRenderer ( window, -1, SDL_RENDERER_SOFTWARE );
   	
	int w, h;


	// Loading image
	background = IMG_LoadTexture(renderer, "../resources/bg.jpg");
	SDL_QueryTexture(background, NULL, NULL, &w, &h);
	SDL_SetRenderTarget(renderer, background);

	// Scaling image
	SDL_Rect texr; 
	texr.x = SCR_WDT/2048;
	texr.y = SCR_HGT/2048;
       	texr.w = w;//*2;
       	texr.h = h;//*2;

	int is_running = 1;
	
	SDL_Event event;
      	while (is_running)
	{
		if ( SDL_PollEvent( &event ))
        	{
           		if ( event.type == SDL_QUIT )
            		{
				is_running = 0;
            		}   
       	 	}	
        	
		// Clears Screen
		SDL_RenderClear ( renderer );
		// Copies Texture to rendering context
		SDL_RenderCopy(renderer, background, NULL, &texr);
		
		// Draws Circle
		DrawCircle( renderer, SCR_CEN_X, SCR_CEN_Y, 200);
		
		SDL_SetRenderDrawColor ( renderer, 0, 0, 0, 255 );
        	SDL_RenderPresent ( renderer );
		
	}

	SDL_DestroyTexture(background);
	SDL_DestroyRenderer(renderer);
    	SDL_DestroyWindow(window);
	
	SDL_Quit ();
	return 0;
}

/*
** DrawCircle : Draws a circle at position x and y
** with a given radius
*/ 


int DrawCircle( SDL_Renderer *r, int x, int y, int radius)
{
    int new_x = 0;
    int new_y = 0;
    int old_x = x + radius;
    int old_y = y;
    float step = (M_PI * 2) / 50; 

    SDL_SetRenderDrawColor ( r, 255, 255, 255, 255 );

    for ( float theta = 0; theta <= (M_PI * 2); theta += step )
    {
        new_x = x + (radius * cos (theta));
	new_y = y - (radius * sin (theta));
        
	SDL_RenderDrawLine ( r, old_x, old_y, new_x, new_y);

        old_x = new_x;
        old_y = new_y;
    }

    new_x = x + (radius * cos( 0 ));
    new_y = y - (radius * sin( 0 ));
    
    SDL_RenderDrawLine( r, old_x, old_y, new_x, new_y );
	
    return old_x;
}

