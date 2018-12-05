#include <Python.h>
#include "hello9.h"

int main() {
    PyImport_AppendInittab("hello", &PyInit_hello9);
    Py_Initialize();
    PyImport_ImportModule("hello");
    hello("embed");
    Py_FinalizeEx();
}
