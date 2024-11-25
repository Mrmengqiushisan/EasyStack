#include"imchattask.h"

using namespace mengqiu;

ImChatTask::ImChatTask(const std::string& sql,enum SQLTYPE type):
IMysqlTask(sql),m_sqlType(type){

}
ImChatTask::~ImChatTask(){

}


 void ImChatTask::Execute(database::DataBaseMySql* poConn) {
    bool isFirstRP=(m_sqlType==SQL_QUERY)?true:false;
    if(isFirstRP){
        m_rpValue.m_queryPtr=poConn->Query(m_strsql);
    }else{
        m_rpValue.m_execute=poConn->Execute(m_strsql.c_str());
    }
 }

 RPValue ImChatTask::Reply() {
    return m_rpValue;
 }