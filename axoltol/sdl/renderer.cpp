#include "renderer.h"
#include "texture.h"

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

int Renderer::copy(Texture* texture, SDL_Rect* srcRect, SDL_Rect* destRect)
{
  return SDL_RenderCopy(renderer, texture->getSDL(), srcRect, destRect);
}

int Renderer::copy(Texture* texture, int sX, int sY, int sW, int sH, SDL_Rect* destRect)
{
  SDL_Rect srcRect = {sX, sY, sW, sH};
  return SDL_RenderCopy(renderer, texture->getSDL(), &srcRect, destRect);
}

int Renderer::copy(Texture* texture, SDL_Rect* srcRect, int dX, int dY, int dW, int dH)
{
  SDL_Rect destRect = {dX, dY, dW, dH};
  return SDL_RenderCopy(renderer, texture->getSDL(), srcRect, &destRect);
}

int Renderer::copy(Texture* texture, int sX, int sY, int sW, int sH, int dX, int dY, int dW, int dH)
{
  SDL_Rect srcRect = {sX, sY, sW, sH};
  SDL_Rect destRect = {dX, dY, dW, dH};
  return SDL_RenderCopy(renderer, texture->getSDL(), &srcRect, &destRect);
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
