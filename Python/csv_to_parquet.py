import numpy as np
import csv
import pandas as pd
import random as rand
import pandas as pd
import pyarrow.parquet as pq
import pyarrow as pa
from datetime import datetime, timedelta
import string



'''This code block creates a CSV file with num_rows number of rows'''

min_year=1900
max_year=datetime.now().year

start = datetime(min_year, 1, 1, 00, 00, 00)
years = max_year - min_year+1
end = start + timedelta(days=365 * years)
random_date = start + (end - start) * rand.random()
num_rows=20
with open("csv1.csv","w",newline="") as file:
  writer = csv.writer(file)
  # writer.writerow(["Time","float32","float64","int16","int32","string","bool"])
  writer.writerow(["Timestamp","float32","float64","string","bool","uint16","uint32","uint64","Date",])


  for i in range(num_rows):
 
    writer.writerow([np.datetime64('2019-01-03T00:02:11')+rand.randint(0, 100),\
                     np.float32(rand.uniform(1.0, 3.0)),\
                     np.float64(rand.uniform(1.0,3.0)),\
                    "".join(rand.choice(string.ascii_uppercase + string.digits) for _ in range(10)),\
                    bool(rand.getrandbits(1)),\
                         rand.randint(1,20),\
                     rand.randint(1,20),\
                     rand.randint(1,20),\
                     random_date.date(),\
    ])

'''write_parquet_file creates a parquet File with name in the write_table function'''

# read csv into pandas dataframe and write dataframe to parquet1.parquet
def write_parquet_file():
    # custom_date_parser = lambda x: datetime.strptime(x,"%YYYY-%mm-%ddT%HH:%MM:%SS")
    # default date_parser is of format 2019-01-03T00:02:11
    df = pd.read_csv('./csv1.csv',parse_dates=['Timestamp',"Date"])#,date_parser=custom_date_parser)

        # df.to_parquet('./parquetfile.parquet')
        # pa.int64() exists
    fields = [
                pa.field("Timestamp",pa.timestamp("ms")),
                pa.field("float32",pa.float32()),
                pa.field("float64",pa.float64()),
                pa.field("string",pa.string()),
              
                pa.field("bool",pa.bool_()),
                pa.field("uint16",pa.uint16()),
                pa.field("uint32",pa.uint32()),#converts int32 into int64
                pa.field("uint64",pa.uint64()),
                pa.field("Date",pa.date32()),
    ]
    
    my_schema = pa.schema(fields)

    table1 = pa.Table.from_pandas(df, schema=my_schema, preserve_index=False)
 

    # table1 = pa.Table.from_pandas(df)
    pq.write_table(table1, 'parquet1.parquet',coerce_timestamps="ms")

write_parquet_file()

'''reads the parquet file into a pandas dataframe and prints it along with its schema.
'''
def read_parquet_file():
  pfile = pq.read_table(source="./parquet1.parquet")
  return pfile.to_pandas(),"Schema: {}".format(pfile.schema)

read_parquet_file()

# Alternative method for later
# def write_parquet_file2():
#   df.to_parquet('./anotherparquetfile.parquet',use_deprecated_int96_timestamps=True)
