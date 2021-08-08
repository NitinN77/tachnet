#include<stdio.h>
#include<stdlib.h>
#include <Python.h>
#include<string.h>
#include<math.h>
#include "dense_layer.h"
#include "activation_layer.h"

#define ARRAYSIZE(a) (sizeof(a) / sizeof(a[0]))

static PyObject *tanh_method(PyObject *self, PyObject *args) {
    PyObject *X;
    PyObject *Xret;
    int dim;
    int xr,xc;

    if(!PyArg_ParseTuple(args, "Oi", &X, &dim)) {
        return NULL;
    }

    if(dim == 1){
        xr = PyObject_Length(X);
        Xret = PyList_New(xr);
        for(int i = 0;i < xr; i++){
            PyObject *e; 
            e = PyList_GetItem(X, i);
            if (!PyFloat_Check(e))
                PyList_SetItem(X, i, 0);
            double temp = tanh(PyFloat_AsDouble(e));
            PyList_SetItem(Xret, i, PyFloat_FromDouble(temp));
        }
    }

    else {
        xr = PyObject_Length(X);
        Xret = PyList_New(xr);
        PyObject *temp = PyList_GetItem(X, 0);    
        xc = PyObject_Length(temp);

        for(int i = 0;i < xr; i++){
            PyObject *e, *e1; 
            e = PyList_GetItem(X, i);
            PyObject *rowarr = PyList_New(xc); 
            for(int j=0; j<xc; j++){
                e1 = PyList_GetItem(e, j);
                double tmp = tanh(PyFloat_AsDouble(e1));
                PyList_SetItem(rowarr, j, PyFloat_FromDouble(tmp));
            }
            PyList_SetItem(Xret, i, rowarr);
        }

    }

    return Xret;
}



static PyMethodDef Methods[] = {
    {"tanh", tanh_method, METH_VARARGS, "tanh"},
    {NULL, NULL, 0, NULL}
};


static struct PyModuleDef tachnet = {
    PyModuleDef_HEAD_INIT,
    "tachnet",
    "Astronomically fast deep learning library",
    -1,
    Methods
};

PyMODINIT_FUNC PyInit_tachnet(void) {
    return PyModule_Create(&tachnet);
}