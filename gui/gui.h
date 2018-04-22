# ifndef GUI_H
# define GUI_H
# include <SDL2/SDL.h>
# include <SDL2/SDL_image.h>
# include "../Physic/libvector.h"
# include "../Camera/camera.h"
# include "hash_table.h"
extern struct htable *img_list;

extern struct button *new_button, *load_button, *options_button, *quit_button, *credit_button, *volume_button, *back_optionmenu_button, *back_creditmenu_button, *x_button, *start_button, *pause_button, *resume_button, *quit_mainmenu_button;                                                                                  
extern struct window *startmenu_w, *optionmenu_w, *creditmenu_w, *namemenu_w, *mainmenu_w, *pausemenu_w;                  
extern int draw_startmenu, draw_optionmenu, draw_creditmenu, draw_namemenu, draw_mainmenu, draw_pausemenu, input;   
extern char *text;
extern SDL_Renderer *renderer;
struct image{
  SDL_Texture *texture;
  int w;
  int h;
};

struct window {
  int event; 
  int visible;
  SDL_Rect rect;
  struct window *parent;
  struct image *bg;
};
struct button {
  int visible;
  int event;
  int active;
  int prelight;
  SDL_Rect rect;
  struct window *window;
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

int button_new(struct button *button, struct image *selected, struct image *unselected, int x, int y, struct window *window);

int button_event(struct button *button, SDL_Event *event, int *draw);

int button_draw(struct button *button, SDL_Renderer *renderer);
  
void clean();

//text input
void drawtextinput();
void textinput();

int camera_event(struct camera *camera, SDL_Event *event);

# endif
