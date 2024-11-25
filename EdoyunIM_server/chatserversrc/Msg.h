
#pragma once

#include <stdint.h>

enum msg_type
{
    msg_type_unknown,
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
    msg_type_chat   = 1100,         //单聊消息
    msg_type_multichat,             //群发消息
};

#pragma pack(push, 1)//用于更改结构体成员的对齐方式
//协议头
struct msg
{
    int32_t  packagesize;       //指定包体的大小
};

#pragma pack(pop)

/** 
 *  错误码
 *  0   成功
 *  100 注册失败
 *  101 已注册
 *  102 未注册
 *  103 密码错误
 *  104 更新用户信息失败
 *  105 修改密码失败
 *  106 创建群失败
 */

/**
 *  心跳包协议
 **/
/*
    cmd = 1000, seq = 0
    cmd = 1000, seq = 0
 **/

/**
 *  注册协议
 **/
/*
    cmd = 1001, seq = 0,  {"username": "13917043329", "nickname": "balloon", "password": "123"}
    cmd = 1001, seq = 0,  {"code": 0, "msg": "ok"}
 **/

/**
 *  登录协议
 **/
/*
    //status: 在线状态 0离线 1在线 2忙碌 3离开 4隐身
    //clienttype: 客户端类型,pc=1, android=2, ios=3
    cmd = 1002, seq = 0, {"username": "13917043329", "password": "123", "clienttype": 1, "status": 1}
    cmd = 1002, seq = 0, {"code": 0, "msg": "ok", "userid": 8, "username": "13917043320", "nickname": "zhangyl",
                          "facetype": 0, "customface":"文件md5", "gender":0, "birthday":19891208, "signature":"哈哈，终于成功了",
                          "address":"上海市东方路3261号", "phonenumber":"021-389456", "mail":"balloonwj@qq.com"}
 **/

/** 
 * 获取用户列表
 **/
/*
    cmd = 1003, seq = 0
    cmd = 1003, seq = 0,  
    {"code": 0, "msg": "ok", "userinfo":[{"userid": 2,"username":"qqq", 
                                          "nickname":"qqq123", "facetype": 0, 
                                          "customface":"466649b507cdf7443c4e88ba44611f0c", 
                                          "gender":1, "birthday":19900101, "signature":"生活需要很多的力气呀。xx",
                                          "address": "", "phonenumber": "", "mail":"", "clienttype": 1, 
                                          "status":1},
                                          {"userid": 3,"username":"hujing", "nickname":"hujingx", 
                                          "facetype": 0, "customface":"", "gender":0, "birthday":19900101, 
                                          "signature":"", "address": "", "phonenumber": "", "mail":"", 
                                          "clienttype": 1, "status":0}]}
**/

/** 
 * 查找用户
 **/
/*
    //type查找类型 0所有， 1查找用户 2查找群
    cmd = 1004, seq = 0, {"type": 1, "username": "zhangyl"}
    cmd = 1004, seq = 0, { "code": 0, "msg": "ok", "userinfo": [{"userid": 2, "username": "qqq", "nickname": "qqq123", "facetype":0}] } 
**/

/** 
 *  操作好友，包括加好友、删除好友
 **/
/* 
    //type为1发出加好友申请 2 收到加好友请求(仅客户端使用) 3应答加好友 4删除好友请求 5应答删除好友
    //当type=3时，accept是必须字段，0对方拒绝，1对方接受
    cmd = 1005, seq = 0, {"userid": 9, "type": 1}
    cmd = 1005, seq = 0, {"userid": 9, "type": 2, "username": "xxx"}
    cmd = 1005, seq = 0, {"userid": 9, "type": 3, "username": "xxx", "accept": 1}

    //发送
    cmd = 1005, seq = 0, {"userid": 9, "type": 4}
    //应答
    cmd = 1005, seq = 0, {"userid": 9, "type": 5, "username": "xxx"}
 **/

/**
 *  用户状态改变
 **/
/*
    //type 1上线(将来会扩展成在线、隐身、忙碌、离开等状态) 2离线 3用户签名、头像、昵称发生变化
    cmd = 1006, seq = 0, {"type": 1, "onlinestatus": 1} //上线onlinestatus=1, 离线onlinestatus=0
    cmd = 1006, seq = 0, {"type": 3}
    **/

/**
 *  更新用户信息
 **/
/*
    cmd = 1007, seq = 0, 用户信息: {"nickname": "xx", "facetype": 0,"customface":"文件md5", "gender":0, "birthday":19891208, "signature":"哈哈，终于成功了",
                                                                "address":"上海市东方路3261号", "phonenumber":"021-389456", "mail":"balloonwj@qq.com"}
    cmd = 1007, seq = 0, {"code": 0, "msg": "ok", "userid": 9, "username": "xxxx", "nickname": "xx", "facetype": 0,
                                                                "customface":"文件md5", "gender":0, "birthday":19891208, "signature":"哈哈，终于成功了",
                                                                "address":"上海市东方路3261号", "phonenumber":"021-389456", "mail":"balloonwj@qq.com"}
**/

/**
 *  修改密码
 **/
/*
    cmd = 1008, seq = 0, {"oldpassword": "xxx", "newpassword": "yyy"}
    cmd = 1008, seq = 0, {"code":0, "msg": "ok"}
**/

/**
 *  创建群
 **/
/*
    cmd = 1009, seq = 0, {"groupname": "我的群名称", "type": 0}
    cmd = 1009, seq = 0, {"code":0, "msg": "ok", "groupid": 12345678, "groupname": "我的群名称"}, 用户id和群id都是4字节整型，32位，群id的高位第七位为1
**/

/**
 *  获取群成员
 **/
/*
cmd = 1010, seq = 0, {"groupid": 群id}
cmd = 1010, seq = 0, {"code":0, "msg": "ok", "groupid": 12345678, 
                    "members": [{"userid": 1, "username": xxxx, "nickname": yyyy, "facetype": 1, "customface": "ddd", "status": 1, "clienttype": 1},
                    {"userid": 1, "username": xxxx, "nickname": yyyy, "facetype": 1, "customface": "ddd", "status": 1, "clienttype": 1},
                    {"userid": 1, "username": xxxx, "nickname": yyyy, "facetype": 1, "customface": "ddd", "status": 1, "clienttype": 1}]}
**/

/**
 *  聊天协议
 **/
/* 
    cmd = 1100, seq = 0, data:聊天内容 targetid(消息接受者)
    cmd = 1100, seq = 0, data:聊天内容 senderid(消息接受者), targetid(消息发送者)
 **/

/**
 *  群发协议
 **/
/*
    cmd = 1101, seq = 0, data:聊天内容 targetid(消息接受者)
    cmd = 1101, seq = 0, data:聊天内容, {"targets": [1, 2, 3]}(消息接收者)
**/

