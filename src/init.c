#include <R.h>
#include <Rinternals.h>
#include <stdlib.h> // for NULL
#include <R_ext/Rdynload.h>

/* FIXME: 
   Check these declarations against the C/Fortran source code.
*/

/* .Call calls */
extern SEXP _RcppPyArrow_receive_arrow_table_from_python(SEXP);

static const R_CallMethodDef CallEntries[] = {
    {"_RcppPyArrow_receive_arrow_table_from_python", (DL_FUNC) &_RcppPyArrow_receive_arrow_table_from_python, 1},
    {NULL, NULL, 0}
};

void R_init_RcppPyArrow(DllInfo *dll)
{
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}
