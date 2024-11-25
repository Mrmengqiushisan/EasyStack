#ifndef BINARY_READER_H
#define BINARY_READER_H
#include "base/copyable.h"
#include <iostream>
#include <string>
#include <string.h>
#include <unistd.h>

namespace mengqiu
{

class BinaryReader:muduo::copyable
{
public:
    static void Dump(const std::string& str){
        Dump(str.c_str(),str.size());
    }
    static void Dump(const char* buf,size_t len){
        for(size_t i=0;i<len;i++){
            if(i!=0&&i%16==0)printf("\r\n");
            printf("%02x ",(unsigned)(buf[i])&0xFF);
        }
        printf("\r\n");
    }
    BinaryReader(const std::string& buffer):m_index(0),m_buffer(buffer){
    }

    BinaryReader():m_index(0){}

    void UpdateBuffer(const std::string& buffer){
        m_buffer=buffer;
        m_index=0;
    }

    ~BinaryReader()=default;
    
    void Reset(){m_index=0;}
    size_t Szie()const {return m_buffer.size();}

    bool ReadInt32(int32_t& data){
        if(m_index+sizeof(int32_t)>m_buffer.size())return false;
        memcpy(&data,m_buffer.c_str()+m_index,sizeof(int32_t));
        m_index+=sizeof(int32_t);
        return true;
    }
    template<typename T>
    bool ReadData(T& data){
        if(m_index+sizeof(T)>m_buffer.size())return false;
        char* pData=(char*)&data;
        for(unsigned int i=0;i<sizeof(T);i++){
            pData[i]=*(m_buffer.c_str()+m_index+sizeof(T)-(i+1));
        }
        m_index+=sizeof(T);
        return true;
    }
    bool ReadData(std::string& data){
        const char* pcur=m_buffer.c_str()+m_index;
        int length{0};
        size_t i=0;
        for(;i<m_buffer.size()-m_index;i++){
            length <<=7;
            length |=pcur[i]&0x7F;
            if((pcur[i]&0x80)==0)break;
        }
        m_index+=i+1;
        data.assign(m_buffer.c_str()+m_index,length);
        m_index+=length;
        return true;
    }
private:
    uint32_t    m_index;
    std::string m_buffer;
};
class BinaryWriter{
public:
    BinaryWriter():m_index(0){

    }
    ~BinaryWriter(){

    }
    template<typename T>
    bool WriteData(const T& data){
        m_buffer.resize(m_index+sizeof(T));
        memcpy((char*)m_buffer.c_str()+m_index,&data,sizeof(data));
        m_index+=sizeof(T);
        return true;
    }
    uint32_t Size(){return m_index;}
    std::string  toString()const{return m_buffer;}
    void    Clear(){
        m_index=0;
        m_buffer.clear();
    }
protected:
    void Compress(size_t len,std::string& out){
        char c{0};
        size_t outlen=0;
        //一个字节就可以表示
        if(len<128){
            c=(char)len&0x7F;
            out+=c;
            return;
        }
        //假定这个长度不会太长 百兆以内
        //输出的时候不会超过5个字节，32个bit能够表达
        for(int i=4;i>=0;i--){
            c=(len>>(7*i))&0x7F;
            if(c==0&&out.size()==0)//目前还没有发现有效数据 都是零
                continue;
            if(i>0)
                c|=0x80;
            out+=c;
        }
    }
private:
    std::string m_buffer;
    uint32_t    m_index;
};
template<>
bool BinaryWriter::WriteData(const std::string& data);
}//namespace imserver
#endif //BINARY_READER_H

