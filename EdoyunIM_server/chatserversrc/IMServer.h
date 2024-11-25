
#pragma once
#include <memory>
#include <list>
#include <map>
#include <mutex>
#include "../net/tcpserver.h"
#include "../net/eventloop.h"
#include "ClientSession.h"

using namespace net;

struct StoredUserInfo
{
    int32_t         userid;     //用户ID
    std::string     username;   //用户名
    std::string     password;   //密码
    std::string     nickname;   //别名
};

class IMServer final
{
public:
    IMServer() = default;
    ~IMServer() = default;

    IMServer(const IMServer& rhs) = delete;
    IMServer& operator =(const IMServer& rhs) = delete;

    bool Init(const char* ip, short port, EventLoop* loop);

    void GetSessions(std::list<std::shared_ptr<ClientSession>>& sessions);
    bool GetSessionByUserId(std::shared_ptr<ClientSession>& session, int32_t userid);
    bool IsUserSessionExsit(int32_t userid);

private:
    //新连接到来调用或连接断开，所以需要通过conn->connected()来判断，一般只在主loop里面调用
    void OnConnection(std::shared_ptr<TcpConnection> conn);  
    //连接断开
    void OnClose(const std::shared_ptr<TcpConnection>& conn);
   

private:
    std::shared_ptr<TcpServer>                     m_server;
    std::list<std::shared_ptr<ClientSession>>      m_sessions;
    std::mutex                                     m_sessionMutex;      //多线程之间保护m_sessions
    int                                            m_baseUserId{};
    std::mutex                                     m_idMutex;           //多线程之间保护m_baseUserId
};
