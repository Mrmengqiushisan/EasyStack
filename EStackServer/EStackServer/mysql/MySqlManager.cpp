#include "MySqlManager.h"
#include "imchattask.h"
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#define LOG_INFO_IM(s) cout<<__FILE__<<": "<<__FUNCTION__<<"["<<__LINE__<<"]: "<<s<<endl
MySqlManager::MySqlManager():m_SqlMsginstance(muduo::Singleton<MysqlThreadMsgr>::instance()){
    //用户
    sTableInfo info;
    info.m_strName="t_user";
    info.m_mapField["f_id"] = { "f_id","bigint(20) NOT NULL AUTO_INCREMENT COMMENT '自增ID'","bigint(20)" };
	info.m_mapField["f_user_id"] = { "f_user_id", "bigint(20) NOT NULL COMMENT '用户ID'", "bigint(20)" };
	info.m_mapField["f_username"] = { "f_username", "varchar(64) NOT NULL COMMENT '用户名'", "varchar(64)" };
	info.m_mapField["f_nickname"] = { "f_nickname", "varchar(64) NOT NULL COMMENT '用户昵称'", "varchar(64)" };
	info.m_mapField["f_password"] = { "f_password", "varchar(64) NOT NULL COMMENT '用户密码'", "varchar(64)" };
	info.m_mapField["f_facetype"] = { "f_facetype", "int(10) DEFAULT 0 COMMENT '用户头像类型'", "int(10)" };
	info.m_mapField["f_customface"] = { "f_customface", "varchar(32) DEFAULT NULL COMMENT '自定义头像名'", "varchar(32)" };
	info.m_mapField["f_customfacefmt"] = { "f_customfacefmt", "varchar(6) DEFAULT NULL COMMENT '自定义头像格式'", "varchar(6)" };
	info.m_mapField["f_gender"] = { "f_gender", "int(2)  DEFAULT 0 COMMENT '性别'", "int(2)" };
	info.m_mapField["f_birthday"] = { "f_birthday", "bigint(20)  DEFAULT 19900101 COMMENT '生日'", "bigint(20)" };
	info.m_mapField["f_signature"] = { "f_signature", "varchar(256) DEFAULT NULL COMMENT '地址'", "varchar(256)" };
	info.m_mapField["f_address"] = { "f_address", "varchar(256) DEFAULT NULL COMMENT '地址'", "varchar(256)" };
	info.m_mapField["f_phonenumber"] = { "f_phonenumber", "varchar(64) DEFAULT NULL COMMENT '电话'", "varchar(64)" };
	info.m_mapField["f_mail"] = { "f_mail", "varchar(256) DEFAULT NULL COMMENT '邮箱'", "varchar(256)" };
	info.m_mapField["f_owner_id"] = { "f_owner_id", "bigint(20) DEFAULT 0 COMMENT '群账号群主userid'", "bigint(20)" };
	info.m_mapField["f_register_time"] = { "f_register_time", "datetime NOT NULL COMMENT '注册时间'", "datetime" };
	info.m_mapField["f_remark"] = { "f_remark", "varchar(64) NULL COMMENT '备注'", "varchar(64)" };
	info.m_mapField["f_update_time"] = { "f_update_time", "timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP COMMENT '更新时间'", "timestamp" };
	info.m_strKeyString = "PRIMARY KEY (f_user_id), INDEX f_user_id (f_user_id), KEY  f_id  ( f_id )";
    m_mapTable.insert(std::pair<string,sTableInfo>(info.m_strName,info));
    //聊天内容
    info.m_mapField.clear();
    info.m_strName="t_chatmsg";
    info.m_mapField["f_id"] = { "f_id", "bigint(20) NOT NULL AUTO_INCREMENT COMMENT '自增ID'", "bigint(20)" };
	info.m_mapField["f_senderid"] = { "f_senderid", "bigint(20) NOT NULL COMMENT '发送者id'", "bigint(20)" };
	info.m_mapField["f_targetid"] = { "f_targetid", "bigint(20) NOT NULL COMMENT '接收者id'", "bigint(20)" };
	info.m_mapField["f_msgcontent"] = { "f_msgcontent", "blob NOT NULL COMMENT '聊天内容'", "blob" };
	info.m_mapField["f_create_time"] = { "f_create_time", "timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP COMMENT '更新时间'", "timestamp" };
	info.m_mapField["f_remark"] = { "f_remark", "varchar(64) NULL COMMENT '备注'", "varchar(64)" };
	info.m_strKeyString = "PRIMARY KEY (f_id), INDEX f_id (f_id)";
    m_mapTable.insert(TablePair(info.m_strName,info));
    //用户关系ID
    info.m_mapField.clear();
    info.m_strName="t_user_relationship";
    info.m_mapField["f_id"] = { "f_id", "bigint(20) NOT NULL AUTO_INCREMENT COMMENT '自增ID'", "bigint(20)" };
	info.m_mapField["f_user_id1"] = { "f_user_id1", "bigint(20) NOT NULL COMMENT '用户ID'", "bigint(20)" };
	info.m_mapField["f_user_id2"] = { "f_user_id2", "bigint(20) NOT NULL COMMENT '用户ID'", "bigint(20)" };
	info.m_mapField["f_remark"] = { "f_remark", "varchar(64) NULL COMMENT '备注'", "varchar(64)" };
	info.m_mapField["f_create_time"] = { "f_create_time", "timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP COMMENT '更新时间'", "timestamp" };
	info.m_strKeyString = "PRIMARY KEY (f_id), INDEX f_id (f_id)";
    m_mapTable.insert(TablePair(info.m_strName,info));
}

