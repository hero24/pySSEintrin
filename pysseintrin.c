#include <stdint.h>
#include <Python.h>
#include "pysseintrin.h"

 
/** TODO:
 * Windows support seems to be broken. Could be my fault.
 * Adds epu needs validation of unsigned ints
 */


/* Add */
static PyObject *sse_addepi8(PyObject *self, PyObject *args)
{
    BASE8(_mm_add_epi8)
}

static PyObject *sse_addepi16(PyObject *self, PyObject *args)
{
    BASE16(_mm_add_epi16)
}

static PyObject *sse_addepi32(PyObject *self, PyObject *args)
{
    BASE32(_mm_add_epi32)
}

static PyObject *sse_addepi64(PyObject *self, PyObject *args)
{
    BASE64(_mm_add_epi64)
}

/* Adds epi*/
static PyObject *sse_addsepi8(PyObject *self, PyObject *args)
{
    BASE8(_mm_adds_epi8)
}

static PyObject *sse_addsepi16(PyObject *self, PyObject *args)
{
    BASE16(_mm_adds_epi16)
}

/* Adds epu */
static PyObject *sse_addsepu8(PyObject *self, PyObject *args)
{
    BASE8(_mm_adds_epu8)
}

static PyObject *sse_addsepu16(PyObject *self, PyObject *args)
{
    BASE16(_mm_adds_epu16)
}

/* and_si128 */
static PyObject *sse_and_si128_64(PyObject *self, PyObject *args)
{
    BASE64(_mm_and_si128)
}

static PyObject *sse_and_si128_32(PyObject *self, PyObject *args)
{
    BASE32(_mm_and_si128)
}

static PyObject *sse_and_si128_16(PyObject *self, PyObject *args)
{
    BASE16(_mm_and_si128)
}

static PyObject *sse_and_si128_8(PyObject *self, PyObject *args)
{
    BASE8(_mm_and_si128)
}

/* andnot_si128 */
static PyObject *sse_andnot_si128_64(PyObject *self, PyObject *args)
{
    BASE64(_mm_andnot_si128)
}

static PyObject *sse_andnot_si128_32(PyObject *self, PyObject *args)
{
    BASE32(_mm_andnot_si128)
}

static PyObject *sse_andnot_si128_16(PyObject *self, PyObject *args)
{
    BASE16(_mm_andnot_si128)
}

static PyObject *sse_andnot_si128_8(PyObject *self, PyObject *args)
{
    BASE8(_mm_andnot_si128)
}

/* Average */
static PyObject *sse_avgepu16(PyObject *self, PyObject *args)
{
    BASE16(_mm_avg_epu16)
}

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

static PyObject *sse_avgepu8(PyObject *self, PyObject *args)
{
    BASE8(_mm_avg_epu8)
}

/* Compare Equal */
static PyObject *sse_cmpeqepi32(PyObject *self, PyObject *args)
{
    BASE32(_mm_cmpeq_epi32)
}

static PyObject *sse_cmpeqepi16(PyObject *self, PyObject *args)
{
    BASE16(_mm_cmpeq_epi16)
}

static PyObject *sse_cmpeqepi8(PyObject *self, PyObject *args)
{
    BASE8(_mm_cmpeq_epi8)
}

/* Compare greater than */
static PyObject *sse_cmpgtepi32(PyObject *self, PyObject *args)
{
    BASE32(_mm_cmpgt_epi32)
}

static PyObject *sse_cmpgtepi16(PyObject *self, PyObject *args)
{
    BASE16(_mm_cmpgt_epi16) 
}

static PyObject *sse_cmpgtepi8(PyObject *self, PyObject *args)
{
    BASE8(_mm_cmpgt_epi8)    
}

/* Compare less than */
static PyObject *sse_cmpltepi32(PyObject *self, PyObject *args)
{
    BASE32(_mm_cmplt_epi32)
}

static PyObject *sse_cmpltepi16(PyObject *self, PyObject *args)
{
    BASE16(_mm_cmplt_epi16) 
}

static PyObject *sse_cmpltepi8(PyObject *self, PyObject *args)
{
    BASE8(_mm_cmplt_epi8)    
}

