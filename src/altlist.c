
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

static const R_CallMethodDef callMethods[]  = {
  { "is_altrep", (DL_FUNC) &is_altrep,    1 },
  { "altlist"  , (DL_FUNC) &make_simple,  1 },
  { "rowwise",   (DL_FUNC) &make_rowwise, 5 },
  { NULL, NULL, 0 }
};

// ---------------------------------------------------------------------

R_xlen_t simple_length(SEXP x);
R_xlen_t simple_length(SEXP x);
SEXP simple_elt(SEXP x, R_xlen_t i);
void simple_setelt(SEXP x, R_xlen_t i, SEXP v);
Rboolean simple_inspect(SEXP x, int pre, int deep, int pvec,
                        void (*inspect_subtree)(SEXP, int, int, int));

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
  /* Duplicate? */

  /* Rowwise iteration over a data frame */
  rowwise_class = R_make_altlist_class("rowwise_altlist", "altlist", dll);
  R_set_altrep_Length_method(rowwise_class, rowwise_length);
  R_set_altlist_Elt_method(rowwise_class, rowwise_elt);
  R_set_altlist_Set_elt_method(rowwise_class, rowwise_setelt);
  R_set_altrep_Inspect_method(rowwise_class, rowwise_inspect);

  R_registerRoutines(dll, NULL, callMethods, NULL, NULL);
}
