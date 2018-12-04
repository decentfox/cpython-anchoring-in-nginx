from setuptools import setup
from distutils.core import Extension

hello = Extension(
    'hello',
    sources=['hello7.pyx'])

setup(name='hello',
      version='1.0',
      description='Say hello',
      setup_requires=['cython'],
      ext_modules=[hello])
