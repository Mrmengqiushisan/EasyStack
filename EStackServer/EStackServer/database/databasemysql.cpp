#include"databasemysql.h"
#include<fstream>
#include"../base/Logging.h"

using namespace mengqiu::database;
using namespace muduo;

DataBaseMySql::DataBaseMySql():
DatabaseInfo(),m_mysql(nullptr),
m_bInit(false){

}

DataBaseMySql::~DataBaseMySql(){
    if(m_mysql!=nullptr&&m_bInit){
        mysql_close(m_mysql);
        m_mysql=nullptr;
    }
}

bool DataBaseMySql::connect(const std::string& user,const std::string& password,const std::string& dbname,const std::string& host,unsigned int port){
    LOG_INFO<<"DatabaseMysql::connect,begin...";
    if(m_bInit){
        mysql_close(m_mysql);
        m_mysql=nullptr;
    }
    m_mysql=mysql_init(m_mysql);
    m_mysql=mysql_real_connect(m_mysql,host.c_str(),user.c_str(),password.c_str(),dbname.c_str(),port,nullptr,0);
    LOG_INFO<<host.c_str();
    LOG_INFO<<user.c_str();
    LOG_INFO<<password.c_str();
    LOG_INFO<<dbname.c_str();
    m_strUser=user;
    m_strHost=host;
    m_strPwd=password;
    m_strDBName=dbname;
    m_uintPort=port;
    if(m_mysql){
        LOG_INFO<<"m_mysql address "<<(long)m_mysql;
        LOG_INFO<<"DatabaseMysql::connect set names utf8";
        mysql_query(m_mysql,"set names utf8");
        m_bInit=true;
    }else{
        LOG_ERROR<<"Could not connect to MYSQL database at"<<host.c_str()<<", "<<mysql_errno(m_mysql);
        mysql_close(m_mysql);
    }
    LOG_INFO<<"DatabaseMysql::connect "<<(m_bInit?"success":"failed");
    return m_bInit;
}

QueryResultPtr DataBaseMySql::Query(const char* sql){
    if(!m_mysql){
        if(!connect(m_strUser,m_strPwd,m_strDBName,m_strHost,m_uintPort)){
            LOG_ERROR<<"DataBaseMySql::Query mysql is disconnected";
            return QueryResultPtr();
        }
    }
    MYSQL_RES*  result=nullptr;
    uint32_t    rowCount;
    uint32_t    fieldCount;
    //开始查询
    LOG_INFO<<sql;
    int iTempRet=mysql_real_query(m_mysql,sql,strlen(sql));
    if(iTempRet){
        unsigned int uErrno=mysql_errno(m_mysql);
        LOG_ERROR<<"DataBaseMySql::Query mysql is abnorma, errno: "<<uErrno;
        //需要考虑以下此错误，表示本地与数据库服务器端口连接 需要重连课解决
        if(uErrno==CR_SERVER_GONE_ERROR){   
            if(!connect(m_strUser,m_strPwd,m_strDBName,m_strHost,m_uintPort)){
                LOG_ERROR<<"DataBaseMySql::Query mysql is disconnect,errno: "<<mysql_errno(m_mysql);
                return QueryResultPtr();
            }
            iTempRet=mysql_real_query(m_mysql,sql,strlen(sql));
            if(iTempRet){
                LOG_ERROR<<"SQL: "<<sql;
                LOG_ERROR<<"query ERROR: "<<mysql_error(m_mysql);
                return QueryResultPtr();
            }
        }else{
            LOG_ERROR<<"SQL: "<<sql;
            LOG_ERROR<<"query ERROR: "<<mysql_error(m_mysql);
            return QueryResultPtr();
        }
    }
    LOG_INFO<<"call mysql_store_result";
    //返回查询结果指针
    result=mysql_store_result(m_mysql);
    //返回行数
    rowCount=mysql_affected_rows(m_mysql);
    //返回列数
    fieldCount=mysql_field_count(m_mysql);
    
    return QueryResultPtr(new QueryResult(result,rowCount,fieldCount));
}

