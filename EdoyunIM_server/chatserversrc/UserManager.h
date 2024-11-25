

#pragma once
#include <stdint.h>
#include <string>
#include <list>
#include <mutex>
#include <set>

using namespace std;

#define GROUPID_BOUBDARY   0x0FFFFFFF 

//用户或者群
struct User
{
    int32_t        userid;      //0x0FFFFFFF以上是群号，以下是普通用户
    string         username;    //群账户的username也是群号userid的字符串形式
    string         password;
    string         nickname;    //群账号为群名称
    int32_t        facetype;
    string         customface;
    string         customfacefmt;//自定义头像格式
    int32_t        gender;
    int32_t        birthday;
    string         signature;
    string         address;
    string         phonenumber;
    string         mail;
    int32_t        ownerid;        //对于群账号，为群主userid
    set<int32_t>   friends;        //为了避免重复
};

class UserManager final
{
public:
    UserManager();
    ~UserManager();

    bool Init(const char* dbServer, const char* dbUserName, const char* dbPassword, const char* dbName);

    UserManager(const UserManager& rhs) = delete;
    UserManager& operator=(const UserManager& rhs) = delete;

    bool AddUser(User& u);
    bool MakeFriendRelationship(int32_t smallUserid, int32_t greaterUserid);
    bool ReleaseFriendRelationship(int32_t smallUserid, int32_t greaterUserid);
    bool AddFriendToUser(int32_t userid, int32_t friendid);
    bool DeleteFriendToUser(int32_t userid, int32_t friendid);
    bool UpdateUserInfo(int32_t userid, const User& newuserinfo);
    bool ModifyUserPassword(int32_t userid, const std::string& newpassword);

    bool AddGroup(const char* groupname, int32_t ownerid, int32_t& groupid);

    //聊天消息入库
    bool SaveChatMsgToDb(int32_t senderid, int32_t targetid, const std::string& chatmsg);

    //TODO: 当用户越来越多，并发量越来越多的时候，这个系列的函数效率高吗？
    bool GetUserInfoByUsername(const std::string& username, User& u);
    bool GetUserInfoByUserId(int32_t userid, User& u);
    bool GetFriendInfoByUserId(int32_t userid, std::list<User>& friends);

private:
    bool LoadUsersFromDb();
    bool LoadRelationhipFromDb(int32_t userid, std::set<int32_t>& r);

private:
    int                 m_baseUserId{ 0 };        //m_baseUserId, 取数据库里面userid最大值，新增用户在这个基础上递增
    int                 m_baseGroupId{0x0FFFFFFF};
    list<User>          m_allCachedUsers;
    mutex               m_mutex;

    string              m_strDbServer;
    string              m_strDbUserName;
    string              m_strDbPassword;
    string              m_strDbName;
};