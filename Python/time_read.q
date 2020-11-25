\l p.q

p)import pyarrow.parquet as pq
p)import pandas as pd
p)pfile = pq.read_table(source="../tests/testdata/time32python.parquet")
p)#print(pfile.to_pandas)
p)a=pfile.to_pandas()
//table:.p.get[`a]
p)a.to_csv("./a.csv",index=False)
t:(enlist "T"; enlist ",")0:`:a.csv
t`Time32

