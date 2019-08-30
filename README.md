
<!-- README.md is generated from README.Rmd. Please edit that file -->

# altlist

> Test Package for ‘ALTREP’ Lists

[![Linux Build
Status](https://travis-ci.org/gaborcsardi/altlist.svg?branch=master)](https://travis-ci.org/gaborcsardi/altlist)
[![Windows Build
status](https://ci.appveyor.com/api/projects/status/github/gaborcsardi/altlist?svg=true)](https://ci.appveyor.com/project/gaborcsardi/altlist)
[![](http://www.r-pkg.org/badges/version/altlist)](http://www.r-pkg.org/pkg/altlist)
[![CRAN RStudio mirror
downloads](http://cranlogs.r-pkg.org/badges/altlist)](http://www.r-pkg.org/pkg/altlist)

Test Package for ‘ALTREP’ Lists. It needs this patch:
<https://github.com/gaborcsardi/r-source/pull/4>

## Installation

``` r
devtools::install_github("gaborcsardi/altlist")
```

## Usage

``` r
library(altlist)
```

## Iterate over the rows of a data frame

``` r
for (el in rowwise(mtcars)) {
  print(paste0("row #", el$.idx))
}
#> [1] "row #1"
#> [1] "row #2"
#> [1] "row #3"
#> [1] "row #4"
#> [1] "row #5"
#> [1] "row #6"
#> [1] "row #7"
#> [1] "row #8"
#> [1] "row #9"
#> [1] "row #10"
#> [1] "row #11"
#> [1] "row #12"
#> [1] "row #13"
#> [1] "row #14"
#> [1] "row #15"
#> [1] "row #16"
#> [1] "row #17"
#> [1] "row #18"
#> [1] "row #19"
#> [1] "row #20"
#> [1] "row #21"
#> [1] "row #22"
#> [1] "row #23"
#> [1] "row #24"
#> [1] "row #25"
#> [1] "row #26"
#> [1] "row #27"
#> [1] "row #28"
#> [1] "row #29"
#> [1] "row #30"
#> [1] "row #31"
#> [1] "row #32"
```

``` r
lapply(rowwise(mtcars), function(elmt) { elmt$wt })
#> [[1]]
#> [1] 2.62
#> 
#> [[2]]
#> [1] 2.875
#> 
#> [[3]]
#> [1] 2.32
#> 
#> [[4]]
#> [1] 3.215
#> 
#> [[5]]
#> [1] 3.44
#> 
#> [[6]]
#> [1] 3.46
#> 
#> [[7]]
#> [1] 3.57
#> 
#> [[8]]
#> [1] 3.19
#> 
#> [[9]]
#> [1] 3.15
#> 
#> [[10]]
#> [1] 3.44
#> 
#> [[11]]
#> [1] 3.44
#> 
#> [[12]]
#> [1] 4.07
#> 
#> [[13]]
#> [1] 3.73
#> 
#> [[14]]
#> [1] 3.78
#> 
#> [[15]]
#> [1] 5.25
#> 
#> [[16]]
#> [1] 5.424
#> 
#> [[17]]
#> [1] 5.345
#> 
#> [[18]]
#> [1] 2.2
#> 
#> [[19]]
#> [1] 1.615
#> 
#> [[20]]
#> [1] 1.835
#> 
#> [[21]]
#> [1] 2.465
#> 
#> [[22]]
#> [1] 3.52
#> 
#> [[23]]
#> [1] 3.435
#> 
#> [[24]]
#> [1] 3.84
#> 
#> [[25]]
#> [1] 3.845
#> 
#> [[26]]
#> [1] 1.935
#> 
#> [[27]]
#> [1] 2.14
#> 
#> [[28]]
#> [1] 1.513
#> 
#> [[29]]
#> [1] 3.17
#> 
#> [[30]]
#> [1] 2.77
#> 
#> [[31]]
#> [1] 3.57
#> 
#> [[32]]
#> [1] 2.78
```

## License

MIT © RStudio
