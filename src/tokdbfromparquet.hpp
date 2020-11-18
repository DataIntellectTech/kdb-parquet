int tokdbfromparquet( parquet::StreamReader &os,std::string t, K x) {
    int64_t k;
    os>>k;
std::cout <<  t << " " << k << std::endl;

return 0;
}