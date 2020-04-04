#include <stdint.h>
#include <Python.h>
#include "sseintrin.h"
 
/** TODO:
 * Adds epu needs validation of unsigned ints
 */

#define ADD_SSE2_METHOD(METH, DOCS) ADD_PREFIX_METHOD(METH, sse2_, DOCS)
/* Add */
static PyObject *sse2_add_epi16(PyObject *self, PyObject *args)
{
    BASE16(_mm_add_epi16)
}

static PyObject *sse2_add_epi32(PyObject *self, PyObject *args)
{
    BASE32(_mm_add_epi32)
}

static PyObject *sse2_add_epi64(PyObject *self, PyObject *args)
{
    BASE64(_mm_add_epi64)
}

static PyObject *sse2_add_epi8(PyObject *self, PyObject *args)
{
    BASE8(_mm_add_epi8)
}

static PyObject *sse2_add_si64(PyObject *self, PyObject *args)
{
    int64_t x, y;
    if (!PyArg_ParseTuple(args, "ll", &x, &y))
        return NULL;
    __m64 a = set__m64(x), b = set__m64(y), r;
    r = _mm_add_si64(a,b);
    return Py_BuildValue("l", set_int64_t(r));
}

/* Adds epi*/
static PyObject *sse2_adds_epi16(PyObject *self, PyObject *args)
{
    BASE16(_mm_adds_epi16)
}

static PyObject *sse2_adds_epi8(PyObject *self, PyObject *args)
{
    BASE8(_mm_adds_epi8)
}

/* Adds epu */
static PyObject *sse2_adds_epu16(PyObject *self, PyObject *args)
{
    BASE16(_mm_adds_epu16)
}

static PyObject *sse2_adds_epu8(PyObject *self, PyObject *args)
{
    BASE8(_mm_adds_epu8)
}


/* and_si128 */
static PyObject *sse2_and_si128_64i(PyObject *self, PyObject *args)
{
    BASE64(_mm_and_si128)
}

static PyObject *sse2_and_si128_32i(PyObject *self, PyObject *args)
{
    BASE32(_mm_and_si128)
}

static PyObject *sse2_and_si128_16i(PyObject *self, PyObject *args)
{
    BASE16(_mm_and_si128)
}

static PyObject *sse2_and_si128_8i(PyObject *self, PyObject *args)
{
    BASE8(_mm_and_si128)
}

/* andnot_si128 */
static PyObject *sse2_andnot_si128_64i(PyObject *self, PyObject *args)
{
    BASE64(_mm_andnot_si128)
}

static PyObject *sse2_andnot_si128_32i(PyObject *self, PyObject *args)
{
    BASE32(_mm_andnot_si128)
}

static PyObject *sse2_andnot_si128_16i(PyObject *self, PyObject *args)
{
    BASE16(_mm_andnot_si128)
}

static PyObject *sse2_andnot_si128_8i(PyObject *self, PyObject *args)
{
    BASE8(_mm_andnot_si128)
}

/* Average */
static PyObject *sse2_avg_epu16(PyObject *self, PyObject *args)
{
    BASE16(_mm_avg_epu16)
}

static PyObject *sse2_avg_epu8(PyObject *self, PyObject *args)
{
    BASE8(_mm_avg_epu8)
}

/* Compare Equal */
static PyObject *sse2_cmpeq_epi16(PyObject *self, PyObject *args)
{
    BASE16(_mm_cmpeq_epi16)
}

static PyObject *sse2_cmpeq_epi32(PyObject *self, PyObject *args)
{
    BASE32(_mm_cmpeq_epi32)
}

static PyObject *sse2_cmpeq_epi8(PyObject *self, PyObject *args)
{
    BASE8(_mm_cmpeq_epi8)
}

/* Compare greater than */
static PyObject *sse2_cmpgt_epi16(PyObject *self, PyObject *args)
{
    BASE16(_mm_cmpgt_epi16) 
}

static PyObject *sse2_cmpgt_epi32(PyObject *self, PyObject *args)
{
    BASE32(_mm_cmpgt_epi32)
}

static PyObject *sse2_cmpgt_epi8(PyObject *self, PyObject *args)
{
    BASE8(_mm_cmpgt_epi8)    
}

/* Compare less than */
static PyObject *sse2_cmplt_epi16(PyObject *self, PyObject *args)
{
    BASE16(_mm_cmplt_epi16) 
}

static PyObject *sse2_cmplt_epi32(PyObject *self, PyObject *args)
{
    BASE32(_mm_cmplt_epi32)
}

static PyObject *sse2_cmplt_epi8(PyObject *self, PyObject *args)
{
    BASE8(_mm_cmplt_epi8)    
}
/* sqrt */
static PyObject *sse2_sqrt_pd(PyObject *self, PyObject *args)
{
    BASEDB(_mm_sqrt_pd)
}

/* Subtract */
static PyObject *sse2_sub_epi16(PyObject *self, PyObject *args)
{
    BASE16(_mm_sub_epi16) 
}

static PyObject *sse2_sub_epi32(PyObject *self, PyObject *args)
{
    BASE32(_mm_sub_epi32)
}

static PyObject *sse2_sub_epi64(PyObject *self, PyObject *args)
{
    BASE64(_mm_sub_epi64)
}

static PyObject *sse2_sub_epi8(PyObject *self, PyObject *args)
{
    BASE8(_mm_sub_epi8)    
}

