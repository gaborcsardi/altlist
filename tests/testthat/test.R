
test_that("altlist", {
  expect_output(
    .Internal(inspect(altlist(as.list(1:3)))),
    "altlist"
  )
})

test_that("is_altrep", {
  expect_false(is_altrep(list(1, 2, 3)))
  expect_true(is_altrep(altlist(list(1, 2, 3))))
  expect_true(is_altrep(rowwise(mtcars)))
})

test_that("iterate", {
  expect_output(
    expect_equal(
      iterate(altlist(as.list(1:3)), function(x) x * 2),
      as.list(1:3 * 2)
    ),
    "Got dataptr"
  )
  expect_output(
    x <- iterate(rowwise(data.frame(a = letters[1:3])), print),
    "No dataptr"
  )
})

test_that("iterate_dataptr_ro", {
  expect_equal(
    iterate_dataptr_ro(altlist(as.list(1:3)), function(x) x * 2),
    as.list(1:3 * 2)
  )
  expect_error(
    iterate_dataptr_ro(rowwise(data.frame(a = letters[1:3])), print),
    "No Dataptr method found for ALTLIST class"
  )
})

test_that("no_dataptr", {
  expect_silent(no_dataptr(as.list(1:3)))
  expect_error(
    no_dataptr(rowwise(mtcars)),
    "ALTREP lists must not return a writeable DATAPTR"
  )
  expect_error(
    no_dataptr(altlist(as.list(1:3))),
    "ALTREP lists must not return a writeable DATAPTR"
  )
})

test_that("dataptr_ro", {
  expect_silent(
    dataptr_ro(altlist(as.list(1:3)))
  )
  expect_error(
    dataptr_ro(rowwise(mtcars))
  )
})

test_that("set_elt", {
  l <- altlist(as.list(1:3))
  l2 <- set_elt(l, 2, 100)
  expect_identical(l, l2);
  expect_equal(l, list(1, 100, 3))
  expect_true(is_altrep(l))
  expect_true(is_altrep(l2))
})
