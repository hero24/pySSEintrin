#include <stdint.h>
#include <Python.h>
#include "sseintrin.h"

/* Add */
#define addps_docstring "Add packed single-precision floating-point elements"
static PyObject *sse_addps(PyObject *self, PyObject *args)
{
    SPBASE(_mm_add_ps)
}

#define addss_docstring "Add the lower single-precision (32-bit) \
floating-point element in a and b, store the result in the lower\
element of dst, and copy the upper 3 packed elements from a to  \
the upper elements of return."

static PyObject *sse_addss(PyObject *self, PyObject *args)
{
    SPBASE(_mm_add_ss)
}

/* And */
#define andps_docstring "Compute the bitwise AND of packed single-precision (32-bit) \
floating-point elements in a and b, and return the results."
static PyObject *sse_andps(PyObject *self, PyObject *args)
{
    SPBASE(_mm_and_ps)
}

#define andnot_ps_docstring "Compute the bitwise NOT of packed single-precision (32-bit) \
floating-point elements in a and b, and return the results."
static PyObject *sse_andnot_ps(PyObject *self, PyObject *args)
{
    SPBASE(_mm_andnot_ps)
}

/* Average */
#define avgpu16_docstring "Average packed unsigned 16bit integers in a and b"
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

#define avgpu8_docstring "Average packed unsigned 8bit integers in a and b"
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

/* Compare Equal */
#define cmpeq_ps_docstring "Compare packed single-precision \
floating-point elements in a and b for equality"
static PyObject *sse_cmpeq_ps(PyObject *self, PyObject *args)
{
    SPBASE(_mm_cmpeq_ps)
}

#define cmpeq_ss_docstring "Compare the lower single-precision   \
floating-point elements in a and b for equality, store the      \
result in the lower element of dst, and copy the upper 3 packed \
elements from a to the upper elements of return."
static PyObject *sse_cmpeq_ss(PyObject *self, PyObject *args)
{
    SPBASE(_mm_cmpeq_ss)
}

/* Compare greater than or equal */
#define cmpge_ps_docstring "Compare packed single-precision \
floating-point elements in a and b for greater-than-or-equal"
static PyObject *sse_cmpge_ps(PyObject *self, PyObject *args)
{
    SPBASE(_mm_cmpge_ps)
}

#define cmpge_ss_docstring "Compare the lower single-precision   \
floating-point elements in a and b for greater-than-or-equal,    \
store the result in the lower element of dst, and copy the upper \
3 packed elements from a to the upper elements of dst."
static PyObject *sse_cmpge_ss(PyObject *self, PyObject *args)
{
    SPBASE(_mm_cmpge_ss)
}

/* Compare greater than */
#define cmpgt_ps_docstring "Compare packed single-precision \
floating-point elements in a and b for greater-than"
static PyObject *sse_cmpgt_ps(PyObject *self, PyObject *args)
{
    SPBASE(_mm_cmpgt_ps)
}

#define cmpgt_ss_docstring "Compare the lower single-precision  \
floating-point elements in a and b for greater-than, store the  \
result in the lower element of dst, and copy the upper 3 packed \
elements from a to the upper elements of dst."
static PyObject *sse_cmpgt_ss(PyObject *self, PyObject *args)
{
    SPBASE(_mm_cmpgt_ss)
}

/* Compare less than or equal */
#define cmple_ps_docstring "Compare packed single-precision \
floating-point elements in a and b for less-than-or-equal"
static PyObject *sse_cmple_ps(PyObject *self, PyObject *args)
{
    SPBASE(_mm_cmple_ps)
}

#define cmple_ss_docstring "Compare the lower single-precision   \
floating-point elements in a and b for less-than-or-equal, store \
the result in the lower element of dst, and copy the upper 3     \
packed elements from a to the upper elements of dst."
static PyObject *sse_cmple_ss(PyObject *self, PyObject *args)
{
    SPBASE(_mm_cmple_ss)
}

/* Compare less than */
#define cmplt_ps_docstring "Compare packed single-precision \
floating-point elements in a and b for less-than"
static PyObject *sse_cmplt_ps(PyObject *self, PyObject *args)
{
    SPBASE(_mm_cmplt_ps)
}

#define cmplt_ss_docstring "Compare the lower single-precision     \
floating-point elements in a and b for less-than, store the result \
in the lower element of dst, and copy the upper 3 packed elements  \
from a to the upper elements of dst."
static PyObject *sse_cmplt_ss(PyObject *self, PyObject *args)
{
    SPBASE(_mm_cmplt_ss)
}

/* Compare not equal */
#define cmpneq_ps_docstring "Compare packed single-precision \
floating-point elements in a and b for non-equality"
static PyObject *sse_cmpneq_ps(PyObject *self, PyObject *args)
{
    SPBASE(_mm_cmpneq_ps)
}

#define cmpneq_ss_docstring "Compare the lower single-precision \
floating-point elements in a and b for non-equality, store the  \
result in the lower element of dst, and copy the upper 3 packed \
elements from a to the upper elements of return."
static PyObject *sse_cmpneq_ss(PyObject *self, PyObject *args)
{
    SPBASE(_mm_cmpneq_ss)
}

/* Compare not greater than or equal */
#define cmpnge_ps_docstring "Compare packed single-precision    \
floating-point elements in a and b for not-greater-than-or-equal"
static PyObject *sse_cmpnge_ps(PyObject *self, PyObject *args)
{
    SPBASE(_mm_cmpnge_ps)
}

