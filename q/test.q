l:`$":libPQ"
o:.Q.def[`init`file`libfile!(1b;`$"tests/testdata/test2.parquet";l);.Q.opt[.z.x]]
`.pq upsert (l 2:(`getparquetlib;1))[]


oo:{[x] .pq.getschema[`$first .z.x]}

if[o[`init];show .pq.getfilebycols[o[`file];exec name from .pq.getschema[o[`file]]]]
