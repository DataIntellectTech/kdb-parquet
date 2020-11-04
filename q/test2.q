l:`$":libPQ"
o:.Q.def[`init`file`libfile!(1b;`$"tests/testdata/out-test2.parquet";l);.Q.opt[.z.x]]
`.pq upsert (l 2:(`getparquetlib;1))[]



//if[o[`init];show n:.pq.getfilebycols[o[`file];exec name from .pq.getschema[o[`file]]]]
tab:(+)`j`f`s`c!(1 2 3;3 4 5.;`q`w`e;("qwe";"wsx";"345"))

.pq.settabletofile[o[`file];tab]
\
Sample lines to run.
af:{[x]`$1_'raze each string x,/:{[x] x where x like "*parquet"}key[x]} `$":tests/testdata/"
af!.pq.getfile each   af