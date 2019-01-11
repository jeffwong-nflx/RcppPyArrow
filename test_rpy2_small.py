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
