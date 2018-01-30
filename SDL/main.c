# include <SDL.h>
# include <SDL/SDL.h>
# include <stdio.h>

int main()
{
	// I am creating images here (pointers to SDL_Surface)
	SDL_Surface *Hello = NULL;
	SDL_Surface *Screen = NULL;

	//Starts SDL library I guess
	SDL_Init(SDL_INIT_EVERYTHING);

	// sets up screen config
	/* Here 640 and 480 are the sizes for our window
	 * e.g: 640 wide and 480 high
	 * 32 is the number of bits per pixel. I'll change that to 64 someday.
	 * SDL_SWSURFACE sets surface in sofware memory
	 */
	Screen = SDL_SetVideoMode(640, 480, 32, SDL_SWSURFACE);

	//Loads Image apparently
	// IF I had a bmp image it would be like that:
	Hello = SDL_LoadBMP("../resources/circle.bmp");

	//To apply the image I would do
	SDL_BlitSurface(Hello, NULL, Screen, NULL);

	//UPDATE SCREEN
	SDL_Flip(Screen);

	// To free loaded image
	SDL_FreeSurface( Hello);

	//Creates a delay to make the windows visible for n milliseconds
	//till I learn a better way to make the windows stay in place 
	SDL_Delay(20000);

	//QUITS SDL 
	SDL_Quit();

	return 0;
}
