#include "py_texture.h"
#include "py_renderer.h"
#include <structmember.h>

PyMemberDef PyTexture::members[] = {
  {NULL}
};

PyTypeObject PyTexture::type = {
  PyVarObject_HEAD_INIT(NULL, 0)
  .tp_name = "axoltol.Texture",
  .tp_doc = "Texture object",
  .tp_basicsize = sizeof(PyTextureObj),
  .tp_itemsize = 0,
  .tp_flags = Py_TPFLAGS_DEFAULT,
  .tp_new = PyType_GenericNew,
  .tp_init = (initproc) PyTexture::__init__,
  .tp_dealloc = (destructor) PyTexture::__dealloc__,
  .tp_members = PyTexture::members,
  .tp_methods = PyTexture::methods
};

PyMethodDef PyTexture::methods[] = {
  {NULL}
};

int PyTexture::__init__(PyTextureObj* self, PyObject* args, PyObject* kwds)
{
  static const char* kwlist[] = {"renderer", "file path", NULL};
  PyRendererObj* pyRenderer;
  const char* filePath = "";

  if (!PyArg_ParseTupleAndKeywords(args, kwds, "O!s", const_cast<char**>(kwlist), &PyRenderer::type, &pyRenderer, &filePath))
    return -1;

  self->texture = new Texture(pyRenderer->renderer, filePath);
  return 0;
}

void PyTexture::__dealloc__(PyTextureObj* self)
{
  delete self->texture;
  Py_TYPE(self)->tp_free((PyObject*) self);
}
