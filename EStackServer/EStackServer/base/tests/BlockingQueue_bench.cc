#include "../BlockingQueue.h"
#include "../CountDownLatch.h"
#include "../Logging.h"
#include "../Thread.h"
#include "../Timestamp.h"

#include <map>
#include <string>
#include <vector>
#include <stdio.h>
#include <unistd.h>

bool g_verbose = true;

// Many threads, one queue.
// 此类主要用于计算通过阻塞队列在多线程环境下进行数据传递的时候存在的延迟时间
// 首先构建了线程执行函数threadfunc 在这里会循环访问队列中的数据 通过拿到的数据时间与当前时间进行计算可以得到延迟时间
// 因为在run函数中会持续向队列中填充时间数据，与此同时线程执行函数也在等待队列中的时间进来；队列中时间的输入与输出几乎是同步的
// 当然可以计算差值 以此来得到由系统性能影响的数据传送影响时间
// 至于哪个线程任务函数会拿到当前时间 完全是由于谁会最先拿到锁来决定的
// run函数执行数据发送的前提是所有线程已经开启，这是通过计数器实现的
// 线程任务函数的结束是通过拿到的时间数据是否valid来决定的，当然这是joinAll函数通过放入invalid值来让线程退出的
// 有一个明显的结论是在单线程环境下由系统性能导致的数据传输延迟明显要高于多线程环境
// 这个结论也说明了多线程环境下的高性能数据传输效率
class Bench
{
 public:
  Bench(int numThreads)
    : latch_(numThreads)
  {
    threads_.reserve(numThreads);
    for (int i = 0; i < numThreads; ++i)
    {
      char name[32];
      snprintf(name, sizeof name, "work thread %d", i);
      threads_.emplace_back(new muduo::Thread(
            std::bind(&Bench::threadFunc, this), muduo::string(name)));
    }
    for (auto& thr : threads_)
    {
      thr->start();
    }
  }

  void run(int times)
  {
    printf("waiting for count down latch\n");
    latch_.wait();//线程计数器 等待所有线程开启
    LOG_INFO << threads_.size() << " threads started";
    int64_t total_delay = 0;
    for (int i = 0; i < times; ++i)
    {
      muduo::Timestamp now(muduo::Timestamp::now());
      queue_.put(now);
      total_delay += delay_queue_.take();
    }
    printf("Average delay: %.3fus\n", static_cast<double>(total_delay) / times);
  }

  void joinAll()
  {
    for (size_t i = 0; i < threads_.size(); ++i)
    {
      queue_.put(muduo::Timestamp::invalid());
    }

    for (auto& thr : threads_)
    {
      thr->join();
    }
    LOG_INFO << threads_.size() << " threads stopped";
  }

 private:

  void threadFunc()
  {
    if (g_verbose) {
    printf("tid=%d, %s started\n",
           muduo::CurrentThread::tid(),
           muduo::CurrentThread::name());
    }

    std::map<int, int> delays;
    latch_.countDown();
    bool running = true;
    int ans{0};
    while (running)
    {
      muduo::Timestamp t(queue_.take());
      muduo::Timestamp now(muduo::Timestamp::now());
      if (t.valid())
      {
        int delay = static_cast<int>(timeDifference(now, t) * 1000000);
        // printf("tid=%d, latency = %d us\n",
        //        muduo::CurrentThread::tid(), delay);
        ++delays[delay];
        ++ans;
        delay_queue_.put(delay);
      }
      running = t.valid();
    }
    printf("get time %d\n",ans);
    if (g_verbose)
    {
      printf("tid=%d, %s stopped\n",
             muduo::CurrentThread::tid(),
             muduo::CurrentThread::name());
      for (const auto& delay : delays)
      {
        printf("tid = %d, delay = %d, count = %d\n",
               muduo::CurrentThread::tid(),
               delay.first, delay.second);
      }
    }
  }

  muduo::BlockingQueue<muduo::Timestamp> queue_;
  muduo::BlockingQueue<int> delay_queue_;
  muduo::CountDownLatch latch_;
  std::vector<std::unique_ptr<muduo::Thread>> threads_;
};

int main(int argc, char* argv[])
{
  int threads = argc > 1 ? atoi(argv[1]) : 1;

  Bench t(threads);
  t.run(100000);
  t.joinAll();
}
