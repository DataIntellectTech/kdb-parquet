\l q/test.q
\l ../qParquet/qparquet.q

show "Generating table and saving";
show example:([] time:.z.p+til 1000000; a:1000000?100; b:1000000?100);
show .pq.settabletofile[`example.parquet;example];

show "initialising EmbedPy functionality";
show .p.import`qparquet;
show f:{[x]tab:.qparquet.py.lib[`:getTable][string x]`;flip .p.wrap[tab][`:to_dict;`list]`};

show "Time to read in using EmbedPy:";
\t:5 f[`example.parquet]

show "Time to read in using our functionality";
\t:5 .pq.getfile[`example.parquet]

hdel`:example.parquet;
show "Done";
