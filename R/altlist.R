
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

no_dataptr <- function(x) {
  .Call(c_no_dataptr, x)
}

dataptr_ro <- function(x) {
  .call(c_dataptr_ro, x)
}
