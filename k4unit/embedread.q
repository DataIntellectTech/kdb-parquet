\l p.q

p)import pyarrow.parquet as pq
p)import pandas as pd
p)def intcast(pfiler):
    time64=[]
    timefile = pfiler.to_pandas()
    for col_index in range(len(timefile.columns)):
      datatype = pfiler.schema.types[col_index]
      col_name=timefile.columns[col_index]
      if datatype == "date32[day]":
        timefile[col_name]=timefile[col_name].astype(str)
        #timefile[col_name]=pd.to_datetime(timefile[col_name]).dt.strftime("%Y%m%d").astype(int).astype(str)
      elif datatype == "timestamp[ms]" or datatype == "timestamp[us]":
        timefile[col_name]=timefile[col_name].astype(str)
        #timefile[col_name]=timefile[col_name].astype(int).astype(str)
      elif datatype == "time32[ms]":
        timefile[col_name]=timefile[col_name].astype(str)
        #timefile[col_name]=pd.to_datetime(timefile[col_name], format='%H:%M:%S').astype(int).astype(str)
      elif datatype == "time64[ns]":
        timefile[col_name]=timefile[col_name].astype(str)
    return timefile
qintcast:.p.get[`intcast;<]
//p)print(timefile)
timeconvert:{[filename];df:(pd:.p.import`pandas)`:DataFrame;
 .p.set[`file;"../tests/testdata/",filename];
 .p.set[`pfile;.p.eval "pq.read_table(source =file)"];
 .p.set[`types;.p.eval "pfile.schema.types"]
 .p.set[`timefile;.p.eval "pfile.to_pandas()"];
 .p.eval "print(timefile)";
 .p.set[`newdf;.p.eval "intcast(pfile)"];
 .p.set[`time64_indices;.p.eval "[i for i, x in enumerate(types) if x == 'time64[ns]']"]; 
 ind:.p.get[`time64_indices]`;
 show ind;
 res:df[.p.get[`newdf]][`:to_dict;`list]`;
 /a:.p.get[`time64];
 /show a`; 
 res
 }

