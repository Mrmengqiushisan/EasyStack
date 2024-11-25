#include"UserManager.h"
#include"MySqlManager.h"
#include<sstream>

bool UserManager::Init(){
    //加载用户信息(所有的用户)
    if(!LoadUsersFromDB()){
        cout<<"load users from database failed!\r\n";
        return false;
    }
    //加载用户关系
    for(auto& user:m_cachedUsers){
        if(!LoadRelationshipFromDB(user.userid,user.friends)){
            cout<<"load friend failed!\r\n";
        }
    }
    return true;
}

bool UserManager::LoadUsersFromDB(){
    stringstream sql;
    sql << "SELECT f_user_id, f_username, f_nickname, \
    f_password,  f_facetype, f_customface, f_gender, \
    f_birthday, f_signature, f_address, f_phonenumber, \
    f_mail FROM t_user ORDER BY  f_user_id DESC;";
    QueryResultPtr result= Singleton<MySqlManager>::instance().Query(sql.str());
    if(result==nullptr)return false;
    while(result!=nullptr){
        Field* pRow=result->Fetch();
        if(pRow==nullptr)break;
        User u;
        u.userid=pRow[0].toInt32();
        u.username=pRow[1].GetString();
        u.nickname = pRow[2].GetString();
		u.password = pRow[3].GetString();
		u.facetype = pRow[4].toInt32();
		u.customface = pRow[5].GetString();
		u.gender = pRow[6].toInt32();
		u.birthday = pRow[7].toInt32();
		u.signature = pRow[8].GetString();
		u.address = pRow[9].GetString();
		u.phonenumber = pRow[10].GetString();
        u.mail=pRow[11].GetString();
        {
            std::lock_guard<std::mutex> guard(m_mutex);
            m_cachedUsers.push_back(u);
        }
        m_baseUserID=max(u.userid,m_baseUserID);
        if(result->NextRow()==false)break;
    }
    result->EndQuery();
    return true;
}

bool UserManager::LoadRelationshipFromDB(int32_t userid, std::set<int32_t>&friends){
    stringstream sql;
    sql<<"SELECT f_user_id1,f_user_id2 FROM t_user_relationship\
    WHERE f_user_id1= "<<userid<<" OR f_user_id2 = "<<userid<<";";
    QueryResultPtr result= Singleton<MySqlManager>::instance().Query(sql.str());
    if(result==nullptr)return false;
    while(result!=nullptr){
        Field* pRow=result->Fetch();
        if(pRow==nullptr)break;
        int32_t friednid1=pRow[0].toInt32();
        int32_t friendid2=pRow[1].toInt32();
        friends.insert((friendid2==userid)?friednid1:friendid2);
        if(result->NextRow()==false)break;
    }
    result->EndQuery();
    return true;
}

bool UserManager::Adduser(User& user){
    stringstream sql;
    m_baseUserID++;
    sql<<"INSERT INTO t_user(f_user_id,f_username,f_nickname,f_password,f_register_time)\
     VALUES("<<m_baseUserID<<", '"<<user.username<<"','"<<user.nickname<<"','"
     <<user.password<<"',NOW());";
    if(!Singleton<MySqlManager>::instance().Excute(sql.str())){
        return false;
    }
    user.userid=m_baseUserID;
    user.facetype=0;
    user.birthday=20000101;
    user.gender=0;
    user.ownerid=0;
    {
        lock_guard<mutex> guard(m_mutex);
        m_cachedUsers.push_back(user);
    }
    return true;
}

bool UserManager::GetUserInfoByUserName(const string& username,User& user){
    lock_guard<mutex> guard(m_mutex);
    for(const auto& iter:m_cachedUsers){
        if(iter.username==username){
            user=iter;
            return true;
        }
    }
    return false;
}