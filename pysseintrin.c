#include <xmmintrin.h>
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

#define BASE(base, pyobj, intrinsic) \
    __m128i r, *n = base(self, args);\
    if(n == NULL)                    \
        return NULL;                 \
    r = intrinsic(n[0], n[1]);       \
    return pyobj(&r, n); 

#define BASE8(intrinsic) BASE(sse_basei8, sse_pyobj_basei8, intrinsic)
#define BASE16(intrinsic) BASE(sse_basei16, sse_pyobj_basei16, intrinsic)
#define BASE32(intrinsic) BASE(sse_basei32, sse_pyobj_basei32, intrinsic)

#define BASE64(intrinsic)                                            \
    int64_t aa[2], ab[2];                                             \
    int64_t *ar;                                                      \
    __m128i n, a ,b;                                                  \
    if(!PyArg_ParseTuple(args, "llll", ASE(&aa, 0), ASE(&ab, 0))){    \
        return NULL;                                                  \
    }                                                                 \
    a = _mm_set_epi64x(ASE(aa, 0));                                   \
    b = _mm_set_epi64x(ASE(ab, 0));                                   \
    n = intrinsic(a, b);                                              \
    ar = (int64_t *) &n;                                              \
    return Py_BuildValue("[ll]", ASE(ar, 0));

/** TODO:
 * Windows support seems to be broken. Could be my fault.
 * Adds epu needs validation of unsigned ints
 */

/* Base 32bit int */
static inline __m128i *sse_basei32(PyObject *self, PyObject *args)
{
    int32_t aa[4], ab[4];
    __m128i *n = malloc(sizeof(__m128i)*N_RET_SZ);
    if(!PyArg_ParseTuple(args, "iiiiiiii", A03(&aa), A03(&ab))){
        return NULL;
    }
    n[0] = _mm_set_epi32(A03(aa));
    n[1] = _mm_set_epi32(A03(ab));
    return n;
}

static inline PyObject *sse_pyobj_basei32(__m128i *r, __m128i *n)
{
    int32_t *ar = (int32_t *) r;
    PyObject *obj = Py_BuildValue("[iiii]", A03(ar));
    free(n);
    return obj;
}

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

#ifndef _WIN32
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
#endif
/* Average */
static PyObject *sse_avgepu16(PyObject *self, PyObject *args)
{
    BASE16(_mm_avg_epu16)
}

#ifndef _WIN32
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
#endif

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

/* si64 */
#ifndef _WIN32
static PyObject *sse_addsi64(PyObject *self, PyObject *args)
{
    int64_t x, y;
    if (!PyArg_ParseTuple(args, "ll", &x, &y))
        return NULL;
    __m64 a = (__m64) x, b = (__m64) y, r;
    r = _mm_add_si64(a,b);
    return Py_BuildValue("l", (int64_t) r);
}

static PyObject *sse_subsi64(PyObject *self, PyObject *args)
{
    int64_t x, y;
    if (!PyArg_ParseTuple(args, "ll", &x, &y))
        return NULL;
    __m64 a = (__m64) x, b = (__m64) y, r;
    r = _mm_sub_si64(a,b);
    return Py_BuildValue("l", (int64_t) r);
}
#endif

static PyMethodDef SSEMethods[] = {
    {"adds_epu8", sse_addsepu8, METH_VARARGS, "Adds 8-bit unsigned integers using saturation"},
    {"adds_epu16", sse_addsepu16, METH_VARARGS, "Adds 16-bit unsigned integers using saturation"},
    {"adds_epi8", sse_addsepi8, METH_VARARGS, "Adds 8-bit integers using saturation"},
    {"adds_epi16", sse_addsepi16, METH_VARARGS, "Adds 16-bit integers using saturation"},
#ifndef _WIN32
    {"sub_si64", sse_subsi64, METH_VARARGS, "Subtract 64-bit integers a and b"},
    {"add_si64", sse_addsi64, METH_VARARGS, "Add 64-bit integers a and b"},
#endif
    {"sub_epi64", sse_subepi64, METH_VARARGS, "Subtract packed 64-bit integers in a and b"},
    {"sub_epi32", sse_subepi32, METH_VARARGS, "Subtract packed 32-bit integers in a and b"},
    {"sub_epi16", sse_subepi16, METH_VARARGS, "Subtract packed 16-bit integers in a and b"},
    {"sub_epi8", sse_subepi8, METH_VARARGS, "Subtract packed 8-bit integers in a and b"},
    {"cmplt_epi32", sse_cmpltepi32, METH_VARARGS, "Compare packed 32-bit integers in a and b for less than"},
    {"cmplt_epi16", sse_cmpltepi16, METH_VARARGS, "Compare packed 16-bit integers in a and b for less than"},
    {"cmplt_epi8", sse_cmpltepi8, METH_VARARGS, "Compare packed 8-bit integers in a and b for less than"},
    {"cmpgt_epi32", sse_cmpgtepi32, METH_VARARGS, "Compare packed 32-bit integers in a and b for greater than"},
    {"cmpgt_epi16", sse_cmpgtepi16, METH_VARARGS, "Compare packed 16-bit integers in a and b for greater than"},
    {"cmpgt_epi8", sse_cmpgtepi8, METH_VARARGS, "Compare packed 8-bit integers in a and b for greater than"},
    {"cmpeq_epi32", sse_cmpeqepi32, METH_VARARGS, "Compare packed 32-bit integers in a and b for equality"},
    {"cmpeq_epi16", sse_cmpeqepi16, METH_VARARGS, "Compare packed 16-bit integers in a and b for equality"},
    {"cmpeq_epi8", sse_cmpeqepi8, METH_VARARGS, "Compare packed 8-bit integers in a and b for equality"},
#ifndef _WIN32
    {"andnot_si128_64i", sse_andnot_si128_64, METH_VARARGS, "Compute bitwise NOT of 128 bits representing 64bit integer data"},
    {"andnot_si128_32i", sse_andnot_si128_32, METH_VARARGS, "Compute bitwise NOT of 128 bits representing 32bit integer data"},
    {"andnot_si128_16i", sse_andnot_si128_16, METH_VARARGS, "Compute bitwise NOT of 128 bits representing 16bit integer data"},
    {"andnot_si128_8i", sse_andnot_si128_8, METH_VARARGS, "Compute bitwise NOT of 128 bits representing 8bit integer data"},
    {"and_si128_64i", sse_and_si128_64, METH_VARARGS, "Compute the bitwise AND of 128 bits representing 64bit integer data in a and b"},
    {"and_si128_32i", sse_and_si128_32, METH_VARARGS, "Compute the bitwise AND of 128 bits representing 32bit integer data in a and b"},
    {"and_si128_16i", sse_and_si128_16, METH_VARARGS, "Compute the bitwise AND of 128 bits representing 16bit integer data in a and b"},
    {"and_si128_8i", sse_and_si128_8, METH_VARARGS, "Compute the bitwise AND of 128 bits representing 8bit integer data in a and b"},
    {"avg_pu16", sse_avgpu16, METH_VARARGS, "Average packed unsigned 16bit integers in a and b"},
    {"avg_pu8", sse_avgpu8, METH_VARARGS, "Average packed unsigned 8bit integers in a and b"},
#endif
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

PyMODINIT_FUNC PyInit_pysseintrin(void){
    return PyModule_Create(&ssemodule);
}
