
#' @useDynLib altlist, .registration = TRUE, .fixes = "c_"
NULL

#' Create an ALTREP-wrapped list
#'
#' This is for testing only.
#'
#' @param x The input list.
#' @return ALTREP wrapped list.
#'
#' @export

altlist <- function(x) {
  .Call(c_altlist, x)
}

is_altrep <- function(x) {
  .Call(c_is_altrep, x)
}

iterate <- function(x, fun, env = parent.frame()) {
  .Call(c_list_iterate, x, fun, env)
}

iterate_dataptr_ro <- function(x, fun, env = parent.frame()) {
  .Call(c_iterate_dataptr_ro, x, fun, env)
}

no_dataptr <- function(x) {
  .Call(c_no_dataptr, x)
}

dataptr_ro <- function(x) {
  .Call(c_dataptr_ro, x)
}

# Modifies list element in place. Only for testing purposes!

set_elt <- function(x, idx, val) {
  .Call(c_set_elt, x, as.integer(idx) - 1L, val)
}
