# kdb-Apache

The tests/testdata directory contains 3 csv files with randomly generated data. Each field is of a different type and has the schema:
[Time:datetime,float32:32 bit float, float64: 64 bit float, string:string,bool:boolean ]

173 Solace Lib API Function | Description | Arguments | Example usage               
174 ------------------------|-------------|-----------|--------------               
175 init | Initialises a connection to the broker | Dictionary `o` of inputs (see Table 2) | ```.solace.init[d:(`user`password`host`port`loglevel)!(`admin;`admin;`$"192.168.1.48";55555;2)]```
176 getstats | Returns a dictionary of number of messages received, sent, batched and processed | Niladic | `.solace.getstats[]`
177 subscribe | Subscribes to a topic | Topic name | `.solace.subscribe["Default"]` 
178 printargs | Prints all library settings and current values | Niladic | `.solace.printargs[]`
179 disconnect | Disconnects from broker | Niladic | `.solace.disconnect[]`  
