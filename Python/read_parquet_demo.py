import sys

filename=sys.argv[1]
import pyarrow.parquet as pq
import pandas as pd
def read_parquet_file(parquetfile):
  pfile = pq.read_table(source=parquetfile)
  print(pfile.to_pandas())
  print("Schema: {}".format(pfile.schema))

read_parquet_file(filename)
