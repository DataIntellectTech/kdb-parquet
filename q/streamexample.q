0N!"Parquet file streaming example";

l:`$":libPQ"
file:`$"test.parquet"
o:.Q.def[`init`file`libfile!(1b;file;l);.Q.opt[.z.x]]
`. upsert o;

//Load library from default location
`.pq upsert (l 2:(`getparquetlib;1))[];

//Load library from default location
`.pq upsert (l 2:(`getparquetlib;1))[];


//Create a simple table
tab:([]j:1 2 3;f:3 4 5.;d:.z.d;s:`a`b`c)

initpq:{[x]
   @[hdel;hsym file;0b];
   -1 "============================================";
   -1 "Saving sample table: ",s:".pq.settabletofile[file;tab]"; 
   show value s;
   -1 "Creating blank list for each element to be inserted into: ",s:"t:()";
   show value s;
   -1 "Creating function for streamread : ",s:"f:{[x] t::t,x}";
   show value s;
   -1 "Streaming sample table: ",s:".pq.streamread[file;`f]";
   show value s;
   -1 "Reformatting sample table: ",s:"flip(col)!flip(count col:`$exec name from .pq.getschema(file)) cut t";
   show value s;
   -1 "============================================";
   -1 " Good bye ";
   /-exit[0];  
     }
if[init;initpq[]];
