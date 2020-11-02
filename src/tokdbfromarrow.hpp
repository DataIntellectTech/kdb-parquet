// To DO. Deal with chunks.
// Add more data types.
// String Int32 Int 64 and double done.
int arrowtoint32vector(K &ns, std::shared_ptr<arrow::ChunkedArray> arrow)
{
int n=arrow->length();
ns=ktn(KI,n);
//   std::shared_ptr<arrow::Int32Array> arrow_int32_array = (arrow::Int32Array)(arrow);
    auto int32_array = std::static_pointer_cast<arrow::Int32Array>(arrow->chunk(0));
    std::cout << "num chunks is " << arrow->num_chunks() << std::endl;
  ns=ktn(KI,n);
for(int i=0;i<n;i++) {
 kI(ns)[i]= (int)int32_array->Value(i);
}
    return 0;
}

int arrowtoint64vector(K &ns, std::shared_ptr<arrow::ChunkedArray> arrow)
{
    int n=arrow->length();
//   std::shared_ptr<arrow::Int32Array> arrow_int32_array = (arrow::Int32Array)(arrow);
    auto int64_array = std::static_pointer_cast<arrow::Int64Array>(arrow->chunk(0));
    std::cout << "num chunks is " << arrow->num_chunks() << std::endl;
    ns=ktn(KJ,n);
    for(int i=0;i<n;i++) {
        kJ(ns)[i]=int64_array->Value(i);
    }
    return 0;
}
int arrowtoStringvector(K &ns, std::shared_ptr<arrow::ChunkedArray> arrow)
{
    int n=arrow->length();
//   std::shared_ptr<arrow::Int32Array> arrow_int32_array = (arrow::Int32Array)(arrow);
    auto String_array = std::static_pointer_cast<arrow::StringArray>(arrow->chunk(0));
    std::cout << "num chunks is " << arrow->num_chunks() << std::endl;
    ns=ktn(KS,n);
    for(int i=0;i<n;i++) {
        kS(ns)[i]=ss((char *)String_array->GetString(i).c_str());
    }
    return 0;
}
int arrowtoDoublevector(K &ns, std::shared_ptr<arrow::ChunkedArray> arrow)
{
    int n=arrow->length();
//   std::shared_ptr<arrow::Int32Array> arrow_int32_array = (arrow::Int32Array)(arrow);
    auto double_array = std::static_pointer_cast<arrow::DoubleArray>(arrow->chunk(0));
    ns=ktn(KF,n);
    for(int i=0;i<n;i++) {
        kF(ns)[i]=(double)double_array->Value(i);
    }
    return 0;
}
int tokdbfromarrow(K &ns,std::shared_ptr<arrow::ChunkedArray> arrow)
{
  std::string thistype=  arrow->type()->ToString();
  //std::cout << thistype << std::endl;
   if(thistype=="double") {

  arrowtoDoublevector(ns,arrow);
   } else if(thistype=="int64")
   {  arrowtoint64vector(ns,arrow);

   }else if(thistype=="string")
   {
       arrowtoStringvector(ns,arrow);
   }
   else if(thistype=="int32")
   {

       arrowtoint32vector(ns,arrow);
   }
   else
   {
       std::cout << " case is unknown" << std::endl;
   }

  return 0;
}

