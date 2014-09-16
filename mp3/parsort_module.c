#include <Python.h>
#include <stdlib.h>
#include "parsort.h"
 
static PyObject*
sort(PyObject* self, PyObject* args)
{
	//WRITE YOUR IMPLEMENTATION HERE......
    //referenced to http://stackoverflow.com/questions/22458298/extending-python-with-c-pass-a-list-to-pyarg-parsetuple & https://mail.python.org/pipermail/capi-sig/2009-January/000205.html
    /* get nums and thread_count */
    PyObject *list;
    int th_cnt;
    if (!PyArg_ParseTuple(args, "Oi", &list, &th_cnt))
        exit(1);

    /* --get array and array size */
    int data_size = 0;
    int *data = malloc(0);
    PyObject *itr = PyObject_GetIter(list);
    if (!itr) exit(1);
    while (1){
        PyObject *next = PyIter_Next(itr);
        if (!next){
            break;
        }
        if (!PyInt_Check(next)) exit(1);
        int value = (int)PyInt_AsLong(next);
        data_size++;
        data = realloc(data, data_size*sizeof(int));
        data[data_size - 1] = value;
    }
    /*int i;
    for (i = 0; i < data_size; i++){
        printf("%d ", data[i]);
    }*/

    /* run parsort */
    data_t input;
    input.data_size = data_size;
    input.data = data;
    input.thread_count = th_cnt;
    data_t res = parsort(input);  
    /*for (i = 0; i < data_size; i++){
        printf("%d ", data[i]);
    }*/


    /* convert result into list */
    PyObject *ret_ls = PyList_New(data_size);
    if (!ret_ls) return NULL;
    int i;
    long tmp;
    for (i = 0; i < data_size; i++){
        tmp = (long)res.data[i];
        PyObject *val = PyInt_FromLong(tmp);
        PyList_SET_ITEM(ret_ls, i, val);
    }

    /* free data */
    free(data);

    return ret_ls;
}

static PyMethodDef ParsortMethods[] = {
  {"sort", sort, METH_VARARGS, "Parallel Merge Sort."},
  {NULL, NULL, 0, NULL}
};
 
PyMODINIT_FUNC
initparsort(void)
{
  (void) Py_InitModule("parsort", ParsortMethods);
}

