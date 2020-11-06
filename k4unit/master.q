
myo:`init`dir`file`libname!(1b;`:unit;`;`$"../libPQ")
o:.Q.def[myo;.Q.opt[.z.x]]
.lg.o:{[x]1(.z.P;x)}
//Load unit test raw code
\l k4unit.q

//Add in better logic so that if o[`file] is non null we only load those tests.//For now well just laod the directory of tests.


KUltd[o[`dir]]

runtests:{[]
 KUrt[];
 show KUTR;
 }

if[o[`init];@[runtests;[];{[x] .lg.o[" Error running unit tests"]}]]
