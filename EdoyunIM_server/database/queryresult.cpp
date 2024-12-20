#include "../base/logging.h"
#include "queryresult.h"


QueryResult::QueryResult(MYSQL_RES *result, uint64_t rowCount, uint32_t fieldCount)
 : mFieldCount(fieldCount), mRowCount(rowCount)
{
    //Fiedld中是对数据库中查询到的一种数据的管理，针对当前行而言，是通过一组Field维护的
    mResult = result;
	mCurrentRow = new Field[mFieldCount];
    assert(mCurrentRow);

    MYSQL_FIELD *fields = mysql_fetch_fields(mResult);

    for (uint32_t i = 0; i < mFieldCount; i++)
    {
        mFieldNames[i] = fields[i].name;
        m_vtFieldNames.push_back(fields[i].name);
        mCurrentRow[i].SetType(ConvertNativeType(fields[i].type));
    }
}

QueryResult::~QueryResult(void)
{
    EndQuery();
}

bool QueryResult::NextRow()
{
    MYSQL_ROW row;

    if (!mResult)
        return false;

    row = mysql_fetch_row(mResult);//获取当前行
    if (!row)
    {
        EndQuery();
        return false;
    }

    unsigned long int *ulFieldLength;
    ulFieldLength = mysql_fetch_lengths(mResult);//获取当前行中每一段数据的长度
    for (uint32_t i = 0; i < mFieldCount; i++)
    {
        if(row[i] == NULL)
        {
            mCurrentRow[i].m_bNULL = true;
            mCurrentRow[i].SetValue("", 0);
        }
        else
        {
            mCurrentRow[i].m_bNULL = false;
            mCurrentRow[i].SetValue(row[i], ulFieldLength[i]);
        }

        mCurrentRow[i].SetName(mFieldNames[i]);
    }

    return true;
}

void QueryResult::EndQuery()
{
    if (mCurrentRow)
    {
        delete [] mCurrentRow;
        mCurrentRow = 0;
    }

    if (mResult)
    {
		LOG_INFO << "QueryResult::EndQuery, mysql_free_result";
        mysql_free_result(mResult);
        mResult = 0;
    }
}

enum Field::DataTypes QueryResult::ConvertNativeType(enum_field_types mysqlType) const
{
    switch (mysqlType)
    {
        case FIELD_TYPE_TIMESTAMP:
        case FIELD_TYPE_DATE:
        case FIELD_TYPE_TIME:
        case FIELD_TYPE_DATETIME:
        case FIELD_TYPE_YEAR:
        case FIELD_TYPE_STRING:
        case FIELD_TYPE_VAR_STRING:
        case FIELD_TYPE_BLOB:
        case FIELD_TYPE_SET:
        case FIELD_TYPE_NULL:
            return Field::DB_TYPE_STRING;
        case FIELD_TYPE_TINY:

        case FIELD_TYPE_SHORT:
        case FIELD_TYPE_LONG:
        case FIELD_TYPE_INT24:
        case FIELD_TYPE_LONGLONG:
        case FIELD_TYPE_ENUM:
            return Field::DB_TYPE_INTEGER;
        case FIELD_TYPE_DECIMAL:
        case FIELD_TYPE_FLOAT:
        case FIELD_TYPE_DOUBLE:
            return Field::DB_TYPE_FLOAT;
        default:
            return Field::DB_TYPE_UNKNOWN;
    }
}
