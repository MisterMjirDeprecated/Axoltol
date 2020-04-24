#include "py_renderer.h"
#include "py_window.h"
#include "py_rect.h"
#include "py_texture.h"
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
  {"copy", (PyCFunction) PyRenderer::copy, METH_VARARGS, "Copies"},
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
  PyObject *arg1, *arg2, *arg3, *arg4;
  if (!PyArg_ParseTuple(args, "O|OOO", &arg1, &arg2, &arg3, &arg4))
    return NULL;

  // axoltol.Rect object
  if (PyObject_IsInstance(arg2, (PyObject*) &PyRect::type))
  {
    PyRectObj* pyRect = (PyRectObj*) arg2;
    SDL_Rect rect = PyRect::getSDL(pyRect);
    return PyLong_FromLong(self->renderer->fillRect(&rect));
  }
  // Four integers
  else if (PyLong_Check(arg1))
  {
    return PyLong_FromLong(self->renderer->fillRect((int) PyLong_AsLong(arg1), (int) PyLong_AsLong(arg2), (int) PyLong_AsLong(arg3), (int) PyLong_AsLong(arg4)));
  }
  else
  {
    PyErr_SetString(PyExc_TypeError, "axoltol.Renderer.fillRect() method requires an axoltol.Rect object or four integers");
    return NULL;
  }
}

PyObject* PyRenderer::copy(PyRendererObj* self, PyObject* args)
{
  /*
   * This part needs explaning
   *
   * PyArg_ParseTuple is interesting
   * You can call it multiple times in a function, but the first PyArg_ParseTuple determines the minimum amount of arguments you can
   * have, that's why there's this section is a little weird.
   * Always make the first PyArg have the maximum amount of arguments
   */
  PyTextureObj* pyTexture;
  PyObject *arg2, *arg3, *arg4, *arg5, *arg6, *arg7, *arg8, *arg9;
  if (!PyArg_ParseTuple(args, "O!O|OOOOOOO", &PyTexture::type, &pyTexture, &arg2, &arg3, &arg4, &arg5, &arg6, &arg7, &arg8, &arg9))
    return NULL;

  // 2nd argument is a destRect
  if (PyObject_IsInstance(arg2, (PyObject*) &PyRect::type))
  {
    // 3rd argument is a destRect
    if (PyObject_IsInstance(arg3, (PyObject*) &PyRect::type))
    {
      PyRectObj* pySrcRect = (PyRectObj*) arg2;
      PyRectObj* pyDestRect = (PyRectObj*) arg3;
      SDL_Rect srcRect = PyRect::getSDL(pySrcRect);
      SDL_Rect destRect = PyRect::getSDL(pyDestRect);
      return PyLong_FromLong(self->renderer->copy(pyTexture->texture, &srcRect, &destRect));
    }
    // 3rd argument is an int
    else if (PyLong_Check(arg3))
    {
      PyRectObj* pySrcRect = (PyRectObj*) arg2;
      SDL_Rect srcRect = PyRect::getSDL(pySrcRect);
      return PyLong_FromLong(self->renderer->copy(pyTexture->texture, &srcRect, (int) PyLong_AsLong(arg3), (int) PyLong_AsLong(arg4), (int) PyLong_AsLong(arg5), (int) PyLong_AsLong(arg6)));
    }
    else
    {
      PyErr_SetString(PyExc_TypeError, "axoltol.Renderer.copy() bad argument(s)");
      return NULL;
    }
  }
  // 2nd argument is an int
  else if (PyLong_Check(arg3))
  {
    // 6th argument is a rect
    if (PyObject_IsInstance(arg6, (PyObject*) &PyRect::type))
    {
      PyRectObj* pyDestRect = (PyRectObj*) arg6;
      SDL_Rect destRect = PyRect::getSDL(pyDestRect);
      return PyLong_FromLong(self->renderer->copy(pyTexture->texture, (int) PyLong_AsLong(arg2), (int) PyLong_AsLong(arg3), (int) PyLong_AsLong(arg4), (int) PyLong_AsLong(arg5), &destRect));
    }
    // 6th argument is an int
    else if (PyLong_Check(arg6))
    {
      return PyLong_FromLong(self->renderer->copy(pyTexture->texture, (int) PyLong_AsLong(arg2), (int) PyLong_AsLong(arg3), (int) PyLong_AsLong(arg4), (int) PyLong_AsLong(arg5), (int) PyLong_AsLong(arg6), (int) PyLong_AsLong(arg7), (int) PyLong_AsLong(arg8), (int) PyLong_AsLong(arg9)));
    }
    else
    {
      PyErr_SetString(PyExc_TypeError, "axoltol.Renderer.copy() bad argument(s)");
      return NULL;
    }
  }
  else
  {
    PyErr_SetString(PyExc_TypeError, "axoltol.Renderer.copy() bad argument(s)");
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
