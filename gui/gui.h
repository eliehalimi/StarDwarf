# ifndef GUI_H
# define GUI_H
# include <SDL2/SDL.h>
# include <SDL2/SDL_image.h>
# include "../Physic/libvector.h"
# include "../Camera/camera.h"
# include "hash_table.h"
# include "list.h"
# define SIMULATION_EDIT 0
# define SIMULATION_PROGRESS 1
# define SIMULATION_PAUSE 2

//extern struct system *sys;
struct image{
  SDL_Texture *texture;
  int w;
  int h;
};
struct slider{

  int visible;
  int event;
  int active;
  int prelight;
  
  SDL_Rect rect_bar;
  SDL_Rect rect_token;

  int mousepos;
  int mousedown;
  int horizontal;
  int maxlength;
  int curlength;
  void *maxvalue;
  void *minvalue;
  
  struct window *window;
  struct image *bar;
  struct image *unselected;
  struct image *selected;
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


SDL_Renderer* init (char *title, int w, int h, struct htable *button_list, struct htable *window_list, struct htable *img_list, struct htable *draw_list, struct htable *text_list, struct htable *slider_list);

int slider_new(struct slider *slider, struct image *bar, struct image *selected, struct image *unselected, int horizontal, int x, int y, int token_pos, struct window *window, void *maxvalue, void *minvalue);

int slider_event(struct slider *slider, SDL_Event *event, int *draw);

int slider_draw(struct slider *slider, SDL_Renderer *renderer);

int window_new(struct window *window, struct image *bg, int x, int y, int w, int h, struct window *parent);

int window_event(struct window *window, SDL_Event *event, int *draw);

int window_draw(struct window *window, SDL_Renderer *renderer);

int button_new(struct button *button, struct image *selected, struct image *unselected, int x, int y, struct window *window);

int button_event(struct button *button, SDL_Event *event, int *draw);

int button_draw(struct button *button, SDL_Renderer *renderer);

void clean(struct htable *button_list, struct htable *window_list, struct htable  *img_list, struct htable *draw_list, struct htable *text_list, struct htable *slider_list);



//text input
void item_to_input(struct htable *text_list, struct item *item);

struct text *get_text(struct htable *text_list, char *name);

void input_to_item(struct htable *text_list, struct item *item);

void display_text(SDL_Renderer *renderer, struct htable *text_list, char *name, int x, int h, int rgb, int size);

void textinput(SDL_Event e, struct text *text, int maxchr, struct button *button);

void init_textinput(struct htable *text_list, char *name, int size);

void get_files(struct list_char *files);

void display_files(SDL_Renderer *renderer, struct list_char *files, struct slider *scrollbar);

//supporting main
void init_lists(int w, int h, struct htable *button_list, struct htable *window_list, struct htable *img_list,  struct htable *draw_list, struct htable *text_list, struct htable *slider_list);

struct system *init_system(int w, int h, struct htable *text_list) ;

//draw.c

void button_active(int w, int h, int *quit, struct system **sys, struct system **reset_sys, struct htable *button_list, struct htable *window_list, struct htable *draw_list, struct htable *text_list, struct list_char *files, int *state);
void draw(SDL_Renderer *renderer, struct htable *button_list, struct htable *window_list,  struct htable *draw_list, struct htable *text_list, struct htable *slider_list, struct system *sys, struct list_char *files);

//camera
int camera_event(struct camera *camera, SDL_Event *event, struct item **selected);

# endif
