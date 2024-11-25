#include"mysqlthreadmgr.h"

using namespace mengqiu::mysql;
using namespace mengqiu;
MysqlThreadMsgr::MysqlThreadMsgr(){

}

MysqlThreadMsgr::MysqlThreadMsgr(const MysqlThreadMsgr& msgr){
    memcpy(m_aoMysqlThreads,msgr.m_aoMysqlThreads,m_dwThreadCount+1);
}
MysqlThreadMsgr& MysqlThreadMsgr::operator=(const MysqlThreadMsgr& msgr){
    if(this!=&msgr){
        memcpy(m_aoMysqlThreads,msgr.m_aoMysqlThreads,m_dwThreadCount+1);
    }
    return *this;
}
MysqlThreadMsgr::~MysqlThreadMsgr(){
    for(int i=0;i<=m_dwThreadCount;i++){
        m_aoMysqlThreads[i].Stop();
    }
}

bool MysqlThreadMsgr::Init(const std::string& user,const std::string& password,const std::string& dbname,const std::string& host="127.0.0.1",unsigned int port=3306){
    for(uint32_t i=0;i<m_dwThreadCount+1;i++){
        if(!m_aoMysqlThreads[i].Start(user,password,dbname,host,port)){
            return false;
        }
    }
    return true;
}

bool MysqlThreadMsgr::AddTask(uint32_t dwHashID,IMysqlTask* poTask){
    LOG_DEBUG<<"MysqlThreadMsgr::AddTask HashID = "<<dwHashID;
    uint32_t btindex=GetTableHashID(dwHashID);
    if(btindex>m_dwThreadCount){
        return false;
    }
    return m_aoMysqlThreads[btindex].AddTask(poTask);
}
bool MysqlThreadMsgr::AddTask(IMysqlTask* poTask){
    return m_aoMysqlThreads[m_dwThreadCount].AddTask(poTask);
}

// bool MysqlThreadMsgr::ProcessReplyTask(int32_t nCount){
//     bool bRet=false;
//     for(uint32_t i=0;i<m_dwThreadCount+1;i++){
//         IMysqlTask* poTask=m_aoMysqlThreads[i].GetReplyTask();
//         uint32_t dwProcessNbr=0;
//         while (((nCount==-1)||(dwProcessNbr<nCount))&&(nullptr!=poTask)){
//             poTask->Reply();
//             poTask=m_aoMysqlThreads[i].GetReplyTask();
//             ++dwProcessNbr;
//         }

//         if(dwProcessNbr==nCount||poTask==nullptr){
//             bRet=true;
//         }
//     }
//     return bRet;
// }
RPValue* MysqlThreadMsgr::ProcessReplyTask(IMysqlTask* poTask){
    RPValue* res=nullptr;
    for(uint32_t i=0;i<m_dwThreadCount+1;i++){
        if((res=m_aoMysqlThreads[i].GetReplyTask(poTask))==nullptr)continue;
        return res;
    }
    return res;
}
uint32_t MysqlThreadMsgr::hash_add(const char* key){
    uint32_t prime=m_dwThreadCount+1;
    uint32_t hash,i;
    size_t len=strlen(key);
    for(hash=len,i=0;i<len;i++){
        hash+=key[i];
    }
    return hash%prime;
}