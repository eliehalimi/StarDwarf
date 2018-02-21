# ifndef GUI_H
# define GUI_H
# include <SDL2/SDL.h>
# include <SDL2/SDL_image.h>

extern struct image *quit_selected, *quit_unselected, *new_selected, *new_unselected, *load_selected, *load_unselected, *startmenu;
//extern int quit;

struct image{
  SDL_Texture *texture;
  int w;
  int h;
};

struct window {
  int visible;
  SDL_Rect rect;
  struct image *bg;
};
struct button {
  int visible;
  int active;
  int prelight;
  SDL_Rect rect;
  struct image *unselected;
  struct image *selected;
};


int MakeRect(SDL_Rect *rect, int x, int y, int w, int h);
int PointInRect(int x, int y, SDL_Rect *rect);



int RenderImage(SDL_Renderer *renderer, struct image *img, int x, int y, SDL_Rect *rect);

int image_new(struct image *img, char *fname, SDL_Renderer* renderer);


SDL_Renderer* init (char *title, int w, int h);

int window_new(struct window *window, struct image *bg, int x, int y, int w, int h);

int window_event(struct window *window, SDL_Event *event, int *draw);

int window_draw(struct window *window, SDL_Renderer *renderer);

int button_new(struct button *button, struct image *selected, struct image *unselected, int x, int y);

int button_event(struct button *button, SDL_Event *event, int *draw);

int button_draw(struct button *button, SDL_Renderer *renderer);
  
void clean();


# endif
