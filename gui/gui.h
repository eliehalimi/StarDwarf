# ifndef GUI_H
# define GUI_H
# include <SDL2/SDL.h>
# include <SDL2/SDL_image.h>
# include "../Physic/libvector.h"
# include "../Camera/camera.h"
# include "hash_table.h"

//extern struct system *sys;
struct image{
  SDL_Texture *texture;
  int w;
  int h;
};
struct text{
  char *text;
  int nbchar;
  int active;
  int item;
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
  int textbox;
  int input;
  SDL_Rect rect;
  struct window *window;
  struct image *unselected;
  struct image *selected;
};


int MakeRect(SDL_Rect *rect, int x, int y, int w, int h);
int PointInRect(int x, int y, SDL_Rect *rect);



int RenderImage(SDL_Renderer *renderer, struct image *img, int x, int y, SDL_Rect *rect);

int image_new(struct image *img, char *fname, SDL_Renderer* renderer);


SDL_Renderer* init (char *title, int w, int h, struct htable *button_list, struct htable *window_list, struct htable *img_list, struct htable *draw_list, struct htable *text_list);

int window_new(struct window *window, struct image *bg, int x, int y, int w, int h);

int window_event(struct window *window, SDL_Event *event, int *draw);

int window_draw(struct window *window, SDL_Renderer *renderer);

int button_new(struct button *button, struct image *selected, struct image *unselected, int x, int y, struct window *window);

int button_event(struct button *button, SDL_Event *event, int *draw);

int button_draw(struct button *button, SDL_Renderer *renderer);

void clean(struct htable *button_list, struct htable *window_list, struct htable  *img_list, struct htable *draw_list, struct htable *text_list);



//text input
void item_to_input(struct htable *text_list, struct item *item);

struct text *get_text(struct htable *text_list, char *name);

void input_to_item(struct htable *text_list, struct item *item);

void display_text(SDL_Renderer *renderer, struct htable *text_list, char *name, int x, int h, int rgb, int size);

void textinput(SDL_Event e, struct text *text, int maxchr, struct button *button);

void init_textinput(struct htable *text_list, char *name, int size);



//supporting main
void init_lists(int w, int h, struct htable *button_list, struct htable *window_list, struct htable *img_list,  struct htable *draw_list, struct htable *text_list);

void button_active(int w, int h, int *quit, struct system **sys, struct htable *button_list, struct htable *window_list, struct htable *draw_list, struct htable *text_list);

struct system *init_system(int w, int h, struct htable *text_list) ;

//draw.c
void draw(SDL_Renderer *renderer, struct htable *button_list, struct htable *window_list,  struct htable *draw_list, struct htable *text_list);

//camera
int camera_event(struct camera *camera, SDL_Event *event, struct item **selected);

# endif
