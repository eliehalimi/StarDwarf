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

int DrawCircle( SDL_Renderer *r, int shiftx, int shifty );
char* getline(void);
int main ( int argc, char *argv[] )
{
    SDL_Init ( SDL_INIT_VIDEO ); 
    SDL_Window *window = SDL_CreateWindow ( "Drawing a Circle", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCR_WDT, SCR_HGT, 0 );
    SDL_Renderer *renderer = SDL_CreateRenderer ( window, -1, SDL_RENDERER_SOFTWARE );
    char * c;
    int is_running = 1;
    int x = 0;
    if (argc > 2)
	    is_running = 0;
    
    int y = 0;
    while ( is_running && x+ SCR_CEN_X < SCR_WDT)
    {
	SDL_Event event;
        if ( SDL_PollEvent( &event ))
        {
            if ( event.type == SDL_QUIT )
            {
                is_running = 0;
            }   
        }	
        SDL_RenderClear ( renderer );
	//TO MOVE CIRCLE FROM LEFT TO RIGHT:
	//x += 1;
        y = DrawCircle( renderer, x, y );
	SDL_SetRenderDrawColor ( renderer, 0, 0, 0, 255 );
        SDL_RenderPresent ( renderer );

    }

    SDL_Quit ();

return 0; 
}

int DrawCircle( SDL_Renderer *r, int shiftx, int shifty)
{
    int radius = 40; 
    int new_x = 0+shiftx;
    int new_y = 0;
    int old_x = shifty;
    int old_y = SCR_CEN_Y;
    float step = (M_PI * 2) / 50; 

    SDL_SetRenderDrawColor ( r, 255, 255, 255, 255 );

    for ( float theta = 0; theta <= (M_PI * 2); theta += step )
    {
        new_x = SCR_CEN_X +shiftx+ (radius * cos ( theta ));
        new_y = SCR_CEN_Y - (radius * sin ( theta ));   

        SDL_RenderDrawLine ( r, old_x, old_y, new_x, new_y);

        old_x = new_x;
        old_y = new_y;
    }

    new_x =  SCR_CEN_X +shiftx+ (radius * cos ( 0 ));
    new_y =  SCR_CEN_Y - (radius * sin ( 0 ));  
    SDL_RenderDrawLine( r, old_x, old_y, new_x, new_y );
	
    return old_x;
}




char * getline(void) {
	    char * line = malloc(100), * linep = line;
	        size_t lenmax = 100, len = lenmax;
		    int c;

		        if(line == NULL)
				        return NULL;

			    for(;;) {
				            c = fgetc(stdin);
					            if(c == EOF)
							                break;

						            if(--len == 0) {
								                len = lenmax;
										            char * linen = realloc(linep, lenmax *= 2);

											                if(linen == NULL) {
														                free(linep);
																                return NULL;
																		            }
													            line = linen + (line - linep);
														                linep = linen;
																        }

							            if((*line++ = c) == '\n')
									                break;
								        }
			        *line = '\0';
				    return linep;
}
