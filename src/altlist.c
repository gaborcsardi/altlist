
#include <R.h>
#include <Rinternals.h>
#include <R_ext/Rdynload.h>
#include <R_ext/Altrep.h>

R_altrep_class_t simple_class;
R_altrep_class_t rowwise_class;

extern SEXP make_simple(SEXP orig);
extern SEXP make_rowwise(SEXP df, SEXP nms, SEXP len, SEXP idxcall,
                         SEXP env);

SEXP is_altrep(SEXP x) {
  return ScalarLogical(ALTREP(x));
}

SEXP list_iterate(SEXP x, SEXP fun, SEXP env) {
  R_xlen_t i, len = XLENGTH(x);
  SEXP res = PROTECT(Rf_allocVector(VECSXP, len));
  SEXP *ptr = (SEXP*) DATAPTR_OR_NULL(x);
  if (ptr == NULL) {
    Rprintf("No dataptr :(\n");
    for (i = 0; i < len; i++) {
      SET_VECTOR_ELT(res, i, Rf_eval(Rf_lang2(fun, VECTOR_ELT(x, i)), env));
    }
  } else {
    Rprintf("Got dataptr :)\n");
    const SEXP *end = ptr + len;
    for (i = 0; ptr < end; i++, ptr++) {
      SET_VECTOR_ELT(res, i, Rf_eval(Rf_lang2(fun, *ptr), env));
    }
  }

  UNPROTECT(1);
  return res;
}

SEXP no_dataptr(SEXP x) {
  SEXP *ptr = (SEXP*) DATAPTR(x);
  (void) ptr;
  return R_NilValue;
}

SEXP dataptr_ro(SEXP x) {
  const SEXP *ptr = (const SEXP*) DATAPTR_RO(x);
  (void) ptr;
  return R_NilValue;
}

SEXP iterate_dataptr_ro(SEXP x, SEXP fun, SEXP env) {
  const SEXP *ptr = (const SEXP*) DATAPTR_RO(x);
  R_xlen_t i, len = XLENGTH(x);
  SEXP res = PROTECT(Rf_allocVector(VECSXP, len));
  const SEXP *end = ptr + len;
  for (i = 0; ptr < end; i++, ptr++) {
    SET_VECTOR_ELT(res, i, Rf_eval(Rf_lang2(fun, *ptr), env));
  }

  UNPROTECT(1);
  return res;
}

SEXP set_elt(SEXP x, SEXP idx, SEXP val) {
  SET_VECTOR_ELT(x, INTEGER(idx)[0], val);
  return x;
}

static const R_CallMethodDef callMethods[]  = {
  { "is_altrep",          (DL_FUNC) &is_altrep,          1 },
  { "altlist",            (DL_FUNC) &make_simple,        1 },
  { "rowwise",            (DL_FUNC) &make_rowwise,       5 },
  { "list_iterate",       (DL_FUNC) &list_iterate,       3 },
  { "no_dataptr",         (DL_FUNC) &no_dataptr,         1 },
  { "dataptr_ro",         (DL_FUNC) &dataptr_ro,         1 },
  { "iterate_dataptr_ro", (DL_FUNC) &iterate_dataptr_ro, 3 },
  { "set_elt",            (DL_FUNC) &set_elt,            3 },
  { NULL, NULL, 0 }
};

// ---------------------------------------------------------------------

R_xlen_t simple_length(SEXP x);
R_xlen_t simple_length(SEXP x);
SEXP simple_elt(SEXP x, R_xlen_t i);
void simple_setelt(SEXP x, R_xlen_t i, SEXP v);
Rboolean simple_inspect(SEXP x, int pre, int deep, int pvec,
                        void (*inspect_subtree)(SEXP, int, int, int));
void *simple_dataptr(SEXP x, Rboolean writeable);
const void *simple_dataptr_or_null(SEXP x);

R_xlen_t rowwise_length(SEXP x);
SEXP rowwise_elt(SEXP x, R_xlen_t idx);
void rowwise_setelt(SEXP x, R_xlen_t i, SEXP v);
Rboolean rowwise_inspect(SEXP x, int pre, int deep, int pvec,
                         void (*inspect_subtree)(SEXP, int, int, int));

void R_init_altlist(DllInfo *dll) {

  /* Simple altlist, does nothing really, just for testing */
  simple_class = R_make_altlist_class("simple_altlist", "altlist", dll);
  R_set_altrep_Length_method(simple_class, simple_length);
  R_set_altlist_Elt_method(simple_class, simple_elt);
  R_set_altlist_Set_elt_method(simple_class, simple_setelt);
  R_set_altrep_Inspect_method(simple_class, simple_inspect);
  R_set_altvec_Dataptr_method(simple_class, simple_dataptr);
  R_set_altvec_Dataptr_or_null_method(simple_class, simple_dataptr_or_null);
  /* Duplicate? */

  /* Rowwise iteration over a data frame */
  rowwise_class = R_make_altlist_class("rowwise_altlist", "altlist", dll);
  R_set_altrep_Length_method(rowwise_class, rowwise_length);
  R_set_altlist_Elt_method(rowwise_class, rowwise_elt);
  R_set_altlist_Set_elt_method(rowwise_class, rowwise_setelt);
  R_set_altrep_Inspect_method(rowwise_class, rowwise_inspect);

  R_registerRoutines(dll, NULL, callMethods, NULL, NULL);
}
