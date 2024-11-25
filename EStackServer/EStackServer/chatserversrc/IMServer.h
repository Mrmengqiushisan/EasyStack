#ifndef IMSERVER_H
#define IMSERVER_H
#include "base/noncopyable.h"
#include <string>
#include "base/Logging.h"
#include "net/EventLoop.h"
#include "net/EventLoopThread.h"
#include "net/EventLoopThreadPool.h"
#include "net/TcpServer.h"
#include "ClientSession.h"
#include <list>
#include <map>
#include <iostream>
using namespace muduo;
using namespace net;
using namespace std::placeholders;
class IMServer final :muduo::noncopyable{
public:
    IMServer();
    ~IMServer();
    bool Init(const std::string&ip,short port,muduo::net::EventLoop* loop);
protected:
    void OnConnection(const muduo::net::TcpConnectionPtr& conn);
    void OnClose(const muduo::net::TcpConnectionPtr& conn);
private:
    std::shared_ptr<muduo::net::TcpServer> m_server;
    std::map<std::string,ClientSessionPtr>m_mapClient;
    std::mutex m_sessionlock;//保护m_mapclient的操作

};

#endif //IMSERVER_H