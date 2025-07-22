// To DO. Deal with chunks.
// Add more data types.
// String Int32 Int 64 and double done.

#include "base.hpp"

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
        char m=(char)kG(ns)[i];
        stringbuilder.Append(std::string(1,m));
    }
    std::shared_ptr<arrow::Array> stringarray;
    stringbuilder.Finish(&stringarray);
    array.push_back(stringarray);
    return 0;
}
int kdbtoarrowSymbolvector(K &ns, std::vector<std::shared_ptr<arrow::Array>>& array)
{
    arrow::StringBuilder stringbuilder;
    for(int i=0;i<ns->n;i++) {
        std::string m((char*)(kS(ns)[i]));
        stringbuilder.Append(m);
    }
    std::shared_ptr<arrow::Array> stringarray;
    stringbuilder.Finish(&stringarray);
    array.push_back(stringarray);

    return 0;
}
int kdbtoarrowTimevector(K &ns, std::vector<std::shared_ptr<arrow::Array>>& array)
{
    arrow::Time32Builder timebuilder(arrow::time32(arrow::TimeUnit::MILLI),arrow::default_memory_pool());

    for(int i=0;i<ns->n;i++) {
        long m=(long)kI(ns)[i];
        timebuilder.Append(m);
    }
    std::shared_ptr<arrow::Array> timearray;
    timebuilder.Finish(&timearray);
    array.push_back(timearray);
    return 0;
}
int kdbtoarrowDate32vector(K &ns, std::vector<std::shared_ptr<arrow::Array>>& array)
{

    arrow::Date32Builder date32builder;
    //Parquet dates are from 1970.01.01. this need to add on DATE_EPOCH_DIFF days.
    for(int i=0;i<ns->n;i++) {
        int m=((int)kI(ns)[i])+DATE_EPOCH_DIFF;
        date32builder.Append(m);
    }
    std::shared_ptr<arrow::Array> date32array;
    date32builder.Finish(&date32array);
    array.push_back(date32array);
    return 0;
}
int kdbtoarrowTimestampvector(K &ns, std::vector<std::shared_ptr<arrow::Array>>& array)
{
    auto timestamp_type = std::make_shared<arrow::TimestampType>(arrow::TimeUnit::NANO);
    arrow::TimestampBuilder timestampbuilder(timestamp_type,arrow::default_memory_pool());
    // Parquet timestamps are are from midnight 1970.01.01. Need to add `TS_EPOCH_DIFF` to match kdb's 2000.01.01 epoch.
    for(int i=0;i<ns->n;i++) {
        long long m = ((long)(kJ(ns)[i])) + TS_EPOCH_DIFF;
        timestampbuilder.Append(m);
    }
    std::shared_ptr<arrow::Array> timestamparray;
    timestampbuilder.Finish(&timestamparray);
    array.push_back(timestamparray);
    return 0;
}
int kdbtoarrowMixedlist(K &ns, std::vector<std::shared_ptr<arrow::Array>>& array)
{
    //Mixed lists and or nested lists not supported for now.
    throw( myexception);
    return 0;
}
int addcolumntoarray(K column,std::vector<std::shared_ptr<arrow::Array>>& array){
     int ktype=column->t;
    switch(ktype){
        case(0):  return kdbtoarrowMixedlist(column,array);
        case(1):  return kdbtoarrowBooleanvector(column,array);
        case(6):  return kdbtoarrowint32vector(column,array);
        case(7):  return kdbtoarrowint64vector(column,array);
        case(9):  return kdbtoarrowDoublevector(column,array);
        case(10): return kdbtoarrowCharvector(column,array);
        case(11): return kdbtoarrowSymbolvector(column,array);
        case(12): return kdbtoarrowTimestampvector(column,array);
        case(14): return kdbtoarrowDate32vector(column,array);
        case(19): return kdbtoarrowTimevector(column,array);
        default:  return kdbtoarrowint64vector(column,array);


    }

}

std::shared_ptr<arrow::Field>createfield(std::string name,int ktype){

    switch(ktype){
        case(0): return arrow::field(name,arrow::null());
        case(1): return arrow::field(name,arrow::boolean());
        case(3): return arrow::field(name,arrow::int64());
        case(6): return arrow::field(name,arrow::int32());
        case(7): return arrow::field(name,arrow::int64());
        case(9): return arrow::field(name,arrow::float64());
        case(10): return arrow::field(name,arrow::utf8());
        case(11): return arrow::field(name,arrow::utf8());
        case(12): return arrow::field(name,arrow::timestamp(arrow::TimeUnit::NANO));
        case(14): return arrow::field(name,arrow::date32());
        case(19): return arrow::field(name,arrow::time32(arrow::TimeUnit::MILLI));
        default: ;
    }
   throw myexception;


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

