#ifndef MY_SQL_MANAGER_H
#define MY_SQL_MANAGER_H
#include "../database/databasemysql.h"
#include "./mysqlthreadmgr.h"
#include "../base/Singleton.h"
#include "../base/copyable.h"
#include <string>
#include <map>
#include <memory>
/*
此类为上层业务逻辑类封装 用于维护数据库的连接，数据库表的创建，检测 等功能
*/
using namespace std;
using namespace muduo;
using namespace mengqiu;
using namespace mengqiu::database;
using namespace mengqiu::mysql;

class MySqlManager:public copyable
{
public:
    /// 此结构体主要用于存储数据库中表每一列属性的列名，数量类型以及描述
    typedef struct fieldinfo{
        fieldinfo()=default;
        fieldinfo(const string& name,const string& type,const string& desc):
        m_strName(name),
        m_strType(type),
        m_strDesc(desc){
            m_strName=name;
            m_strType=type;
            m_strDesc=desc;
        }
        string m_strName;
        string m_strType;
        string m_strDesc;
    }sFieldInfo;
    //此结构用于存放一个表的表名，KEY值，以及所有的列名
    typedef struct TableInfo{
        TableInfo()=default;
        TableInfo(std::string strname):m_strName(strname){}
        string m_strName;
        map<string,sFieldInfo> m_mapField;
        string m_strKeyString;
    }sTableInfo;
public:
    MySqlManager();
    MySqlManager(const MySqlManager& manager);
    MySqlManager& operator=(const MySqlManager& manager);
    ~MySqlManager(); 
    //初始化 调用底层对象进行连接
    bool Init(const string& host,const string& user,const string& passwd,const string& dbname,unsigned port=3306);
    // 底层数据查询功能
    QueryResultPtr Query(const string& sql);
    bool Excute(const string& sql);
private:
    //检查数据库的状态 用于查找是否含有指定的数据库
    bool CheckDataBase();
    //用于检测数据库中是否有对应的表，以及表中列属性信息是否一致，包括：数据类型以及所有列信息
    //同时若存在列信息不一致的情况 改函数会进行更新
    bool CheckTable(const sTableInfo& info);
    //创建对应的数据库
    bool CreateDatabase();
    //创建表
    bool CreateTable(const sTableInfo& info);
    //更新表信息
    bool UpdateTable(const sTableInfo& info);
private:
    //表数据记录
    map<string,sTableInfo> m_mapTable;
    //sql指针
    //shared_ptr<DataBaseMySql> m_mysql; 
    //msg单例
    std::string       m_strDataBase;
    MysqlThreadMsgr&  m_SqlMsginstance;
    using TablePair=std::pair<string,sTableInfo>;
    using TableIter=map<string,sTableInfo>::iterator;
};

#endif