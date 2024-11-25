#include"TcpSession.h"
#include"../base/Logging.h"

using namespace mengqiu;
using namespace std;
TCPSession::TCPSession(const TcpConnectionPtr& conn):
tmpConn_(conn){

}
TCPSession::~TCPSession(){

}
void TCPSession::Send(const std::string& buf){
    string strSendData;
    msg header={(int32_t)buf.length()};
    LOG_INFO<<"Send data,header length: "<<sizeof(header)<<", body length "<<header.packagesize;
    strSendData.append()
}
void TCPSession::Send(const char* p,int length){

}