from setuptools import setup, Extension
import os

os.environ["CC"] = "clang"
os.environ["CXX"] = "clang++"

extension = Extension('axoltol',
                    include_dirs=['/usr/include/python3.7', '/usr/include', 'axoltol/sdl', 'axoltol/py_sdl'],
                    libraries=['SDL2', 'SDL2_image'],
                    library_dirs=['/usr/lib/x86_64-linux-gnu'],
                    sources=['axoltol/axoltol.cpp',
                    'axoltol/py_sdl/py_event.cpp',
                    'axoltol/py_sdl/py_rect.cpp',
                    'axoltol/py_sdl/py_renderer.cpp',
                    'axoltol/py_sdl/py_texture.cpp',
                    'axoltol/py_sdl/py_window.cpp',
                    'axoltol/sdl/renderer.cpp',
                    'axoltol/sdl/texture.cpp',
                    'axoltol/sdl/window.cpp'])

setup(name='axoltol',
      version='0.0.1',
      description='Tools for making games',
      author="Mister Mjir",
      ext_modules=[extension])
