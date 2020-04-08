#include <stdint.h>
#include <Python.h>
#include "sseintrin.h"

#define SSE_METH(name) static PyObject *\
sse_ ## name (PyObject *self, PyObject *args)

#define ADD_SSE_METHOD(METH) ADD_PREFIX_METHOD(METH, sse_, METH ## _docstring)

/* Add */
#define addps_docstring "Add packed single-precision floating-point elements"
SSE_METH(addps)
{
    SPBASE(_mm_add_ps)
}

#define addss_docstring "Add the lower single-precision          \
floating-point element in a and b, store the result in the lower \
element of dst, and copy the upper 3 packed elements from a to   \
the upper elements of return."
SSE_METH(addss)
{
    SPBASE(_mm_add_ss)
}

/* And */
#define andps_docstring "Compute the bitwise AND of packed single-precision \
floating-point elements in a and b, and return the results."
SSE_METH(andps)
{
    SPBASE(_mm_and_ps)
}

#define andnot_ps_docstring "Compute the bitwise NOT of packed  \
single-precision floating-point elements in a and b, and return \
the results."
SSE_METH(andnot_ps)
{
    SPBASE(_mm_andnot_ps)
}

/* Average */
#define avgpu16_docstring "Average packed unsigned 16bit integers in a and b"
SSE_METH(avgpu16)
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
SSE_METH(avgpu8)
{
    int8_t aa[8], ab[8], *ar;
    __m64 a, b, r;
    if(!PyArg_ParseTuple(args, "iiiiiiiiiiiiiiii", 
                         A03(&aa), A47(&aa), A03(&ab), A47(&ab)))
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
SSE_METH(cmpeq_ps)
{
    SPBASE(_mm_cmpeq_ps)
}

#define cmpeq_ss_docstring "Compare the lower single-precision   \
floating-point elements in a and b for equality, store the      \
result in the lower element of dst, and copy the upper 3 packed \
elements from a to the upper elements of return."
SSE_METH(cmpeq_ss)
{
    SPBASE(_mm_cmpeq_ss)
}

/* Compare greater than or equal */
#define cmpge_ps_docstring "Compare packed single-precision \
floating-point elements in a and b for greater-than-or-equal"
SSE_METH(cmpge_ps)
{
    SPBASE(_mm_cmpge_ps)
}

#define cmpge_ss_docstring "Compare the lower single-precision   \
floating-point elements in a and b for greater-than-or-equal,    \
store the result in the lower element of dst, and copy the upper \
3 packed elements from a to the upper elements of dst."
SSE_METH(cmpge_ss)
{
    SPBASE(_mm_cmpge_ss)
}

/* Compare greater than */
#define cmpgt_ps_docstring "Compare packed single-precision \
floating-point elements in a and b for greater-than"
SSE_METH(cmpgt_ps)
{
    SPBASE(_mm_cmpgt_ps)
}

#define cmpgt_ss_docstring "Compare the lower single-precision  \
floating-point elements in a and b for greater-than, store the  \
result in the lower element of dst, and copy the upper 3 packed \
elements from a to the upper elements of dst."
SSE_METH(cmpgt_ss)
{
    SPBASE(_mm_cmpgt_ss)
}

/* Compare less than or equal */
#define cmple_ps_docstring "Compare packed single-precision \
floating-point elements in a and b for less-than-or-equal"
SSE_METH(cmple_ps)
{
    SPBASE(_mm_cmple_ps)
}

#define cmple_ss_docstring "Compare the lower single-precision   \
floating-point elements in a and b for less-than-or-equal, store \
the result in the lower element of dst, and copy the upper 3     \
packed elements from a to the upper elements of dst."
SSE_METH(cmple_ss)
{
    SPBASE(_mm_cmple_ss)
}

/* Compare less than */
#define cmplt_ps_docstring "Compare packed single-precision \
floating-point elements in a and b for less-than"
SSE_METH(cmplt_ps)
{
    SPBASE(_mm_cmplt_ps)
}

#define cmplt_ss_docstring "Compare the lower single-precision     \
floating-point elements in a and b for less-than, store the result \
in the lower element of dst, and copy the upper 3 packed elements  \
from a to the upper elements of dst."
SSE_METH(cmplt_ss)
{
    SPBASE(_mm_cmplt_ss)
}

/* Compare not equal */
#define cmpneq_ps_docstring "Compare packed single-precision \
floating-point elements in a and b for non-equality"
SSE_METH(cmpneq_ps)
{
    SPBASE(_mm_cmpneq_ps)
}

#define cmpneq_ss_docstring "Compare the lower single-precision \
floating-point elements in a and b for non-equality, store the  \
result in the lower element of dst, and copy the upper 3 packed \
elements from a to the upper elements of return."
SSE_METH(cmpneq_ss)
{
    SPBASE(_mm_cmpneq_ss)
}

/* Compare not greater than or equal */
#define cmpnge_ps_docstring "Compare packed single-precision    \
floating-point elements in a and b for not-greater-than-or-equal"
SSE_METH(cmpnge_ps)
{
    SPBASE(_mm_cmpnge_ps)
}

#define cmpnge_ss_docstring "Compare the lower single-precision  \
floating-point elements in a and b for not-greater-than-or-equal,\
store the result in the lower element of dst, and copy the upper \
3 packed elements from a to the upper elements of dst."
SSE_METH(cmpnge_ss)
{
    SPBASE(_mm_cmpnge_ss)
}

/* Compare not greater than */
#define cmpngt_ps_docstring "Compare packed single-precision \
floating-point elements in a and b for not-greater-than"
SSE_METH(cmpngt_ps)
{
    SPBASE(_mm_cmpngt_ps)
}

#define cmpngt_ss_docstring "Compare the lower single-precision   \
floating-point elements in a and b for not-greater-than, store the\
result in the lower element of dst, and copy the upper 3 packed   \
elements from a to the upper elements of dst."
SSE_METH(cmpngt_ss)
{
    SPBASE(_mm_cmpngt_ss)
}

/* Compare not less than or equal */
#define cmpnle_ps_docstring "Compare packed single-precision \
floating-point elements in a and b for not-less-than-or-equal"
SSE_METH(cmpnle_ps)
{
    SPBASE(_mm_cmpnle_ps)
}

#define cmpnle_ss_docstring "Compare the lower single-precision  \
floating-point elements in a and b for not-less-than-or-equal,   \
store the result in the lower element of dst, and copy the upper \
3 packed elements from a to the upper elements of dst."
SSE_METH(cmpnle_ss)
{
    SPBASE(_mm_cmpnle_ss)
}

/* Compare not less than */
#define cmpnlt_ps_docstring "Compare packed single-precision \
floating-point elements in a and b for not-less-than"
SSE_METH(cmpnlt_ps)
{
    SPBASE(_mm_cmpnlt_ps)
}

#define cmpnlt_ss_docstring "Compare the lower single-precision \
floating-point elements in a and b for not-less-than, store the \
result in the lower element of dst, and copy the upper 3 packed \
elements from a to the upper elements of dst."
SSE_METH(cmpnlt_ss)
{
    SPBASE(_mm_cmpnlt_ss)
}

/* cmpord and cmpnord*/
#define cmpord_ps_docstring "Compare packed single-precision \
floating-point elements in a and b to see if neither is NaN, \
and return the results."
SSE_METH(cmpord_ps)
{
    SPBASE(_mm_cmpord_ps)
}

#define cmpord_ss_docstring "Compare the lower single-precision \
floating-point elements in a and b to see if neither is NaN,    \
store the result in the lower element of dst, and copy the      \
upper 3 packed elements from a to the upper elements of return."
SSE_METH(cmpord_ss)
{
    SPBASE(_mm_cmpord_ss)
}

#define cmpunord_ps_docstring "Compare packed single-precision  \
floating-point elements in a and b to see if either is NaN, and \
return the results"
SSE_METH(cmpunord_ps)
{
    SPBASE(_mm_cmpunord_ps)
}

#define cmpunord_ss_docstring "Compare the lower single-precision \
floating-point elements in a and b to see if either is NaN, store \
the result in the lower element of dst, and copy the upper 3      \
packed elements from a to the upper elements of return."
SSE_METH(cmpunord_ss)
{
    SPBASE(_mm_cmpunord_ss)
}

#define comieq_ss_docstring "Compare the lower single-precision \
floating-point element in a and b for equality, and return the  \
boolean result (0 or 1)."
SSE_METH(comieq_ss)
{
    RBOOL_SPBASE(_mm_comieq_ss);
}

#define comige_ss_docstring "Compare the lower single-precision  \
floating-point element in a and b for greater-than-or-equal, and \
return the boolean result (0 or 1)."
SSE_METH(comige_ss)
{
    RBOOL_SPBASE(_mm_comige_ss);
}

#define comigt_ss_docstring "Compare the lower single-precision \
floating-point element in a and b for greater-than, and return  \
the boolean result (0 or 1)."
SSE_METH(comigt_ss)
{
    RBOOL_SPBASE(_mm_comigt_ss);
}

#define comile_ss_docstring "Compare the lower single-precision \
floating-point element in a and b for less-than-or-equal, and   \
return the boolean result (0 or 1)."
SSE_METH(comile_ss)
{
    RBOOL_SPBASE(_mm_comile_ss);
}

#define comilt_ss_docstring "Compare the lower single-precision \
floating-point element in a and b for less-than, and return the \
boolean result (0 or 1)."
SSE_METH(comilt_ss)
{
    RBOOL_SPBASE(_mm_comilt_ss);
}

#define comineq_ss_docstring "Compare the lower single-precision \
floating-point element in a and b for not-equal, and return the  \
boolean result (0 or 1)."
SSE_METH(comineq_ss)
{
    RBOOL_SPBASE(_mm_comineq_ss);
}

/* divide */
#define divps_docstring "Divide packed single-precision   \
floating-point elements in a by packed elements in b, and \
store the results"
SSE_METH(divps)
{
    SPBASE(_mm_div_ps)
}

#define divss_docstring "Divide the lower single-precision \
floating-point element in a by the lower single-precision  \
floating-point element in b, store the result in the lower \
element of dst, and copy the upper 3 packed elements from a\
to the upper elements of return"
SSE_METH(divss)
{
    SPBASE(_mm_div_ss)
}

/* handle imm8 */
#define IMM8_CASE_BASE(num, intrinsic)  \
        case num:                       \
          r = intrinsic(a, num); \
          break

#define IMM8_CASE_2(num, intrinsic) IMM8_CASE_BASE(num, intrinsic);   \
                                    IMM8_CASE_BASE(num+1, intrinsic)

#define IMM8_CASE_5(num, intrinsic) IMM8_CASE_2(num, intrinsic);      \
                                     IMM8_CASE_2(num+2, intrinsic);   \
                                     IMM8_CASE_BASE(num+4, intrinsic)

#define IMM8_CASE_10(num, intrinsic) IMM8_CASE_5(num, intrinsic);     \
                                     IMM8_CASE_5(num+5, intrinsic)

#define IMM8_CASE_25(num, intrinsic) IMM8_CASE_10(num, intrinsic);    \
                                     IMM8_CASE_10(num+10, intrinsic); \
                                     IMM8_CASE_5(num+20, intrinsic)

#define IMM8_CASE_50(num, intrinsic) IMM8_CASE_25(num, intrinsic);    \
                                     IMM8_CASE_25(num+25, intrinsic)

#define IMM8_CASE_100(num, intrinsic) IMM8_CASE_50(num, intrinsic);   \
                                      IMM8_CASE_50(num+50, intrinsic)

#define IMM8_CASE_200(num, intrinsic) IMM8_CASE_100(num, intrinsic);  \
                                      IMM8_CASE_100(num+100, intrinsic)

#define IMM8_CASE_UINT8T(intrinsic) IMM8_CASE_200(0, intrinsic);   \
                                    IMM8_CASE_50(200, intrinsic);  \
                                    IMM8_CASE_5(250, intrinsic);   \
                                    IMM8_CASE_BASE(255, intrinsic)
/* extract_pi16 */
#define extract_pi16_docstring "Extract a 16-bit integer from a, selected \
with imm8, and store the result in the lower element of dst."
SSE_METH(extract_pi16)
{
    int16_t x[4]; uint8_t imm8; int r;
    if(!PyArg_ParseTuple(args, "iiiii", A03(&x), &imm8))
        return NULL;
    if (imm8 > 3)
        imm8 = imm8 % 4;
    __m64 a = _mm_set_pi16(A03(x));
    switch (imm8){
            IMM8_CASE_2(0, _mm_extract_pi16);
            IMM8_CASE_2(2, _mm_extract_pi16);
    }
    _mm_empty();
    return Py_BuildValue("i", r);
}

/* insert_pi16 */
#define MM_INSERT_PI16(_, num) _mm_insert_pi16(a, i, num)
#define insert_pi16_docstring "Copy a to dst, and insert the 16-bit integer \
i into dst at the location specified by imm8."
SSE_METH(insert_pi16)
{
    int16_t x[4], *ar, i; uint8_t imm8;;
    if(!PyArg_ParseTuple(args, "iiiiii", A03(&x), &i, &imm8))
        return NULL;
    __m64 a = _mm_set_pi16(A03(x)), r;
    if (imm8 > 3)
        imm8 = imm8 % 4;
    switch (imm8){
            IMM8_CASE_2(0, MM_INSERT_PI16);
            IMM8_CASE_2(2, MM_INSERT_PI16);
    }
    ar = (int16_t *) &r;
    _mm_empty();
    return Py_BuildValue("[iiii]", A03(ar));
}

/* max and min */
#define max_pi16_docstring "Compare packed signed 16-bit integers in a and b, \
and return packed maximum values"
SSE_METH(max_pi16)
{
    M64_BASE_M64M64(_mm_max_pi16);
}

#define maxps_docstring "Compare packed single-precision floating-point \
elements in a and b, and return packed maximum values"
SSE_METH(maxps)
{
    SPBASE(_mm_max_ps);
}
/*_mm_max_pu8 (__m64 a, __m64 b)
*/
#define maxss_docstring "Compare the lower single-precision floating-point \
elements in a and b, store the maximum value in the lower element of dst,  \
and copy the upper 3 packed elements from a to the upper element of return"
SSE_METH(maxss)
{
    SPBASE(_mm_max_ss);
}

#define min_pi16_docstring "Compare packed signed 16-bit integers in a and b, \
and return packed minimum values"
SSE_METH(min_pi16)
{
    M64_BASE_M64M64(_mm_min_pi16);
}
#define minps_docstring "Compare packed single-precision floating-point \
elements in a and b, and return packed minimum values"
SSE_METH(minps)
{
    SPBASE(_mm_min_ps);
}

#define minss_docstring "Compare the lower single-precision floating-point \
elements in a and b, store the minimum value in the lower element of dst,  \
and copy the upper 3 packed elements from a to the upper element of return"
SSE_METH(minss)
{
    SPBASE(_mm_min_ss);
}

/* move */
#define movess_docstring "Move the lower single-precision  \
floating-point element from b to the lower element of dst, \
and copy the upper 3 packed elements from a to the upper   \
elements of dst."
SSE_METH(movess)
{
    SPBASE(_mm_move_ss);
}

#define movehl_ps_docstring "Move the upper 2 single-precision  \
floating-point elements from b to the lower 2 elements of dst,  \
and copy the upper 2 elements from a to the upper 2 elements of \
dst"
SSE_METH(movehl_ps)
{
    SPBASE(_mm_movehl_ps);
}

#define movelh_ps_docstring "Move the lower 2 single-precision  \
floating-point elements from b to the upper 2 elements of dst,  \
and copy the lower 2 elements from a to the lower 2 elements of \
dst."
SSE_METH(movelh_ps)
{
    SPBASE(_mm_movelh_ps);
}

/* multuply */
#define mulps_docstring "Multiply packed single-precision \
floating-point elements in a and b, and return the results"
SSE_METH(mulps)
{
    SPBASE(_mm_mul_ps);
}

#define mulss_docstring "Multiply the lower single-precision \
floating-point element in a and b, store the result in the   \
lower element of dst, and copy the upper 3 packed elements   \
from a to the upper elements of return."
SSE_METH(mulss)
{
    SPBASE(_mm_mul_ss);
}

/* or */
#define orps_docstring "Compute the bitwise OR of packed  \
single-precision floating-point elements in a and b, and \
return the results"
SSE_METH(orps)
{
    SPBASE(_mm_or_ps);
}

/* shuffle_pi16 */
#define shuffle_pi16_docstring "Shuffle 16-bit integers in a using \
the control in imm8"
SSE_METH(shuffle_pi16)
{
    int16_t x[4], *ar; uint8_t imm8;
    if(!PyArg_ParseTuple(args, "iiiii", A03(&x), &imm8))
        return NULL;
    __m64 a = _mm_set_pi16(A03(x)), r;
    switch(imm8){
            IMM8_CASE_UINT8T(_mm_shuffle_pi16);
    }
    ar = (int16_t *) &r;
    _mm_empty();
    return Py_BuildValue("[iiii]", A03(ar));
}

#define shuffle_ps_docstring "Shuffle single-precision floating numbers \
using the control in imm8"
#define SHUFFLE_PSMCR(_, num) _mm_shuffle_ps(a, b, num)
SSE_METH(shuffle_ps)
{
    float aa[4], ab[4], *ar; uint8_t imm8;
    if (!PyArg_ParseTuple(args, "ffffffffi", A03(&aa), A03(&ab), &imm8))
        return NULL;
    __m128 a = _mm_set_ps(A03(aa)), b = _mm_set_ps(A03(ab)), r;
    switch(imm8){
            IMM8_CASE_UINT8T(SHUFFLE_PSMCR);
    }
    ar = (float *) &r;
    return Py_BuildValue("[ffff]", A03(ar));
}

#define sqrtps_docstring "Compute the square root of packed single-precision \
floating-point elements in a, and store the results in dst."
SSE_METH(sqrtps)
{
    SINGLE128_SPBASE(_mm_sqrt_ps);
}

#define sqrtss_docstring "Compute the square root of the lower single-precision \
floating-point element in a, store the result in the lower element of dst, and  \
copy the upper 3 packed elements from a to the upper elements of dst."
SSE_METH(sqrtss)
{
    SINGLE128_SPBASE(_mm_sqrt_ss);
}

/* sub */
#define subps_docstring "Subtract packed single-precision \
floating-point elements in b from packed single-precision \
floating-point elements in a, and return the results."
SSE_METH(subps)
{
    SPBASE(_mm_sub_ps);
}

#define subss_docstring "Subtract the lower single-precision \
floating-point element in b from the lower single-precision  \
floating-point element in a, store the result in the lower   \
element of dst, and copy the upper 3 packed elements from a  \
to the upper elements of return."
SSE_METH(subss)
{
    SPBASE(_mm_sub_ss);
}

#define ucomieq_ss_docstring "Compare the lower single-precision \
floating-point element in a and b for equality, and return the   \
boolean result (0 or 1). This instruction will not signal an     \
exception for QNaNs."
SSE_METH(ucomieq_ss)
{
    RBOOL_SPBASE(_mm_ucomieq_ss);
}

#define ucomige_ss_docstring "Compare the lower single-precision \
floating-point element in a and b for greater-than-or-equal, and \
return the boolean result (0 or 1). This instruction will not    \
signal an exception for QNaNs."
SSE_METH(ucomige_ss)
{
    RBOOL_SPBASE(_mm_ucomige_ss);
}

#define ucomigt_ss_docstring "Compare the lower single-precision \
floating-point element in a and b for greater-than, and return   \
the boolean result (0 or 1). This instruction will not signal an \
exception for QNaNs."
SSE_METH(ucomigt_ss)
{
    RBOOL_SPBASE(_mm_ucomigt_ss);
}

#define ucomile_ss_docstring "Compare the lower single-precision \
floating-point element in a and b for less-than-or-equal, and    \
return the boolean result (0 or 1). This instruction will not    \
signal an exception for QNaNs."
SSE_METH(ucomile_ss)
{
    RBOOL_SPBASE(_mm_ucomile_ss);
}

#define ucomilt_ss_docstring "Compare the lower single-precision \
floating-point element in a and b for less-than, and return the  \
boolean result (0 or 1). This instruction will not signal an     \
exception for QNaNs."
SSE_METH(ucomilt_ss)
{
    RBOOL_SPBASE(_mm_ucomilt_ss);
}

#define ucomineq_ss_docstring "Compare the lower single-precision \
floating-point element in a and b for not-equal, and return the   \
boolean result (0 or 1). This instruction will not signal an      \
exception for QNaNs."
SSE_METH(ucomineq_ss)
{
    RBOOL_SPBASE(_mm_ucomineq_ss);
}

/* unpack */
#define unpackhi_ps_docstring "Unpack and interleave   \
single-precision floating-point elements from the high \
half a and b, and return the results."
SSE_METH(unpackhi_ps)
{
    SPBASE(_mm_unpackhi_ps);
}

#define unpacklo_ps_docstring "Unpack and interleave single-precision \
floating-point elements from the low half of a and b, and return the  \
results."
SSE_METH(unpacklo_ps)
{
    SPBASE(_mm_unpacklo_ps)
}

/* xor */
#define xorps_docstring "Compute the bitwise XOR of packed single-precision \
floating-point elements in a and b, and store the results in dst"
SSE_METH(xorps)
{
    SPBASE(_mm_xor_ps);
}

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
    ADD_SSE_METHOD(comieq_ss),
    ADD_SSE_METHOD(comige_ss),
    ADD_SSE_METHOD(comigt_ss),
    ADD_SSE_METHOD(comile_ss),
    ADD_SSE_METHOD(comilt_ss),
    ADD_SSE_METHOD(comineq_ss),
    ADD_SSE_METHOD(divps),
    ADD_SSE_METHOD(divss),
    ADD_SSE_METHOD(extract_pi16),
    ADD_SSE_METHOD(insert_pi16),
    ADD_SSE_METHOD(max_pi16),
    ADD_SSE_METHOD(maxps),
    ADD_SSE_METHOD(maxss),
    ADD_SSE_METHOD(minps),
    ADD_SSE_METHOD(minss),
    ADD_SSE_METHOD(min_pi16),
    ADD_SSE_METHOD(movess),
    ADD_SSE_METHOD(movehl_ps),
    ADD_SSE_METHOD(movelh_ps),
    ADD_SSE_METHOD(mulps),
    ADD_SSE_METHOD(mulss),
    ADD_SSE_METHOD(orps),
    ADD_SSE_METHOD(shuffle_pi16),
    ADD_SSE_METHOD(shuffle_ps),
    ADD_SSE_METHOD(sqrtps),
    ADD_SSE_METHOD(sqrtss),
    ADD_SSE_METHOD(subps),
    ADD_SSE_METHOD(subss),
    ADD_SSE_METHOD(ucomieq_ss),
    ADD_SSE_METHOD(ucomige_ss),
    ADD_SSE_METHOD(ucomigt_ss),
    ADD_SSE_METHOD(ucomile_ss),
    ADD_SSE_METHOD(ucomilt_ss),
    ADD_SSE_METHOD(ucomineq_ss),
    ADD_SSE_METHOD(unpackhi_ps),
    ADD_SSE_METHOD(unpacklo_ps),
    ADD_SSE_METHOD(xorps),
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
