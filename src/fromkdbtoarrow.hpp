// To DO. Deal with chunks.
// Add more data types.
// String Int32 Int 64 and double done.
int kdbtoarrowint32vector(K &ns, std::vector<std::shared_ptr<arrow::Array>>& array)
{
    arrow::Int32Builder i32builder;
    for(int i=0;i<ns->n;i++) {
        i32builder.Append(kI(ns)[i]);
    }
    std::shared_ptr<arrow::Array> i32array;
    i32builder.Finish(&i32array);
    array.push_back(i32array);
    return 0;
}

int kdbtoarrowint64vector(K &ns, std::vector<std::shared_ptr<arrow::Array>>& array)
{
    arrow::Int64Builder i64builder;
    for(int i=0;i<ns->n;i++) {
        i64builder.Append(kJ(ns)[i]);
    }
    std::shared_ptr<arrow::Array> i64array;
    i64builder.Finish(&i64array);
    array.push_back(i64array);
    return 0;
}
int kdbtoarrowStringvector(K &ns, std::vector<std::shared_ptr<arrow::Array>>& array)
{

    return 0;
}
int kdbtoarrowDoublevector(K &ns, std::vector<std::shared_ptr<arrow::Array>>& array)
{
    arrow::DoubleBuilder doublebuilder;
    for(int i=0;i<ns->n;i++) {
        doublebuilder.Append(kF(ns)[i]);
    }
    std::shared_ptr<arrow::Array> doublearray;
    doublebuilder.Finish(&doublearray);
    array.push_back(doublearray);
    return 0;
}
int kdbtoarrowBooleanvector(K &ns, std::vector<std::shared_ptr<arrow::Array>>& array)
{
    arrow::BooleanBuilder booleanbuilder;
    for(int i=0;i<ns->n;i++) {
        booleanbuilder.Append(kG(ns)[i]);
    }
    std::shared_ptr<arrow::Array> booleanarray;
    booleanbuilder.Finish(&booleanarray);
    array.push_back(booleanarray);
    return 0;
}
int kdbtoarrowCharvector(K &ns, std::vector<std::shared_ptr<arrow::Array>>& array)
{
    arrow::StringBuilder stringbuilder;
    for(int i=0;i<ns->n;i++) {
        std::cout << " length wwww  " <<std::endl;
        char m=(char)kG(ns)[i];
        //std::cout << " length wwww  " << mystr <<std::endl;
        stringbuilder.Append(std::string(1,m));
    }
    std::shared_ptr<arrow::Array> stringarray;
    stringbuilder.Finish(&stringarray);
    array.push_back(stringarray);
    return 0;
}


int addcolumntoarray(K column,std::vector<std::shared_ptr<arrow::Array>>& array){
     int ktype=column->t;
    switch(ktype){
        case(1):  return kdbtoarrowBooleanvector(column,array);
        case(6):  return kdbtoarrowint32vector(column,array);
        case(7):  return kdbtoarrowint64vector(column,array);
        case(9):  return kdbtoarrowDoublevector(column,array);
        case(10): return kdbtoarrowCharvector(column,array);
        default:  return kdbtoarrowint64vector(column,array);


    }

}

std::shared_ptr<arrow::Field>createfield(std::string name,int ktype){

    switch(ktype){
        case(1): return arrow::field(name,arrow::boolean());
        case(3): return arrow::field(name,arrow::int64());
        case(6): return arrow::field(name,arrow::int32());
        case(7): return arrow::field(name,arrow::int64());
        case(9): return arrow::field(name,arrow::float64());
        case(10): return arrow::field(name,arrow::utf8());
        default: return  arrow::field(name,arrow::int64());
    }

}

arrow::Status createschemafromkdb(K ns,std::shared_ptr<arrow::Schema> &schema)
{
    K flip =ktd(ns) ;
    //arrow::Field n=arrow::Field();
    std::vector<std::shared_ptr<arrow::Field>> cols;

        K columnNames=kK(flip->k)[0];
        K columnData=kK(flip->k)[1];
        int nCols=columnNames->n;
        for(int i=0;i<nCols;i++) {
           std:: string  name=std::string((char*)kS(columnNames)[i]);
           int ktype=kK(columnData)[i]->t;
         std::shared_ptr<arrow::Field> fld=createfield( name, ktype);
         cols.push_back(fld);
    }
        schema= arrow::schema(cols);
    return s;
}
arrow::Status createarraysfromkdb(K ns,std::vector<std::shared_ptr<arrow::Array>>& array)
{
    K flip =ktd(ns) ;

    K columnData=kK(flip->k)[1];
    int nCols=columnData->n;
    for(int i=0;i<nCols;i++) {
         K kdata=kK(columnData)[i];
        addcolumntoarray(kdata,array);
    }
    return s;
}



int kdbtoarrow(K ns,std::shared_ptr<arrow::Table> &arrow)
{
    std::vector<std::shared_ptr<arrow::Field>> cols;
    std::shared_ptr<arrow::Schema> schema;
    s=createschemafromkdb(ns,schema);

    std::vector<std::shared_ptr<arrow::Array>> array;
    s=createarraysfromkdb(ns,array);
    arrow=arrow::Table::Make(schema, array);

    return 0;
}

