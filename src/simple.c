
#include <R.h>
#include <Rinternals.h>
#include <R_ext/Rdynload.h>
#include <R_ext/Altrep.h>

// ---------------------------------------------------------------------

extern R_altrep_class_t simple_class;

SEXP make_simple(SEXP orig) {
  return R_new_altrep(simple_class, orig, R_NilValue);
}

R_xlen_t simple_length(SEXP x) {
  SEXP data = R_altrep_data1(x);
  return LENGTH(data);
}

SEXP simple_elt(SEXP x, R_xlen_t i) {
  SEXP data = R_altrep_data1(x);
  return VECTOR_ELT(data, i);
}

void simple_setelt(SEXP x, R_xlen_t i, SEXP v) {
  SEXP data = R_altrep_data1(x);
  SET_VECTOR_ELT(data, i, v);
}

const void *simple_dataptr_or_null(SEXP x) {
  SEXP data = R_altrep_data1(x);
  return DATAPTR_OR_NULL(data);
}

Rboolean simple_inspect(SEXP x, int pre, int deep, int pvec,
                        void (*inspect_subtree)(SEXP, int, int, int)) {
  SEXP data = R_altrep_data1(x);
  Rprintf(" altlist\n");
  inspect_subtree(data, pre, deep, pvec);
  return TRUE;
}
