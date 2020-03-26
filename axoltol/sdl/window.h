#ifndef AXOLTOL_WINDOW
#define AXOLTOL_WINDOW

#include <SDL2/SDL.h>

class Window
{
public:
  Window(const char* title, int x, int y, int w, int h, Uint32 flags);
  ~Window();
  SDL_Window* getSDL();
private:
  SDL_Window* window;
};

#endif
