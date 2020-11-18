import numpy as np

import pandas as pd

import pyarrow as pa

df = pd.DataFrame({'one': [1,2,3],
                   'two': ['a', 'b', 'c'],
                   'three': [True, False, True]},
                   index=list('abc'))
fields=[
pa.field("one",pa.float64()),
pa.field("two",pa.string()),
              
pa.field("three",pa.bool_()),
]
my_schema = pa.schema(fields)
table = pa.Table.from_pandas(df,schema=my_schema)

import pyarrow.parquet as pq

pq.write_table(table, 'simple_example2.parquet')
pfile = pq.read_table(source="./simple_example2.parquet")
pfile.to_pandas(),"Schema: {}".format(pfile.schema)
