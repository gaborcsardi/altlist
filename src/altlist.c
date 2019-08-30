
#include <R.h>
#include <Rinternals.h>
#include <R_ext/Rdynload.h>
#include <R_ext/Altrep.h>

static R_altrep_class_t simple_class;
static R_altrep_class_t rowwise_class;

static SEXP make_simple(SEXP orig);
static SEXP make_rowwise(SEXP df, SEXP nms, SEXP len, SEXP idxcall,
                         SEXP env);

static const R_CallMethodDef callMethods[]  = {
  { "altlist", (DL_FUNC) &make_simple, 1 },
  { "rowwise", (DL_FUNC) &make_rowwise, 5 },
  { NULL, NULL, 0 }
};

// ---------------------------------------------------------------------

static SEXP make_simple(SEXP orig) {
  return R_new_altrep(simple_class, orig, R_NilValue);
}

static R_xlen_t simple_length(SEXP x) {
  SEXP data = R_altrep_data1(x);
  return LENGTH(data);
}

static SEXP simple_elt(SEXP x, R_xlen_t i) {
  SEXP data = R_altrep_data1(x);
  return VECTOR_ELT(data, i);
}

static void simple_setelt(SEXP x, R_xlen_t i, SEXP v) {
  SEXP data = R_altrep_data1(x);
  SET_VECTOR_ELT(data, i, v);
}

static Rboolean simple_inspect(SEXP x, int pre, int deep, int pvec,
                               void (*inspect_subtree)(SEXP, int,
                                                       int, int)) {
  SEXP data = R_altrep_data1(x);
  Rprintf(" altlist\n");
  inspect_subtree(data, pre, deep, pvec);
  return TRUE;
}


// ---------------------------------------------------------------------

static SEXP make_rowwise(SEXP df, SEXP nms, SEXP len, SEXP idxcall,
                         SEXP env) {
  SEXP rowwise_data = PROTECT(allocVector(VECSXP, 5));
  SEXP altlist = R_NilValue, template = R_NilValue,
    templatenms = R_NilValue;
  int i, numcols = LENGTH(df);

  /* Template */
  template = PROTECT(allocVector(VECSXP, numcols + 1L));
  templatenms = allocVector(STRSXP, numcols + 1L);
  for (i = 0; i < numcols; i++) {
    SET_STRING_ELT(templatenms, i, STRING_ELT(nms, i));
  }
  SET_STRING_ELT(templatenms, numcols, mkChar(".idx"));
  setAttrib(template, R_NamesSymbol, templatenms);
  SET_VECTOR_ELT(rowwise_data, 0, template);

  SET_VECTOR_ELT(rowwise_data, 1, len);     /* Length of iteration */
  SET_VECTOR_ELT(rowwise_data, 2, ScalarInteger(numcols));
  SET_VECTOR_ELT(rowwise_data, 3, idxcall);
  SET_VECTOR_ELT(rowwise_data, 4, env);

  altlist = PROTECT(R_new_altrep(rowwise_class, df, rowwise_data));
  UNPROTECT(3);
  return altlist;
}

static R_xlen_t rowwise_length(SEXP x) {
  SEXP data = R_altrep_data2(x);
  return INTEGER(VECTOR_ELT(data, 1))[0];
}

static SEXP rowwise_elt(SEXP x, R_xlen_t idx) {
  SEXP df = R_altrep_data1(x);
  SEXP data = R_altrep_data2(x);
  SEXP row = VECTOR_ELT(data, 0);
  SEXP idxcall = VECTOR_ELT(data, 3);
  SEXP env = VECTOR_ELT(data, 4);
  SEXP ridx = ScalarInteger(idx + 1);
  int i, numcols = LENGTH(df);
  SET_VECTOR_ELT(row, numcols, ridx);
  for (i = 0; i < numcols; i++) {
    SETCADR(idxcall, VECTOR_ELT(df, i));
    SETCADDR(idxcall, ridx);
    SET_VECTOR_ELT(row, i, Rf_eval(idxcall, env));
  }
  return row;
}

static void rowwise_setelt(SEXP x, R_xlen_t i, SEXP v) {
  error("Trying to change a read only rowwise iterator, see ?rowwise");
}

static Rboolean rowwise_inspect(SEXP x, int pre, int deep, int pvec,
                               void (*inspect_subtree)(SEXP, int,
                                                       int, int)) {
  SEXP data = R_altrep_data1(x);
  Rprintf(" altrep rowwise\n");
  inspect_subtree(data, pre, deep, pvec);
  return TRUE;
}

// ---------------------------------------------------------------------

void R_init_altlist(DllInfo *dll) {

  /* Simple altlist, does nothing really, just for testing */
  simple_class = R_make_altlist_class("simple_altlist", "altlist", dll);
  R_set_altrep_Length_method(simple_class, simple_length);
  R_set_altlist_Elt_method(simple_class, simple_elt);
  R_set_altlist_Set_elt_method(simple_class, simple_setelt);
  R_set_altrep_Inspect_method(simple_class, simple_inspect);
  /* Duplicate? */

  /* Rowwise iteration over a data frame */
  rowwise_class = R_make_altlist_class("rowwise_altlist", "altlist", dll);
  R_set_altrep_Length_method(rowwise_class, rowwise_length);
  R_set_altlist_Elt_method(rowwise_class, rowwise_elt);
  R_set_altlist_Set_elt_method(rowwise_class, rowwise_setelt);
  R_set_altrep_Inspect_method(rowwise_class, rowwise_inspect);

  R_registerRoutines(dll, NULL, callMethods, NULL, NULL);
}
