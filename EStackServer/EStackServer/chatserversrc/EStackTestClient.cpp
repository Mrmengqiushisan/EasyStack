#include"net/TcpClient.h"
#include"net/EventLoop.h"
#include"net/InetAddress.h"
#include"base/Logging.h"
#include"net/Buffer.h"
#include<iostream>
#include<unistd.h>
#include<stdio.h>
#include<sys/types.h>

using namespace muduo;
using namespace muduo::net;

void onClose(const TcpConnectionPtr& conn){
    std::cout<<"onClose called"<<std::endl;
    exit(0);
}

void onConnected(const TcpConnectionPtr& conn){
    conn->send("hello");
}
void onMessaged(const TcpConnectionPtr& conn,Buffer* buffer,Timestamp ts){
    std::cout<<buffer->retrieveAllAsString()<<std::endl;
    conn->setConnectionCallback(onClose);
    conn->shutdown();
}
int main(){
    EventLoop loop;
    InetAddress servAddr("127.0.0.1",9527);
    TcpClient client(&loop,servAddr,"echo client");
    client.setConnectionCallback(onConnected);
    client.setMessageCallback(onMessaged);
    client.connect();
    loop.loop();
    return 1;
}