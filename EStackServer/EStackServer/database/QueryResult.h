#ifndef QUERY_RESULT_H
#define QUERY_RESULT_H
#include<mysql/mysql.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
#include<base/Logging.h>
#include<string>
#include<memory>
#include"Field.h"
#include<vector>
using namespace std;
/*
此类用于获取和保存由数据库查询到的数据
*/
namespace mengqiu{
    namespace database{
        class QueryResult   
        {
        public:
            //并没有提供默认构造 因为必须提供MYSQL_RES对象 用于获取数据
            QueryResult(MYSQL_RES* result,uint32_t rowcount,uint32_t columncount);
            ~QueryResult();
            //获取res中的下一行
            bool NextRow();//true表示有下一个，并且切换成功，false表示没有了
            //得到一个指针类型为元素类型的指针，该指针指向顺序元素的首地址
            Field* Fetch(){
                if(m_result==nullptr)return nullptr;
                return m_currentRow.data();
            }
            const Field& operator[](int index)const{
                return m_currentRow[index];
            }
            const Field& operator[](const string& name)const{
                return m_currentRow[GetFieldIndexByname(name)];
            }
            inline uint32_t GetFieldCount(){return m_colcount;}
            inline uint32_t GetRowCount(){return m_rowcount;}
            vector<string> const& GetFieldName()const{return m_vecFieldName;}
            void EndQuery();
            static Field::DataTypes toEDYTtpe(enum_field_types mysqltype);
        protected:
            int GetFieldIndexByname(const string& name)const {
                for(uint32_t i=0;i<m_vecFieldName.size();i++){
                    if(m_vecFieldName[i]==name)return i;
                }
                return -1;
            }
        private:
            vector<Field>  m_currentRow;
            vector<string> m_vecFieldName;
            MYSQL_RES*    m_result;
            uint32_t      m_rowcount;
            uint32_t      m_colcount;

        };
        typedef std::shared_ptr<QueryResult> QueryResultPtr;
    }
}
#endif //QUERY_RESULT_H