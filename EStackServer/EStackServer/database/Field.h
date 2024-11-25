#ifndef FIELD_H
#define FIELD_H
#include<mysql/mysql.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
#include<base/Logging.h>
#include<string>
#include<memory>
using namespace std;

namespace mengqiu{
    namespace database{
        class Field{
        public:
            typedef enum{
                EDY_TYPE_NONE=0,
                EDY_TYPE_STRING,
                EDY_TYPE_INTERGER,
                EDY_TYPE_FLOAT,
                EDY_TYPE_BOOL,
                EDY_TYPE_NULL
            }DataTypes;
        public:
            Field();
            ~Field();
            bool          IsNull(){return m_isnull;}
            void          SetType(DataTypes tp){m_type=tp;}
            void          SetName(const string& name){m_name=name;}
            void          SetValue(const char* value,size_t len);
            DataTypes     GetType() const{return m_type;}
            const string& GetName()const{return m_name;}
            const string& GetValue()const{return m_value;}
            //TODO:整数 小数 字符串
            bool     toBool()const{return atoi(m_value.c_str())!=0;}
            int8_t   toInt8()const{return static_cast<int8_t>(atoi(m_value.c_str()));}
            uint8_t  toUInt8()const{return static_cast<uint8_t>(atoi(m_value.c_str()));}
            int32_t  toInt32()const{return atoi(m_value.c_str());}
            uint32_t toUInt32()const{return (uint32_t)atoi(m_value.c_str());}
            int64_t  toInt64()const{return atoll(m_value.c_str());}
            uint64_t toUInt64()const{return (uint64_t)atoll(m_value.c_str());}
            float    toFloat()const{return atof(m_value.c_str());}
            const string& GetString()const{return m_value;}
        private:
            bool      m_isnull;
            string    m_value;
            string    m_name;
            DataTypes m_type;
            
        };
    } // namespace database 
}
#endif //FIELD_H