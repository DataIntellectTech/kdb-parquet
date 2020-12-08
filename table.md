| Table Kdb Api Function | Description                   | Arguments            | Usage                                    | Example Usage                                     | 
|------------------------|-------------------------------|----------------------|------------------------------------------|---------------------------------------------------|
| Init                   | Initialize                    |                      |                                          |                                                   |  
| .pq.getproperties      |                               |                      |                                          |                                                   |   
| .pq.getschema          | shows columns and their types | &lt;filepath&gt;           | .pq.getschema[&lt;filepath&gt;]           |.pq.getschema[`` ` ``$"tests/testdata/simple_example.parquet"]|   
| .pq.getfile            | retrieves table               | &lt;filepath&gt;           | .pq.getfile[&lt;filepath&gt;]             | .pq.getfile`` [`$ ``"tests/testdata/simple_example.parquet"] |   
| .pq.getfilebycols      | retrives columns from tables  | &lt;filepath&gt; &lt;col_list&gt; | .pq.getfilebycols[&lt;filepath&gt;;&lt;col_list&gt;] |.pq.getfilebycols[getdatafile "simple_example.parquet";]       |
| .pq.settabletofile     | saves to a file               | &lt;filepath&gt;&lt;table&gt;    | .pq.settabletofile[&lt;filepath&gt;;&lt;table&gt;]   | alltab:([]c:("h";"w");b:tabletofile[`` ` ``here;alltab] |
| .pq.versioninfo        | shows build version and date  | no arguments         |                                          | .pq.versioninfo[]                                 |
| .pq.getfilebyindices   |                               |                      |                                          |                                                   |
|                        |                               |                      |                                          |                                                   |
