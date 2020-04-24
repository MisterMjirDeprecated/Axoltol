#include "py_rect.h"
#include <structmember.h>

PyMemberDef PyRect::members[] = {
  {(char*) "x", T_INT, offsetof(PyRectObj, x), 0, (char*) "X position"},
  {(char*) "y", T_INT, offsetof(PyRectObj, y), 0, (char*) "X position"},
  {(char*) "w", T_INT, offsetof(PyRectObj, w), 0, (char*) "Width"},
  {(char*) "h", T_INT, offsetof(PyRectObj, h), 0, (char*) "Height"},
  {NULL}
};

PyTypeObject PyRect::type = {
  PyVarObject_HEAD_INIT(NULL, 0)
  .tp_name = "axoltol.Rect",
  .tp_doc = "Rectangle object",
  .tp_basicsize = sizeof(PyRectObj),
  .tp_itemsize = 0,
  .tp_flags = Py_TPFLAGS_DEFAULT,
  .tp_new = PyRect::__new__,
  .tp_init = (initproc) PyRect::__init__,
  .tp_dealloc = (destructor) PyRect::__dealloc__,
  .tp_members = PyRect::members,
  .tp_methods = PyRect::methods
};


PyMethodDef PyRect::methods[] = {
  {NULL}
};

void PyRect::__dealloc__(PyRectObj* self)
{
  Py_TYPE(self)->tp_free((PyObject*) self);
}

PyObject* PyRect::__new__(PyTypeObject* type, PyObject* args, PyObject* kwds)
{
  PyRectObj* self;
  self = (PyRectObj*) type->tp_alloc(type, 0);
  if (self)
  {
    self->x = 0;
    self->y = 0;
    self->w = 0;
    self->h = 0;
  }
  return (PyObject*) self;
}

int PyRect::__init__(PyRectObj* self, PyObject* args, PyObject* kwds)
{
  static const char* kwlist[] = {"x", "y", "w", "h", NULL};
  if (!PyArg_ParseTupleAndKeywords(args, kwds, "iiii", const_cast<char**>(kwlist), &self->x, &self->y, &self->w, &self->h))
    return -1;

  return 0;
}

SDL_Rect PyRect::getSDL(const PyRectObj* pyRect)
{
  return {pyRect->x, pyRect->y, pyRect->w, pyRect->h};
}
