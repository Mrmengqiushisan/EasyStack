#ifndef USER_MANAGER_H
#define USER_MANAGER_H
#include "base/Singleton.h"
#include "base/noncopyable.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <set>
#include <list>
#include <mutex>
using namespace std;
using namespace muduo;
class User{
public:
    User()
    :userid(-1),facetype(-1),gender(-1),birthday(-1),ownerid(-1){}
    ~User()=default;
public:
    int32_t userid;         //用户id
    string  username;       //用户名
    string  password;       //密码
    string  nickname;       //昵称
    int32_t facetype;       //默认头像
    string  customface;     //自定义头像
    string  customfacefmt;  //自定义头像格式
    int32_t gender;         //性别
    int32_t birthday;       //生日
    string  signature;      //签名
    string  address;         //位置
    string  phonenumber;    //手机号
    string  mail;           //邮箱
    int32_t ownerid;        //用于标记群主
    set<int32_t> friends;   //用于记录好友的id
};

class UserManager final :muduo::noncopyable{
public:
    UserManager()=default;
    ~UserManager()=default;
    bool Init();
    //添加用户
    bool Adduser(User& user);
    //从数据库加载用户信息
    bool LoadUsersFromDB();
    //从数据库中加载用户关系信息
    bool LoadRelationshipFromDB(int32_t userid, std::set<int32_t>&friends);
    //通过用户名称获取用户信息
    bool GetUserInfoByUserName(const string& username,User& user);
private:
    list<User> m_cachedUsers;
    std::mutex m_mutex;
    int32_t    m_baseUserID{0};
    int32_t    m_baseGroupID{0xFFFFFFF};
};

#endif