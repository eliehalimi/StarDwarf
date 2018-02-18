#include "SDL.h"
#include <SDL2/SDL.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define SCR_WDT 1280
#define SCR_HGT 960
#define M_PI	3.14159265358979323846264338327950288

const int SCR_CEN_X = SCR_WDT / 2;
const int SCR_CEN_Y = SCR_HGT / 2;


int DrawCircle( SDL_Renderer *r, int x, int y, int radius);


int main ( int argc, char *argv[] )
{
       	SDL_Init ( SDL_INIT_VIDEO ); 
    	SDL_Window *window = SDL_CreateWindow ( "Drawing a Circle", SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, SCR_WDT, SCR_HGT, 0 );
    	SDL_Renderer *renderer = SDL_CreateRenderer ( window, -1, SDL_RENDERER_SOFTWARE );
   	
       	char * c;
   	int is_running = 1;
    	int x = 0;
	
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
        
		SDL_RenderClear ( renderer );
		DrawCircle( renderer, 280, 500, 50);
		SDL_SetRenderDrawColor ( renderer, 0, 0, 0, 255 );
        	SDL_RenderPresent ( renderer );
	}
    	SDL_Quit ();
	return 0;
}

int DrawCircle( SDL_Renderer *r, int x, int y, int radius)
{
    //int radius = 200;
    int new_x = 0;
    int new_y = 0;
    int old_x = x + radius;// SCR_CEN_X + radius;
    int old_y = y;//SCR_CEN_Y;
    float step = (M_PI * 2) / 50; 

    SDL_SetRenderDrawColor ( r, 255, 255, 255, 255 );

    for ( float theta = 0; theta <= (M_PI * 2); theta += step )
    {
        //new_x = SCR_CEN_X + (radius * cos ( theta ));
        //new_y = SCR_CEN_Y - (radius * sin ( theta ));   
	new_x = x + (radius * cos (theta));
	new_y = y - (radius * sin (theta));
        
	SDL_RenderDrawLine ( r, old_x, old_y, new_x, new_y);

        old_x = new_x;
        old_y = new_y;
    }

    //new_x =  SCR_CEN_X + (radius * cos ( 0 ));
    //new_y =  SCR_CEN_Y - (radius * sin ( 0 ));  
    new_x = x + (radius * cos( 0 ));
    new_y = y - (radius * sin( 0 ));
    
    SDL_RenderDrawLine( r, old_x, old_y, new_x, new_y );
	
    return old_x;
}

