
#' Iterate over the rows of a data frame
#'
#' See examples below.
#'
#' @export
#' @param x Data frame to iterate over.
#' @return ALTREP object, that behaves like list of rows of a data frame.
#'   List elements also have an `.idx` entry, which is a scalar integer,
#'   the row number.
#'
#' @examples
#' for (el in rowwise(mtcars)) {
#'   print(paste0("row #", el$.idx))
#' }
#'
#' lapply(rowwise(mtcars), function(elmt) { elmt$wt })

rowwise <- function(x) {
  stopifnot(is.data.frame(x))
  cll <- as.call(list(`[[`, x, 1))
  .Call(c_rowwise, x, names(x), nrow(x), cll, environment())
}
