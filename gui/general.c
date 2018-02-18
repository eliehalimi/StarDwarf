# include <SDL2/SDL.h>
# include "gui.h"

int MakeRect(SDL_Rect *rect, int x, int y, int w, int h)
{
  if (!rect) return -1;
  rect->x = x;
  rect->y = y;
  rect->w = w;
  rect->h = h;
  return 1;
}

//check as if the point belonging to particular region 
int PointInRect(int x, int y, SDL_Rect *rect)
{
  return x >= rect->x && x < (rect->x + rect->w) && y >= rect->y && y < rect->y + rect->h;
}

