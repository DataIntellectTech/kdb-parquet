
myo:`init`dir`file`libname`datadir`verbose!(1b;`:unit;`;`$"../libPQ";`$"../tests/testdata/";2)
o:.Q.def[myo;.Q.opt[.z.x]]
.lg.o:{[x]1(.z.P;x)}

//This line probably makes one of the unit tests redundant but its needed.
`.pq upsert (myo[`libname] 2:(`getparquetlib;1))[]

//This line abstracts the location of the test data. [ Morris for each file in the folder myo[`datadir] please expalin whats in it at the bottom o fthis file`
getdatafile:{[y;x] `$string[y],x}[myo[`datadir]]
/.KU.VERBOSE:o`verbose


//Load unit test raw code
\l k4unit.q
.KU.VERBOSE:o`verbose

//Add in better logic so that if o[`file] is non null we only load those tests.//For now well just laod the directory of tests.


/KUltd[o[`dir]]
$[o[`file]~`;KUltd[o[`dir]];KUltf[` sv o[`dir],o[`file]]]

runtests:{[]
 KUrt[];
 show KUTR;
 show "#####################################";
 show " Failed Tests";
 show select from KUTR where not ok;
 show "#####################################";
 }

if[o[`init];@[runtests;[];{[x] .lg.o[" Error running unit tests"]}]]