/* Subtract */
static PyObject *sse_subepi64(PyObject *self, PyObject *args)
{
    BASE64(_mm_sub_epi64)
}

static PyObject *sse_subepi32(PyObject *self, PyObject *args)
{
    BASE32(_mm_sub_epi32)
}

static PyObject *sse_subepi16(PyObject *self, PyObject *args)
{
    BASE16(_mm_sub_epi16) 
}

static PyObject *sse_subepi8(PyObject *self, PyObject *args)
{
    BASE8(_mm_sub_epi8)    
}

/* Subs epi*/
static PyObject *sse_subsepi8(PyObject *self, PyObject *args)
{
    BASE8(_mm_subs_epi8)
}

static PyObject *sse_subsepi16(PyObject *self, PyObject *args)
{
    BASE16(_mm_subs_epi16)
}

/* Subs epu */
static PyObject *sse_subsepu8(PyObject *self, PyObject *args)
{
    BASE8(_mm_subs_epu8)
}

static PyObject *sse_subsepu16(PyObject *self, PyObject *args)
{
    BASE16(_mm_subs_epu16)
}

/* si64 */
static PyObject *sse_addsi64(PyObject *self, PyObject *args)
{
    int64_t x, y;
    if (!PyArg_ParseTuple(args, "ll", &x, &y))
        return NULL;
    __m64 a = set__m64(x), b = set__m64(y), r;
    r = _mm_add_si64(a,b);
    return Py_BuildValue("l", set_int64_t(r));
}

