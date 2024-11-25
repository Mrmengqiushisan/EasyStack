// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: Shuo Chen (chenshuo at chenshuo dot com)

#ifndef MUDUO_BASE_THREAD_H
#define MUDUO_BASE_THREAD_H

#include "Atomic.h"
#include "CountDownLatch.h"
#include "Types.h"

#include <functional>
#include <memory>
#include <pthread.h>

namespace muduo
{

class Thread : noncopyable
{
 public:
  //回调函数制造
  typedef std::function<void ()> ThreadFunc;
  //非隐式构造函数
  explicit Thread(ThreadFunc, const string& name = string());
  // FIXME: make it movable in C++11
  ~Thread();

  void start();
  int join(); // return pthread_join()
  bool started() const { return started_; }
  // pthread_t pthreadId() const { return pthreadId_; }
  pid_t tid() const { return tid_; }
  const string& name() const { return name_; }

  static int numCreated() { return numCreated_.get(); }

 private:
  void setDefaultName();

  bool       started_;             //表示线程是否开启
  bool       joined_;              //表示线程是否被joined
  pthread_t  pthreadId_;           //线程标识符
  pid_t      tid_;                 //线程ID
  ThreadFunc func_;                //当前线程的回调函数
  string     name_;                //线程名称
  CountDownLatch latch_;           //计数器，在线程真正开始执行

  static AtomicInt32 numCreated_;  //用于记录创建线程实例的数量
};

}  // namespace muduo
#endif  // MUDUO_BASE_THREAD_H
