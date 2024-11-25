#include"QueryResult.h"
using namespace mengqiu::database;

QueryResult::QueryResult(MYSQL_RES* result,uint32_t rowcount,uint32_t columncount):
m_result(result),m_rowcount(rowcount),m_colcount(columncount){
    m_currentRow.resize(m_colcount);
    m_vecFieldName.resize(m_colcount);
    MYSQL_FIELD* field=mysql_fetch_field(m_result);
    for(uint32_t i=0;i<columncount;i++){
        m_vecFieldName[i]=field[i].name;
        m_currentRow[i].SetType(toEDYTtpe(field[i].type));
    }
}
QueryResult::~QueryResult(){

}
bool QueryResult::NextRow(){
    if(m_result==nullptr)return false;
    //获取查询结果集中下一行的函数
    MYSQL_ROW row=mysql_fetch_row(m_result);
    if(row==nullptr){
        EndQuery();
        return false;
    }
    //这个API返回的是每列的长度信息
    unsigned long* pFieldLength=mysql_fetch_lengths(m_result);
    for(uint32_t i=0;i<m_colcount;i++){
        if(row[i]==nullptr){
            m_currentRow[i].SetValue(nullptr,0);
        }else{
            m_currentRow[i].SetValue(row[i],pFieldLength[i]);
        }
    }
    return true;
}

void QueryResult::EndQuery(){
    m_currentRow.clear();
    m_vecFieldName.clear();
    if(m_result){
        mysql_free_result(m_result);
        m_result=nullptr;
    }
    m_colcount=0;
    m_rowcount=0;
}

Field::DataTypes QueryResult::toEDYTtpe(enum_field_types mysqltype){
    switch (mysqltype)
    {
    case FIELD_TYPE_TIMESTAMP:
    case FIELD_TYPE_DATE:
    case FIELD_TYPE_DATETIME:
    case FIELD_TYPE_YEAR:
    case FIELD_TYPE_STRING:
    case FIELD_TYPE_VAR_STRING:
    case FIELD_TYPE_BLOB:
    case FIELD_TYPE_SET:
        return Field::EDY_TYPE_NONE;
    case FIELD_TYPE_NULL:
        return Field::EDY_TYPE_NULL;
    case FIELD_TYPE_TINY:
    case FIELD_TYPE_SHORT:
    case FIELD_TYPE_LONG:
    case FIELD_TYPE_LONGLONG:
    case FIELD_TYPE_INT24:
    case FIELD_TYPE_ENUM:
        return Field::EDY_TYPE_INTERGER;
    case FIELD_TYPE_DECIMAL:
    case FIELD_TYPE_FLOAT:
    case FIELD_TYPE_DOUBLE:
        return Field::EDY_TYPE_FLOAT;
    default:
        return Field::EDY_TYPE_NONE;
    }
    return Field::EDY_TYPE_NONE;
}