MySqlManager::MySqlManager(const MySqlManager& manager):m_SqlMsginstance(manager.m_SqlMsginstance){
    m_mapTable=manager.m_mapTable;
    m_strDataBase=manager.m_strDataBase;
}

MySqlManager& MySqlManager::operator=(const MySqlManager& manager){
    if(this!=&manager){
        m_mapTable=manager.m_mapTable;
        m_SqlMsginstance=manager.m_SqlMsginstance;
        m_strDataBase=manager.m_strDataBase;
    }
    return *this;
}
MySqlManager::~MySqlManager(){

}
bool MySqlManager::Init(const string& host,const string& user,const string& passwd,const string& dbname,unsigned port){
    m_strDataBase=dbname;
    if(!muduo::Singleton<MysqlThreadMsgr>::instance().Init(user,passwd,dbname,host,port)){
        cout<<"connect mysql failed!\r\n";
        return false;
    }
    // if(!m_mysql->connect(host,user,passwd,dbname,port)){
    //     cout<<"connect mysql failed!\r\n";
    //     return false;
    // }
    if(CheckDataBase()==false){
        if(CreateDatabase()==false){
            return false;
        }
    }
    for(auto&[name,table]:m_mapTable){
        if(CheckTable(table)==false){
            if(CreateTable(table)==false){
                return false;
            }
        }
    }
    return true;
}
QueryResultPtr MySqlManager::Query(const string& sql){
    if(&m_SqlMsginstance==nullptr)return QueryResultPtr();
    IMysqlTask* poTask=new ImChatTask(sql);
    m_SqlMsginstance.AddTask(MysqlThreadMsgr::hash_add(sql.c_str()),poTask);
    RPValue* res=m_SqlMsginstance.ProcessReplyTask(poTask);
    return res->m_queryPtr;
}

bool MySqlManager::Excute(const string& sql){
    if(&m_SqlMsginstance==nullptr)return false;
    IMysqlTask* poTask=new ImChatTask(sql,SQL_OTHER);
    m_SqlMsginstance.AddTask(MysqlThreadMsgr::hash_add(sql.c_str()),poTask);
    return m_SqlMsginstance.ProcessReplyTask(poTask)->m_execute;
}

