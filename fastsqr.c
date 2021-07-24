#include <Python.h>

 int fpow(int a, int b) {
    int res = 1;
    while (b > 0) {
        if (b & 1)
            res = res * a;
        a = a * a;
        b >>= 1;
    }
    return res;
}

static PyObject *method_sqr(PyObject *self, PyObject *args) {
    int n = 0, exp = 0;
    int sqr = 0;

    if(!PyArg_ParseTuple(args, "ii", &n, &exp)) {
        return NULL;
    }

    sqr = fpow(n, exp);

    return PyLong_FromLong(sqr);
}

static PyMethodDef Methods[] = {
    {"sqr", method_sqr, METH_VARARGS, "fast square computation"},
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