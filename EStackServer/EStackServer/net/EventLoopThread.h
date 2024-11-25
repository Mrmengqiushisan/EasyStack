// Copyright 2010, Shuo Chen.  All rights reserved.
// http://code.google.com/p/
//
// Use of this source code is governed by a BSD-style license
// that can be found in the License file.

// Author: Shuo Chen (chenshuo at chenshuo dot com)
//
// This is a public header file, it must only include public header files.

#ifndef MUDUO_NET_EVENTLOOPTHREAD_H
#define MUDUO_NET_EVENTLOOPTHREAD_H

#include "base/Condition.h"
#include "base/Mutex.h"
#include "base/Thread.h"

namespace muduo
{
namespace net
{

class EventLoop;

class EventLoopThread : noncopyable
{
 public:
  typedef std::function<void(EventLoop*)> ThreadInitCallback;

  EventLoopThread(const ThreadInitCallback& cb = ThreadInitCallback(),
                  const string& name = string());
  ~EventLoopThread();
  EventLoop* startLoop();

 private:
  void threadFunc();

  EventLoop* loop_ GUARDED_BY(mutex_);//事件循环指针，值得注意的是初始化的值为NULL，可是需要在事件循环中loop
  //其实这个变量是线程启动状态的标志，直到线程中的loop成功创建，才会通过条件变量进行通知；
  bool exiting_;//此变量几乎没什么用
  Thread thread_;//线程变量用于执行子线程函数
  MutexLock mutex_;//锁
  Condition cond_ GUARDED_BY(mutex_);//条件变量
  ThreadInitCallback callback_;//线程初始化回调函数
};

}  // namespace net
}  // namespace muduo

#endif  // MUDUO_NET_EVENTLOOPTHREAD_H

