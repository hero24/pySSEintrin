#include "mxcsrctrl.h"

static PyMethodDef mxcrtlmethods[] = {
    {"set_exception_mask"  , sse_csfr_sexcmsk,     METH_VARARGS,
     "Set the exception mask bits of the MXCSR control and status register"},
    {"set_exception_state" , sse_csfr_sexcst,      METH_VARARGS,
     "Set the exception state bits of the MXCSR control and status register"},
    {"set_flush_zero_mode" , sse_csfr_sfzm,        METH_VARARGS,
     "Set the flush zero bits of the MXCSR control and status register"},
    {"set_rounding_mode"   , sse_set_rnd_mode,     METH_VARARGS,
     "Set the rounding mode bits of the MXCSR control and status \
     register to the value in unsigned 32-bit integer a"},
    {"setcsr"              , sse_setcsr,           METH_VARARGS,
     "Set the MXCSR control and status register with the value in \
     unsigned 32-bit integer a."},
    {"getcsr"              , sse_getcsr,           METH_NOARGS,
     "Get the unsigned 32bit value of the MXCSR control and status register."},
    {"get_rounding_mode"   , sse_get_rnd_mnd,      METH_NOARGS,
     "Get the rounding mode bits of the MXCSR control and status register"},
    {"get_flush_zero_mode" , sse_get_fzmm,         METH_NOARGS,
     "Get the flush zero bits of the MXCSR control and status register"},
    {"get_exception_state" , sse_get_exst,         METH_NOARGS, 
     "Get the exception state bits of the MXCSR control and status register"},
    {"get_exception_mask"  , sse_get_exmsk,        METH_NOARGS,
     "Get the exception mask bits of the MXCSR control and status register"},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef mxcsrctl = {
    PyModuleDef_HEAD_INIT,
    "mxcsrctl",
    "Python wrapper for SSE mxcsr control register intrinsics",
    -1,
    mxcrtlmethods
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

PyMODINIT_FUNC PyInit_mxcsrctrl(void){    
    PyObject *module = PyModule_Create(&mxcsrctl);
    addobj(module, constants);
    return module;
}