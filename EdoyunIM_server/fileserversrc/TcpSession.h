

#pragma once

#include <memory>
#include "../net/tcpconnection.h"

using namespace net;

//为了让业务与逻辑分开，实际应该新增一个子类继承自TcpSession，让TcpSession中只有逻辑代码，其子类存放业务代码
class TcpSession
{
public:
    TcpSession(const std::shared_ptr<TcpConnection>& conn);
    ~TcpSession();

    TcpSession(const TcpSession& rhs) = delete;
    TcpSession& operator =(const TcpSession& rhs) = delete;

    std::shared_ptr<TcpConnection> GetConnectionPtr()
    {
        return tmpConn_.lock();
    }

    void Send(const std::string& buf);
    void Send(const char* p, int length);

protected:
    std::weak_ptr<TcpConnection>    tmpConn_;
};
