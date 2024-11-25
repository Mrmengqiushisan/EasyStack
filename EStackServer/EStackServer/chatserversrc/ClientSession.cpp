#include"ClientSession.h"
#include<iostream>
#include<sstream>
#include"BinaryReader.h"
#include"json/json.h"
#include<base/Singleton.h>
#include"UserManager.h"

ClientSession::ClientSession(const muduo::net::TcpConnectionPtr& conn):
TCPSession(conn) m_seq(0){
    //m_sessionid=to_string(random_generator()()); 
    stringstream ss;
    ss<<(void*)conn.get();
    m_sessionid=ss.str();
    TcpConnectionPtr* client=const_cast<TcpConnectionPtr*>(&conn);
    //*const_cast<std::string*>(&conn->name())=m_sessionid;
    (*client)->setMessageCallback(std::bind(&ClientSession::OnRead,this,_1,_2,_3));
}

void ClientSession::OnRead(const std::shared_ptr<TcpConnectionPtr>& coon,Buffer* buf,Timestamp time){
    cout<<"come from client"<<endl;
    while(buf->readableBytes()>=sizeof(int32_t)){
        int32_t packageSize{0};
        packageSize=*(int32_t*)buf->peek();
        cout<<"packageSize: "<<packageSize<<endl;
        if(buf->readableBytes()<sizeof(int32_t)+packageSize) return;
        BinaryReader::Dump(buf->peek(),buf->readableBytes());
        buf->retrieve(sizeof(int32_t));
        string msgbuff;
        msgbuff.assign(buf->peek()+6,packageSize-6);
        BinaryReader::Dump(msgbuff);
        buf->retrieve(packageSize);
        if(Process(conn,msgbuff)==false){
            cout<<"process error,closse connection\r\n";
            conn->forceClose();
        }
    }
    
}

bool ClientSession::Process(const TcpConnectionPtr& conn,string msgbuff){
    BinaryReader reader(msgbuff);
    int cmd=-1;
    if(!reader.ReadData(cmd))return false;
    if(!reader.ReadData(m_seq))return false;
    string data;
    if(reader.ReadData(data)==false)return false;
    cout<<__FILE__<<"["<<__LINE__<<"]: cmd: "<<cmd<<endl;
    cout<<__FILE__<<"["<<__LINE__<<"]: m_seq: "<<m_seq<<endl;
    cout<<__FILE__<<"["<<__LINE__<<"]: size: "<<data.size()<<endl;
    cout<<data<<endl;
    switch (cmd){
    case msg_type_heartbeart://心跳包
        OnHeartbreakResponse(conn,data);
        break;
    case msg_type_register://注册消息
        OnRegisterResponse(conn,data);
        break;
    case msg_type_login://登录消息
        OnLoginResponse(conn,data);
        break;
    case msg_type_getofriendlist://获取好友列表
        break;
    case msg_type_finduser://查找用户
        OnSearchUserResponse(conn,data);
        break;
    case msg_type_operatefriend://操作好友
        break;
    case msg_type_userstatuschange://用户状态改变
        break;
    case msg_type_updateuserinfo://更新用户信息
        break;
    case msg_type_modifypassword://修改密码
        break;
    case msg_type_creategroup://创建群聊
        break;
    case msg_type_getgroupmembers://获取群成员
        break;
    case msg_type_chat://单聊消息
        break;
    case msg_type_multichat://群发消息
        break;
    default:
        break;
    }                        
    return true;
}


