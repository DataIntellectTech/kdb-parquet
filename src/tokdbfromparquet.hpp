#include "base.hpp"
#include <iostream>

template <typename TFunc, typename TArg>
void convertStream2k(NewStreamReader& os, K& x, K(*func)(TFunc))
{
    TArg val;
    os >> val;
    x = (*func)(static_cast<TFunc>(val));
}

template <typename T>
void convertStream2k(NewStreamReader& os, K& x, K(*func)(T))
{
    convertStream2k<T,T>(os,x,func);
}

template <typename T, int PRECISION>
void convertStream2kTimestamp(NewStreamReader& os, K& x)
{
    T val;
    os >> val;
    x = ktj(-KP, PRECISION*val.count() - TS_EPOCH_DIFF);
}

void convertStream2kDateTime32(NewStreamReader& os, K& x, K(*func)(I), int precision, int offset)
{
    int32_t v;
    os.customint32(v);
    x = func(precision*v-offset);
}

template <typename T>
int getPrecision(const std::shared_ptr<arrow::Field>& arrow, arrow::TimeUnit::type unit)
{
    const auto& arrowCast = static_cast<const T&>(*(arrow->type()));
    if (arrowCast.unit() == unit) return 1000;
    return 1;
}

int toKdbFromParquet( NewStreamReader& os, const std::shared_ptr<arrow::Field>& arrow, K& x)
{
    bool is_parsed{ true };
    auto arrow_type = arrow->type()->id();
    if      (arrow::Type::type::DOUBLE == arrow_type)     convertStream2k<F>(os,x,kf);
    else if (arrow::Type::type::FLOAT  == arrow_type)     convertStream2k<F,float>(os,x,ke);
    else if (arrow::Type::type::INT64  == arrow_type)     convertStream2k<J,int64_t>(os,x,kj);
    else if (arrow::Type::type::INT32  == arrow_type)     convertStream2k<I,int32_t>(os,x,ki);
    else if (arrow::Type::type::UINT16 == arrow_type)     convertStream2k<I,uint16_t>(os,x,ki);
    else if (arrow::Type::type::UINT32 == arrow_type)     convertStream2k<J,uint32_t>(os,x,kj);
    else if (arrow::Type::type::UINT64 == arrow_type)     convertStream2k<F,uint64_t>(os,x,kf);
    else if (arrow::Type::type::BOOL   == arrow_type)     convertStream2k<I,bool>(os,x,kb);
    else if (arrow::Type::type::TIME32 == arrow_type)     convertStream2kDateTime32(os,x,kt,getPrecision<arrow::Time32Type>(arrow,arrow::TimeUnit::SECOND),0);
    else if (arrow::Type::type::DATE32 == arrow_type)     convertStream2kDateTime32(os,x,kd,1,DATE_EPOCH_DIFF);
    else if (arrow::Type::type::TIME64 == arrow_type)
    {
        int precision = getPrecision<arrow::Time64Type>(arrow, arrow::TimeUnit::MICRO);
        int64_t v;
        os.customint64(v);
        x = ktj(-KN, precision*v);
    }
    else if (arrow::Type::type::STRING == arrow_type)
    {
        std::string v;
        os >> v;
        x = kpn(const_cast<char*>(v.c_str()), v.size());
    }
    else if (arrow::Type::type::TIMESTAMP == arrow_type)
    {
        const auto& arrow_timestamp = static_cast<const arrow::TimestampType&>(*(arrow->type()));
        if (arrow_timestamp.unit() != arrow::TimeUnit::NANO && arrow_timestamp.timezone().size())
        {
            if      (arrow_timestamp.unit() == arrow::TimeUnit::MILLI) convertStream2kTimestamp<std::chrono::milliseconds,1000000>(os,x);
            else if (arrow_timestamp.unit() == arrow::TimeUnit::MICRO) convertStream2kTimestamp<std::chrono::microseconds,1000>(os,x);
            else                                                       is_parsed = false;
        }
        else
        {
            int64_t val;
            os >> val;
            int precision = 1;
            if      (arrow_timestamp.unit() == arrow::TimeUnit::MICRO) precision = 1000;
            else if (arrow_timestamp.unit() == arrow::TimeUnit::MILLI) precision = 1000000;
            else if (arrow_timestamp.unit() == arrow::TimeUnit::SECOND)precision = 1000000000;
            x = ktj(-KP, precision*val - TS_EPOCH_DIFF);
        }
    }
    else
    {
        is_parsed = false;
    }

    if (!is_parsed) throw std::exception{};
    return 0;
}
