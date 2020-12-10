import numpy as np

import pandas as pd
import sys
import pyarrow as pa



df = pd.DataFrame()
df["Time32"]=pd.date_range("2015-07", periods=5, freq='H').time
fields=[pa.field("Time32",pa.time32("ms"))]
my_schema = pa.schema(fields)
table = pa.Table.from_pandas(df,schema=my_schema)
import pyarrow.parquet as pq
pq.write_table(table, "../tests/testdata/time32python.parquet")