bool MySqlManager::CheckDataBase(){
    if(&m_SqlMsginstance==nullptr)return false;
    std::string sql="show databases;";
    IMysqlTask* poTask=new ImChatTask(sql);
    m_SqlMsginstance.AddTask(MysqlThreadMsgr::hash_add(sql.c_str()),poTask);
    QueryResultPtr result=m_SqlMsginstance.ProcessReplyTask(poTask)->m_queryPtr;
    if(result==nullptr){
        cout<<"no database found in mysql";
        return false;
    }
    Field* pRow= result->Fetch();
    while(pRow!=nullptr){
        string name=pRow[0].GetString();
        if(name==m_strDataBase){
            result->EndQuery();
            LOG_INFO_IM("databases success");
            return true;
        }
        if(result->NextRow()==false)break;
        pRow=result->Fetch();
    }
    result->EndQuery();
    cout<<"database not found\r\n";
    return false;
}
bool MySqlManager::CheckTable(const sTableInfo& info){
    if(&m_SqlMsginstance==nullptr)return false;
    stringstream sql;
    sql<<"desc "<<info.m_strName<<";";
    IMysqlTask* poTask=new ImChatTask(sql.str());
    m_SqlMsginstance.AddTask(MysqlThreadMsgr::hash_add(sql.str().c_str()),poTask);
    QueryResultPtr result=m_SqlMsginstance.ProcessReplyTask(poTask)->m_queryPtr;
    if(result==nullptr){
        if(CreateTable(info)==false){
            return false;
        }
        LOG_INFO_IM("success");
        return true;
    }
    map<string,sFieldInfo>rest(info.m_mapField.begin(),info.m_mapField.end());
    map<string,sFieldInfo>mapChange;
    using FieldPair=pair<string,sFieldInfo>;
    Field* pRow=result->Fetch();
    while(pRow!=nullptr){
        string name=pRow[0].GetString();
        string type=pRow[1].GetString();
        if(!info.m_mapField.count(name)){
            result->NextRow();
            pRow=result->Fetch();
            continue;
        }
        rest.erase(name);
        if((info.m_mapField).at(name).m_strDesc!=type){
            mapChange.insert(FieldPair(info.m_strName,info.m_mapField.at(name)));
        }
        result->NextRow();
        pRow=result->Fetch();
    }
    result->EndQuery();
    if(rest.size()>0){
        for(auto&[name,table]:rest){
            stringstream sql;
            sql<<"alter table "<<name<<" add column "<<table.m_strName<<" "<<table.m_strType<<";";
            IMysqlTask* poTask=new ImChatTask(sql.str(),SQL_INCREASE);
            m_SqlMsginstance.AddTask(MysqlThreadMsgr::hash_add(sql.str().c_str()),poTask);
            if(m_SqlMsginstance.ProcessReplyTask(poTask)->m_execute==false){
                return false;
            }
        }
    }
    for(auto&[name,table]:mapChange){
        stringstream sql;
        sql<<"alter table "<<name<<
        " modify column "<<table.m_strName<<" "<<table.m_strType<<";";
        IMysqlTask* poTask=new ImChatTask(sql.str(),SQL_UPDATE);
        m_SqlMsginstance.AddTask(MysqlThreadMsgr::hash_add(sql.str().c_str()),poTask);
        if(m_SqlMsginstance.ProcessReplyTask(poTask)->m_execute==false){
            return false;
        }
    }
    LOG_INFO_IM("success");
    return true;
}
bool MySqlManager::CreateDatabase(){
    if(&m_SqlMsginstance==nullptr)return false;
    stringstream sql;
    sql<<"create database "<<m_strDataBase<<";";
    IMysqlTask* poTask=new ImChatTask(sql.str(),SQL_OTHER);
    m_SqlMsginstance.AddTask(MysqlThreadMsgr::hash_add(sql.str().c_str()),poTask);
    if(m_SqlMsginstance.ProcessReplyTask(poTask)->m_execute==false)
        return false;
    return true;
}
bool MySqlManager::CreateTable(const sTableInfo& info){
    if(&m_SqlMsginstance==nullptr)return false;
    if(!info.m_mapField.size())return false;
    stringstream sql;
    sql<<"CREATE TABLE IF NOT EXISTS "<<info.m_strName<<"(";
    string hadstr=sql.str();
    int i{0};
    for(auto&[name,table]:info.m_mapField){
        if(i)sql<<",";
        sql<<" "<<name<<" "<<table.m_strType;
        i++;
    }
    if(info.m_strKeyString.size()>0){
        sql<<","<<info.m_strKeyString;
    }
    sql<<") default charset=utf-8,ENGINE=InnoDB;";
    IMysqlTask* poTask=new ImChatTask(hadstr,SQL_INCREASE);
    m_SqlMsginstance.AddTask(MysqlThreadMsgr::hash_add(hadstr.c_str()),poTask);
    return m_SqlMsginstance.ProcessReplyTask(poTask)->m_execute;
}
bool MySqlManager::UpdateTable(const sTableInfo& info){
    if(CheckTable(info)==false){
        return CreateTable(info);
    }
    return true;
}