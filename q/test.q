l:`$":libPQ"
o:.Q.def[`init`file`libfile!(1b;`$"tests/testdata/test2.parquet";l);.Q.opt[.z.x]]
`.pq upsert (l 2:(`getparquetlib;1))[]



if[o[`init];show n:.pq.getfilebycols[o[`file];exec name from .pq.getschema[o[`file]]]]

\
Sample lines to run.
af:{[x]`$1_'raze each string x,/:{[x] x where x like "*parquet"}key[x]} `$":tests/testdata/"
af!.pq.getfile each   af