#define cmpnge_ss_docstring "Compare the lower single-precision  \
floating-point elements in a and b for not-greater-than-or-equal,\
store the result in the lower element of dst, and copy the upper \
3 packed elements from a to the upper elements of dst."
static PyObject *sse_cmpnge_ss(PyObject *self, PyObject *args)
{
    SPBASE(_mm_cmpnge_ss)
}

/* Compare not greater than */
#define cmpngt_ps_docstring "Compare packed single-precision \
floating-point elements in a and b for not-greater-than"
static PyObject *sse_cmpngt_ps(PyObject *self, PyObject *args)
{
    SPBASE(_mm_cmpngt_ps)
}

#define cmpngt_ss_docstring "Compare the lower single-precision   \
floating-point elements in a and b for not-greater-than, store the\
result in the lower element of dst, and copy the upper 3 packed   \
elements from a to the upper elements of dst."
static PyObject *sse_cmpngt_ss(PyObject *self, PyObject *args)
{
    SPBASE(_mm_cmpngt_ss)
}

/* Compare not less than or equal */
#define cmpnle_ps_docstring "Compare packed single-precision \
floating-point elements in a and b for not-less-than-or-equal"
static PyObject *sse_cmpnle_ps(PyObject *self, PyObject *args)
{
    SPBASE(_mm_cmpnle_ps)
}

#define cmpnle_ss_docstring "Compare the lower single-precision  \
floating-point elements in a and b for not-less-than-or-equal,   \
store the result in the lower element of dst, and copy the upper \
3 packed elements from a to the upper elements of dst."
static PyObject *sse_cmpnle_ss(PyObject *self, PyObject *args)
{
    SPBASE(_mm_cmpnle_ss)
}

/* Compare not less than */
#define cmpnlt_ps_docstring "Compare packed single-precision \
floating-point elements in a and b for not-less-than"
static PyObject *sse_cmpnlt_ps(PyObject *self, PyObject *args)
{
    SPBASE(_mm_cmpnlt_ps)
}

#define cmpnlt_ss_docstring "Compare the lower single-precision \
floating-point elements in a and b for not-less-than, store the \
result in the lower element of dst, and copy the upper 3 packed \
elements from a to the upper elements of dst."
static PyObject *sse_cmpnlt_ss(PyObject *self, PyObject *args)
{
    SPBASE(_mm_cmpnlt_ss)
}

/* cmpord and cmpnord*/
#define cmpord_ps_docstring "Compare packed single-precision \
floating-point elements in a and b to see if neither is NaN, \
and return the results."
static PyObject *sse_cmpord_ps(PyObject *self, PyObject *args)
{
    SPBASE(_mm_cmpord_ps)
}

#define cmpord_ss_docstring "Compare the lower single-precision \
floating-point elements in a and b to see if neither is NaN,    \
store the result in the lower element of dst, and copy the      \
upper 3 packed elements from a to the upper elements of return."
static PyObject *sse_cmpord_ss(PyObject *self, PyObject *args)
{
    SPBASE(_mm_cmpord_ss)
}

#define cmpunord_ps_docstring "Compare packed single-precision  \
floating-point elements in a and b to see if either is NaN, and \
return the results"
static PyObject *sse_cmpunord_ps(PyObject *self, PyObject *args)
{
    SPBASE(_mm_cmpunord_ps)
}

#define cmpunord_ss_docstring "Compare the lower single-precision \
floating-point elements in a and b to see if either is NaN, store \
the result in the lower element of dst, and copy the upper 3      \
packed elements from a to the upper elements of return."
static PyObject *sse_cmpunord_ss(PyObject *self, PyObject *args)
{
    SPBASE(_mm_cmpunord_ss)
}

/* shuffle */
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

#define shuffle_pi16_docstring "Shuffle 16-bit integers in a using the control in imm8"
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

#define ADD_SSE_METHOD(METH) ADD_PREFIX_METHOD(METH, sse_, METH ## _docstring)
static PyMethodDef SSEMethods[] = {
    ADD_SSE_METHOD(addps),
    ADD_SSE_METHOD(addss),
    ADD_SSE_METHOD(andps),
    ADD_SSE_METHOD(andnot_ps),
    ADD_SSE_METHOD(avgpu16),
    ADD_SSE_METHOD(avgpu8),
    ADD_SSE_METHOD(cmpeq_ps),
    ADD_SSE_METHOD(cmpeq_ss),
    ADD_SSE_METHOD(cmpge_ps),
    ADD_SSE_METHOD(cmpge_ss),  
    ADD_SSE_METHOD(cmpgt_ps),
    ADD_SSE_METHOD(cmpgt_ss),
    ADD_SSE_METHOD(cmple_ps),
    ADD_SSE_METHOD(cmple_ss),  
    ADD_SSE_METHOD(cmplt_ps),
    ADD_SSE_METHOD(cmplt_ss),
    ADD_SSE_METHOD(cmpneq_ps),
    ADD_SSE_METHOD(cmpneq_ss),
    ADD_SSE_METHOD(cmpnge_ps),
    ADD_SSE_METHOD(cmpnge_ss),  
    ADD_SSE_METHOD(cmpngt_ps),
    ADD_SSE_METHOD(cmpngt_ss),
    ADD_SSE_METHOD(cmpnle_ps),
    ADD_SSE_METHOD(cmpnle_ss),  
    ADD_SSE_METHOD(cmpnlt_ps),
    ADD_SSE_METHOD(cmpnlt_ss),
    ADD_SSE_METHOD(cmpord_ps),
    ADD_SSE_METHOD(cmpord_ss),
    ADD_SSE_METHOD(cmpunord_ss),
    ADD_SSE_METHOD(cmpunord_ps),
    ADD_SSE_METHOD(shuffle_pi16),
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
