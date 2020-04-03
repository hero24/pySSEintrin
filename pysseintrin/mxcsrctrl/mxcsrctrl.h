#if defined(_MSC_VER)
#include <intrin.h>
#else
#include <x86intrin.h>
#endif
#include <stdint.h>
#include <Python.h>
/* MXCSR control regiser functions */
#define MXCSR_CTRL_BASE(CTRL)  unsigned int mode;                      \
                               if(!PyArg_ParseTuple(args, "i", &mode)) \
                                        return NULL;                   \
                               CTRL(mode);                             \
                               Py_RETURN_NONE;

struct SSEConstants {
    char *name;
    char *type;
    int value;
};

inline void addobj(PyObject *module, struct SSEConstants *constants)
{ 
    int i;
    for (i=0; constants[i].name != NULL; i++){
        PyModule_AddObject(module, constants[i].name,
                                 Py_BuildValue(constants[i].type,constants[i].value));
    }
}

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
