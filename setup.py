from setuptools import setup
from distutils.core import Extension

hello = Extension(
    'hello',
    sources=['hello6.c'])

setup(name='hello',
      version='1.0',
      description='Say hello',
      ext_modules=[hello])
