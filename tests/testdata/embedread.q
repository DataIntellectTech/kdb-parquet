\l p.q
/params:`filename`variable`row!("simple_example.parquet";`tab;`)
/op:.Q.def[params;.Q.opt[.z.x]]

p)import pyarrow.parquet as pq
p)import pandas as pd
p)def intcast(pfiler):
    timefile = pfiler.to_pandas()
    for col_index in range(len(timefile.columns)):
      datatype = pfiler.schema.types[col_index]
      col_name=timefile.columns[col_index]
      if datatype == "date32[day]":
        timefile[col_name]=pd.to_datetime(timefile[col_name]).dt.strftime("%Y%m%d").astype(int).astype(str)
      elif datatype == "timestamp[ms]" or datatype == "timestamp[us]":
        timefile[col_name]=timefile[col_name].astype(int).astype(str)
      elif datatype == "time32[ms]":
        timefile[col_name]=pd.to_datetime(timefile[col_name], format='%H:%M:%S').astype(int).astype(str)
    return timefile
qintcast:.p.get[`intcast;<]

timeconvert:{[filename];df:(pd:.p.import`pandas)`:DataFrame;
 .p.set[`file;filename];
 .p.set[`pfile;.p.qeval "pq.read_table(source =file)"];
 .p.set[`timefile;.p.qeval "pfile.to_pandas()"];
 .p.set[`newdf;.p.eval "intcast(pfile)"];
 res:df[.p.get[`newdf]][`:to_dict;`list]`;
 res 
 }

