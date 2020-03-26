#ifndef AXOLTOL_PY_WINDOW
#define AXOLTOL_PY_WINDOW

#include <Python.h>
#include "sdl.h"

typedef struct
{
  PyObject_HEAD
  Window* window;
} PyWindowObj;

class PyWindow
{
public:
  // Standard Functions
  static int __init__(PyWindowObj* self, PyObject* args, PyObject* kwds);
  static void __dealloc__(PyWindowObj* self);

  // Variables
  static PyMemberDef members[];
  static PyTypeObject type;
  static PyMethodDef methods[];
private:
  PyWindow();
};

#endif
