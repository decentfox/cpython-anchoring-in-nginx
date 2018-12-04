#include <stdio.h>
#include <Python.h>

static PyObject *hello(PyObject *self, PyObject *args) {
    const char *world;

    if (!PyArg_ParseTuple(args, "s", &world))
        return NULL;

    printf("Hello, %s!\n", world);

    Py_INCREF(Py_None);
    return Py_None;
}

static PyMethodDef HelloMethods[] = {
        {"hello", hello, METH_VARARGS, "Say hello."},
        {NULL,    NULL,  0,            NULL}
};

static struct PyModuleDef hellomodule = {
        PyModuleDef_HEAD_INIT, "hello", NULL, -1, HelloMethods
};

PyMODINIT_FUNC PyInit_hello(void) {
    return PyModule_Create(&hellomodule);
}
