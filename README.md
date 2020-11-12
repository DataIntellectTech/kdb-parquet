# kdb-Apache

The tests/testdata directory contains 3 csv files with randomly generated data. Each field is of a different type and has the schema:
[Time:datetime,float32:32 bit float, float64: 64 bit float, string:string,bool:boolean ]


|Pyarrow API function   | Description  | Arguments  | Example Usage  |
|---|---|---|---|
| init  | Initialise Code  |   |   |
| getproperties  |   |   |   |
| getschema  | shows columns and their types  | [`:filepath]  |`.pq.getschema[`$"tests/testdata/simple_example.parquet"]   |
| .pq.getfile  | retrieves table  | [`:filepath]  |`.pq.getfile[`$"tests/testdata/simple_example.parquet"]   |
| .pq.getfilebycols  | retrieves columns from tables  | [`:filepath;col_list]  |```.pq.getfilebycols[getdatafile "simple_example.parquet";`one`two]``` |
| .pq.settabletofile | saves table to a file  | [`:filepath;table]  |  ```alltab:([] c:("h";"w"); f:(21.5;22.6); i:(25;26); b:(1b;0b)) .pq.settabletofile[`here;alltab]``` |
| .pq.versioninfo  |  shows build version and date  |  [] | .pq.versioninfo[]  |
| .getfilebyindices  |  |   |   |


