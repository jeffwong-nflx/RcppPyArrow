#include "arrow_python.h"

// [[Rcpp::export]]
SEXP receive_arrow_table_from_python(SEXP python_ref) {
  arrow::py::import_pyarrow();
  PyObject* python_table = (PyObject *)R_ExternalPtrAddr(python_ref);
  std::shared_ptr<arrow::Table> table;
  arrow::py::unwrap_table(python_table, &table);
  Rcpp::XPtr<std::shared_ptr<arrow::Table>> output(new std::shared_ptr<arrow::Table>(table), true);
  return output;
}
