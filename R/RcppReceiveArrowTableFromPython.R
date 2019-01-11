#' Receive Arrow Table From Python
#'
#' @param xp an external pointer from rpy2.rinterface.SexpExtPtr. 
#'
#' @import arrow
#' @import tibble
#' @useDynLib RcppPyArrow
#' @export
RcppReceiveArrowTableFromPython = function(xp, as_tibble = TRUE) {
  table = receive_arrow_table_from_python(xp)
  if (as_tibble) {
    table = arrow::as_tibble(arrow:::shared_ptr(arrow:::`arrow::Table`, table))
  }
  return (table)
}
