#include <emmintrin.h>
#include <stdint.h>
#include <Python.h>

#define N_RET_SZ 2

#define ASE(a, n) a[n], a[n+1]
#define ADSE(a, n) ASE(a, n), ASE(a, n+2)
#define A03(a) ADSE(a, 0)
#define A47(a) ADSE(a, 4)
#define A811(a) ADSE(a,8)
#define A1216(a) ADSE(a, 12)

/* Base 16bit int */
static inline __m128i *sse_basei16(PyObject *self, PyObject *args)
{
    int16_t aa[8], ab[8]; 
    __m128i *n = malloc(sizeof(__m128i)*N_RET_SZ);
    if(!PyArg_ParseTuple(args, "iiiiiiiiiiiiiiii", A03(&aa), A47(&aa), A03(&ab), A47(&ab))){
        return NULL;
    }
    n[0] = _mm_set_epi16(A03(aa), A47(aa));
    n[1] = _mm_set_epi16(A03(ab), A47(ab));
    return n;
}

static inline PyObject *sse_pyobj_basei16(__m128i *r, __m128i *n)
{
    int16_t *ar;
    ar = (int16_t *) r;
    free(n);
    return Py_BuildValue("[iiiiiiii]", A03(ar), A47(ar));
}

/* base 8 bit int */
static inline __m128i *sse_basei8(PyObject *self, PyObject *args)
{
    int8_t aa[16], ab[16];
    __m128i *n = malloc(sizeof(__m128i)*N_RET_SZ);
    if(!PyArg_ParseTuple(args, "iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii",
                                A03(&aa), A47(&aa), A811(&aa), A1216(&aa),
                                A03(&ab), A47(&ab), A811(&ab), A1216(&ab))){
         return NULL;
    }
    n[0] = _mm_set_epi8(A03(aa), A47(aa), A811(aa), A1216(aa)); 
    n[1] = _mm_set_epi8(A03(ab), A47(ab), A811(ab), A1216(ab));
    return n;
}

static inline PyObject *sse_pyobj_basei8(__m128i *r, __m128i *n)
{
    int8_t *ar;
    ar = (int8_t *) r;
    free(n);
    return Py_BuildValue("[iiiiiiiiiiiiiiii]", A03(ar), A47(ar), A811(ar), A1216(ar));
}

/* Add */
static PyObject *sse_addepi8(PyObject *self, PyObject *args)
{
    int8_t aa[16], ab[16];
    int8_t *ar;
    __m128i n, a, b;
    if(!PyArg_ParseTuple(args, "iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii",
                                A03(&aa), A47(&aa), A811(&aa), A1216(&aa),
                                A03(&ab), A47(&ab), A811(&ab), A1216(&ab))){
         return NULL;
    }
    a = _mm_set_epi8(A03(aa), A47(aa), A811(aa), A1216(aa)); 
    b = _mm_set_epi8(A03(ab), A47(ab), A811(ab), A1216(ab));
    n = _mm_add_epi8(a, b);
    ar = (int8_t *) &n;
    return Py_BuildValue("[iiiiiiiiiiiiiiii]", A03(ar), A47(ar), A811(ar), A1216(ar));
}

static PyObject *sse_addepi16(PyObject *self, PyObject *args)
{
    int16_t *ar, aa[8], ab[8];
    __m128i n, a ,b;
    if(!PyArg_ParseTuple(args, "iiiiiiiiiiiiiiii", A03(&aa), A47(&aa), A03(&ab), A47(&ab))){
        return NULL;
    }
    a = _mm_set_epi16(A03(aa), A47(aa));
    b = _mm_set_epi16(A03(ab), A47(ab));
    n = _mm_add_epi16(a, b);
    ar = (int16_t *) &n;
    return Py_BuildValue("[iiiiiiii]", A03(ar), A47(ar));
}

static PyObject *sse_addepi32(PyObject *self, PyObject *args)
{
    int32_t aa[4], ab[4]; 
    int32_t *ar;
    __m128i n, a ,b;
    if(!PyArg_ParseTuple(args, "iiiiiiii", A03(&aa), A03(&ab))){
        return NULL;
    }
    a = _mm_set_epi32(A03(aa));
    b = _mm_set_epi32(A03(ab));
    n = _mm_add_epi32(a, b);
    ar = (int32_t *) &n;
    return Py_BuildValue("[iiii]", A03(ar));
}

static PyObject *sse_addepi64(PyObject *self, PyObject *args)
{
    int64_t aa[2], ab[2]; 
    int64_t *ar;
    __m128i n, a ,b;
    if(!PyArg_ParseTuple(args, "llll", ASE(&aa, 0), ASE(&ab, 0))){
        return NULL;
    }
    a = _mm_set_epi64x(ASE(aa, 0));
    b = _mm_set_epi64x(ASE(ab, 0));
    n = _mm_add_epi64(a, b);
    ar = (int64_t *) &n;
    return Py_BuildValue("[ll]", ASE(ar, 0));
}

/* Average */
static PyObject *sse_avgepu16(PyObject *self, PyObject *args)
{
    __m128i r, *n = sse_basei16(self, args);
    if(n == NULL)
        return NULL;
    r = _mm_avg_epu16(n[0], n[1]);
    return sse_pyobj_basei16(&r, n);

}

static PyObject *sse_avgepu8(PyObject *self, PyObject *args)
{
    __m128i r, *n = sse_basei8(self, args);
    if (n == NULL)
        return NULL;
    r = _mm_avg_epu8(n[0], n[1]);
    return sse_pyobj_basei8(&r, n);
}

/* Compare Equal */

static PyObject *sse_cmpeqepi16(PyObject *self, PyObject *args)
{
    __m128i r, *n = sse_basei16(self, args);
    if(n == NULL)
        return NULL;
    r = _mm_cmpeq_epi16(n[0], n[1]);
    return sse_pyobj_basei16(&r, n);
}

static PyObject *sse_cmpeqepi8(PyObject *self, PyObject *args)
{
    __m128i r, *n = sse_basei8(self, args);
    if (n == NULL)
        return NULL;
    r = _mm_cmpeq_epi8(n[0], n[1]);
    return sse_pyobj_basei8(&r, n);
}

static PyMethodDef SSEMethods[] = {
    {"cmpeq_epi16", sse_cmpeqepi16, METH_VARARGS, "Compare packed 16-bit integers in a and b for equality"},
    {"cmpeq_epi8", sse_cmpeqepi8, METH_VARARGS, "Compare packed 8-bit integers in a and b for equality"},
    {"avg_epu16", sse_avgepu16, METH_VARARGS, "Average packed unsigned 16bit integers in a and b"},
    {"avg_epu8",  sse_avgepu8,  METH_VARARGS, "Average packed unsigned 8bit integers in a and b"},
    {"add_epi64", sse_addepi64, METH_VARARGS, "Add packed 64-bit integers in a and b"},
    {"add_epi32", sse_addepi32, METH_VARARGS, "Add packed 32-bit integers in a and b"},
    {"add_epi16", sse_addepi16, METH_VARARGS, "Add packed 16-bit integers in a and b"},
    {"add_epi8", sse_addepi8, METH_VARARGS, "Add packed 8-bit integers in a and b"},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef ssemodule = {
    PyModuleDef_HEAD_INIT,
    "pysseintrin",
    "Python wrapper for sse intrinsics",
    -1,
    SSEMethods
};

PyMODINIT_FUNC PyInit_sseintrin(void){
    return PyModule_Create(&ssemodule);
}
