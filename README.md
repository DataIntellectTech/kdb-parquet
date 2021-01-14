# Kdb-Parquet

Kdb-Parquet is a library that is able to convert kdb tables to and from the Apache Parquet table format. The library provides a translation of the most common kdb+ primitive data types to Apache Parquet equivalent and vice versa. The codebase provides similar functionality to the library [here](https://github.com/rianoc/qParquet), however, the library does not utilize the embedpy interface and potentially avoids an extra translation step when encoding and decoding datasets.

## Build Instructions

First step is to clone the kdb-Parquet repository as shown below.

`kdb@linux:~$ git clone https://github.com/AquaQAnalytics/kdb-parquet`

After cloning the repository from GitHub the package and examples can be built by executing ```cmake .``` and then ```make```. The test folder contains a number of test scripts and a suite of unit tests has been supplied and discussed below. Please note that various standard utilities such as make and cmake are required. The package has been tested on vanilla Linux installs, though no reason exists why it can't be ported to other operating systems.


`kdb@linux:~/kdb-Parquet$ cmake .`

-- Configuring done

-- Generating done

-- Build files have been written to: /home/kdb/kdb-Parquet

`kdb@linux:~/kdb-Parquet$ make`

[100%] Built target PQ

 

## Examples

Simple examples are available in the test file supplied. These are supplied for reading, writing and inspecting parquet files and demonstrated.

```
(base) kdb@linux:~/parquet/kdb-Parquet$ q q/examples.q
KDB+ 4.0 2020.06.18 Copyright (C) 1993-2020 Kx Systems
l64/ 24()core 128387MB **********************************************

"Parquet file reading examples"
============================================
Saving sample table: .pq.settabletofile[file;tab]
0i
Reading sample table: .pq.getfile[file]
j f d          s
-------------------
1 3 2020.12.15 ,"a"
2 4 2020.12.15 ,"b"
3 5 2020.12.15 ,"c"
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
1 3 2020.12.15
2 4 2020.12.15
3 5 2020.12.15
============================================
 Good bye
```

## Data type mappings 

The parquet intrinsic types are mapped according to the table below when reading and writing to and from kdb+. In some cases assumptions have been made, especially when considering symbol and certain temporal data types. Where possible `getfile` and `settabletofile` should encode and decode fields so that the functions are essentially the reciprocals of one another.   

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

## Streaming functionality

An example of the streaming functionality is also included in the test file supplied.
```
(base) kdb@linux:~/parquet/kdb-Parquet$ q q/streamexample.q
KDB+ 4.0 2020.06.18 Copyright (C) 1993-2020 Kx Systems
l64/ 24()core 128387MB **********************************************

"Parquet file streaming example"
============================================
Saving sample table: .pq.settabletofile[file;tab]
0i
Creating function for streamread : f:{[x] show x}
Streaming sample table: .pq.streamread[file;`f]
1
3f
2050.12.18
,"a"
2
4f
2050.12.18
,"b"
3
5f
2050.12.18
,"c"
============================================
 Good bye
````

## API Usage Table

| Table Kdb API Function | Description                   | Arguments            | Example Usage                            | 
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

Unit Tests are automated using the K4unit testing library from KX. Our tests are run using the master.q file which has 2 flags to indicate whether the user wishes the tests to be printed to the screen or not, and which .pq namespace function to run unit tests for. The default is verbosity is 2, which prints the test to the screen and for all the tests to be run. 

