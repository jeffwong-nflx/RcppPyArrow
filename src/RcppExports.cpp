// Generated by using Rcpp::compileAttributes() -> do not edit by hand
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include <Rcpp.h>

using namespace Rcpp;

// receive_arrow_table_from_python
SEXP receive_arrow_table_from_python(SEXP python_ref);
RcppExport SEXP _RcppPyArrow_receive_arrow_table_from_python(SEXP python_refSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< SEXP >::type python_ref(python_refSEXP);
    rcpp_result_gen = Rcpp::wrap(receive_arrow_table_from_python(python_ref));
    return rcpp_result_gen;
END_RCPP
}
