show taxidatajan2020:.pq.getfile[`$"q/taxidatajan2020.parquet"]
show "Running an example select query:"
show "select from taxidatajan2020 where passenger_count > 5"
show select from taxidatajan2020 where passenger_count > 5
show "Parquet loading times:"
\t .pq.getfile[`$"q/taxidatajan2020.parquet"]
show "CSV loading times:"
\t taxidatajan2020:("IPPIFICIIIIIFFIFFF";enlist ",") 0: `:tests/testdata/yellow_tripdata_202001.csv
show "Loading in parquet, using reduced columns"
show ".pq.getfilebycols[`$"q/taxidatajan2020.parquet";`tpep_pickup_datetime`tpep_dropoff_datetime`passenger_count`trip_distance]"
\t .pq.getfilebycols[`$"q/taxidatajan2020.parquet";`tpep_pickup_datetime`tpep_dropoff_datetime`passenger_count`trip_distance]
