# include "gui.h"                                          

SDL_Window *window;                               
//SDL_Renderer *renderer;

int MakeRect(SDL_Rect *rect, int x, int y, int w, int h)
{
  if (!rect) return -1;
  rect->x = x;  rect->y = y;  rect->w = w;  rect->h = h;
  return 1;
}
int PointInRect(int x, int y, SDL_Rect *rect)
{
  return x >= rect->x && x < (rect->x + rect->w) && y >= rect->y && y < rect->y + rect->h;
}

int PointInRect_Circle(int x, int y, SDL_Rect *rect)
{
  return x >= rect->x-rect->w/2 && x < (rect->x + rect->w/2) && y >= rect->y-rect->h/2 && y < rect->y + rect->h/2;
}
int RenderImage(SDL_Renderer *renderer, struct image *img, int x, int y, SDL_Rect *rect)
{
  SDL_Rect dst;
  if (!renderer || !img->texture) return -1;
  MakeRect(&dst, x, y, img->w, img->h);
  if (rect) dst.w = rect->w;
  if (rect) dst.h = rect->h;
  SDL_RenderCopy(renderer, img->texture, rect, &dst);
  return 0;
}


int image_new(struct image *img, char *fname, SDL_Renderer* renderer)
{
  if (!img || !fname) return -1;
  char path[100] = "img/";
  strcat(path, fname);
  img->texture = IMG_LoadTexture(renderer, path);
  if (!img->texture)
    {
      errx(1,"Could not load image: %s\n", SDL_GetError());
      return -1;
    }
    
  SDL_QueryTexture(img->texture, NULL, NULL, &img->w, &img->h);
  return 0;
}

