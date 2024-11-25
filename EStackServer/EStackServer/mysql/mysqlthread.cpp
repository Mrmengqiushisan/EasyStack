#include"mysqlthread.h"

#include<functional>
using namespace mengqiu;

MySqlThread::MySqlThread()
:m_bTerminate(false),m_bStart(false),m_poConn(nullptr){

}

MySqlThread::~MySqlThread(){

}

void MySqlThread::Run(){
}

bool MySqlThread::_init(){
    if(m_bStart)return true;
    //启动线程
    m_pThread.reset(new std::thread(std::bind(&MySqlThread::_mainLoop,this)));
    {
        std::unique_lock<std::mutex> lock(mutex_);
        while (m_bStart==false){
            cond_.wait(lock);
        }
    }
}
void MySqlThread::_mainLoop(){
    m_bStart=true;
    {
        std::unique_lock<std::mutex> lock(mutex_);
        cond_.notify_one();
    }
    IMysqlTask* poTask;
    while(!m_bTerminate){
        if((poTask=m_oTask.Pop())!=nullptr){
            poTask->Execute(m_poConn);
            m_oPelyMap.insert(PaitTaskMap(poTask,&poTask->Reply()));
            continue;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}
void MySqlThread::_Uninit(){

}

bool MySqlThread::Start(const std::string& user,const std::string& pwd,const std::string& dbname,const std::string& host,unsigned int port){
    m_poConn=new database::DataBaseMySql();
    if(!m_poConn){
        LOG_FATAL<<"MySqlThread::Start , Cannot open database";
        return false;
    }
    if(!m_poConn->connect(user,pwd,dbname,host,port)){
        LOG_FATAL<<"MySqlThread::Start, mysql connect failed";
        return false;
    }
    return _init();
}

void MySqlThread::Stop(){
    if(m_bTerminate)return;
    m_bTerminate=true;
    if(m_pThread->joinable()){
        m_pThread->join();
    }
}

bool MySqlThread::AddTask(IMysqlTask* poTask){
    return m_oTask.Push(poTask);
}

RPValue* MySqlThread::GetReplyTask(IMysqlTask* poTask){
    if(!m_oPelyMap.count(poTask)){
        return nullptr;
    }
    RPValue* res=m_oPelyMap[poTask];
    m_oPelyMap.erase(poTask);
    return res;
}

