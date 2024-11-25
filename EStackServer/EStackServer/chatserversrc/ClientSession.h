#ifndef CLIENT_SESSION_H
#define CLIENT_SESSION_H

#include "base/noncopyable.h"
#include "base/Logging.h"
#include "net/EventLoop.h"
#include "net/EventLoopThread.h"
#include "net/EventLoopThreadPool.h"
#include "net/TcpServer.h"
#include "BinaryReader.h"
#include "TcpSession.h"
#include "Msg.h"
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <string>
#include <mutex>

using namespace std;
using namespace mengqiu;
using namespace muduo;
using namespace muduo::net;
using namespace boost::uuids;
using namespace std::placeholders;

/*
此类用于处理接入会话的事件处理 为通信模块
*/
namespace mengqiu{
struct OnlineUserInfo{
    int32_t     userid;
    std::string username;
    std::string nickname;
    std::string password;
    int32_t     clienttype; //客户端类型  pc=1,android=2 ios=3
    int32_t     status;     //在线状态 0离线 1在忙 2忙碌 3离开 4隐身
};

class ClientSession: noncopyable,public TCPSession{
public:
    ClientSession(const muduo::net::TcpConnectionPtr& conn);
    ~ClientSession();
    inline std::string getSessionID()const{
        return m_sessionid;
    }
    //有数据可读  会被多个工作loop调用
    void OnRead(const std::shared_ptr<TcpConnectionPtr>& coon,Buffer* buf,Timestamp time);
    //业务函数
    bool Process(const TcpConnectionPtr& conn,string msgbuff);
protected:
    //心跳
    void OnHeartbreakResponse(const TcpConnectionPtr& conn,const string& data);
    //注册
    void OnRegisterResponse(const TcpConnectionPtr& conn,const string& data);
    //登录
    void OnLoginResponse(const TcpConnectionPtr& conn,const string& data);
    //查找其他用户
    void OnSearchUserResponse(const TcpConnectionPtr& conn,const string& data);
private:
    //记录会话ID
    std::string m_sessionid;
    //命令序号
    int         m_seq;
};
typedef std::shared_ptr<ClientSession> ClientSessionPtr;
}
#endif //CLIENT_SESSION_H