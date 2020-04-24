#ifndef AXOLTOL_PY_TEXTURE
#define AXOLTOL_PY_TEXTURE

#include <Python.h>
#include "sdl.h"

typedef struct
{
  PyObject_HEAD
  Texture* texture;
} PyTextureObj;

class PyTexture
{
public:
  // Standard Functions
  static int __init__(PyTextureObj* self, PyObject* args, PyObject* kwds);
  static void __dealloc__(PyTextureObj* self);

  // Variables
  static PyMemberDef members[];
  static PyTypeObject type;
  static PyMethodDef methods[];
private:
  PyTexture();
};

#endif
