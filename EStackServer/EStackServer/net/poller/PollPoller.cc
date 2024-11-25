// Copyright 2010, Shuo Chen.  All rights reserved.
// http://code.google.com/p/
//
// Use of this source code is governed by a BSD-style license
// that can be found in the License file.

// Author: Shuo Chen (chenshuo at chenshuo dot com)

#include "../poller/PollPoller.h"

#include "base/Logging.h"
#include "base/Types.h"
#include "../Channel.h"

#include <assert.h>
#include <errno.h>
#include <poll.h>

using namespace muduo;
using namespace muduo::net;

PollPoller::PollPoller(EventLoop* loop)
  : Poller(loop)
{
}

PollPoller::~PollPoller() = default;
/// @brief 此函数是对系统调用::POLL的封装 会将发生了事件的文件描述符更新到channel
/// @param timeoutMs 监听时长 0不阻塞 -1阻塞 >0 阻塞时长
/// @param activeChannels 传输参数 输出发生了更改的channel
/// @return 返回执行完成后的当前时间
Timestamp PollPoller::poll(int timeoutMs, ChannelList* activeChannels)
{
  // XXX pollfds_ shouldn't change
  // 调用系统POLL  参数一输入监听数组的首地址  参数二输入监听数据的大小  参数三数据监听时长
  // 返回正数的话 代表发生改变的文件数 
  int numEvents = ::poll(&*pollfds_.begin(), pollfds_.size(), timeoutMs);
  int savedErrno = errno;
  Timestamp now(Timestamp::now());
  //表示有事件发生
  if (numEvents > 0)
  {
    LOG_TRACE << numEvents << " events happened";
    fillActiveChannels(numEvents, activeChannels);
  }
  //无事发生
  else if (numEvents == 0)
  {
    LOG_TRACE << " nothing happened";
  }
  else
  {
    //如果不是系统中断
    if (savedErrno != EINTR)
    {
      errno = savedErrno;
      LOG_SYSERR << "PollPoller::poll()";
    }
  }
  return now;
}
/// @brief 遍历整个需要监听的文件,判断文件的返回事件revent的值如果>0;代表发生了事件，执行channel更新操作
/// @param numEvents  发生更改的文件数量
/// @param activeChannels  可用channel 该参数为传出参数
void PollPoller::fillActiveChannels(int numEvents,
                                    ChannelList* activeChannels) const
{
  for (PollFdList::const_iterator pfd = pollfds_.begin();
      pfd != pollfds_.end() && numEvents > 0; ++pfd)
  {
    if (pfd->revents > 0)
    {
      --numEvents;
      ChannelMap::const_iterator ch = channels_.find(pfd->fd);
      assert(ch != channels_.end());
      Channel* channel = ch->second;
      assert(channel->fd() == pfd->fd);
      channel->set_revents(pfd->revents);
      // pfd->revents = 0;
      activeChannels->push_back(channel);
    }
  }
}
/// @brief 更新channel
/// @param channel 需要更新的channel
void PollPoller::updateChannel(Channel* channel)
{
  //TODO: 此处看起来是判断是否在循环线程中
  Poller::assertInLoopThread();
  LOG_TRACE << "fd = " << channel->fd() << " events = " << channel->events();
  if (channel->index() < 0)
  {
    // a new one, add to pollfds_
    // 此处证明该channel还没有放入map中，同时该文件描述符也没有放入pollfds中
    assert(channels_.find(channel->fd()) == channels_.end());
    struct pollfd pfd;
    pfd.fd = channel->fd();
    pfd.events = static_cast<short>(channel->events());
    pfd.revents = 0;
    pollfds_.push_back(pfd);
    int idx = static_cast<int>(pollfds_.size())-1;
    channel->set_index(idx);
    channels_[pfd.fd] = channel;
  }
  else
  {
    // update existing one
    // 此处说明在chache表中已经存在了该channel 需要做的是更新该值
    assert(channels_.find(channel->fd()) != channels_.end());
    assert(channels_[channel->fd()] == channel);
    int idx = channel->index();
    assert(0 <= idx && idx < static_cast<int>(pollfds_.size()));
    struct pollfd& pfd = pollfds_[idx];
    assert(pfd.fd == channel->fd() || pfd.fd == -channel->fd()-1);
    pfd.fd = channel->fd();
    pfd.events = static_cast<short>(channel->events());
    pfd.revents = 0;
    //判断该文件描述符需要监听的事件 是否为空
    if (channel->isNoneEvent())
    {
      // ignore this pollfd
      pfd.fd = -channel->fd()-1;
    }
  }
}
/// @brief 移除channel
/// @param channel 需要移除的channel
void PollPoller::removeChannel(Channel* channel)
{
  Poller::assertInLoopThread();
  LOG_TRACE << "fd = " << channel->fd();
  assert(channels_.find(channel->fd()) != channels_.end());
  assert(channels_[channel->fd()] == channel);
  assert(channel->isNoneEvent());
  int idx = channel->index();
  assert(0 <= idx && idx < static_cast<int>(pollfds_.size()));
  const struct pollfd& pfd = pollfds_[idx]; (void)pfd;
  assert(pfd.fd == -channel->fd()-1 && pfd.events == channel->events());
  size_t n = channels_.erase(channel->fd());
  assert(n == 1); (void)n;
  if (implicit_cast<size_t>(idx) == pollfds_.size()-1)
  {
    pollfds_.pop_back();
  }
  else
  {
    int channelAtEnd = pollfds_.back().fd;
    //交换pollfds_中channel和末尾元素 使得将需要删除的元素放在末尾
    iter_swap(pollfds_.begin()+idx, pollfds_.end()-1);
    if (channelAtEnd < 0)
    {
      channelAtEnd = -channelAtEnd-1;
    }
    channels_[channelAtEnd]->set_index(idx);
    pollfds_.pop_back();
  }
}

