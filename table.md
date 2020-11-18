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
