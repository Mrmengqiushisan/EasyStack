#include"Field.h"

using namespace mengqiu::database;

void Field::SetValue(const char* value,size_t len){
    if(value==nullptr||len==0){
        m_isnull=true;
        m_value.clear();
        return;
    }   
    m_value.assign(value,len);
    m_isnull=false;
}
Field::Field():m_isnull(true),m_type(EDY_TYPE_NONE){

}
Field::~Field(){

}