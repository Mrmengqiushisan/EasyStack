#pragma once
#include<base/Logging.h>
#include<thread>
#include<condition_variable>
#include<unordered_map>
#include"mysqltask.h"
#include"tasklist.h"
#include"../database/databasemysql.h"

namespace mengqiu{
    class MySqlThread{
    public:
        MySqlThread();
        ~MySqlThread();
    public:
        void Run();
        bool Start(const std::string& user,const std::string& pwd,const std::string& dbname,const std::string& host="127.0.0.1",unsigned int port=3306);
        void Stop();
        bool AddTask(IMysqlTask* poTask);
        RPValue* GetReplyTask(IMysqlTask* poTask);
    protected:
        bool _init();
        void _mainLoop();
        void _Uninit();
    private:
        bool           m_bTerminate;
        bool           m_bStart;
        TaskList       m_oTask;
        std::unordered_map<IMysqlTask*,RPValue*>  m_oPelyMap;
        database::DataBaseMySql* m_poConn;
        std::mutex  mutex_;
        std::condition_variable       cond_;
        std::shared_ptr<std::thread>  m_pThread;
        using PaitTaskMap=std::pair<mengqiu::IMysqlTask*,mengqiu::RPValue*>;
    };
}