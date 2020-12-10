# kdb-Apache

Kdb-Apache is an library that is able to convert kdb tables to and from the Apache Parquet table format. The library provides a translation of most common kdb primitive data types to Apache Parquet equivilent and vice versa. The codebase provides similiar functionality to the library [here](https://github.com/rianoc/qParquet), however the library does not utilize the embedpy interface and potentially avoids an extra translation step when encoding and decoding files.

## Build Instructions

First step is to clone the TorQ-Quanthouse repository as shown below.

`mstranger@homer:~$ git clone https://github.com/AquaQAnalytics/kdb-Apache`

After cloning the repository from GitHub the package and examples can be built by executing cmake and then executing then make. The test folder contains a number of test scripts and a suite of unit tests has been supplied and discussed below. Please note that various standard utilities such as make and cmake are required. The package has been tested on vanillia Linux installs, though no reason exists why it cant be ported to other operating systems.

`mstranger@homer:~/kdb-Apache$ cmake .`

`mstranger@homer:~/kdb-Apache$ make`

 

## Examples
Simple examples are available in the test file supplied. Examples are supplied for reading, writing and inspecting parquet files anddemonstarted.

```
kdb@linux$ q q/examples.q
KDB+ 3.6 2020.02.14 Copyright (C) 1993-2020 Kx Systems
l64/ 4(16)core 15999MB **********************************************

"Parquet file reading examples"
============================================
Saving sample table: .pq.settabletofile[file;tab]
0i
Reading sample table: .pq.getfile[file]
j f d          s   
-------------------
1 3 2020.12.06 ,"a"
2 4 2020.12.06 ,"b"
3 5 2020.12.06 ,"c"
Inspecting sample table: .pq.getschema[file]
name type         
------------------
,"j" "int64"      
,"f" "double"     
,"d" "date32[day]"
,"s" "string"     
Reading subset of columns from file: .pq.getfilebycols[file;`j`f`d]
j f d         
--------------
1 3 2020.12.06
2 4 2020.12.06
3 5 2020.12.06
Streaming sample table: .pq.streamread[file]
code[`test.parquet]
============================================
 Good bye 
```
## Data type mappings ##

The parquet intrinsic types are mapped according to the table below when reading and writing to and from kdb+. In some cases assumptions have been made, especially when considering symbol data types andcertain temporal data types. Where possible `getfile` and `settabletofile` should encode and decode fields so that the functions are essentially the reciprocals of one another.   

|  Parquet Type  | kdb Type | Example |
| ------------- | ------------- | ------------|
| Timestamp(ms) | Timestamp     | 2001.01.01D12:01:01:01.000000|
| Date32(day)   | Date          | 2001.01.01                   |
| Time32        | Time          | 12:01:01.000                |
| Time64        | nyi           |    |
| int64         | Long          |          12|                  
| string        | array of characters||
| float32       | Float           |1.0|
| float64       | Float           |1.0|
| bool          | Boolean         |0b|
| uint16        | Int             |12i|
| uint32        | Long            |12|
| uint64        | Float           |12.3|
| decimal128    | nyi             ||
| binary        | nyi             ||
| Null          | 0h list         |()|

## Api Usage Table

| Table Kdb Api Function | Description                   | Arguments            | Example Usage                            | 
|------------------------|-------------------------------|----------------------|------------------------------------------|
| Init                   | Initialize                    |                      |                                          | 
| .pq.getproperties      |                               |                      |                                          | 
| .pq.getschema          | shows columns and their types | &lt;filepath&gt;     | ``.pq.getschema[`simple_example.parquet]``|   
| .pq.getfile            | retrieves table               | &lt;filepath&gt;           |  ``.pq.getfile[`simple_example.parquet]`` |   
| .pq.getfilebycols      | retrives columns from tables  | &lt;filepath&gt; &lt;col_list&gt; |``.pq.getfilebycols[`simple_example.parquet;`cols1`col2]``|
| .pq.settabletofile     | saves to a file               | &lt;filepath&gt;&lt;table&gt;|  ``.pq.settabletofile[`here;([]a:1 2 3;b:3 4 5)]`` |
| .pq.versioninfo        | shows build version and date  |         |               `.pq.versioninfo[]`                                 |
| .pq.streamread         |                               |                      |                                          |




## Unit Testing
Unit Tests are automated using the K4unit testing library from KX
Our tests are run using the master.q file which has 2 flags to indicate whether the user wishes the tests to be printed to the screen or not and which .pq namespace function to run unit tests for. The default is verbose:2 which prints the test to the screen and for all the tests to be run. 

```
 mstranger@homer:~/kdb-Apache/k4unit$ q master.q -verbose 2 -file getfile.csv
KDB+ 4.0 2020.07.15 Copyright (C) 1993-2020 Kx Systems
l64/ 24()core 128387MB mstranger homer 127.0.1.1 EXPIRE 2021.06.30 AquaQ #59946

`.pq
24
2020.12.10T17:32:23.290 start
2020.12.10T17:32:23.290 :unit/getfile.csv 20 test(s)
q).pq.getfile[1]
q).pq.getfile[`q]
Could not get table schema
q).pq.getfile["q" 1]
\ts q)@[.pq.getfile;1;1b]
q)98h= type .pq.getfile getdatafile "test2.parquet"
q).pq.getfile[getdatafile "doesntexist.parquet"]
Could not get table schema
q)`error=@[.pq.getfile;getdatafile "doesntexist.parquet";{[x] `$x}]
Could not get table schema
q).pq.getfile[getdatafile "info.txt"]
Could not get table schema
q)2878=count .pq.getfile[getdatafile "test2.parquet"]
q)@[.pq.getfile; "info.txt";1b]
q).pq.getfile[``]
q)`argtype=@[.pq.getfile;``;{[x] `$x}]
\ts q)timetab:([]time:.z.T+3?10;int: 1 2 3)
\ts q).pq.settabletofile[`there;timetab]
q)timetab~.pq.getfile[`there]
\ts q)nulltab:([]f:(0n;0n); j:(0Nj;0Nj);i:(0Ni;0Ni);t:(0Nt;0Nt);c:(" ";" "))
\ts q).pq.settabletofile[`here;nulltab]
q)nulltab~.pq.getfile[`here]
\ts q)hdel `:here
\ts q)hdel `:there
2020.12.10T17:32:23.505 end
action ms bytes lang code                                                                   repeat file              msx bytesx ok okms okbytes valid timestamp 
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
fail   0  0     q    .pq.getfile[1]                                                         1      :unit/getfile.csv 0   0      1  1    1       1     2020.12.10T17:32:23.290
fail   0  0     q    .pq.getfile[`q]                                                        1      :unit/getfile.csv 0   0      1  1    1       1     2020.12.10T17:32:23.296
fail   0  0     q    .pq.getfile["q" 1]                                                     1      :unit/getfile.csv 0   0      1  1    1       1     2020.12.10T17:32:23.296
run    0  0     q    @[.pq.getfile;1;1b]                                                    1      :unit/getfile.csv 0   1024   1  1    1       1     2020.12.10T17:32:23.296
true   0  0     q    98h= type .pq.getfile getdatafile "test2.parquet"                      1      :unit/getfile.csv 0   0      1  1    1       1     2020.12.10T17:32:23.387
fail   0  0     q    .pq.getfile[getdatafile "doesntexist.parquet"]                         1      :unit/getfile.csv 0   0      1  1    1       1     2020.12.10T17:32:23.387
true   0  0     q    `error=@[.pq.getfile;getdatafile "doesntexist.parquet";{[x] `$x}]      1      :unit/getfile.csv 0   0      1  1    1       1     2020.12.10T17:32:23.387
fail   0  0     q    .pq.getfile[getdatafile "info.txt"]                                    1      :unit/getfile.csv 0   0      1  1    1       1     2020.12.10T17:32:23.432
true   0  0     q    2878=count .pq.getfile[getdatafile "test2.parquet"]                    1      :unit/getfile.csv 0   0      1  1    1       1     2020.12.10T17:32:23.451
true   0  0     q    @[.pq.getfile; "info.txt";1b]                                          1      :unit/getfile.csv 0   0      1  1    1       1     2020.12.10T17:32:23.451
fail   0  0     q    .pq.getfile[``]                                                        1      :unit/getfile.csv 0   0      1  1    1       1     2020.12.10T17:32:23.451
true   0  0     q    `argtype=@[.pq.getfile;``;{[x] `$x}]                                   1      :unit/getfile.csv 0   0      1  1    1       1     2020.12.10T17:32:23.451
run    0  0     q    timetab:([]time:.z.T+3?10;int: 1 2 3)                                  1      :unit/getfile.csv 0   2368   1  1    1       1     2020.12.10T17:32:23.451
run    0  0     q    .pq.settabletofile[`there;timetab]                                     1      :unit/getfile.csv 42  928    1  1    1       1     2020.12.10T17:32:23.493
true   0  0     q    timetab~.pq.getfile[`there]                                            1      :unit/getfile.csv 0   0      1  1    1       1     2020.12.10T17:32:23.496
run    0  0     q    nulltab:([]f:(0n;0n); j:(0Nj;0Nj);i:(0Ni;0Ni);t:(0Nt;0Nt);c:(" ";" ")) 1      :unit/getfile.csv 0   4352   1  1    1       1     2020.12.10T17:32:23.496
run    0  0     q    .pq.settabletofile[`here;nulltab]                                      1      :unit/getfile.csv 4   928    1  1    1       1     2020.12.10T17:32:23.501
true   0  0     q    nulltab~.pq.getfile[`here]                                             1      :unit/getfile.csv 0   0      0  1    1       1     2020.12.10T17:32:23.505
run    0  0     q    hdel `:here                                                            1      :unit/getfile.csv 0   528    1  1    1       1     2020.12.10T17:32:23.505
run    0  0     q    hdel `:there                                                           1      :unit/getfile.csv 0   528    1  1    1       1     2020.12.10T17:32:23.505
"#####################################"
" Failed Tests"
action ms bytes lang code                       repeat file              msx bytesx ok okms okbytes valid timestamp
---------------------------------------------------------------------------------------------------------------------------------
true   0  0     q    nulltab~.pq.getfile[`here] 1      :unit/getfile.csv 0   0      0  1    1       1     2020.12.10T17:32:23.505
"#####################################"
```
## Comparison to EmbedPy interface
We have a script demo.q that utilises embedpy to convert python datatypes from a pandas dataframe to kdb datatypes. Below is a comparison of the time taken to read in a file using this interface with the timeconvert function to ParquetLib.

mstranger@homer:~/kdb-Apache/tests/testdata$ q embedread.q
KDB+ 4.0 2020.07.15 Copyright (C) 1993-2020 Kx Systems
l64/ 24()core 128387MB mstranger homer 127.0.1.1 EXPIRE 2021.06.30 AquaQ #59946

timing simple table read with embedpy interface: q)\t timeconvert "simple_example.parquet"
one  | -1          2.5
two  | "foo" "bar" "baz"
three| 1     0     1
13

## Future Work



