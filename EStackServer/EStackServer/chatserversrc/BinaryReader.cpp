#include"BinaryReader.h"
using namespace mengqiu;

template<>
bool BinaryWriter::WriteData(const std::string& data){
    std::string out;
    Compress(data.size(),out);
    m_buffer.append(out.c_str(),out.size());
    m_index+=out.size();
    if(data.size()>0){
        m_buffer.append(data.c_str(),data.size());
        m_index+=data.size();
    }
    return true;
}