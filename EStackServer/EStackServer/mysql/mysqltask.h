#pragma once
#include"../database/databasemysql.h"
#include"../database/QueryResult.h"

namespace mengqiu{
    
    enum EMysqlError{
        EME_ERROR=-1,
        EME_OK,
        EME_NOT_EXIST,
        EME_EXIST
    };
    union  RPValue
    {
        RPValue():m_execute(false){}
        RPValue(const RPValue& value){
            m_queryPtr=value.m_queryPtr;
            m_execute=value.m_execute;
        }
        RPValue& operator=(const RPValue& value){
            if(this!=&value){
                m_queryPtr=value.m_queryPtr;
                m_execute=value.m_execute;
            }
            return *this;
        }
        ~RPValue(){}
        database::QueryResultPtr  m_queryPtr;
        bool                      m_execute;
    };
    
    enum SQLTYPE:int{
        SQL_QUERY=1,
        SQL_INCREASE,
        SQL_DELETE,
        SQL_UPDATE,
        SQL_OTHER
    };

    class IMysqlTask{
    public:
        IMysqlTask(const std::string& str):m_strsql(str){}
        virtual ~IMysqlTask(void){}
    public:
        virtual void Execute(database::DataBaseMySql* poConn)=0;
        virtual RPValue Reply()=0;
        virtual void Release(){delete this;}
        virtual std::string GetStrSql(){return m_strsql;}
    protected:
        std::string m_strsql;
    };
}