// To DO. Deal with chunks.
// Add more data types.
// String Int32 Int 64 and double done.

#include "base.hpp"

int arrowToInt32Vector(K &ns, std::shared_ptr<arrow::ChunkedArray> arrow)
{
    int n=arrow->length();
    ns=ktn(KI,n);
    auto int32_array = std::static_pointer_cast<arrow::Int32Array>(arrow->chunk(0));
    for(int i=0;i<n;i++) {
        kI(ns)[i]= (int)int32_array->Value(i);
    }
    return 0;
}

int arrowToUInt32Vector(K &ns, std::shared_ptr<arrow::ChunkedArray> arrow)
{
    int n=arrow->length();
    ns=ktn(KJ,n);
    auto uint32_array = std::static_pointer_cast<arrow::UInt32Array>(arrow->chunk(0));
    for(int i=0;i<n;i++) {
        kJ(ns)[i]= (int)uint32_array->Value(i);
    }
    return 0;
}
int arrowToUInt64Vector(K &ns, std::shared_ptr<arrow::ChunkedArray> arrow)
{
    int n=arrow->length();
    ns=ktn(KF,n);
    auto uint64_array = std::static_pointer_cast<arrow::UInt64Array>(arrow->chunk(0));
    ns=ktn(KF,n);
    for(int i=0;i<n;i++) {
        kF(ns)[i]= (float)uint64_array->Value(i);
    }
    return 0;
}
int arrowToUInt16Vector(K &ns, std::shared_ptr<arrow::ChunkedArray> arrow)
{
    int n=arrow->length();
    ns=ktn(KI,n);
    auto uint16_array = std::static_pointer_cast<arrow::UInt16Array>(arrow->chunk(0));
    for(int i=0;i<n;i++) {
        kI(ns)[i]= (int)uint16_array->Value(i);
    }
    return 0;
}
int arrowToInt64Vector(K &ns, std::shared_ptr<arrow::ChunkedArray> arrow)
{
    int n=arrow->length();
    auto int64_array = std::static_pointer_cast<arrow::Int64Array>(arrow->chunk(0));
    ns=ktn(KJ,n);
    for(int i=0;i<n;i++) {
        kJ(ns)[i]=int64_array->Value(i);
    }
    return 0;
}
int arrowToStringVector(K &ns, std::shared_ptr<arrow::ChunkedArray> arrow)
{
    int n=arrow->length();
    auto String_array = std::static_pointer_cast<arrow::StringArray>(arrow->chunk(0));
    ns=ktn(0,n);
    for(int i=0;i<n;i++) {
        std::string nn = String_array->GetString(i);
        int l=nn.length();
        kK(ns)[i]=kpn((char *)nn.c_str(),l);
    }
    return 0;
}
int arrowToDoubleVector(K &ns, std::shared_ptr<arrow::ChunkedArray> arrow)
{
    int n=arrow->length();
    auto double_array = std::static_pointer_cast<arrow::DoubleArray>(arrow->chunk(0));
    ns=ktn(KF,n);
    for(int i=0;i<n;i++) {
        kF(ns)[i]=(double)double_array->Value(i);
    }
    return 0;
}
int arrowToBoolVector(K &ns, std::shared_ptr<arrow::ChunkedArray> arrow)
{
    int n=arrow->length();
    auto boolean_array = std::static_pointer_cast<arrow::BooleanArray>(arrow->chunk(0));
    ns=ktn(KB,n);
    for(int i=0;i<n;i++) {
        kG(ns)[i]=(bool)boolean_array->Value(i);
    }
    return 0;
}

int arrowToTimestampVector(K &ns, std::shared_ptr<arrow::ChunkedArray> arrow, int scale)
{
    int n=arrow->length();
    auto time_array = std::static_pointer_cast<arrow::TimestampArray>(arrow->chunk(0));
    ns=ktn(KP,n);
    for(int i=0;i<n;i++) {
        kJ(ns)[i]=(scale*((long)time_array->Value(i)))-TS_EPOCH_DIFF;
    }
    return 0;
}

int arrowToTimeVector(K &ns, std::shared_ptr<arrow::ChunkedArray> arrow)
{
    int n=arrow->length();
    auto time32_array = std::static_pointer_cast<arrow::Time32Array>(arrow->chunk(0));
    ns=ktn(KT,n);
    for(int i=0;i<n;i++) {
        kI(ns)[i]=(int)time32_array->Value(i);
    }
    return 0;
}