SDL_Renderer* init (char *title, int w, int h, struct htable *button_list, struct htable *window_list, struct htable *img_list, struct htable *draw_list, struct htable *text_list, struct htable *slider_list, struct music *music)
{
  SDL_Rect srect;
  SDL_Init(SDL_INIT_EVERYTHING);
  SDL_GetDisplayBounds(0, &srect);
  if  (w > srect.w || h > srect.h)
    {
      SDL_Quit();
      return NULL;
    }
  IMG_Init(IMG_INIT_JPG|IMG_INIT_PNG);
  window = SDL_CreateWindow(title, srect.w/2 - w/2, srect.h/2-h/2,w,h,SDL_WINDOW_SHOWN);
  SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

  add_htable(img_list, "startmenu", malloc(sizeof(struct image)));
  add_htable(img_list, "optionmenu", malloc(sizeof(struct image)));
  add_htable(img_list, "creditmenu", malloc(sizeof(struct image)));
  add_htable(img_list, "namemenu", malloc(sizeof(struct image)));  
  add_htable(img_list, "new_selected", malloc(sizeof(struct image)));
  add_htable(img_list, "new_unselected", malloc(sizeof(struct image)));
  add_htable(img_list, "load_selected", malloc(sizeof(struct image)));
  add_htable(img_list, "load_unselected", malloc(sizeof(struct image)));
  add_htable(img_list, "quit_selected", malloc(sizeof(struct image)));
  add_htable(img_list, "quit_unselected", malloc(sizeof(struct image)));
  add_htable(img_list, "options_selected", malloc(sizeof(struct image)));
  add_htable(img_list, "options_unselected", malloc(sizeof(struct image)));
  add_htable(img_list, "credit_selected", malloc(sizeof(struct image)));
  add_htable(img_list, "credit_unselected", malloc(sizeof(struct image)));  
  add_htable(img_list, "back_selected", malloc(sizeof(struct image)));
  add_htable(img_list, "back_unselected", malloc(sizeof(struct image)));
  add_htable(img_list, "volume_selected", malloc(sizeof(struct image)));
  add_htable(img_list, "volume_unselected", malloc(sizeof(struct image)));
  add_htable(img_list, "x_selected", malloc(sizeof(struct image)));
  add_htable(img_list, "x_unselected", malloc(sizeof(struct image)));
  add_htable(img_list, "start_selected", malloc(sizeof(struct image)));
  add_htable(img_list, "start_unselected", malloc(sizeof(struct image)));

  add_htable(img_list, "mainmenu", malloc(sizeof(struct image)));  
  add_htable(img_list, "pause_selected", malloc(sizeof(struct image)));
  add_htable(img_list, "pause_unselected", malloc(sizeof(struct image)));  
  add_htable(img_list, "pausemenu", malloc(sizeof(struct image)));  
  add_htable(img_list, "quit_mainmenu_selected", malloc(sizeof(struct image)));
  add_htable(img_list, "quit_mainmenu_unselected", malloc(sizeof(struct image)));
  add_htable(img_list, "resume_selected", malloc(sizeof(struct image)));
  add_htable(img_list, "resume_unselected", malloc(sizeof(struct image)));
  add_htable(img_list, "saveandquit_selected", malloc(sizeof(struct image)));
  add_htable(img_list, "saveandquit_unselected", malloc(sizeof(struct image)));
  add_htable(img_list, "reset_selected", malloc(sizeof(struct image)));
  add_htable(img_list, "reset_unselected", malloc(sizeof(struct image)));
  
  
  add_htable(img_list, "itemsmenu", malloc(sizeof(struct image)));
  add_htable(img_list, "item_namebox_selected", malloc(sizeof(struct image)));
  add_htable(img_list, "item_namebox_unselected", malloc(sizeof(struct image)));
  add_htable(img_list, "item_posbox_selected", malloc(sizeof(struct image)));
  add_htable(img_list, "item_posbox_unselected", malloc(sizeof(struct image)));
  add_htable(img_list, "add_selected", malloc(sizeof(struct image)));
  add_htable(img_list, "add_unselected", malloc(sizeof(struct image)));
  add_htable(img_list, "delete_selected", malloc(sizeof(struct image)));
  add_htable(img_list, "delete_unselected", malloc(sizeof(struct image)));

  add_htable(img_list, "start_mainmenu_selected", malloc(sizeof(struct image)));
  add_htable(img_list, "start_mainmenu_unselected", malloc(sizeof(struct image)));

  add_htable(img_list, "timelapse", malloc(sizeof(struct image)));
  add_htable(img_list, "token_slider_selected", malloc(sizeof(struct image)));
  add_htable(img_list, "token_slider_unselected", malloc(sizeof(struct image)));

  add_htable(img_list, "loadmenu", malloc(sizeof(struct image)));
  add_htable(img_list, "scrollbar", malloc(sizeof(struct image)));
  add_htable(img_list, "token_scrollbar_selected", malloc(sizeof(struct image)));
  add_htable(img_list, "token_scrollbar_unselected", malloc(sizeof(struct image)));


  
  
  int r = 0;
  r += image_new(access_htable(img_list, "startmenu")->value, "startmenu.png", renderer);
  r += image_new(access_htable(img_list, "new_selected")->value, "new_selected.png", renderer);
  r += image_new(access_htable(img_list, "new_unselected")->value, "new_unselected.png", renderer);
  r += image_new(access_htable(img_list, "load_selected")->value, "load_selected.png", renderer);
  r += image_new(access_htable(img_list, "load_unselected")->value , "load_unselected.png", renderer);
  r += image_new(access_htable(img_list, "quit_selected")->value, "quit_selected.png", renderer);
  r += image_new(access_htable(img_list, "quit_unselected")->value, "quit_unselected.png", renderer);
  r += image_new(access_htable(img_list, "options_selected")->value, "options_selected.png", renderer);
  r += image_new(access_htable(img_list, "options_unselected")->value, "options_unselected.png", renderer);
  
  r += image_new(access_htable(img_list, "optionmenu")->value, "optionmenu.png", renderer);
  r += image_new(access_htable(img_list, "credit_selected")->value, "credit_selected.png", renderer);
  r += image_new(access_htable(img_list, "credit_unselected")->value, "credit_unselected.png", renderer);
  r += image_new(access_htable(img_list, "back_selected")->value, "back_selected.png", renderer);
  r += image_new(access_htable(img_list, "back_unselected")->value, "back_unselected.png", renderer);
  r += image_new(access_htable(img_list, "volume_selected")->value, "volume_selected.png", renderer);
  r += image_new(access_htable(img_list, "volume_unselected")->value, "volume_unselected.png", renderer);

  r += image_new(access_htable(img_list, "creditmenu")->value, "creditmenu.png", renderer);

  r += image_new(access_htable(img_list, "namemenu")->value, "namemenu.png", renderer);
  r += image_new(access_htable(img_list, "x_selected")->value, "x_selected.png", renderer);
  r += image_new(access_htable(img_list, "x_unselected")->value, "x_unselected.png", renderer);
  r += image_new(access_htable(img_list, "start_selected")->value, "start_selected.png", renderer);
  r += image_new(access_htable(img_list, "start_unselected")->value, "start_unselected.png", renderer);

  r += image_new(access_htable(img_list, "mainmenu")->value, "mainmenu.png", renderer);
  r += image_new(access_htable(img_list, "pause_selected")->value, "pause_selected.png", renderer);
  r += image_new(access_htable(img_list, "pause_unselected")->value, "pause_unselected.png", renderer);

  r += image_new(access_htable(img_list, "pausemenu")->value, "pausemenu.png", renderer);
  r += image_new(access_htable(img_list, "resume_selected")->value, "resume_selected.png", renderer);
  r += image_new(access_htable(img_list, "resume_unselected")->value, "resume_unselected.png", renderer);
  r += image_new(access_htable(img_list, "quit_mainmenu_selected")->value, "quit_main_selected.png", renderer);
  r += image_new(access_htable(img_list, "quit_mainmenu_unselected")->value, "quit_main_unselected.png", renderer);
   r += image_new(access_htable(img_list, "reset_selected")->value, "reset_selected.png", renderer);
  r += image_new(access_htable(img_list, "reset_unselected")->value, "reset_unselected.png", renderer);
  r += image_new(access_htable(img_list, "saveandquit_selected")->value, "saveandquit_selected.png", renderer);
  r += image_new(access_htable(img_list, "saveandquit_unselected")->value, "saveandquit_unselected.png", renderer);
 

  r += image_new(access_htable(img_list, "itemsmenu")->value, "itemsmenu.png", renderer);
  r += image_new(access_htable(img_list, "item_namebox_selected")->value, "item_namebox_selected.png", renderer);
  r += image_new(access_htable(img_list, "item_namebox_unselected")->value, "item_namebox_unselected.png", renderer);
  r += image_new(access_htable(img_list, "item_posbox_selected")->value, "item_posbox_selected.png", renderer);
  r += image_new(access_htable(img_list, "item_posbox_unselected")->value, "item_posbox_unselected.png", renderer);
  r += image_new(access_htable(img_list, "add_selected")->value, "add_selected.png", renderer);
  r += image_new(access_htable(img_list, "add_unselected")->value, "add_unselected.png", renderer);
  r += image_new(access_htable(img_list, "delete_selected")->value, "delete_selected.png", renderer);
  r += image_new(access_htable(img_list, "delete_unselected")->value, "delete_unselected.png", renderer);
  r += image_new(access_htable(img_list, "start_mainmenu_selected")->value, "start_mainmenu_selected.png", renderer);
  r += image_new(access_htable(img_list, "start_mainmenu_unselected")->value, "start_mainmenu_unselected.png", renderer);
  r += image_new(access_htable(img_list, "timelapse")->value, "timelapse.png", renderer);
  r += image_new(access_htable(img_list, "token_slider_unselected")->value, "token_slider_unselected.png", renderer);
  r += image_new(access_htable(img_list, "token_slider_selected")->value, "token_slider_selected.png", renderer);

  r += image_new(access_htable(img_list, "loadmenu")->value, "loadmenu.png", renderer);
  r += image_new(access_htable(img_list, "scrollbar")->value, "scrollbar.png", renderer);
  r += image_new(access_htable(img_list, "token_scrollbar_unselected")->value, "token_scrollbar_unselected.png", renderer);
  r += image_new(access_htable(img_list, "token_scrollbar_selected")->value, "token_scrollbar_selected.png", renderer);
  
  if (r)
    {
      clean(renderer, button_list, window_list, img_list, draw_list, text_list, slider_list, music);
      return NULL;
    }
  return renderer;
}

