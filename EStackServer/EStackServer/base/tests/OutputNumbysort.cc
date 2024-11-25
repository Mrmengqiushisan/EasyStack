#include"../Thread.h"
#include"../Logging.h"
#include"../CountDownLatch.h"
#include"../CurrentThread.h"
#include"../Mutex.h"
#include"../Condition.h"
#include"../Timestamp.h"
#include<stdint.h>
#include<stdio.h>
#include<vector>
#include<memory>
#include<unistd.h>
bool running=true;
int data=1;
class Test{
public:
    Test(int numThread):
    cond_(mutex_),
    startLatch_(numThread),
    endLatch_(numThread)
    {
        thread_.reserve(numThread);
        for(int i=0;i<numThread;i++){
            char name[32];
            snprintf(name,sizeof(name),"work thread %d",i+1);
            thread_.emplace_back(new muduo::Thread([this,i]{threadfunc(i+1);},muduo::string(name)));
        }
    }

    void Start(){
        muduo::Timestamp start=muduo::Timestamp::now();
        for(auto& thr:thread_){
            thr->start();
        }
        startLatch_.wait();
        muduo::Timestamp stop=muduo::Timestamp::now();
        printf("tid:%d, all thread started, %.3fms\n",muduo::CurrentThread::tid(),1000*muduo::timeDifference(stop,start));
    }
    void joinAll(){
        printf("tid=%d,%s joinning\n",muduo::CurrentThread::tid(),muduo::CurrentThread::name());
        muduo::Timestamp start=muduo::Timestamp::now();
        running=false;
        cond_.notifyAll();
        endLatch_.wait();
        for(auto& thr:thread_){
            thr->join();
        }
        muduo::Timestamp stop=muduo::Timestamp::now();
        printf("all %zd thread joined, %.3fms \n",thread_.size(),muduo::timeDifference(stop,start)*1000);
    }

    void threadfunc(int  i){
        printf("tid=%d, %s started num=%d\n",
        muduo::CurrentThread::tid(),
        muduo::CurrentThread::name(),i);
        startLatch_.countDown();
        while(running){
            // if(data!=i)continue;
            while(data!=i&&running){
                cond_.wait();
            }
            if(!running)break;
            assert(data==i);
            printf("tid=%d,Output data=%d\n",muduo::CurrentThread::tid(),data);
            if(data==4)data=1;
            else ++data;
            cond_.notifyAll();
        }
        endLatch_.countDown();
        printf("tid=%d,%s stopped\n",muduo::CurrentThread::tid(),muduo::CurrentThread::name());
    }
    muduo::MutexLock       mutex_;
    muduo::Condition       cond_;
    muduo::CountDownLatch  startLatch_;
    muduo::CountDownLatch  endLatch_;
    std::vector<std::unique_ptr<muduo::Thread>>thread_;
};

int main(){
    //此段代码证明cond_waitforSeconds是在指定时间跳出wait的
    // Test t(4);
    // while(running){
    //     printf("tid=%d,%s waitting\n",muduo::CurrentThread::tid(),muduo::CurrentThread::name());
    //     t.cond_.waitForSeconds(1);
    //     printf("tid=%d,%s out\n",muduo::CurrentThread::tid(),muduo::CurrentThread::name());
    // }

    Test t(4);
    t.Start();
    struct timespec tim{0,500*1000*1000};
    nanosleep(&tim,NULL);
    t.joinAll();
    printf("output end \n");
}