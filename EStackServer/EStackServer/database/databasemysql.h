#pragma once
#include<stdint.h>
#include<mysql/mysql.h>
#include<mysql/errmsg.h>
#include"./QueryResult.h"
#define MAX_QUERY_LEN 1024
namespace mengqiu{
    namespace database{
        struct DatabaseInfo{
            DatabaseInfo():m_uintPort(0){}
            DatabaseInfo(const std::string& user,const std::string& password,const std::string& dbname,
            const std::string& host="127.0.0.1",unsigned int port=3306):
            m_strHost(host),m_strUser(user),m_strPwd(password),m_strDBName(dbname),m_uintPort(port){}
            std::string  m_strHost;
            std::string  m_strUser;
            std::string  m_strPwd;
            std::string  m_strDBName;
            unsigned int m_uintPort;
        };
        class DataBaseMySql:protected DatabaseInfo{
        public:
            DataBaseMySql();
            ~DataBaseMySql();
            //用于与数据库的连接 同时也是该对象的初始化功能
            bool connect(const std::string& user,const std::string& password,const std::string& dbname,const std::string& host="127.0.0.1",unsigned int port=3306);
            //通过sql语句执行数据库的查询操作,通过QueryResultPtr对查询结果进行维护
            QueryResultPtr Query(const char* sql);
            inline QueryResultPtr Query(const string& sql){
                return Query(sql.c_str());
            }
            QueryResultPtr PQuery(const char* format,...);
            //数据库的增加，更新，删除操作
            bool Execute(const char* sql);
            bool Execute(const char* sql,uint32_t& uAffectedCount,int& nErrno);
            bool PExecute(const char* format,...);
            //返回上一步INSERT操作产生的ID
            uint32_t GetInsertID();
            //清除mysql中存储的查询结果
            void ClearStoredResults();
            //防止数据库被注入攻击
            int32_t EscapeString(char* szDst,const char* szSrc ,uint32_t uSize);
        private:
            MYSQL*  m_mysql;
            bool    m_bInit;
        };



    }

}