```
kdb@linux:~/kdb-Parquet/k4unit$ q master.q -file getfile.csv -verbose 1
KDB+ 4.0 2020.07.15 Copyright (C) 1993-2020 Kx Systems
l64/ 24()core 128387MB **********************************************

`.pq
24
2020.12.11T09:27:00.682 start
2020.12.11T09:27:00.682 :unit/getfile.csv 20 test(s)
Could not get table schema
Could not get table schema
Could not get table schema
Could not get table schema
2020.12.11T09:27:00.712 end
action ms bytes lang code                                                                   repeat file              msx bytesx ok okms okbytes valid timestamp 
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
fail   0  0     q    .pq.getfile[1]                                                         1      :unit/getfile.csv 0   0      1  1    1       1     2020.12.11T09:27:00.682
fail   0  0     q    .pq.getfile[`q]                                                        1      :unit/getfile.csv 0   0      1  1    1       1     2020.12.11T09:27:00.683
fail   0  0     q    .pq.getfile["q" 1]                                                     1      :unit/getfile.csv 0   0      1  1    1       1     2020.12.11T09:27:00.683
run    0  0     q    @[.pq.getfile;1;1b]                                                    1      :unit/getfile.csv 0   1024   1  1    1       1     2020.12.11T09:27:00.683
true   0  0     q    98h= type .pq.getfile getdatafile "test2.parquet"                      1      :unit/getfile.csv 0   0      1  1    1       1     2020.12.11T09:27:00.696
fail   0  0     q    .pq.getfile[getdatafile "doesntexist.parquet"]                         1      :unit/getfile.csv 0   0      1  1    1       1     2020.12.11T09:27:00.696
true   0  0     q    `error=@[.pq.getfile;getdatafile "doesntexist.parquet";{[x] `$x}]      1      :unit/getfile.csv 0   0      1  1    1       1     2020.12.11T09:27:00.696
fail   0  0     q    .pq.getfile[getdatafile "info.txt"]                                    1      :unit/getfile.csv 0   0      1  1    1       1     2020.12.11T09:27:00.697
true   0  0     q    2878=count .pq.getfile[getdatafile "test2.parquet"]                    1      :unit/getfile.csv 0   0      1  1    1       1     2020.12.11T09:27:00.706
true   0  0     q    @[.pq.getfile; "info.txt";1b]                                          1      :unit/getfile.csv 0   0      1  1    1       1     2020.12.11T09:27:00.706
fail   0  0     q    .pq.getfile[``]                                                        1      :unit/getfile.csv 0   0      1  1    1       1     2020.12.11T09:27:00.706
true   0  0     q    `argtype=@[.pq.getfile;``;{[x] `$x}]                                   1      :unit/getfile.csv 0   0      1  1    1       1     2020.12.11T09:27:00.706
run    0  0     q    timetab:([]time:.z.T+3?10;int: 1 2 3)                                  1      :unit/getfile.csv 0   2368   1  1    1       1     2020.12.11T09:27:00.706
run    0  0     q    .pq.settabletofile[`there;timetab]                                     1      :unit/getfile.csv 1   928    1  1    1       1     2020.12.11T09:27:00.707
true   0  0     q    timetab~.pq.getfile[`there]                                            1      :unit/getfile.csv 0   0      1  1    1       1     2020.12.11T09:27:00.708
run    0  0     q    nulltab:([]f:(0n;0n); j:(0Nj;0Nj);i:(0Ni;0Ni);t:(0Nt;0Nt);c:(" ";" ")) 1      :unit/getfile.csv 0   4352   1  1    1       1     2020.12.11T09:27:00.708
run    0  0     q    .pq.settabletofile[`here;nulltab]                                      1      :unit/getfile.csv 1   928    1  1    1       1     2020.12.11T09:27:00.710
true   0  0     q    nulltab~.pq.getfile[`here]                                             1      :unit/getfile.csv 0   0      0  1    1       1     2020.12.11T09:27:00.712
run    0  0     q    hdel `:here                                                            1      :unit/getfile.csv 0   528    1  1    1       1     2020.12.11T09:27:00.712
run    0  0     q    hdel `:there                                                           1      :unit/getfile.csv 0   528    1  1    1       1     2020.12.11T09:27:00.712
"#####################################"
" Failed Tests"
action ms bytes lang code                       repeat file              msx bytesx ok okms okbytes valid timestamp
---------------------------------------------------------------------------------------------------------------------------------
true   0  0     q    nulltab~.pq.getfile[`here] 1      :unit/getfile.csv 0   0      0  1    1       1     2020.12.11T09:27:00.712
"#####################################"
```

## Comparison to Kx embedPy interface

The [embedPy interface](https://code.kx.com/q/ml/embedpy/) is a flexible API that allows python and kdb+ to share memory and interact with each other. In theory the universe of functionality available within python is opened up to kdb+. However this flexibility does come at a certain cost when it comes to performance. In the example below we create a simple parquet file with 1 million rows and a small number of columns and import this file into kdb+ via the embedpy interface and for comparison directly via the functionality available in this repository. The example clearly shows how the translation of data into python and then subsequently to kdb+ has a large overhead, with the import being twice as slow. When working interactively with kdb+ this may not be an issue, however when speed is an issue for applications such as EOD exports from an external system this may be an important factor. Furthermore, the number of temporal variables supported natively, rather than needing special transformations when involving embedpy may be important. With that said the embedpy suite has a number of other features that make it generally a more useful tool. This example is meant to highlight the improvements that can be made by writing a custom application in this specific instance.

```
(kdb) kdb@linux:~/parquet/kdb-Parquet$ q comparison.q
KDB+ 4.0 2020.07.15 Copyright (C) 1993-2020 Kx Systems
l64/ 24()core 128387MB **********************************************

`.pq
"Generating table and saving"
time                          a  b
-----------------------------------
2020.12.14D13:01:06.648155000 81 12
2020.12.14D13:01:06.648155001 2  10
2020.12.14D13:01:06.648155002 80 1
2020.12.14D13:01:06.648155003 96 90
2020.12.14D13:01:06.648155004 95 73
2020.12.14D13:01:06.648155005 94 90
2020.12.14D13:01:06.648155006 72 43
2020.12.14D13:01:06.648155007 87 90
2020.12.14D13:01:06.648155008 89 84
2020.12.14D13:01:06.648155009 58 63
2020.12.14D13:01:06.648155010 79 93
2020.12.14D13:01:06.648155011 64 54
2020.12.14D13:01:06.648155012 21 38
2020.12.14D13:01:06.648155013 31 97
2020.12.14D13:01:06.648155014 75 88
2020.12.14D13:01:06.648155015 78 58
2020.12.14D13:01:06.648155016 17 68
2020.12.14D13:01:06.648155017 44 45
2020.12.14D13:01:06.648155018 62 2
2020.12.14D13:01:06.648155019 1  39
..
0i
"initialising EmbedPy functionality"
{[f;x]embedPy[f;x]}[foreign]enlist
{[x]tab:.qparquet.py.lib[`:getTable][string x]`;flip .p.wrap[tab][`:to_dict;`list]`}
"Time to read in using EmbedPy:"
10981
"Time to read in using native functionality"
883
"Done"
```

## Use Case - New York Taxi Data

A use case can be demonstrated using [NYC taxi data](https://www1.nyc.gov/site/tlc/about/tlc-trip-record-data.page) from the NYC Taxi and Limousine Commission.
```
(base) kdb@linux:~/parquet/kdb-Parquet$ q nyccomparison.q
KDB+ 4.0 2020.06.18 Copyright (C) 1993-2020 Kx Systems
l64/ 24()core 128387MB **********************************************

`.pq
VendorID tpep_pickup_datetime          tpep_dropoff_datetime         passenge..
-----------------------------------------------------------------------------..
1        2020.01.01D00:28:15.000000000 2020.01.01D00:33:03.000000000 1       ..
1        2020.01.01D00:35:39.000000000 2020.01.01D00:43:04.000000000 1       ..
1        2020.01.01D00:47:41.000000000 2020.01.01D00:53:52.000000000 1       ..
1        2020.01.01D00:55:23.000000000 2020.01.01D01:00:14.000000000 1       ..
2        2020.01.01D00:01:58.000000000 2020.01.01D00:04:16.000000000 1       ..
2        2020.01.01D00:09:44.000000000 2020.01.01D00:10:37.000000000 1       ..
2        2020.01.01D00:39:25.000000000 2020.01.01D00:39:29.000000000 1       ..
2        2019.12.18D15:27:49.000000000 2019.12.18D15:28:59.000000000 1       ..
2        2019.12.18D15:30:35.000000000 2019.12.18D15:31:35.000000000 4       ..
1        2020.01.01D00:29:01.000000000 2020.01.01D00:40:28.000000000 2       ..
1        2020.01.01D00:55:11.000000000 2020.01.01D01:12:03.000000000 2       ..
1        2020.01.01D00:37:15.000000000 2020.01.01D00:51:41.000000000 1       ..
1        2020.01.01D00:56:27.000000000 2020.01.01D01:21:44.000000000 1       ..
2        2020.01.01D00:21:54.000000000 2020.01.01D00:27:31.000000000 1       ..
2        2020.01.01D00:38:01.000000000 2020.01.01D01:15:21.000000000 1       ..
1        2020.01.01D00:15:35.000000000 2020.01.01D00:27:06.000000000 3       ..
1        2020.01.01D00:41:20.000000000 2020.01.01D00:44:22.000000000 1       ..
1        2020.01.01D00:56:38.000000000 2020.01.01D01:13:34.000000000 1       ..
2        2020.01.01D00:08:21.000000000 2020.01.01D00:25:29.000000000 1       ..
1        2020.01.01D00:25:39.000000000 2020.01.01D00:27:05.000000000 1       ..
..
"Running an example select query:"
"select from taxidatajan2020 where passenger_count > 5"
VendorID tpep_pickup_datetime          tpep_dropoff_datetime         passenge..
-----------------------------------------------------------------------------..
1        2020.01.01D00:54:57.000000000 2020.01.01D00:58:50.000000000 6       ..
2        2020.01.01D00:17:28.000000000 2020.01.01D00:37:16.000000000 6       ..
2        2020.01.01D00:38:43.000000000 2020.01.01D00:54:55.000000000 6       ..
2        2020.01.01D00:24:07.000000000 2020.01.01D00:27:48.000000000 6       ..
2        2020.01.01D00:39:43.000000000 2020.01.01D00:45:55.000000000 6       ..
2        2020.01.01D00:48:29.000000000 2020.01.01D00:55:05.000000000 6       ..
2        2020.01.01D00:45:19.000000000 2020.01.01D01:00:10.000000000 6       ..
2        2020.01.01D00:47:13.000000000 2020.01.01D00:54:52.000000000 6       ..
2        2020.01.01D00:24:13.000000000 2020.01.01D00:27:36.000000000 6       ..
2        2020.01.01D00:42:03.000000000 2020.01.01D01:01:42.000000000 6       ..
2        2020.01.01D00:13:01.000000000 2020.01.01D00:22:33.000000000 6       ..
2        2020.01.01D00:38:34.000000000 2020.01.01D00:41:49.000000000 6       ..
2        2020.01.01D00:21:44.000000000 2020.01.01D00:35:27.000000000 6       ..
2        2020.01.01D00:42:56.000000000 2020.01.01D00:59:50.000000000 6       ..
2        2020.01.01D00:53:40.000000000 2020.01.02D00:18:40.000000000 6       ..
2        2020.01.01D00:35:59.000000000 2020.01.01D00:44:34.000000000 6       ..
2        2020.01.01D00:45:38.000000000 2020.01.01D00:50:19.000000000 6       ..
2        2020.01.01D00:52:23.000000000 2020.01.01D00:55:58.000000000 6       ..
2        2020.01.01D00:04:41.000000000 2020.01.01D00:12:37.000000000 6       ..
2        2020.01.01D00:19:03.000000000 2020.01.01D00:37:13.000000000 6       ..
..
"Parquet loading times:"
9459
"CSV loading times:"
11989
"Loading in parquet, using a reduced number of columns"
1904
```

## Future Work

The next stage of this interface will be to potentially explore the possibility of allowing multiple kdb+ sessions to share data via the in-memory arrow format and a shared memory segment. In effect large tables would be loaded into one shared memory segment and made accessible via multiple different applications, potentially with the arrow table being appended to from a master process. For certain applications this could remove the need for IPC communication when operating on data sets and potentially reduce overall memory usage of the system as a whole. The actual practicalities of this design have not yet been considered.  

## Further Enquiries

For more information, please contact AquaQ at info@aquaq.co.uk.

