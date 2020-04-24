#ifndef AXOLTOL_RENDERER
#define AXOLTOL_RENDERER

#include <SDL2/SDL.h>
#include "window.h"

class Texture;

class Renderer
{
public:
  Renderer(Window*);
  ~Renderer();
  int setDrawColor(Uint8 r, Uint8 g, Uint8 b);
  int setDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
  int fillRect(const SDL_Rect*);
  int fillRect(int x, int y, int w, int h);
  // Copy
  int copy(Texture*, SDL_Rect* srcRect, SDL_Rect* destRect);
  int copy(Texture*, int sX, int sY, int sW, int sH, SDL_Rect* destRect);
  int copy(Texture*, SDL_Rect* srcRect, int dX, int dY, int dW, int dH);
  int copy(Texture*, int sX, int sY, int sW, int sH, int dX, int dY, int dW, int dH);
  /* CopyEx
  int copy(Texture*, SDL_Rect* srcRect, SDL_Rect* destRect, double angle); */
  int clear();
  void present();
  SDL_Renderer* getSDL();
private:
  SDL_Renderer* renderer;
};

#endif
