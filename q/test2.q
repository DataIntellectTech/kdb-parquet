l:`$":libPQ"
o:.Q.def[`init`file`libfile!(1b;`$"tests/testdata/out-test2.parquet";l);.Q.opt[.z.x]]
`.pq upsert (l 2:(`getparquetlib;1))[]



//if[o[`init];show n:.pq.getfilebycols[o[`file];exec name from .pq.getschema[o[`file]]]]
tab:(+)`j`f`s`c!(1 2 3;3 4 5.;`q`w`e;("qwe";"wsx";"345"))
tab2:update j:i,t:t+i,d:d+i from 10000#(+)`j`f`i`c`t`d!(1 2 3;1 3 4.1;1 2 3i;"123";12:00:00.000;.z.D)
@[system;"rm myfile.test";1b]
.pq.settabletofile[o[`file];tab2]
//show .pq.getfile[o[`file]]
\
Sample lines to run.
af:{[x]`$1_'raze each string x,/:{[x] x where x like "*parquet"}key[x]} `$":tests/testdata/"
af!.pq.getfile each   af