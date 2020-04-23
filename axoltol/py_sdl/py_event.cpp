#include "py_event.h"
#include <structmember.h>

PyMemberDef PyEvent::members[] = {
  {NULL}
};

PyTypeObject PyEvent::type = {
  PyVarObject_HEAD_INIT(NULL, 0)
  .tp_name = "axoltol.Event",
  .tp_doc = "Event object",
  .tp_basicsize = sizeof(PyEventObj),
  .tp_itemsize = 0,
  .tp_flags = Py_TPFLAGS_DEFAULT,
  .tp_richcompare = (richcmpfunc) PyEvent::compare,
  .tp_new = PyType_GenericNew,
  .tp_init = (initproc) PyEvent::__init__,
  .tp_dealloc = (destructor) PyEvent::__dealloc__,
  .tp_members = PyEvent::members,
  .tp_methods = PyEvent::methods
};

PyMethodDef PyEvent::methods[] = {
  {NULL}
};

int PyEvent::__init__(PyEventObj* self, PyObject* args, PyObject* kwds)
{
  return 0;
}

void PyEvent::__dealloc__(PyEventObj* self)
{
  Py_TYPE(self)->tp_free((PyObject*) self);
}

PyObject* PyEvent::compare(PyEventObj* self, PyObject* other, int op)
{
  if (!PyLong_Check(other))
    return Py_False;

  Py_RETURN_RICHCOMPARE(self->event.type, PyLong_AsLong(other), op);
}

void PyEvent::addEvents(PyObject *module)
{
  PyModule_AddIntConstant(module, "QUIT", SDL_QUIT);
}
