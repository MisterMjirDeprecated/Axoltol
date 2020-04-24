#ifndef AXOLTOL_PY_RENDERER
#define AXOLTOL_PY_RENDERER

#include <Python.h>
#include "sdl.h"

typedef struct
{
  PyObject_HEAD
  Renderer* renderer;
} PyRendererObj;

class PyRenderer
{
public:
  // Standard Functions
  static int __init__(PyRendererObj* self, PyObject* args, PyObject* kwds);
  static void __dealloc__(PyRendererObj* self);

  // Custom Functions
  static PyObject* setDrawColor(PyRendererObj* self, PyObject* args);
  static PyObject* fillRect(PyRendererObj* self, PyObject* args);
  static PyObject* copy(PyRendererObj* self, PyObject* args);
  static PyObject* clear(PyRendererObj* self, PyObject* args);
  static PyObject* present(PyRendererObj* self, PyObject* args);

  // Variables
  static PyMemberDef members[];
  static PyTypeObject type;
  static PyMethodDef methods[];
private:
  PyRenderer();
};

#endif
