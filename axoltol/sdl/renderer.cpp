#include "renderer.h"

#include <iostream>

Renderer::Renderer(Window* window)
{
  renderer = SDL_CreateRenderer(window->getSDL(), -1, 0);
  SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
}

Renderer::~Renderer()
{
  SDL_DestroyRenderer(renderer);
}

int Renderer::setDrawColor(Uint8 r, Uint8 g, Uint8 b)
{
  return SDL_SetRenderDrawColor(renderer, r, g, b, 255);
}

int Renderer::setDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
  return SDL_SetRenderDrawColor(renderer, r, g, b, a);
}

int Renderer::fillRect(const SDL_Rect* rect)
{
  return SDL_RenderFillRect(renderer, rect);
}

int Renderer::fillRect(int x, int y, int w, int h)
{
  SDL_Rect rect = {x, y, w, h};
  return SDL_RenderFillRect(renderer, &rect);
}

int Renderer::clear()
{
  return SDL_RenderClear(renderer);
}

void Renderer::present()
{
  SDL_RenderPresent(renderer);
}

SDL_Renderer* Renderer::getSDL()
{
  return renderer;
}
