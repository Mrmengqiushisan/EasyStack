// Use of this source code is governed by a BSD-style license
// that can be found in the License file.base/
//
// Author: Shuo Chen (chenshuo at chenshuo dot com)

#include "AsyncLogging.h"
#include "LogFile.h"
#include "Timestamp.h"

#include <stdio.h>

using namespace muduo;

AsyncLogging::AsyncLogging(const string& basename,
                           off_t rollSize,
                           int flushInterval)
  : flushInterval_(flushInterval),
    running_(false),
    basename_(basename),
    rollSize_(rollSize),
    thread_(std::bind(&AsyncLogging::threadFunc, this), "Logging"),
    latch_(1),
    mutex_(),
    cond_(mutex_),
    currentBuffer_(new Buffer),
    nextBuffer_(new Buffer),
    buffers_()
{
  currentBuffer_->bzero();
  nextBuffer_->bzero();
  buffers_.reserve(16);
}

void AsyncLogging::append(const char* logline, int len)
{
  muduo::MutexLockGuard lock(mutex_);
  if (currentBuffer_->avail() > len)
  {
    //如果空间够用 直接append
    currentBuffer_->append(logline, len);
  }
  else
  {
    //如果已经满了 则将该buffer移动到buffers_中
    buffers_.push_back(std::move(currentBuffer_));
    //更新当前buffer的指针指向区域
    if (nextBuffer_)
    {
      currentBuffer_ = std::move(nextBuffer_);
    }
    else
    {
      //如果备份buffer已经被用了 那么直接新建
      currentBuffer_.reset(new Buffer); // Rarely happens
    }
    currentBuffer_->append(logline, len);
    cond_.notify();
  }
}

void AsyncLogging::threadFunc()
{
  assert(running_ == true);
  //计数值直接降为0 然后通知start线程启动成功
  latch_.countDown();
  //初始化日志文件 非线程安全的 
  //因为消费者唯一，且单线程同步处理日志消息数据，因此后端LogFile使用非线程安全到本地文件的版本，可以提高新能
  LogFile output(basename_, rollSize_, false);
  //定义了连个新的Buffer 用处：
  BufferPtr newBuffer1(new Buffer);
  BufferPtr newBuffer2(new Buffer);
  newBuffer1->bzero();
  newBuffer2->bzero();
  //定义一个新的buffer容器 用处：
  BufferVector buffersToWrite;
  buffersToWrite.reserve(16);
  while (running_)
  {
    assert(newBuffer1 && newBuffer1->length() == 0);
    assert(newBuffer2 && newBuffer2->length() == 0);
    assert(buffersToWrite.empty());
    //此部分主要做的就是将日志数据得到，并肩他们放到临时容器中
    //更新两块缓冲区以及日志队列，一般是将其都置为空了
    {
      muduo::MutexLockGuard lock(mutex_);
      if (buffers_.empty())  // unusual usage!
      {
        //等待条件变量固定时间 flushInterval_ 即刷新时间
        //当时间到了后，不论是否发出了notify 都会执行下面的代码
        cond_.waitForSeconds(flushInterval_);
      }
      //将当前buffer放入buffer_队列
      buffers_.push_back(std::move(currentBuffer_));
      //更新当前缓冲区
      currentBuffer_ = std::move(newBuffer1);
      //置换buffer队列中的数据 
      //这样做的结果是真正buffer_队列志伟空，但已经将日志信息保存到了临时队列中
      buffersToWrite.swap(buffers_);
      //如果预备buffer被使用了，那么也需要更新
      if (!nextBuffer_)
      {
        nextBuffer_ = std::move(newBuffer2);
      }
    }
    //断言判断buffer队列是否为空，为空会发生断言错误
    assert(!buffersToWrite.empty());
    //日志待写入文件bufferToWrite队列超限(短时间堆积，多为异常情况)
    if (buffersToWrite.size() > 25)
    {
      char buf[256];
      snprintf(buf, sizeof buf, "Dropped log messages at %s, %zd larger buffers\n",
               Timestamp::now().toFormattedString().c_str(),
               buffersToWrite.size()-2);
      fputs(buf, stderr);
      output.append(buf, static_cast<int>(strlen(buf)));
      buffersToWrite.erase(buffersToWrite.begin()+2, buffersToWrite.end());
    }
    //将bufferToWrite队列中的日志消息交给后端写入
    for (const auto& buffer : buffersToWrite)
    {
      // FIXME: use unbuffered stdio FILE ? or use ::writev ?
      output.append(buffer->data(), buffer->length());
    }

    if (buffersToWrite.size() > 2)
    {
      // drop non-bzero-ed buffers, avoid trashing
      buffersToWrite.resize(2);
    }
    //将bufferToWrite队列中的buffer重新填充到newBuffer1,newBuffer2
    if (!newBuffer1)
    {
      assert(!buffersToWrite.empty());
      newBuffer1 = std::move(buffersToWrite.back());
      buffersToWrite.pop_back();
      newBuffer1->reset();
    }

    if (!newBuffer2)
    {
      assert(!buffersToWrite.empty());
      newBuffer2 = std::move(buffersToWrite.back());
      buffersToWrite.pop_back();
      newBuffer2->reset();
    }

    buffersToWrite.clear();
    output.flush();
  }
  output.flush();
}

