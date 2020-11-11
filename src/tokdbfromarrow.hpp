// To DO. Deal with chunks.
// Add more data types.
// String Int32 Int 64 and double done.
int arrowtoint32vector(K &ns, std::shared_ptr<arrow::ChunkedArray> arrow)
{
int n=arrow->length();
  ns=ktn(KI,n);
    auto int32_array = std::static_pointer_cast<arrow::Int32Array>(arrow->chunk(0));
  ns=ktn(KI,n);
for(int i=0;i<n;i++) {
 kI(ns)[i]= (int)int32_array->Value(i);
}
    return 0;
}

int arrowtoint64vector(K &ns, std::shared_ptr<arrow::ChunkedArray> arrow)
{
    int n=arrow->length();
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
    ns=ktn(0,n);
    for(int i=0;i<n;i++) {
        std::string nn = String_array->GetString(i);
        int l=nn.length();
        kK(ns)[i]=kpn((char *)nn.c_str(),l);
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
int arrowtoBoolvector(K &ns, std::shared_ptr<arrow::ChunkedArray> arrow)
{
    int n=arrow->length();
//   std::shared_ptr<arrow::Int32Array> arrow_int32_array = (arrow::Int32Array)(arrow);
    auto boolean_array = std::static_pointer_cast<arrow::BooleanArray>(arrow->chunk(0));
    ns=ktn(KB,n);
    for(int i=0;i<n;i++) {
        kG(ns)[i]=(bool)boolean_array->Value(i);
    }
    return 0;
}
int arrowtoTimevector(K &ns, std::shared_ptr<arrow::ChunkedArray> arrow)
{
    int n=arrow->length();
//   std::shared_ptr<arrow::Int32Array> arrow_int32_array = (arrow::Int32Array)(arrow);
    auto time32_array = std::static_pointer_cast<arrow::Time32Array>(arrow->chunk(0));
    ns=ktn(KT,n);
    for(int i=0;i<n;i++) {
        kI(ns)[i]=(int)time32_array->Value(i);
    }
    return 0;
}
int arrowtoDatevector(K &ns, std::shared_ptr<arrow::ChunkedArray> arrow)
{
    int n=arrow->length();
//   std::shared_ptr<arrow::Int32Array> arrow_int32_array = (arrow::Int32Array)(arrow);
    auto date32_array = std::static_pointer_cast<arrow::Date32Array>(arrow->chunk(0));
    ns=ktn(KD,n);
    for(int i=0;i<n;i++) {
        kI(ns)[i]=(int)date32_array->Value(i);
    }
    return 0;
}
int arrowtofloat32vector(K &ns, std::shared_ptr<arrow::ChunkedArray> arrow)
{
    int n=arrow->length();
//   std::shared_ptr<arrow::Int32Array> arrow_int32_array = (arrow::Int32Array)(arrow);
    auto float32_array = std::static_pointer_cast<arrow::FloatArray>(arrow->chunk(0));
    ns=ktn(KF,n);
    for(int i=0;i<n;i++) {
        kF(ns)[i]=(double)float32_array->Value(i);
    }
    return 0;
}
int arrowtofloat64vector(K &ns, std::shared_ptr<arrow::ChunkedArray> arrow)
{
    int n=arrow->length();
//   std::shared_ptr<arrow::Int32Array> arrow_int32_array = (arrow::Int32Array)(arrow);
    auto date32_array = std::static_pointer_cast<arrow::Date32Array>(arrow->chunk(0));
    ns=ktn(KD,n);
    for(int i=0;i<n;i++) {
        kI(ns)[i]=(int)date32_array->Value(i);
    }
    return 0;
}

int tokdbfromarrow(K &ns,std::shared_ptr<arrow::ChunkedArray> arrow)
{
  std::string thistype=  arrow->type()->ToString();
  std::cout << arrow.get()->type()->ToString() << "wwww" << std::endl;
    std::cout << arrow.get()->length() << " length wwww" << std::endl;
   if(thistype=="double") {
       arrowtoDoublevector(ns,arrow);
   }else if(thistype=="float")
   {  arrowtofloat32vector(ns,arrow);

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
   else if(thistype=="bool")
   {

       arrowtoBoolvector(ns,arrow);
   }
   else if(thistype=="time32[ms]")
   {

       arrowtoTimevector(ns,arrow);
   }
   else if(thistype=="date32[day]")
   {

       arrowtoDatevector(ns,arrow);
   }
   else
   {
       ns=ktn(0,arrow->length());

       std::cout << " case is unknown" << arrow->length()  << std::endl;
   }

  return 0;
}

