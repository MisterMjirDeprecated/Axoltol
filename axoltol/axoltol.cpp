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

static PyObject* Test_System(PyObject* self, PyObject *args)
{
  const char* command;
  int sts;

  if (!PyArg_ParseTuple(args, "s", &command))
    return NULL;

  sts = system(command);
  return PyLong_FromLong(sts);
}

static PyMethodDef AxoltolMethods[] =
{
  {"init", (PyCFunction) Axoltol_Init, METH_NOARGS, "Initialize Axoltol"},
  {"quit", (PyCFunction) Axoltol_Quit, METH_NOARGS, "Quit Axoltol"},
  {"system", Test_System, METH_VARARGS, "Execute a shell command."},
  {NULL, NULL, 0, NULL}
};

static struct PyModuleDef axoltolmodule =
{
  PyModuleDef_HEAD_INIT,
  "axoltol",
  "No doc",
  -1,
  AxoltolMethods
};

PyMODINIT_FUNC PyInit_axoltol(void)
{
  PyObject* module;
  if (PyType_Ready(&PyWindow::type) < 0)
    return NULL;

  if (PyType_Ready(&PyRenderer::type) < 0)
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

  return module;
}
