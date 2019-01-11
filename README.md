# RcppPyArrow

This project helps python users and R users exchange data by standardizing on the C++ Arrow library.

Python developers that are building engineering systems may have the need to access R and its large collection of libraries. This can be done by using [rpy2](https://rpy2.readthedocs.io/en/version_2.8.x/), which embeds an R process inside the python process. Python developers can invoke R functions and pass python objects into those functions. However, passing large datasets into the R process can have large overhead.

[Arrow](https://arrow.apache.org/) specifies a language agnostic columnar memory format for data, and its core is written in C++. The main class which is most similar to a dataframe is the [Table Class](https://arrow.apache.org/docs/cpp/classarrow_1_1_table.html). PyArrow is a python library that integrates with Arrow and exposes a [PyArrow Table](https://arrow.apache.org/docs/python/data.html) type. This class can wrap memory that was allocated by the C++ library. R can also wrap memory that was allocated in C++ through Rcpp. Given a pointer to an Arrow Table object, R can construct a dataframe. 

Arrow provides a very convenient mechanism to exchange data between Python and R without having to write anything to disk, and without having to copy any memory. Python developers that needs to pass data through rpy2 more efficiently can create a PyArrow table object, then pass the address of the underlying Arrow Table object to R. R can receive the pointer and instantiate a data frame from it using `RcppPyArrow::RcppReceiveArrowTableFromPython`. This is an efficient transfer of data because it reuses the memory allocated by Arrow in both Python and R, so the transfer from Python to R happens without serialization and without copy. 

# Installation

Your development environment must have access to `libarrow.so` and `libarrow_python.so`. To get these dependencies build the [Arrow C++ project from source](https://github.com/apache/arrow/tree/master/cpp). When running cmake, you will need to make sure to include the flag `-DARROW_PYTHON=ON`.

You will also need Python headers. On Ubuntu this requires installing python-dev using `sudo apt-get install python-dev`.

RcppPyArrow uses a configure script to help compile and link the Rcpp code with `libarrow.so` and `libarrow_python.so`. The configure script needs access to 4 directories: the location of the arrow headers, the location of `libarrow.so` and `libarrow_python.so`, the location of python headers and the location of `libpython2.7.so`. These are passed in to configure using the variables `ARROW_INCLUDE_DIR`, `ARROW_LIB_DIR`, `PYTHON_INCLUDE_DIR`, and `PYTHON_LIB_DIR`. On Ubuntu 16.04 these directories might be

* ARROW_INCLUDE_DIR=/usr/local/include
* ARROW_LIB_DIR=/usr/local/lib
* PYTHON_INCLUDE_DIR=/usr/include/python2.7
* PYTHON_LIB_DIR=/usr/lib/x86_64-linux-gnu/

If that is the case, then RcppPyArrow can be installed with the command
`R CMD INSTALL ./ --configure-vars='ARROW_INCLUDE_DIR=/usr/local/include ARROW_LIB_DIR=/usr/local/lib/ PYTHON_INCLUDE_DIR=/usr/include/python2.7 PYTHON_LIB_DIR=/usr/lib/x86_64-linux-gnu/'`

# Usage

Python developers can use parquet files, arrow files, or Pandas dataframes to make a PyArrow Table.
Using rpy2.rinterface.SexpExtPtr we can get an external pointer to the PyArrow Table object. This pointer can be passed to `RcppPyArrow::RcppReceiveArrowTableFromPython`, which will return a R tibble.

```
import numpy as np
import pandas as pd
import pyarrow as pa

df = pd.DataFrame({"a": [1, 2, 3]})
table = pa.Table.from_pandas(df)

import rpy2.robjects as robjects
import rpy2.rinterface as rinterface

rinterface.initr()
func = robjects.r(
     """
     f = function(inputs) {
       require(RcppPyArrow)
       require(arrow)
       df = RcppReceiveArrowTableFromPython(inputs)
       print (dim(df))
       print (head(df))
     }
     """
)
param = rinterface.SexpExtPtr(table)
response = func(param)
```