QueryResultPtr DataBaseMySql::PQuery(const char* format,...){
    if(!format)return QueryResultPtr();
    va_list ap;
    char szQuery[MAX_QUERY_LEN];
    va_start(ap,format);
    int res=vsnprintf(szQuery,MAX_QUERY_LEN,format,ap);
    va_end(ap);
    if(res==-1){
        LOG_ERROR<<"SQL Query truncated (and not execcute) for format: "<<format;
        return QueryResultPtr();
    }
    return Query(szQuery);
}

bool DataBaseMySql::Execute(const char* sql){
    uint32_t uaffectcount{0};
    int nerrno{0};
    return Execute(sql,uaffectcount,nerrno);
}

//后两个为传出参数
bool DataBaseMySql::Execute(const char* sql,uint32_t& uAffectedCount,int& nErrno){
    if(!m_mysql){
        if(!connect(m_strUser,m_strPwd,m_strDBName,m_strHost,m_uintPort)){
            LOG_ERROR<<"DataBaseMySql::Execute mysql is disconnected";
            nErrno=mysql_errno(m_mysql);
            // uAffectedCount 不用提出 因为本身就没有被影响的行
            return false;
        }
    }
    int iTempRet=mysql_query(m_mysql,sql);
    if(iTempRet){
        unsigned int uErrno=mysql_errno(m_mysql);
        LOG_ERROR<<"DataBaseMySql::Execute mysql is abnorma, errno: "<<uErrno;
        //需要考虑以下此错误，表示本地与数据库服务器端口连接 需要重连课解决
        if(uErrno==CR_SERVER_GONE_ERROR){   
            if(!connect(m_strUser,m_strPwd,m_strDBName,m_strHost,m_uintPort)){
                LOG_ERROR<<"DataBaseMySql::Execute mysql is disconnect,errno: "<<mysql_errno(m_mysql);
                nErrno=mysql_errno(m_mysql);
                return false;
            }
            iTempRet=mysql_query(m_mysql,sql);
            if(iTempRet){
                LOG_ERROR<<"SQL: "<<sql;
                LOG_ERROR<<"query ERROR: "<<mysql_error(m_mysql);
                nErrno=mysql_errno(m_mysql);
                return false;
            }
        }else{
            LOG_ERROR<<"SQL: "<<sql;
            LOG_ERROR<<"query ERROR: "<<mysql_error(m_mysql);
            nErrno=mysql_errno(m_mysql);
            return false;
        }
    }
    LOG_INFO<<"DataBaseMySql::Execute success";
    nErrno=mysql_errno(m_mysql);
    uAffectedCount=static_cast<uint32_t>(mysql_affected_rows(m_mysql));
    return true;
}

bool DataBaseMySql::PExecute(const char* format,...){
    if(!format)return false;
    va_list ap;
    char szQuery[MAX_QUERY_LEN];
    va_start(ap,format);
    int len=vsnprintf(szQuery,MAX_QUERY_LEN,format,ap);
    va_end(ap);
    if(len==-1){
        LOG_ERROR<<"SQL Query truncated (and not execcute) for format: "<<format;
        return false;
    }
    return Execute(szQuery);
}

void DataBaseMySql::ClearStoredResults(){
    if(!m_mysql)return;
    MYSQL_RES* result;
    while(!mysql_next_result(m_mysql)){
        if(result=mysql_store_result(m_mysql)){
            mysql_free_result(result);
        }
    }
}

uint32_t DataBaseMySql::GetInsertID(){
    if(!m_mysql)return 0;
    uint32_t res=static_cast<uint32_t>(mysql_insert_id(m_mysql));
    return res;
}

int32_t DataBaseMySql::EscapeString(char* szDst,const char* szSrc ,uint32_t uSize){
    if(!m_mysql)return 0;
    if(szDst==nullptr||szSrc==nullptr)return 0;
    return mysql_real_escape_string(m_mysql,szDst,szSrc,uSize);
}