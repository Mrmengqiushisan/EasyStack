#include<string>
#include<net/TcpConnection.h>
#include"./BinaryReader.h"
#include"../base/noncopyable.h"
#include"./Msg.h"
using namespace muduo::net;
namespace mengqiu{
    class TCPSession:muduo::noncopyable{
    public:
        TCPSession(const TcpConnectionPtr& conn);
        ~TCPSession();
        void Send(const std::string& buf);
        void Send(const char* p,int length);
    protected:
        std::weak_ptr<TcpConnection> tmpConn_;
    };
}
