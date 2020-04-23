#ifndef AXOLTOL_RENDERER
#define AXOLTOL_RENDERER

#include <SDL2/SDL.h>
#include "window.h"

class Renderer
{
public:
  Renderer(Window*);
  ~Renderer();
  int setDrawColor(Uint8 r, Uint8 g, Uint8 b);
  int setDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
  int fillRect(const SDL_Rect*);
  int fillRect(int x, int y, int w, int h);
  int clear();
  void present();
  SDL_Renderer* getSDL();
private:
  SDL_Renderer* renderer;
};

#endif
