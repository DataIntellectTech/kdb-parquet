# kdb-Apache

Kdb-Apache is an library that is able to convert kdb tables to and from the Apache Parquet table format. The library provides a translation of most common kdb primitive data types to Apache Parquet equivilent. The library provides similiar functionality to the library at https://github.com/rianoc/qParquet
, however the librray does not utilize the embedpy interface and potentially avoids an extra translation step when encodinga nd decoding files.

## Build Instructions

After cloning the repository from GitHub the package and examples can be built by executing cmake and then executing then make. The test folder contains a number of test scripts and a suite of unit tests has been supplied and discussed below. Please note that various standard utilities such as make and cmake are required. The package has been tested on vanillia Linux installs, though no reason exists why it cant be prted to other operating systems. 

## Examples
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

.pq.getschema reads in the column names and parquet types of the parquet file
```
q).pq.getschema[`$"tests/testdata/simple_example.parquet"]
name                type
----------------------------
"one"               "double"
"two"               "string"
"three"             "bool"
"__index_level_0__" "string"
```


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

.pq.getfilebycols reads in columns specified in a symbol list of the parquet file
```
q).pq.getfilebycols[`$"tests/testdata/simple_example.parquet";`one`two]
num chunks is 1
one two
---------
-1  "foo"
0   "bar"
2.5 "baz"
```
.pq.settabletofile saves a kdb table (second argument) to the filepath in the first argument which can then be read in as before using getfile:
```
alltab:([] c:("h";"w"); f:(21.5;22.6); i:(25;26); b:(1b;0b)) .pq.settabletofile[`here;alltab]
```

.pq.versioninfo[] shows build version info which can be updated as described in the Build Instructions section.
q).pq.versioninfo[]
builddatetime| "Wed Nov 11 17:40:03 2020"
buildinfo    | "7.5.0"



The tests/testdata directory contains 3 csv files with randomly generated data. Each field is of a different type and has the schema:
[Time:datetime,float32:32 bit float, float64: 64 bit float, string:string,bool:boolean ]






| Table Kdb Api Function | Description                   | Arguments            | Usage                                    | Example Usage                                                            |
|------------------------|-------------------------------|----------------------|------------------------------------------|--------------------------------------------------------------------------|
| Init                   | Initialize                    |                      |                                          |                                                                          |
| .pq.getproperties      |                               |                      |                                          |                                                                          |
| .pq.getschema          | shows columns and their types | <filepath>           | .pq.getschema[<filepath>]                | .pq.getschema[`$"tests/testdata/simple_example.parquet"]                 |
| .pq.getfile            | retrieves table               | <filepath>           | .pq.getfile[<filepath>]                  | .pq.getfile[`$"tests/testdata/simple_example.parquet"]                   |
| .pq.getfilebycols      | retrives columns from tables  | <filepath><col_list> | .pq.getfilebycols[<filepath>;<col_list>] | .pq.getfilebycols[getdatafile "simple_example.parquet";`one`two]         |
| .pq.settabletofile     | saves to a file               | <filepath><table>    | .pq.settabletofile[<filepath>;<table>]   | ```alltab:([]c:("h";"w");b:(1b;0b))  .pq.settabletofile[`here;alltab]``` |
| .pq.versioninfo        | shows build version and date  | no arguments         |                                          | .pq.versioninfo[]                                                        |
| .pq.getfilebyindices   |                               |                      |                                          |                                                                          |
|                        |                               |                      |                                          |                                                                          |

Unit Tests are automated using the K4unit testing library from KX
https://github.com/simongarland/k4unit

Our tests are run using the master.q file which has 2 flags to indicate whether the user wishes the tests to be printed to the screen or not and which .pq namespace function to run unit tests for. The default is verbose:2 which prints the test to the screen and for all the tests to be run. 
q master.q -verbose "2" -file "getfile.csv"


```
17
2020.11.12T18:59:36.166 start
2020.11.12T18:59:36.166 :unit/getfile.csv 12 test(s)
q).pq.getfile[1]
\ts q)@[.pq.getfile;1;1b]
q)98h= type .pq.getfile getdatafile "test2.parquet"
num chunks is 1
q).pq.getfile[getdatafile "doesntexist"]
Could not get table schema
q)`error=@[.pq.getfile;getdatafile "doesntexist";{[x] `$x}]
Could not get table schema
q)2878=count .pq.getfile[getdatafile "test2.parquet"]
num chunks is 1
q)@[.pq.getfile; "info.txt";1b]
q).pq.getfile[``]
\ts q)timetab:([]time:.z.T+3?10;int: 1 2 3)
\ts q).pq.settabletofile[`there;timetab]
q)timetab~.pq.getfile[`there]
num chunks is 1
q).pq.getfile[`q]
Could not get table schema
2020.11.12T18:59:36.220 end
action ms bytes lang code                                                      repeat file              msx bytesx ok okms okbytes valid timestamp
----------------------------------------------------------------------------------------------------------------------------------------------------------------
fail   0  0     q    .pq.getfile[1]                                            1      :unit/getfile.csv 0   0      1  1    1       1     2020.11.12T18:59:36.166
run    0  0     q    @[.pq.getfile;1;1b]                                       1      :unit/getfile.csv 0   1024   1  1    1       1     2020.11.12T18:59:36.166
true   0  0     q    98h= type .pq.getfile getdatafile "test2.parquet"         1      :unit/getfile.csv 0   0      1  1    1       1     2020.11.12T18:59:36.208
fail   0  0     q    .pq.getfile[getdatafile "doesntexist"]                    1      :unit/getfile.csv 0   0      1  1    1       1     2020.11.12T18:59:36.208
true   0  0     q    `error=@[.pq.getfile;getdatafile "doesntexist";{[x] `$x}] 1      :unit/getfile.csv 0   0      1  1    1       1     2020.11.12T18:59:36.208
true   0  0     q    2878=count .pq.getfile[getdatafile "test2.parquet"]       1      :unit/getfile.csv 0   0      1  1    1       1     2020.11.12T18:59:36.218
true   0  0     q    @[.pq.getfile; "info.txt";1b]                             1      :unit/getfile.csv 0   0      1  1    1       1     2020.11.12T18:59:36.218
fail   0  0     q    .pq.getfile[``]                                           1      :unit/getfile.csv 0   0      1  1    1       1     2020.11.12T18:59:36.218
run    0  0     q    timetab:([]time:.z.T+3?10;int: 1 2 3)                     1      :unit/getfile.csv 0   2368   1  1    1       1     2020.11.12T18:59:36.218
run    0  0     q    .pq.settabletofile[`there;timetab]                        1      :unit/getfile.csv 0   0      0  1    1       0     2020.11.12T18:59:36.219
true   0  0     q    timetab~.pq.getfile[`there]                               1      :unit/getfile.csv 0   0      0  1    1       1     2020.11.12T18:59:36.220
fail   0  0     q    .pq.getfile[`q]                                           1      :unit/getfile.csv 0   0      1  1    1       1     2020.11.12T18:59:36.220
"#####################################"
" Failed Tests"
action ms bytes lang code                               repeat file              msx bytesx ok okms okbytes valid timestamp
-----------------------------------------------------------------------------------------------------------------------------------------
run    0  0     q    .pq.settabletofile[`there;timetab] 1      :unit/getfile.csv 0   0      0  1    1       0     2020.11.12T18:59:36.219
true   0  0     q    timetab~.pq.getfile[`there]        1      :unit/getfile.csv 0   0      0  1    1       1     2020.11.12T18:59:36.220
"#####################################"
q)
```
