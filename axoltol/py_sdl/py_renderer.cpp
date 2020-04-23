#include "py_renderer.h"
#include "py_window.h"
#include "py_rect.h"
#include <structmember.h>
#include <SDL2/SDL.h>


PyMemberDef PyRenderer::members[] = {
  {NULL}
};

PyTypeObject PyRenderer::type = {
  PyVarObject_HEAD_INIT(NULL, 0)
  .tp_name = "axoltol.Renderer",
  .tp_doc = "Renderer object",
  .tp_basicsize = sizeof(PyRendererObj),
  .tp_itemsize = 0,
  .tp_flags = Py_TPFLAGS_DEFAULT,
  .tp_new = PyType_GenericNew,
  .tp_init = (initproc) PyRenderer::__init__,
  .tp_dealloc = (destructor) PyRenderer::__dealloc__,
  .tp_members = PyRenderer::members,
  .tp_methods = PyRenderer::methods
};

PyMethodDef PyRenderer::methods[] = {
  {"setDrawColor", (PyCFunction) PyRenderer::setDrawColor, METH_VARARGS, "Sets the draw color of the renderer"},
  {"fillRect", (PyCFunction) PyRenderer::fillRect, METH_VARARGS, "Fills in a rect"},
  {"clear", (PyCFunction) PyRenderer::clear, METH_NOARGS, "Clears the screen"},
  {"present", (PyCFunction) PyRenderer::present, METH_NOARGS, "Presents the screen"},
  {NULL}
};

int PyRenderer::__init__(PyRendererObj* self, PyObject* args, PyObject* kwds)
{
  static const char* kwlist[] = {"window", NULL};
  PyObject* object = nullptr;
  if (!PyArg_ParseTupleAndKeywords(args, kwds, "O!", const_cast<char**>(kwlist), &PyWindow::type, &object))
    return -1;

  PyWindowObj* window = (PyWindowObj*) object;
  self->renderer = new Renderer(window->window);
  return 0;
}

void PyRenderer::__dealloc__(PyRendererObj* self)
{
  delete self->renderer;
  Py_TYPE(self)->tp_free((PyObject*) self);
}

PyObject* PyRenderer::setDrawColor(PyRendererObj* self, PyObject* args)
{
  unsigned char r = 0, g = 0, b = 0, a = 255;
  if (!PyArg_ParseTuple(args, "bbb|b", &r, &g, &b, &a))
    return NULL;

  return PyLong_FromLong(self->renderer->setDrawColor(r, g, b, a));
}

PyObject* PyRenderer::fillRect(PyRendererObj* self, PyObject* args)
{
  // This is major finessing, Python doesn't support overloads but doing it anyways
  PyObject* obj;
  if (PyArg_ParseTuple(args, "O", &obj))
  {
    // axoltol.Rect object
    if (PyObject_IsInstance(obj, (PyObject*) &PyRect::type))
    {
      PyRectObj* pyRect = (PyRectObj*) obj;
      SDL_Rect rect = PyRect::getSDL(pyRect);
      return PyLong_FromLong(self->renderer->fillRect(&rect));
    }
    // Four integers
    else if (PyLong_Check(obj))
    {
      int x, y, w, h;
      if(!PyArg_ParseTuple(args, "iiii", &x, &y, &w, &h))
        return NULL;

      return PyLong_FromLong(self->renderer->fillRect(x, y, w, h));
    }
    else
    {
      PyErr_SetString(PyExc_TypeError, "axoltol.Renderer.fillRect() method requires an axoltol.Rect object or four integers.");
      return NULL;
    }
  }
  else
  {
    return NULL;
  }
}

PyObject* PyRenderer::clear(PyRendererObj* self, PyObject* args)
{
  return PyLong_FromLong(self->renderer->clear());
}

PyObject* PyRenderer::present(PyRendererObj* self, PyObject* args)
{
  self->renderer->present();
  Py_RETURN_NONE;
}
