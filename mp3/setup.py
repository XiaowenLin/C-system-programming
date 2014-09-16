#DO NOT MODIFY THIS FILE

from distutils.core import setup, Extension

module1 = Extension('parsort', sources = ['parsort_module.c', 'parsort.c', 'scheduler.c', 'register.c'])

setup (name = 'parsort',
       version = '1.0',
       description = 'Parallel mergesort, CS241 SU2014',
       ext_modules = [module1])

