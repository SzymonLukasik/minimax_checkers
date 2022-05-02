from setuptools import setup

from Cython.Build import cythonize
from Cython.Distutils.extension import Extension

setup(
    ext_modules=cythonize(Extension(
        "engine",
        ["engine.pyx"],
        language="c++",
        extra_compile_args=["-std=c++17"]
    ))
)