static PyObject *sse2_sub_si64(PyObject *self, PyObject *args)
{
    int64_t x, y;
    if (!PyArg_ParseTuple(args, "ll", &x, &y))
        return NULL;
    __m64 a = set__m64(x), b = set__m64(y), r;
    r = _mm_sub_si64(a,b);
    return Py_BuildValue("l", set_int64_t(r));
}
/* Subs epi*/
static PyObject *sse2_subs_epi16(PyObject *self, PyObject *args)
{
    BASE16(_mm_subs_epi16)
}

static PyObject *sse2_subs_epi8(PyObject *self, PyObject *args)
{
    BASE8(_mm_subs_epi8)
}

/* Subs epu */
static PyObject *sse2_subs_epu16(PyObject *self, PyObject *args)
{
    BASE16(_mm_subs_epu16)
}

static PyObject *sse2_subs_epu8(PyObject *self, PyObject *args)
{
    BASE8(_mm_subs_epu8)
}


static PyMethodDef SSE2Methods[] = {
    ADD_SSE2_METHOD( add_epi16        , "Add packed 16-bit integers in a and b"),
    ADD_SSE2_METHOD( add_epi32        , "Add packed 32-bit integers in a and b"),
    ADD_SSE2_METHOD( add_epi64        , "Add packed 64-bit integers in a and b"),
    ADD_SSE2_METHOD( add_epi8         , "Add packed 8-bit integers in a and b"),
    ADD_SSE2_METHOD( add_si64         , "Add 64-bit integers a and b"),
    ADD_SSE2_METHOD( adds_epi16       , "Adds 16-bit integers using saturation"),
    ADD_SSE2_METHOD( adds_epi8        , "Adds 8-bit integers using saturation"),
    ADD_SSE2_METHOD( adds_epu16       , "Adds 16-bit unsigned integers using saturation"),
    ADD_SSE2_METHOD( adds_epu8        , "Adds 8-bit unsigned integers using saturation"),
    ADD_SSE2_METHOD( and_si128_64i    , "Compute the bitwise AND of 128 bits representing 64bit integer data in a and b"),
    ADD_SSE2_METHOD( and_si128_32i    , "Compute the bitwise AND of 128 bits representing 32bit integer data in a and b"),
    ADD_SSE2_METHOD( and_si128_16i    , "Compute the bitwise AND of 128 bits representing 16bit integer data in a and b"),
    ADD_SSE2_METHOD( and_si128_8i     , "Compute the bitwise AND of 128 bits representing 8bit integer data in a and b"),    
    ADD_SSE2_METHOD( andnot_si128_64i , "Compute bitwise NOT of 128 bits representing 64bit integer data"),
    ADD_SSE2_METHOD( andnot_si128_32i , "Compute bitwise NOT of 128 bits representing 32bit integer data"),
    ADD_SSE2_METHOD( andnot_si128_16i , "Compute bitwise NOT of 128 bits representing 16bit integer data"),
    ADD_SSE2_METHOD( andnot_si128_8i  , "Compute bitwise NOT of 128 bits representing 8bit integer data"),
    ADD_SSE2_METHOD( avg_epu16        , "Average packed unsigned 16bit integers in a and b"),
    ADD_SSE2_METHOD( avg_epu8         , "Average packed unsigned 8bit integers in a and b"),    
    ADD_SSE2_METHOD( cmpeq_epi16      , "Compare packed 16-bit integers in a and b for equality"),
    ADD_SSE2_METHOD( cmpeq_epi32      , "Compare packed 32-bit integers in a and b for equality"),
    ADD_SSE2_METHOD( cmpeq_epi8       , "Compare packed 8-bit integers in a and b for equality"),
    ADD_SSE2_METHOD( cmplt_epi16      , "Compare packed 16-bit integers in a and b for less than"),
    ADD_SSE2_METHOD( cmplt_epi32      , "Compare packed 32-bit integers in a and b for less than"),
    ADD_SSE2_METHOD( cmplt_epi8       , "Compare packed 8-bit integers in a and b for less than"),
    ADD_SSE2_METHOD( cmpgt_epi16      , "Compare packed 16-bit integers in a and b for greater than"),
    ADD_SSE2_METHOD( cmpgt_epi32      , "Compare packed 32-bit integers in a and b for greater than"),
    ADD_SSE2_METHOD( cmpgt_epi8       , "Compare packed 8-bit integers in a and b for greater than"),
    ADD_SSE2_METHOD( sqrt_pd          , "Compute square root of packed double-precision (64bit) floating point elements"),
    ADD_SSE2_METHOD( subs_epu8        , "Subtract 8-bit unsigned integers using saturation"),
    ADD_SSE2_METHOD( subs_epu16       , "Subtract 16-bit unsigned integers using saturation"),
    ADD_SSE2_METHOD( subs_epi8        , "Subtract 8-bit integers using saturation"),
    ADD_SSE2_METHOD( subs_epi16       , "Subtract 16-bit integers using saturation"),
    ADD_SSE2_METHOD( sub_si64         , "Subtract 64-bit integers a and b"),
    ADD_SSE2_METHOD( sub_epi64        , "Subtract packed 64-bit integers in a and b"),
    ADD_SSE2_METHOD( sub_epi32        , "Subtract packed 32-bit integers in a and b"),
    ADD_SSE2_METHOD( sub_epi16        , "Subtract packed 16-bit integers in a and b"),
    ADD_SSE2_METHOD( sub_epi8         , "Subtract packed 8-bit integers in a and b"),
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef sse2module = {
    PyModuleDef_HEAD_INIT,
    "sse2intrin",
    "Python wrapper for SSE2 intrinsics",
    -1,
    SSE2Methods
};


PyMODINIT_FUNC PyInit_sse2intrin(void){
    PyObject *module = PyModule_Create(&sse2module);
    return module;
}
