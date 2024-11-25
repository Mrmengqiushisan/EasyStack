#include"./mysqltask.h"
#include"./mysqlthread.h"
#include"../base/copyable.h"
namespace mengqiu{
    namespace mysql{
        class MysqlThreadMsgr:public copyable{
        public:
            MysqlThreadMsgr();
            MysqlThreadMsgr(const MysqlThreadMsgr& msgr);
            MysqlThreadMsgr& operator=(const MysqlThreadMsgr& msgr);
            ~MysqlThreadMsgr();
        public:
            bool Init(const std::string& user,const std::string& password,const std::string& dbname,const std::string& host="127.0.0.1",unsigned int port=3306);
            //可以通过ADDHash的方式得到需要的值dwHashID
            bool AddTask(uint32_t dwHashID,IMysqlTask* poTask);
            bool AddTask(IMysqlTask* poTask);
            inline uint32_t GetTableHashID(int32_t dwHashid)const{
                return dwHashid%(m_dwThreadCount+1);
            }

            // bool ProcessReplyTask(int32_t nCount);
            RPValue* ProcessReplyTask(IMysqlTask* poTask);
            inline static uint32_t GetThreadCount(){
                return m_dwThreadCount;
            }
            static uint32_t hash_add(const char* key);
        protected:
            static const uint32_t m_dwThreadCount=9;
            MySqlThread           m_aoMysqlThreads[m_dwThreadCount+1];
        };
    }

}