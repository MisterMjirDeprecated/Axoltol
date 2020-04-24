#ifndef AXOLTOL_PY_EVENT
#define AXOLTOL_PY_EVENT

#include <Python.h>
#include <SDL2/SDL.h>

typedef struct
{
  PyObject_HEAD
  PyObject* data;
  SDL_Event event;
} PyEventObj;

class PyEvent
{
public:
  // Standard Functions
  static PyObject* __new__(PyTypeObject* type, PyObject* args, PyObject* kwds);
  static int __init__(PyEventObj* self, PyObject* args, PyObject* kwds);
  static void __dealloc__(PyEventObj* self);
  static PyObject* compare(PyEventObj* self, PyObject* other, int op);

  // Utility Functions
  static void addEvents(PyObject* module);

  // Variables
  static PyMemberDef members[];
  static PyTypeObject type;
  static PyMethodDef methods[];
private:
  PyEvent();
};

#endif
