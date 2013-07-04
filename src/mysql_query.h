#ifndef MYSQL_RESULT_H
#define MYSQL_RESULT_H

#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <map>
#include <sstream>

#include <mysql.h>

class MySQL_Result
{
public:
    explicit MySQL_Result(std::string data);
    ~MySQL_Result();
    int toInt();
    long long toLongLong();
    bool toBool();
    double toDouble();
    std::string toString();
    //std::wstring toWstring();

private:
    template <class T>
    T Result_Cast(std::string what);

    std::string _data;
};

class MySQL_Query
{
public:
    explicit MySQL_Query();
    explicit MySQL_Query(MYSQL_RES *result);
    //explicit MySQL_Query(MySQL *connection);
    ~MySQL_Query();

    void setResultSource(MYSQL_RES *result);
    void initResult(MYSQL_RES *result);

    bool empty();

    //bool query(std::string query);

    bool nextRow();
    MySQL_Result getValue(std::string fieldName);
    MySQL_Result getValue(int fieldNum);
    /*MySQL_Result& operator=(MYSQL_RES *_res)
    {
        if (this == _res)
        {
            return *this;
        }
        _result = _res;
        return *this;
    } */

private:
    //MySQL *_connection;
    MYSQL_RES *_result;
    MYSQL_ROW _row;
    MYSQL_FIELD *_field;
    unsigned int _numFields;

    std::map <std::string, unsigned int> _fieldNames;
};

/*template <typename T>
class Result_Cast
{
public:
    Result_Cast() {}
    T& operator()(std::string &what) const
    {
        T x;
        std::stringstream ss(what);
        ss >> x;
        return x;
    }
}; */

#endif // MYSQL_RESULT_H
