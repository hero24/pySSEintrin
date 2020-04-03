#include <stdint.h>
#include <Python.h>
#include "sseintrin.h"
 
/* Average */

static PyObject *sse_avgpu16(PyObject *self, PyObject *args)
{
    /* WARNING: Seems to be crashing on windows */
    int16_t aa[4], ab[4], *ar;
    __m64 a, b, r;
    if(!PyArg_ParseTuple(args, "iiiiiiii", A03(&aa), A03(&ab)))
        return NULL;
    a = _mm_set_pi16(A03(aa));
    b = _mm_set_pi16(A03(ab));
    r = _mm_avg_pu16(a, b);
    ar = (int16_t *) &r;
    _mm_empty();
    return Py_BuildValue("[iiii]", A03(ar));
}

static PyObject *sse_avgpu8(PyObject *self, PyObject *args)
{
    int8_t aa[8], ab[8], *ar;
    __m64 a, b, r;
    if(!PyArg_ParseTuple(args, "iiiiiiiiiiiiiiii", A03(&aa), A47(&aa), A03(&ab), A47(&ab)))
        return NULL;
    a = _mm_set_pi8(A03(aa), A47(aa));
    b = _mm_set_pi8(A03(ab), A47(ab));
    r = _mm_avg_pu8(a, b);
    ar = (int8_t *) &r;
    _mm_empty();
    return Py_BuildValue("[iiiiiiii]", A03(ar), A47(ar));
}

#define SHUFFLE_PI16_BASE(num) case num: \
      r = _mm_shuffle_pi16(a, num); \
      break

#define SHUFFLE_PI16_2(num) SHUFFLE_PI16_BASE(num); SHUFFLE_PI16_BASE(num+1)
#define SHUFFLE_PI16_5(num) SHUFFLE_PI16_2(num); SHUFFLE_PI16_2(num+2); SHUFFLE_PI16_BASE(num+4)
#define SHUFFLE_PI16_10(num) SHUFFLE_PI16_5(num); SHUFFLE_PI16_5(num+5)
#define SHUFFLE_PI16_25(num) SHUFFLE_PI16_10(num); SHUFFLE_PI16_10(num+10); SHUFFLE_PI16_5(num+20)
#define SHUFFLE_PI16_50(num) SHUFFLE_PI16_25(num); SHUFFLE_PI16_25(num+25)
#define SHUFFLE_PI16_100(num) SHUFFLE_PI16_50(num); SHUFFLE_PI16_50(num+50)
#define SHUFFLE_PI16_200(num) SHUFFLE_PI16_100(num); SHUFFLE_PI16_100(num+100)
/* shuffle */
static PyObject *sse_shuffle_pi16(PyObject *self, PyObject *args)
{
    int16_t x[4], *ar; uint8_t imm8;
    if(!PyArg_ParseTuple(args, "iiiii", A03(&x), &imm8))
        return NULL;
    __m64 a = _mm_set_pi16(A03(x)), r;
    switch(imm8){
            SHUFFLE_PI16_200(0);
            SHUFFLE_PI16_50(200);
            SHUFFLE_PI16_5(250);
    }
    ar = (int16_t *) &r;
    _mm_empty();
    return Py_BuildValue("[iiii]", A03(ar));
}

#define ADD_SSE_METHOD(METH, DOCS) ADD_PREFIX_METHOD(METH, sse_, DOCS)
static PyMethodDef SSEMethods[] = {
    ADD_SSE_METHOD(shuffle_pi16, "Shuffle 16-bit integers in a using the control in imm8"),
    ADD_SSE_METHOD(avgpu16, "Average packed unsigned 16bit integers in a and b"),
    ADD_SSE_METHOD(avgpu8, "Average packed unsigned 8bit integers in a and b"),
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef ssemodule = {
    PyModuleDef_HEAD_INIT,
    "sseintrin",
    "Python wrapper for SSE intrinsics",
    -1,
    SSEMethods
};


PyMODINIT_FUNC PyInit_sseintrin(void){
    PyObject *module = PyModule_Create(&ssemodule);
    return module;
}
