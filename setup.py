from setuptools import setup, Extension
import os

os.environ["CC"] = "clang"
os.environ["CXX"] = "clang++"

extension = Extension('axoltol',
                    include_dirs=['/usr/include/python3.6', '/usr/include', 'axoltol/sdl', 'axoltol/py_sdl'],
                    libraries=['SDL2'],
                    library_dirs=['/usr/lib/x86_64-linux-gnu'],
                    sources=['axoltol/axoltol.cpp',
                    'axoltol/py_sdl/py_renderer.cpp',
                    'axoltol/py_sdl/py_window.cpp',
                    'axoltol/sdl/renderer.cpp',
                    'axoltol/sdl/window.cpp'])

setup(name='axoltol',
      version='0.0.1',
      description='Tools for making games',
      author="Mister Mjir",
      ext_modules=[extension])
