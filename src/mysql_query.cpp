#include "mysql_query.h"

MySQL_Query::MySQL_Query()
{
    _result = NULL;
    _row = NULL;
}

MySQL_Query::MySQL_Query(MYSQL_RES *result)
{
    initResult(result);
}

//MySQL_Query::MySQL_Query(MySQL *connection)
//{
//    _connection = connection;
//}

MySQL_Query::~MySQL_Query()
{
    mysql_free_result(_result);
}

void MySQL_Query::setResultSource(MYSQL_RES *result)
{
    initResult(result);
}

void MySQL_Query::initResult(MYSQL_RES *result)
{
    _result = result;
    _numFields = mysql_num_fields(_result);
    MYSQL_FIELD *field;
    for(unsigned int i = 0; (field = mysql_fetch_field(_result)); i++)
    {
        _fieldNames[(const char*)(field->name)] = i;
    }
}

bool MySQL_Query::nextRow()
{
    if (!(_row = mysql_fetch_row(_result)))
    {
        return false;
    }
    return true;
}

MySQL_Result MySQL_Query::getValue(std::string fieldName)
{
    return MySQL_Result((const char*)(_row[_fieldNames[fieldName]]));
}

MySQL_Result MySQL_Query::getValue(int fieldNum)
{
    return MySQL_Result((const char*)(_row[fieldNum]));
}

bool MySQL_Query::empty()
{
    return (_result == NULL);
}

// MySQL_Result Class

MySQL_Result::MySQL_Result(std::string data)
{
    _data = data;
}

MySQL_Result::~MySQL_Result()
{

}

int MySQL_Result::toInt()
{
    return Result_Cast <int>(_data);
}

bool MySQL_Result::toBool()
{
    return (bool)(Result_Cast <int>(_data));
}

long long MySQL_Result::toLongLong()
{
    return Result_Cast <long long>(_data);
}

double MySQL_Result::toDouble()
{
    return Result_Cast <double>(_data);
}

std::string MySQL_Result::toString()
{
    return _data;
}

template <class T>
T MySQL_Result::Result_Cast(std::string what)
{
    T x;
    std::stringstream ss(what);
    ss >> x;
    return x;
}