static PyObject *sse_subsi64(PyObject *self, PyObject *args)
{
    int64_t x, y;
    if (!PyArg_ParseTuple(args, "ll", &x, &y))
        return NULL;
    __m64 a = set__m64(x), b = set__m64(y), r;
    r = _mm_sub_si64(a,b);
    return Py_BuildValue("l", set_int64_t(r));
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

/* MXCSR control regiser functions */
#define MXCSR_CTRL_BASE(CTRL)  unsigned int mode;                      \
                               if(!PyArg_ParseTuple(args, "i", &mode)) \
                                        return NULL;                   \
                               CTRL(mode);                             \
                               Py_RETURN_NONE;

static PyObject *sse_setcsr(PyObject *self, PyObject *args)
{
    MXCSR_CTRL_BASE(_mm_setcsr)
}

static PyObject *sse_set_rnd_mode(PyObject *self, PyObject *args)
{
    /*
    _MM_ROUND_NEAREST, _MM_ROUND_DOWN, _MM_ROUND_UP, _MM_ROUND_TOWARD_ZERO
    */
    MXCSR_CTRL_BASE(_MM_SET_ROUNDING_MODE)
}

static PyObject *sse_csfr_sfzm(PyObject *self, PyObject *args)
{    
    /* _MM_FLUSH_ZERO_ON, _MM_FLUSH_ZERO_OFF */
    MXCSR_CTRL_BASE(_MM_SET_FLUSH_ZERO_MODE)
}

static PyObject *sse_csfr_sexcst(PyObject *self, PyObject *args)
{
    /* 
    _MM_EXCEPT_INVALID, _MM_EXCEPT_DIV_ZERO, _MM_EXCEPT_DENORM,
    _MM_EXCEPT_OVERFLOW, _MM_EXCEPT_UNDERFLOW, _MM_EXCEPT_INEXACT
    */
    MXCSR_CTRL_BASE(_MM_SET_EXCEPTION_STATE)
}

static PyObject *sse_csfr_sexcmsk(PyObject *self, PyObject *args)
{
    /*
    _MM_MASK_INVALID, _MM_MASK_DIV_ZERO, _MM_MASK_DENORM,
    _MM_MASK_OVERFLOW, _MM_MASK_UNDERFLOW, _MM_MASK_INEXACT
    */
    MXCSR_CTRL_BASE(_MM_SET_EXCEPTION_MASK)
}

/* mathematical functions pd */
static PyObject *sse_sqrtpd(PyObject *self, PyObject *args)
{
    BASEDB(_mm_sqrt_pd)
}

static PyMethodDef SSEMethods[] = {
    {"set_exception_mask"  , sse_csfr_sexcmsk,     METH_VARARGS, "Set the exception mask bits of the MXCSR control and status register"},
    {"set_exception_state" , sse_csfr_sexcst,      METH_VARARGS, "Set the exception state bits of the MXCSR control and status register"},
    {"set_flush_zero_mode" , sse_csfr_sfzm,        METH_VARARGS, "Set the flush zero bits of the MXCSR control and status register"},
    {"set_rounding_mode"   , sse_set_rnd_mode,     METH_VARARGS, "Set the rounding mode bits of the MXCSR control and status register to the value in unsigned 32-bit integer a"},
    {"setcsr"              , sse_setcsr,           METH_VARARGS, "Set the MXCSR control and status register with the value in unsigned 32-bit integer a."},
    {"shuffle_pi16"        , sse_shuffle_pi16,     METH_VARARGS, "Shuffle 16-bit integers in a using the control in imm8"},
    {"sqrt_pd"             , sse_sqrtpd,           METH_VARARGS, "Compute square root of packed double-precision (64bit) floating point elements"},
    {"subs_epu8"           , sse_subsepu8,         METH_VARARGS, "Subtract 8-bit unsigned integers using saturation"},
    {"subs_epu16"          , sse_subsepu16,        METH_VARARGS, "Subtract 16-bit unsigned integers using saturation"},
    {"subs_epi8"           , sse_subsepi8,         METH_VARARGS, "Subtract 8-bit integers using saturation"},
    {"subs_epi16"          , sse_subsepi16,        METH_VARARGS, "Subtract 16-bit integers using saturation"},
    {"adds_epu8"           , sse_addsepu8,         METH_VARARGS, "Adds 8-bit unsigned integers using saturation"},
    {"adds_epu16"          , sse_addsepu16,        METH_VARARGS, "Adds 16-bit unsigned integers using saturation"},
    {"adds_epi8"           , sse_addsepi8,         METH_VARARGS, "Adds 8-bit integers using saturation"},
    {"adds_epi16"          , sse_addsepi16,        METH_VARARGS, "Adds 16-bit integers using saturation"},
    {"sub_si64"            , sse_subsi64,          METH_VARARGS, "Subtract 64-bit integers a and b"},
    {"add_si64"            , sse_addsi64,          METH_VARARGS, "Add 64-bit integers a and b"},
    {"sub_epi64"           , sse_subepi64,         METH_VARARGS, "Subtract packed 64-bit integers in a and b"},
    {"sub_epi32"           , sse_subepi32,         METH_VARARGS, "Subtract packed 32-bit integers in a and b"},
    {"sub_epi16"           , sse_subepi16,         METH_VARARGS, "Subtract packed 16-bit integers in a and b"},
    {"sub_epi8"            , sse_subepi8,          METH_VARARGS, "Subtract packed 8-bit integers in a and b"},
    {"cmplt_epi32"         , sse_cmpltepi32,       METH_VARARGS, "Compare packed 32-bit integers in a and b for less than"},
    {"cmplt_epi16"         , sse_cmpltepi16,       METH_VARARGS, "Compare packed 16-bit integers in a and b for less than"},
    {"cmplt_epi8"          , sse_cmpltepi8,        METH_VARARGS, "Compare packed 8-bit integers in a and b for less than"},
    {"cmpgt_epi32"         , sse_cmpgtepi32,       METH_VARARGS, "Compare packed 32-bit integers in a and b for greater than"},
    {"cmpgt_epi16"         , sse_cmpgtepi16,       METH_VARARGS, "Compare packed 16-bit integers in a and b for greater than"},
    {"cmpgt_epi8"          , sse_cmpgtepi8,        METH_VARARGS, "Compare packed 8-bit integers in a and b for greater than"},
    {"cmpeq_epi32"         , sse_cmpeqepi32,       METH_VARARGS, "Compare packed 32-bit integers in a and b for equality"},
    {"cmpeq_epi16"         , sse_cmpeqepi16,       METH_VARARGS, "Compare packed 16-bit integers in a and b for equality"},
    {"cmpeq_epi8"          , sse_cmpeqepi8,        METH_VARARGS, "Compare packed 8-bit integers in a and b for equality"},
    {"andnot_si128_64i"    , sse_andnot_si128_64,  METH_VARARGS, "Compute bitwise NOT of 128 bits representing 64bit integer data"},
    {"andnot_si128_32i"    , sse_andnot_si128_32,  METH_VARARGS, "Compute bitwise NOT of 128 bits representing 32bit integer data"},
    {"andnot_si128_16i"    , sse_andnot_si128_16,  METH_VARARGS, "Compute bitwise NOT of 128 bits representing 16bit integer data"},
    {"andnot_si128_8i"     , sse_andnot_si128_8,   METH_VARARGS, "Compute bitwise NOT of 128 bits representing 8bit integer data"},
    {"and_si128_64i"       , sse_and_si128_64,     METH_VARARGS, "Compute the bitwise AND of 128 bits representing 64bit integer data in a and b"},
    {"and_si128_32i"       , sse_and_si128_32,     METH_VARARGS, "Compute the bitwise AND of 128 bits representing 32bit integer data in a and b"},
    {"and_si128_16i"       , sse_and_si128_16,     METH_VARARGS, "Compute the bitwise AND of 128 bits representing 16bit integer data in a and b"},
    {"and_si128_8i"        , sse_and_si128_8,      METH_VARARGS, "Compute the bitwise AND of 128 bits representing 8bit integer data in a and b"},
    {"avg_pu16"            , sse_avgpu16,          METH_VARARGS, "Average packed unsigned 16bit integers in a and b"},
    {"avg_pu8"             , sse_avgpu8,           METH_VARARGS, "Average packed unsigned 8bit integers in a and b"},
    {"avg_epu16"           , sse_avgepu16,         METH_VARARGS, "Average packed unsigned 16bit integers in a and b"},
    {"avg_epu8"            , sse_avgepu8,          METH_VARARGS, "Average packed unsigned 8bit integers in a and b"},
    {"add_epi64"           , sse_addepi64,         METH_VARARGS, "Add packed 64-bit integers in a and b"},
    {"add_epi32"           , sse_addepi32,         METH_VARARGS, "Add packed 32-bit integers in a and b"},
    {"add_epi16"           , sse_addepi16,         METH_VARARGS, "Add packed 16-bit integers in a and b"},
    {"add_epi8"            , sse_addepi8,          METH_VARARGS, "Add packed 8-bit integers in a and b"},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef ssemodule = {
    PyModuleDef_HEAD_INIT,
    "pysseintrin",
    "Python wrapper for sse intrinsics",
    -1,
    SSEMethods
};

static struct SSEConstants constants[] = {    
    {"_MM_ROUND_NEAREST",     "i", _MM_ROUND_NEAREST},
    {"_MM_ROUND_DOWN",        "i", _MM_ROUND_DOWN},
    {"_MM_ROUND_UP",          "i", _MM_ROUND_UP},
    {"_MM_ROUND_TOWARD_ZERO", "i", _MM_ROUND_TOWARD_ZERO},
    {"_MM_EXCEPT_INVALID",    "i", _MM_EXCEPT_INVALID,},
    {"_MM_EXCEPT_DIV_ZERO",   "i", _MM_EXCEPT_DIV_ZERO},
    {"_MM_EXCEPT_DENORM",     "i", _MM_EXCEPT_DENORM},
    {"_MM_EXCEPT_OVERFLOW",   "i", _MM_EXCEPT_OVERFLOW},
    {"_MM_EXCEPT_UNDERFLOW",  "i", _MM_EXCEPT_UNDERFLOW},
    {"_MM_EXCEPT_INEXACT",    "i", _MM_EXCEPT_INEXACT},
    {"_MM_MASK_INVALID",      "i", _MM_MASK_INVALID,},
    {"_MM_MASK_DIV_ZERO",     "i", _MM_MASK_DIV_ZERO},
    {"_MM_MASK_DENORM",       "i", _MM_MASK_DENORM},
    {"_MM_MASK_OVERFLOW",     "i", _MM_MASK_OVERFLOW},
    {"_MM_MASK_UNDERFLOW",    "i", _MM_MASK_UNDERFLOW},
    {"_MM_MASK_INEXACT",      "i", _MM_MASK_INEXACT},
    {NULL, NULL, 0}
};

PyMODINIT_FUNC PyInit_pysseintrin(void){
    PyObject *module = PyModule_Create(&ssemodule);
    addobj(module, constants);
    return module;
}
