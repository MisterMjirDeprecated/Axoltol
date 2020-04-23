#ifndef AXOLTOL_PY_RECT
#define AXOLTOL_PY_RECT

#include <Python.h>
#include <SDL2/SDL.h>
#include "sdl.h"

typedef struct
{
  PyObject_HEAD
  int x;
  int y;
  int w;
  int h;
} PyRectObj;

class PyRect
{
public:
  // Standard Functions
  static PyObject* __new__(PyTypeObject* type, PyObject* args, PyObject* kwds);
  static int __init__(PyRectObj* self, PyObject* args, PyObject* kwds);
  static void __dealloc__(PyRectObj* self);

  // Utility Functions
  static SDL_Rect getSDL(const PyRectObj*);

  // Variables
  static PyMemberDef members[];
  static PyTypeObject type;
  static PyMethodDef methods[];
private:
  PyRect();
};

#endif
