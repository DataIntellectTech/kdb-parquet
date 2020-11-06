
myo:`init`dir`file`libname`datadir!(1b;`:unit;`;`$"../libPQ";`$"../tests/testdata/")
o:.Q.def[myo;.Q.opt[.z.x]]
.lg.o:{[x]1(.z.P;x)}

//This line probably makes one of the unit tests redundant but its needed.
`.pq upsert (myo[`libname] 2:(`getparquetlib;1))[]

//This line abstracts the location of the test data. [ Morris for each file in the folder myo[`datadir] please expalin whats in it at the bottom o fthis file`
getdatafile:{[y;x] `$string[y],x}[myo[`datadir]]

//Load unit test raw code
\l k4unit.q

//Add in better logic so that if o[`file] is non null we only load those tests.//For now well just laod the directory of tests.


KUltd[o[`dir]]

runtests:{[]
 KUrt[];
 show KUTR;
 show "#####################################";
 show " Failed Tests";
 show select from KUTR where not ok;
 show "#####################################";
 }

if[o[`init];@[runtests;[];{[x] .lg.o[" Error running unit tests"]}]]
