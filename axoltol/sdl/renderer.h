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
  int clear();
  void present();
  SDL_Renderer* getSDL();
private:
  SDL_Renderer* renderer;
};

#endif
