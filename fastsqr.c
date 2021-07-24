#include <Python.h>
#include <math.h>

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

static PyObject *method_arrsqr(PyObject *self, PyObject *args) {
    PyObject *float_list;
    int len;
    double *arr;

    if (!PyArg_ParseTuple(args, "O", &float_list))
        return NULL;
    len = PyObject_Length(float_list);

    if (len < 0) return NULL;

    arr = (double *)malloc(sizeof(double *) * len);
    
    if (arr == NULL) return NULL;

    PyObject *sqrs = PyList_New(len);

    for(int i = 0;i < len; i++){
        PyObject *e;
        e = PyList_GetItem(float_list, i);
        if (!PyFloat_Check(e)) arr[i] = 0.0;
        arr[i] = pow(PyFloat_AsDouble(e),2);
        PyList_SetItem(sqrs, i, Py_BuildValue("d", arr[i]));
    }

    return sqrs;
}


static PyMethodDef Methods[] = {
    {"sqr", method_sqr, METH_VARARGS, "fast square computation"},
    {"asqr", method_arrsqr, METH_VARARGS, "array element-wise square computation"},
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