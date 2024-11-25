#pragma once
#include"mysqltask.h"
#include<stdint.h>
#define MAX_TASK_NUM 1000
namespace mengqiu{
    class TaskList{
    public:
        TaskList();
        ~TaskList();
        bool Push(IMysqlTask* poTask);
        IMysqlTask* Pop();
    private:
        uint16_t    m_uReadIndex;
        uint16_t    m_uWriteIndex;
        IMysqlTask* m_pTaskNode[MAX_TASK_NUM];
    };
}
