# kdb-Apache

Kdb-Apache is an adaptor that is able to convert Kdb Tables into the Apache Parquet table format. The API provides a translation of all Kdb Data types to Apache Parquet and vice versa.

Build Instructions

In the command line run cmake . followed by make to create the new build.
the build version can be checked by entering a q session using q q/test.q and then typing .pq.versioninfo[] to check the build version and date.

Examples
after entering a q session using  q q/test.q
.pq


below are all the functions available in the pq namespace.
q).pq
init             | code
getproperties    | code
getschema        | code
getfile          | code
getfilebycols    | code
settabletofile   | code
versioninfo      | code
getfilebyindicies| code

.pq.getfile reads in a parquet file into a kdb table
```
q).pq.getfile[`$"tests/testdata/simple_example.parquet"]
num chunks is 1
num chunks is 1
one two   three __index_level_0__
---------------------------------
-1  "foo" 1     ,"a"
0   "bar" 0     ,"b"
2.5 "baz" 1     ,"c"
```



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


