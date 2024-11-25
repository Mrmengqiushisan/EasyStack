#include "IMServer.h"
IMServer::IMServer(){

}
IMServer::~IMServer(){

}
bool IMServer::Init(const std::string&ip,short port,muduo::net::EventLoop* loop){
    muduo::net::InetAddress addr(ip,port);
    m_server.reset(new muduo::net::TcpServer(loop,addr,"chatserver",net::TcpServer::kReusePort));;
    m_server->setConnectionCallback(std::bind(&IMServer::OnConnection,this,_1));
    m_server->start();
    return true;
}

void IMServer::OnConnection(const muduo::net::TcpConnectionPtr& conn){
    if(conn->connected()){
        ClientSessionPtr client(new ClientSession(conn));
        {
            std::lock_guard<std::mutex> guard(m_sessionlock);
            m_mapClient[client->getSessionID()]=client;
        }
    }else{
        OnClose(conn);
    }
}

void IMServer::OnClose(const muduo::net::TcpConnectionPtr& conn){
    if(m_mapClient.count(conn->name())){
        //TODO::关闭连接的操作
        m_mapClient.erase(conn->name());
    }else{
        //TODO::有问题的连接
        std::cout<<conn->name()<<std::endl;
    }
}