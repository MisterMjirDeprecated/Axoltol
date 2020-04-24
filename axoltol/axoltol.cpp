#include <Python.h>
#include <SDL2/SDL.h>
#include "py_sdl.h"

/*
 * Methods
 * -------
 * These are the methods which will be visible to Python
 */
static PyObject* Axoltol_Init(PyObject* self, PyObject* args)
{
  return PyLong_FromLong(SDL_Init(SDL_INIT_EVERYTHING));
}

static PyObject* Axoltol_Quit(PyObject* self, PyObject* args)
{
  SDL_Quit();
  Py_RETURN_NONE;
}

static PyObject* Axoltol_PollEvent(PyObject* self, PyObject* args)
{
  PyObject* obj;
  if (!PyArg_ParseTuple(args, "O!", &PyEvent::type, &obj))
    return NULL;

  SDL_PollEvent(&((PyEventObj*) obj)->event);

  Py_RETURN_NONE;
}

static PyMethodDef AxoltolMethods[] =
{
  {"init", (PyCFunction) Axoltol_Init, METH_NOARGS, "Initialize Axoltol"},
  {"quit", (PyCFunction) Axoltol_Quit, METH_NOARGS, "Quit Axoltol"},
  {"pollEvent", (PyCFunction) Axoltol_PollEvent, METH_VARARGS, "Poll pending events"},
  {NULL, NULL, 0, NULL}
};

static struct PyModuleDef axoltolmodule =
{
  PyModuleDef_HEAD_INIT,
  "axoltol",
  "Game Library",
  -1,
  AxoltolMethods
};

PyMODINIT_FUNC PyInit_axoltol(void)
{
  // TODO: Figure out an easier/cleaner way to initialize every type
  PyObject* module;
  if (PyType_Ready(&PyWindow::type) < 0)
    return NULL;

  if (PyType_Ready(&PyRenderer::type) < 0)
    return NULL;

  if (PyType_Ready(&PyRect::type) < 0)
    return NULL;

  if (PyType_Ready(&PyEvent::type) < 0)
    return NULL;

  if (PyType_Ready(&PyTexture::type) < 0)
    return NULL;

  module = PyModule_Create(&axoltolmodule);
  if (module == NULL)
    return NULL;

  Py_INCREF(&PyWindow::type);
  if (PyModule_AddObject(module, "Window", (PyObject*) &PyWindow::type) < 0)
  {
    Py_DECREF(&PyWindow::type);
    Py_DECREF(module);
    return NULL;
  }

  Py_INCREF(&PyRenderer::type);
  if (PyModule_AddObject(module, "Renderer", (PyObject*) &PyRenderer::type) < 0)
  {
    Py_DECREF(&PyRenderer::type);
    Py_DECREF(module);
    return NULL;
  }

  Py_INCREF(&PyRect::type);
  if (PyModule_AddObject(module, "Rect", (PyObject*) &PyRect::type) < 0)
  {
    Py_DECREF(&PyRect::type);
    Py_DECREF(module);
    return NULL;
  }

  Py_INCREF(&PyEvent::type);
  if (PyModule_AddObject(module, "Event", (PyObject*) &PyEvent::type) < 0)
  {
    Py_DECREF(&PyEvent::type);
    Py_DECREF(module);
    return NULL;
  }

  Py_INCREF(&PyTexture::type);
  if (PyModule_AddObject(module, "Texture", (PyObject*) &PyTexture::type) < 0)
  {
    Py_DECREF(&PyTexture::type);
    Py_DECREF(module);
    return NULL;
  }

  PyEvent::addEvents(module);

  return module;
}
