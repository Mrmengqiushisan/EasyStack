// Copyright 2010, Shuo Chen.  All rights reserved.
// http://code.google.com/p/
//
// Use of this source code is governed by a BSD-style license
// that can be found in the License file.

// Author: Shuo Chen (chenshuo at chenshuo dot com)
//
// This is an internal header file, you should not include this.

#ifndef MUDUO_NET_TIMERQUEUE_H
#define MUDUO_NET_TIMERQUEUE_H

#include <set>
#include <vector>

#include "base/Mutex.h"
#include "base/Timestamp.h"
#include "Callbacks.h"
#include "Channel.h"

namespace muduo
{
namespace net
{

class EventLoop;
class Timer;
class TimerId;

///
/// A best efforts timer queue.
/// No guarantee that the callback will be on time.
///
class TimerQueue : noncopyable
{
 public:
  explicit TimerQueue(EventLoop* loop);
  ~TimerQueue();

  ///
  /// Schedules the callback to be run at given time,
  /// repeats if @c interval > 0.0.
  ///
  /// Must be thread safe. Usually be called from other threads.
  /// @brief 
  /// @param cb     回调函数
  /// @param when   定时器到期时间
  /// @param interval   重复间隔
  /// @return 返回TimerId对象 表示唯一标识添加的定时器
  TimerId addTimer(TimerCallback cb,
                   Timestamp when,
                   double interval);
  /// @brief 取消指定TinerId对应的计时器
  /// @param timerId 
  void cancel(TimerId timerId);

 private:

  // FIXME: use unique_ptr<Timer> instead of raw pointers.
  // This requires heterogeneous comparison lookup (N3465) from C++14
  // so that we can find an T* in a set<unique_ptr<T>>.
  typedef std::pair<Timestamp, Timer*> Entry;
  typedef std::set<Entry> TimerList;
  typedef std::pair<Timer*, int64_t> ActiveTimer;
  typedef std::set<ActiveTimer> ActiveTimerSet;
  //在事件循环中添加定时器 
  void addTimerInLoop(Timer* timer);
  //在事件循环中取消指定TimerId对应的定时器
  void cancelInLoop(TimerId timerId);
  // called when timerfd alarms
  //当定时器文件描述符触发可读事件时调用的函数
  void handleRead();
  // move out all expired timers
  //获取已过期的定时器列表
  std::vector<Entry> getExpired(Timestamp now);
  //重新设定定时器队列，将已过期的定时器重新添加到队列中
  void reset(const std::vector<Entry>& expired, Timestamp now);
  //将定时器插入到定时器列表中
  bool insert(Timer* timer);

  EventLoop* loop_;
  //定时器文件描述符
  const int timerfd_;
  //用于监听定时器文件描述符的通道
  Channel timerfdChannel_;
  // Timer list sorted by expiration
  // 定时器列表 按照到期事件排序
  TimerList timers_;
  //活跃的定时器集合 用于处理定时器到期
  // for cancel()
  ActiveTimerSet activeTimers_;
  //用于标识是否正在处理到期的定时器 atomic
  bool callingExpiredTimers_; 
  //用于存储正在取消的定时器集合
  ActiveTimerSet cancelingTimers_;
};

}  // namespace net
}  // namespace muduo
#endif  // MUDUO_NET_TIMERQUEUE_H
