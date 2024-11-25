// Copyright 2010, Shuo Chen.  All rights reserved.
// http://code.google.com/p/
//
// Use of this source code is governed by a BSD-style license
// that can be found in the License file.

// Author: Shuo Chen (chenshuo at chenshuo dot com)
//
// This is an internal header file, you should not include this.

#ifndef MUDUO_NET_CONNECTOR_H
#define MUDUO_NET_CONNECTOR_H

#include "base/noncopyable.h"
#include "InetAddress.h"

#include <functional>
#include <memory>

namespace muduo
{
namespace net
{

class Channel;
class EventLoop;

class Connector : noncopyable,
                  public std::enable_shared_from_this<Connector>
{
 public:
  typedef std::function<void (int sockfd)> NewConnectionCallback;

  Connector(EventLoop* loop, const InetAddress& serverAddr);
  ~Connector();

  void setNewConnectionCallback(const NewConnectionCallback& cb)
  { newConnectionCallback_ = cb; }

  void start();  // can be called in any thread
  void restart();  // must be called in loop thread
  void stop();  // can be called in any thread

  const InetAddress& serverAddress() const { return serverAddr_; }

 private:
  enum States { kDisconnected, kConnecting, kConnected };
  static const int kMaxRetryDelayMs = 30*1000;
  static const int kInitRetryDelayMs = 500;

  void setState(States s) { state_ = s; }
  void startInLoop();
  void stopInLoop();
  void connect();
  void connecting(int sockfd);
  void handleWrite();
  void handleError();
  void retry(int sockfd);
  int removeAndResetChannel();
  void resetChannel();

  EventLoop* loop_;//指向事件循环对象的指针
  InetAddress serverAddr_;//服务器的地址信息
  bool connect_; // atomic 是否处于连接状态
  States state_;  // FIXME: use atomic variable 连接的状态
  std::unique_ptr<Channel> channel_; //用于注册和处理事件
  NewConnectionCallback newConnectionCallback_;//用户设置的新连接建立时的回调函数
  int retryDelayMs_;//重试延迟的时间间隔
};

}  // namespace net
}  // namespace muduo

#endif  // MUDUO_NET_CONNECTOR_H
