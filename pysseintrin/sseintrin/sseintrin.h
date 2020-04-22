#ifndef __PYSSEINTRIN_H
#define __PYSSEINTRIN_H

#if defined(_MSC_VER)
#include <intrin.h>
#else
#include <x86intrin.h>
#endif
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

#define BASEDB(intrinsic)                         \
    __m128d db, *dbp = sse_based128(self, args);  \
    double* dv;                                   \
    if(!dbp)                                      \
        return NULL;                              \
    db = intrinsic(*dbp);                         \
    dv = (double *) &db;                          \
    free(dbp);                                    \
    return Py_BuildValue("[dd]", dv[0], dv[1]);

#define SPBASE(intrinsic)                                         \
    float aa[4], ab[4], *ar;                                      \
    if (!PyArg_ParseTuple(args, "ffffffff", A03(&aa), A03(&ab)))  \
        return NULL;                                              \
    __m128 a = _mm_set_ps(A03(aa)), b = _mm_set_ps(A03(ab)), r;   \
    r = intrinsic(a, b);                                          \
    ar = (float *) &r;                                            \
    return Py_BuildValue("[ffff]", A03(ar));                 

#define RBOOL_SPBASE(intrinsic)                                   \
    float aa[4], ab[4]; int r;                                    \
    if (!PyArg_ParseTuple(args, "ffffffff", A03(&aa), A03(&ab)))  \
        return NULL;                                              \
    __m128 a = _mm_set_ps(A03(aa)), b = _mm_set_ps(A03(ab));      \
    r = intrinsic(a, b);                                          \
    return Py_BuildValue("O", r ? Py_True : Py_False);    

#define SINGLE128_SPBASE(intrinsic)                               \
    float aa[4], *ar;                                             \
    if (!PyArg_ParseTuple(args, "ffff", A03(&aa)))                \
        return NULL;                                              \
    __m128 a = _mm_set_ps(A03(aa)), r;                            \
    r = intrinsic(a);                                             \
    ar = (float *) &r;                                            \
    return Py_BuildValue("[ffff]", A03(ar));       

#define M64_BASE_M64M64(intrinsic)                                 \
    int16_t aa[4], ab[4], *ar;                                     \
    if(!PyArg_ParseTuple(args, "iiiiiiii", A03(&aa), A03(&ab)))    \
        return NULL;                                               \
    __m64 a = _mm_set_pi16(A03(aa)), b = _mm_set_pi16(A03(ab)), r; \
    r = intrinsic(a, b);                                           \
    ar = (int16_t *) &r;                                           \
    _mm_empty();                                                   \
    return Py_BuildValue("[iiii]", A03(ar));                       \

#define ADD_PREFIX_METHOD(METH, PREFIX, DOCS) {#METH, PREFIX ## METH, METH_VARARGS, DOCS}

/* Base double 128d */
inline __m128d *sse_based128(PyObject *self, PyObject *args)
{
    double a, b;
    __m128d *db;
    if(!PyArg_ParseTuple(args, "dd", &a, &b))
        return NULL;
    db = malloc(sizeof(__m128d));
    *db = _mm_set_pd(a, b);
    return db;
}

/* Base 32bit int */
inline __m128i *sse_basei32(PyObject *self, PyObject *args)
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

inline PyObject *sse_pyobj_basei32(__m128i *r, __m128i *n)
{
    int32_t *ar = (int32_t *) r;
    PyObject *obj = Py_BuildValue("[iiii]", A03(ar));
    free(n);
    return obj;
}

/* Base 16bit int */
inline __m128i *sse_basei16(PyObject *self, PyObject *args)
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

inline PyObject *sse_pyobj_basei16(__m128i *r, __m128i *n)
{
    int16_t *ar;
    ar = (int16_t *) r;
    free(n);
    return Py_BuildValue("[iiiiiiii]", A03(ar), A47(ar));
}

/* base 8 bit int */
inline __m128i *sse_basei8(PyObject *self, PyObject *args)
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

inline PyObject *sse_pyobj_basei8(__m128i *r, __m128i *n)
{
    int8_t *ar;
    ar = (int8_t *) r;
    free(n);
    return Py_BuildValue("[iiiiiiiiiiiiiiii]", A03(ar), A47(ar), A811(ar), A1216(ar));
}

inline __m64 set__m64(int64_t num){
    union {
        int64_t from;
        __m64 value;
    } converter;
    converter.from = num;
    return converter.value;
}

inline int64_t set_int64_t(__m64 num){
    union {
        __m64 from;
        int64_t value;
    } converter;
    converter.from = num;
    return converter.value;
}

#endif