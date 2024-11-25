#pragma once
#include"mysqltask.h"

namespace mengqiu{
    class ImChatTask:public IMysqlTask{
    public:
        ImChatTask(const std::string& sql,enum SQLTYPE type=SQL_QUERY);
        ~ImChatTask();
    public:
        virtual void    Execute(database::DataBaseMySql* poConn) override;
        virtual RPValue Reply() override;
    private:
        enum SQLTYPE m_sqlType;
        RPValue      m_rpValue;
    };
}