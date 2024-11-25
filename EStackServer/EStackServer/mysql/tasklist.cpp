#include"tasklist.h"
#include"../base/Logging.h"
#include<string.h>
using namespace mengqiu;

TaskList::TaskList():m_uReadIndex(0),m_uWriteIndex(0){
    memset(m_pTaskNode,0,sizeof(m_pTaskNode));
}

TaskList::~TaskList(){
    for(int i=0;i<MAX_TASK_NUM;i++){
        if(m_pTaskNode[i]){
            delete m_pTaskNode[i];
            m_pTaskNode[i]=nullptr;
        }
    }
}
bool TaskList::Push(IMysqlTask* poTask){
    uint16_t uNextindex=static_cast<uint16_t>((m_uWriteIndex+1)%MAX_TASK_NUM);
    if(uNextindex==m_uReadIndex){
        LOG_ERROR<<"mysql task list full (read :"<<m_uReadIndex<<", write: "<<m_uWriteIndex<<")";
        return false;
    }
    m_pTaskNode[m_uWriteIndex]=poTask;
    m_uWriteIndex=uNextindex;
    return true;
}
IMysqlTask* TaskList::Pop(){
    if(m_uWriteIndex==m_uReadIndex){
        LOG_INFO<<"mysql task list is empty";
        return nullptr;
    }
    IMysqlTask* pTask=m_pTaskNode[m_uReadIndex];
    m_uReadIndex=static_cast<uint16_t>((m_uReadIndex+1)%MAX_TASK_NUM);
    return pTask;
}