ClientSession::~ClientSession(){

}
/*
-----------------------------------------------------------------------------------------------
                                       
包长度(4字节)|命令类型(4字节)|包的序号(4字节)|包的数据: 包的长度(4字节)+包内容
                                           这里的包长度应该是指改命令及序号下的包长度，因为可以发多条
------------------------------------------------------------------------------------------------
*/
void ClientSession::OnHeartbreakResponse(const TcpConnectionPtr& conn,const string& data){
    BinaryWriter writer;
    int cmd=msg_type_heartbeart;
    writer.WriteData<int>(cmd);
    writer.WriteData<int>(m_seq);
    string empty;
    writer.WriteData(empty);
    Send(conn,writer);
}
/*
注册消息为json数据
{
    "user":"手机号",
    "nickname":"昵称",
    "password":"密码"
}
*/
void ClientSession::OnRegisterResponse(const TcpConnectionPtr& conn,const string& data){
    Json::Reader reader;
    Json::Value root;
    string result;
    BinaryWriter writer;
    Json::Value response;
    int cmd=msg_type_register;
    writer.WriteData(htonl(cmd));
    writer.WriteData(htonl(m_seq));
    if(!reader.parse(data,root)){
        cout<<"error json : "<<data<<endl;
        response["code"]=101;
        response["msg"]="Json parse failed";
        result=response.toStyledString();
        writer.WriteData(result);
        Send(conn,writer);
        return;
    }
    if(!root["username"].isString()||!root["nickname"].isString()||!root["password"].isString()){
        cout<<"error type:"<<data<<endl;
        response["code"]=102;
        response["msg"]="Json data type error";
        result=response.toStyledString();
        writer.WriteData(result);
        Send(conn,writer);
        return;
    }
    //注册的本质就插入新的数据在数据库表中
    User user;
    user.username=root["username"].asString();
    user.nickname=root["nickname"].asString();
    user.password=root["password"].asString();
    
    if(!muduo::Singleton<UserManager>::instance().Adduser(user)){
        cout<<"add user failed!\r\n";
        response["code"]=103;
        response["msg"]="register failed";
        result=response.toStyledString();
        writer.WriteData(result);
    }else{
        response["code"]=0;
        response["msg"]="ok";
        result=response.toStyledString();
        writer.WriteData(result);
    }
    Send(conn,writer);
}

void ClientSession::OnLoginResponse(const TcpConnectionPtr& conn,const string& data){
    BinaryWriter writer;
    string result;
    Json::Value root;
    Json::Value response;
    int cmd=msg_type_login;
    int bigcmd=htonl(cmd);
    int bigseq=htonl(m_seq);
    writer.WriteData(bigcmd);
    writer.WriteData(bigseq);
    Json::Reader reader;
    if(reader.parse(data,root)==false){
        response["code"]=101;
        response["msg"]="Json parse failed";
        result=response.toStyledString();
        writer.WriteData(result);
        Send(conn,writer);
        return;
    }
    if(!root["username"].isString()||!root["password"].isString()||!root["status"].isInt()||!root["clienttype"].isInt()){
        response["code"]=102;
        response["msg"]="Json data type error !";
        result=response.toStyledString();
        writer.WriteData(result);
        Send(conn,writer);
        return;
    }
    string username=root["username"].asString();
    string password=root["password"].asString();
    User user;
    if(!Singleton<UserManager>::instance().GetUserInfoByUserName(username,user)){
        response["code"]=103;
        response["msg"]="user is not existed or password is incorrect !";
        result=response.toStyledString();
        writer.WriteData(result);
        Send(conn,writer);
        return;
    }
    if(password!=user.password){
        response["code"]=104;
        response["msg"]="user is not existed or password is incorrect !";
        result=response.toStyledString();
        writer.WriteData(result);
        Send(conn,writer);
        return;
    }
    response["code"]=0;
    response["msg"]="ok";
    response["userid"]=user.userid;
    response["username"]=user.username;
    response["nickname"]=user.nickname;
    response["facetype"]=user.facetype;
    response["customface"] = user.customface;
	response["gender"] = user.gender;
	response["birthday"] = user.birthday;
	response["signature"] = user.signature;
	response["address"] = user.address;
	response["phonenumber"] = user.phonenumber;
	response["mail"] = user.mail;
    result=response.toStyledString();
    writer.WriteData(result);
    Send(conn,writer);
}


void ClientSession::OnSearchUserResponse(const TcpConnectionPtr& conn,const string& data){
    Json::Reader reader;
    Json::Value root,response;
    string result;
    BinaryWriter writer;
    int cmd=msg_type_finduser;
    writer.WriteData(htonl(cmd));
    writer.WriteData(htonl(m_seq));
    if(!reader.parse(data,root)){
        LOG_WARN<<"invaild json: "<<data<<",userid: "<<
    }
    if(!root["username"].isString()||!root["type"].isInt()){
        
    }
    User user;
    string username=root["username"].asString();
    if(!Singleton<UserManager>::instance().GetUserInfoByUserName(username,user)){
        
    }
    
}