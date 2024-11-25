#pragma once
#include<stdint.h>
namespace mengqiu{
    enum{
        msg_type_unknown,
        //用户消息
        msg_type_heartbeart = 1000,
        msg_type_register,
        msg_type_login,
        msg_type_getofriendlist,
        msg_type_finduser,
        msg_type_operatefriend,
        msg_type_userstatuschange,
        msg_type_updateuserinfo,
        msg_type_modifypassword,
        msg_type_creategroup,
        msg_type_getgroupmembers,
        //聊天消息
        msg_type_chat = 1100,         //单聊消息
        msg_type_multichat,             //群发消息
    }IM_MSGTYPE;

    #pragma pack(push,1)
    struct msg{
        int32_t packagesize;    //指定包体的大小
    };
    #pragma pack(pop)
    



}