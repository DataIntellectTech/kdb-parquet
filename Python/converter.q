p)import pandas as pd

p)import pyarrow.parquet as pq
p)def converter():
    #filename=sys.argv[1]
    #row = sys.argv[2]
    #pfile=pq.read_table(source=str(filename)))
    #print(pfile.to_pydict()[str(row)])[1].hour
     filename = "../tests/testdata/time32python.parquet"
     pfile=pq.read_table(source = filename)
     output=pfile.to_pydict()["Time32"]
     print(output)
     small_list=[]
     big_list = []

     for i in ["hour","minute","second","microsecond"]:
          for j in range(len(output)):
              print((f"output[{j}].{i}"),eval(f"output[{j}].{i}"))
              small_list.append(eval(f"output[{j}].{i}"))
          big_list.append(small_list)
          small_list=[]
     hourlist=big_list[0]
     minutelist=big_list[1]
     secondlist=big_list[2]
     microsecondlist=big_list[3]
     return big_list
converter:.p.get[`converter;<]
times_list:converter[]
time32_list:(01:00:00.000000*times_list[0])+(00:01:00.000000*times_list[1])+(00:00:01.000000*times_list[2])+(00:00:00.001*times_list[3])