void clean(SDL_Renderer *renderer, struct htable *button_list, struct htable *window_list, struct htable *img_list, struct htable *draw_list, struct htable *text_list, struct htable *slider_list, struct music *music)
{ 
  SDL_DestroyTexture(((struct image *)access_htable(img_list, "startmenu")->value)->texture);
  SDL_DestroyTexture(((struct image *)access_htable(img_list, "new_selected")->value)->texture);
  SDL_DestroyTexture(((struct image *)access_htable(img_list, "new_unselected")->value)->texture);
  SDL_DestroyTexture(((struct image *)access_htable(img_list, "load_selected")->value)->texture);
  SDL_DestroyTexture(((struct image *)access_htable(img_list, "load_unselected")->value)->texture);
  SDL_DestroyTexture(((struct image *)access_htable(img_list, "quit_selected")->value)->texture);
  SDL_DestroyTexture(((struct image *)access_htable(img_list, "quit_unselected")->value)->texture);
  SDL_DestroyTexture(((struct image *)access_htable(img_list, "options_selected")->value)->texture);
  SDL_DestroyTexture(((struct image *)access_htable(img_list, "options_unselected")->value)->texture);
  
  SDL_DestroyTexture(((struct image *)access_htable(img_list, "optionmenu")->value)->texture);
  SDL_DestroyTexture(((struct image *)access_htable(img_list, "credit_selected")->value)->texture);
  SDL_DestroyTexture(((struct image *)access_htable(img_list, "credit_unselected")->value)->texture);
  SDL_DestroyTexture(((struct image *)access_htable(img_list, "back_selected")->value)->texture);
  SDL_DestroyTexture(((struct image *)access_htable(img_list, "back_unselected")->value)->texture);
  SDL_DestroyTexture(((struct image *)access_htable(img_list, "volume_selected")->value)->texture);
  SDL_DestroyTexture(((struct image *)access_htable(img_list, "volume_unselected")->value)->texture);

  SDL_DestroyTexture(((struct image *)access_htable(img_list, "creditmenu")->value)->texture);

  SDL_DestroyTexture(((struct image *)access_htable(img_list, "namemenu")->value)->texture);
  SDL_DestroyTexture(((struct image *)access_htable(img_list, "x_selected")->value)->texture);
  SDL_DestroyTexture(((struct image *)access_htable(img_list, "x_unselected")->value)->texture);
  SDL_DestroyTexture(((struct image *)access_htable(img_list, "start_selected")->value)->texture);
  SDL_DestroyTexture(((struct image *)access_htable(img_list, "start_unselected")->value)->texture);

  SDL_DestroyTexture(((struct image *)access_htable(img_list, "mainmenu")->value)->texture);
  SDL_DestroyTexture(((struct image *)access_htable(img_list, "pause_selected")->value)->texture);
  SDL_DestroyTexture(((struct image *)access_htable(img_list, "pause_unselected")->value)->texture);
  SDL_DestroyTexture(((struct image *)access_htable(img_list, "pausemenu")->value)->texture);
  SDL_DestroyTexture(((struct image *)access_htable(img_list, "resume_selected")->value)->texture);
  SDL_DestroyTexture(((struct image *)access_htable(img_list, "resume_unselected")->value)->texture);
  SDL_DestroyTexture(((struct image *)access_htable(img_list, "saveandquit_selected")->value)->texture);
  SDL_DestroyTexture(((struct image *)access_htable(img_list, "saveandquit_unselected")->value)->texture);

  SDL_DestroyTexture(((struct image *)access_htable(img_list, "quit_mainmenu_selected")->value)->texture);
  SDL_DestroyTexture(((struct image *)access_htable(img_list, "quit_mainmenu_unselected")->value)->texture);
  SDL_DestroyTexture(((struct image *)access_htable(img_list, "itemsmenu")->value)->texture);
  SDL_DestroyTexture(((struct image *)access_htable(img_list, "item_namebox_selected")->value)->texture);
  SDL_DestroyTexture(((struct image *)access_htable(img_list, "item_namebox_selected")->value)->texture);
  SDL_DestroyTexture(((struct image *)access_htable(img_list, "item_namebox_unselected")->value)->texture);
  SDL_DestroyTexture(((struct image *)access_htable(img_list, "item_posbox_selected")->value)->texture);
  SDL_DestroyTexture(((struct image *)access_htable(img_list, "item_posbox_unselected")->value)->texture);
  
  SDL_DestroyTexture(((struct image *)access_htable(img_list, "add_selected")->value)->texture);
  SDL_DestroyTexture(((struct image *)access_htable(img_list, "add_unselected")->value)->texture);
  SDL_DestroyTexture(((struct image *)access_htable(img_list, "delete_selected")->value)->texture);
  SDL_DestroyTexture(((struct image *)access_htable(img_list, "delete_unselected")->value)->texture);
  SDL_DestroyTexture(((struct image *)access_htable(img_list, "start_mainmenu_selected")->value)->texture);
  SDL_DestroyTexture(((struct image *)access_htable(img_list, "start_mainmenu_unselected")->value)->texture);
  SDL_DestroyTexture(((struct image *)access_htable(img_list, "reset_selected")->value)->texture);
  SDL_DestroyTexture(((struct image *)access_htable(img_list, "reset_unselected")->value)->texture);  
  SDL_DestroyTexture(((struct image *)access_htable(img_list, "token_slider_selected")->value)->texture);
  SDL_DestroyTexture(((struct image *)access_htable(img_list, "token_slider_unselected")->value)->texture);
  SDL_DestroyTexture(((struct image *)access_htable(img_list, "timelapse")->value)->texture);
  
  SDL_DestroyTexture(((struct image *)access_htable(img_list, "loadmenu")->value)->texture);
    SDL_DestroyTexture(((struct image *)access_htable(img_list, "token_scrollbar_selected")->value)->texture);
  SDL_DestroyTexture(((struct image *)access_htable(img_list, "token_scrollbar_unselected")->value)->texture);
  SDL_DestroyTexture(((struct image *)access_htable(img_list, "scrollbar")->value)->texture);
  
  
  free(((struct text *)(access_htable(text_list, "name")->value))->text);
  free(((struct text *)(access_htable(text_list, "intro")->value))->text);
  free(((struct text *)(access_htable(text_list, "item_name")->value))->text);
  free(((struct text *)(access_htable(text_list, "item_x")->value))->text);
  free(((struct text *)(access_htable(text_list, "item_y")->value))->text);
  free(((struct text *)(access_htable(text_list, "item_z")->value))->text);
  free(((struct text *)(access_htable(text_list, "item_radius")->value))->text);
  free(((struct text *)(access_htable(text_list, "item_mass")->value))->text);
  free(((struct text *)(access_htable(text_list, "item_vx")->value))->text);
  free(((struct text *)(access_htable(text_list, "item_vy")->value))->text);
  free(((struct text *)(access_htable(text_list, "item_vz")->value))->text);  
  free(((struct text *)(access_htable(text_list, "name_loadmenu")->value))->text);
  free(((struct text *)(access_htable(text_list, "warning_loadmenu")->value))->text);
  free(((struct slider *)(access_htable(slider_list, "timelapse")->value))->maxvalue);
  free(((struct slider *)(access_htable(slider_list, "timelapse")->value))->minvalue);      
  free(((struct slider *)(access_htable(slider_list, "scrollbar")->value))->maxvalue);
  free(((struct slider *)(access_htable(slider_list, "scrollbar")->value))->minvalue);

  SDL_StopTextInput();

  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);  

  free_htable(img_list);
  free_htable(button_list);
  free_htable(window_list);

  free_htable(draw_list);
  free_htable(slider_list);
  free_htable(text_list);
  
  TTF_Quit();
  IMG_Quit();
  SDL_Quit();

  SDL_RenderClear(renderer);
  free(music);
}
