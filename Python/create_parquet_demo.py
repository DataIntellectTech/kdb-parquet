import numpy as np

import pandas as pd
import sys
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
filename=sys.argv[1]

pq.write_table(table, filename)
pfile = pq.read_table(source="./"+str(filename))
#simple_example2.parquet")
#pfile = pq.read_table(table)
pfile.to_pandas(),"Schema: {}".format(pfile.schema)
