#include "py_window.h"
#include <structmember.h>

PyMemberDef PyWindow::members[] = {
  {NULL}
};

PyTypeObject PyWindow::type = {
  PyVarObject_HEAD_INIT(NULL, 0)
  .tp_name = "axoltol.Window",
  .tp_doc = "Window object",
  .tp_basicsize = sizeof(PyWindowObj),
  .tp_itemsize = 0,
  .tp_flags = Py_TPFLAGS_DEFAULT,
  .tp_new = PyType_GenericNew,
  .tp_init = (initproc) PyWindow::__init__,
  .tp_dealloc = (destructor) PyWindow::__dealloc__,
  .tp_members = PyWindow::members,
  .tp_methods = PyWindow::methods
};

PyMethodDef PyWindow::methods[] = {
  {NULL}
};

int PyWindow::__init__(PyWindowObj* self, PyObject* args, PyObject* kwds)
{
  static const char* kwlist[] = {"title", "x", "y", "w", "h", NULL};
  const char* title = "Axoltol Window";
  int x = 0, y = 0, w = 480, h = 320;

  if (!PyArg_ParseTupleAndKeywords(args, kwds, "|siiii", const_cast<char**>(kwlist), &title, x, y, w, h))
    return -1;

  self->window = new Window(title, x, y, w, h, 0);
  return 0;
}

void PyWindow::__dealloc__(PyWindowObj* self)
{
  delete self->window;
  Py_TYPE(self)->tp_free((PyObject*) self);
}
