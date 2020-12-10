import numpy as np
import csv
import pandas as pd
import random as rand
import pandas as pd
import pyarrow.parquet as pq
import pyarrow as pa
from datetime import datetime, timedelta
import string
import decimal
parquet_path = "./tests/testdata/"
parquet_name = "timer.parquet"


'''This code block creates a CSV file with num_rows number of rows'''

# min_year=2000
# max_year=datetime.now().year

# start = datetime(min_year, 1, 10, 00, 00, 00)
# years = max_year - min_year+1
# end = start + timedelta(days=365 * years)
# random_date = start + (end - start) * rand.random()
num_rows=3
with open("csv1.csv","w",newline="") as file:
  writer = csv.writer(file)
  # writer.writerow(["Time","float32","float64","int16","int32","string","bool"])
  writer.writerow(["Timestamp","Date"])


  for i in range(num_rows):
 
    writer.writerow([np.datetime64('2019-01-03T00:02:11')+rand.randint(0, 100),\
                   
                    #  random_date.date(),\
])

'''write_parquet_file creates a parquet File with name in the write_table function'''

# read csv into pandas dataframe and write dataframe to parquet1.parquet
def write_parquet_file():
    # custom_date_parser = lambda x: datetime.strptime(x,"%YYYY-%mm-%ddT%HH:%MM:%SS")
    # default date_parser is of format 2019-01-03T00:02:11
    date="2020-11"
    df = pd.read_csv('./csv1.csv',parse_dates=['Timestamp'])#,date_parser=custom_date_parser)
    df["Time32"]=pd.date_range("2020-01", periods=num_rows, freq='H').time
    df["Time64"]=pd.date_range(date, periods=num_rows, freq='H').time
    # df["Date32"]=pd.date_range(date, periods=num_rows, freq='M').date
    df["Date"]=pd.date_range(date, periods=num_rows, freq='M').date
    df["Timestamp_us"]=pd.date_range(date, periods=num_rows, freq='H').astype("datetime64[ns]")
    
        # df.to_parquet('./parquetfile.parquet')
        # pa.int64() exists
    fields = [
                pa.field("Timestamp",pa.timestamp("ms")),
               
                pa.field("Date",pa.date32()),
          
               pa.field("Time32",pa.time32("ms")),
               pa.field("Time64",pa.time64("ns")),
              # pa.field("Date32",pa.date32()),
              # pa.field("Date",pa.date64()),
              pa.field("Timestamp_us",pa.timestamp("us")),
              


    ]
    
    my_schema = pa.schema(fields)

    table1 = pa.Table.from_pandas(df, schema=my_schema, preserve_index=False)
 

    # table1 = pa.Table.from_pandas(df)
    pq.write_table(table1, parquet_path+parquet_name,allow_truncated_timestamps=False)#,)#)#,coerce_timestamps="ms")

write_parquet_file()

'''reads the parquet file into a pandas dataframe and prints it along with its schema.
'''
def read_parquet_file():
  pfile = pq.read_table(source=parquet_path+parquet_name)
  return pfile,pfile.to_pandas()

read_parquet_file()

# Alternative method for later
# def write_parquet_file2():
#   df.to_parquet('./anotherparquetfile.parquet',use_deprecated_int96_timestamps=True)