int arrowToTime64Vector(K &ns, std::shared_ptr<arrow::ChunkedArray> arrow,int mult)
{
    int n=arrow->length();
    auto time64_array = std::static_pointer_cast<arrow::Time64Array>(arrow->chunk(0));
    ns=ktn(KN,n);
    for(int i=0;i<n;i++) {
        kJ(ns)[i]=(long)(time64_array->Value(i))*mult;
    }
    return 0;
}

int arrowToDateVector(K &ns, std::shared_ptr<arrow::ChunkedArray> arrow)
{
    int n=arrow->length();
    auto date32_array = std::static_pointer_cast<arrow::Date32Array>(arrow->chunk(0));
    ns=ktn(KD,n);
    for(int i=0;i<n;i++) {
	    //Parquet date format is offset since 1970.01.01. this we need to subtract DATE_EPOCH_DIFF to turn to kdb date.
        kI(ns)[i]=((int)date32_array->Value(i))-DATE_EPOCH_DIFF;
    }
    return 0;
}
int arrowToFloat32Vector(K &ns, std::shared_ptr<arrow::ChunkedArray> arrow)
{
    int n=arrow->length();
    auto float32_array = std::static_pointer_cast<arrow::FloatArray>(arrow->chunk(0));
    ns=ktn(KE,n);
    for(int i=0;i<n;i++) {
        kE(ns)[i]=(float)float32_array->Value(i);
    }
    return 0;
}
int arrowToFloat64Vector(K &ns, std::shared_ptr<arrow::ChunkedArray> arrow)
{
    int n=arrow->length();
    auto date32_array = std::static_pointer_cast<arrow::Date32Array>(arrow->chunk(0));
    ns=ktn(KD,n);
    for(int i=0;i<n;i++) {
        kI(ns)[i]=(int)date32_array->Value(i);
    }
    return 0;
}
int arrowToNullVector(K &ns, std::shared_ptr<arrow::ChunkedArray> arrow)
{
    int n=arrow->length();
    ns=ktn(0,n);
    for(int i=0;i<n;i++) {
        kK(ns)[i]=ktn(0,0);
    }
    return 0;
}

int toKdbFromArrow(K &ns,std::shared_ptr<arrow::ChunkedArray> arrow)
{
    arrow::Type::type typ = arrow->type()->id();

    if (typ == arrow::Type::type::DOUBLE)
        arrowToDoubleVector(ns, arrow);
    else if (typ == arrow::Type::type::FLOAT)
        arrowToFloat32Vector(ns, arrow);
    else if (typ == arrow::Type::type::STRING)
        arrowToStringVector(ns, arrow);
    else if (typ == arrow::Type::type::INT32)
        arrowToInt32Vector(ns, arrow);
    else if (typ == arrow::Type::type::UINT16)
        arrowToUInt16Vector(ns, arrow);
    else if (typ == arrow::Type::type::UINT32)
        arrowToUInt32Vector(ns, arrow);
    else if (typ == arrow::Type::type::UINT64)
        arrowToUInt64Vector(ns, arrow);
    else if (typ == arrow::Type::type::BOOL)
        arrowToBoolVector(ns, arrow);
    else if (typ == arrow::Type::type::TIME32)
        arrowToTimeVector(ns, arrow);
    else if (typ == arrow::Type::type::DATE32)
        arrowToDateVector(ns, arrow);
    else if (typ == arrow::Type::type::NA)
        arrowToNullVector(ns, arrow);
    else if (typ == arrow::Type::type::INT64)
        arrowToInt64Vector(ns, arrow);
    else if (arrow->type()->id() == arrow::Type::type::TIME64 ||
             arrow->type()->id() == arrow::Type::type::TIMESTAMP)
    {
        int precision = 1;
        if(arrow->type()->id() == arrow::Type::type::TIME64)
        {
            if(((arrow::TimeType*)(arrow->type().get()))->unit() == arrow::TimeUnit::MICRO) precision = 1000;
            arrowToTime64Vector(ns,arrow,precision);
        }
        else if (arrow->type()->id() == arrow::Type::type::TIMESTAMP)
        {
            const auto& type = (arrow::TimestampType*)(arrow->type().get());
            if      (type->unit() == arrow::TimeUnit::SECOND)   precision = 1000000000;
            else if (type->unit() == arrow::TimeUnit::MILLI)    precision = 1000000;
            else if (type->unit() == arrow::TimeUnit::MICRO)    precision = 1000;
            arrowToTimestampVector(ns,arrow,precision);
        }
    }
    else
    {
        ns=ktn(0,0);
    }

    return 0;
}

