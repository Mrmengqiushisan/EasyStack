#include <fstream>
#include <stdarg.h>

#include "databasemysql.h"
#include "../base/logging.h"

CDatabaseMysql::CDatabaseMysql(void)
{
	//m_Mysql = new MYSQL;
    m_Mysql = NULL;
	m_bInit = false;
}

CDatabaseMysql::~CDatabaseMysql(void)
{
	if (m_Mysql != NULL)
	{
		if (m_bInit)
		{
			mysql_close(m_Mysql);
		}

		//delete m_Mysql;
	}	
}


bool CDatabaseMysql::Initialize(const string& host, const string& user, const string& pwd, const string& dbname)
{
	LOG_INFO << "CDatabaseMysql::Initialize, begin...";

	//ClearStoredResults();
	if(m_bInit)
	{
		mysql_close(m_Mysql);
	}

    m_Mysql = mysql_init(m_Mysql);
	m_Mysql = mysql_real_connect(m_Mysql, host.c_str(), user.c_str(),
        pwd.c_str(), dbname.c_str(), 0, NULL, 0);

	//ClearStoredResults();

	LOG_INFO << host.c_str() ;
	LOG_INFO << user.c_str() ;
	LOG_INFO << pwd.c_str() ;
	LOG_INFO << dbname.c_str() ;
	
	m_DBInfo.strDBName = dbname;
	m_DBInfo.strHost = host;
	m_DBInfo.strUser = user;
	m_DBInfo.strPwd = pwd;

	if (m_Mysql)
    {
		LOG_INFO << "m_Mysql address " << (long)m_Mysql;
		LOG_INFO << "CDatabaseMysql::Initialize, set names utf8";
        mysql_query(m_Mysql, "set names utf8");
        //mysql_query(m_Mysql, "set names latin1");
		m_bInit = true;
        return true;
    }
    else
    {
        LOG_ERROR << "Could not connect to MySQL database at " << host.c_str()
            << ", " << mysql_error(m_Mysql);
        mysql_close(m_Mysql);
        return false;
    }

	LOG_INFO << "CDatabaseMysql::Initialize, init failed!";
	return false;
}

QueryResult* CDatabaseMysql::Query(const char *sql)
{
    if (!m_Mysql)
    {
		LOG_INFO << "CDatabaseMysql::Query, mysql is disconnected!";
        if(false == Initialize(m_DBInfo.strHost, m_DBInfo.strUser,
                               m_DBInfo.strPwd, m_DBInfo.strDBName))
        {
            return NULL;
        }
    }

    if (!m_Mysql)
        return 0;

    MYSQL_RES *result = 0;
    uint64_t rowCount = 0;
    uint32_t fieldCount = 0;

    {
		LOG_INFO << sql;
		int iTempRet = mysql_real_query(m_Mysql, sql, strlen(sql));
        if(iTempRet)
        {
			unsigned int uErrno = mysql_errno(m_Mysql);
			LOG_INFO << "CDatabaseMysql::Query, mysql is abnormal, errno : " << uErrno;
			if(CR_SERVER_GONE_ERROR == uErrno)
			{
				LOG_INFO << "CDatabaseMysql::Query, mysql is disconnected!";
				if(false == Initialize(m_DBInfo.strHost, m_DBInfo.strUser,
					m_DBInfo.strPwd, m_DBInfo.strDBName))
				{
					return NULL;
				}
				LOG_INFO << sql;
				iTempRet = mysql_real_query(m_Mysql, sql, strlen(sql));
				if(iTempRet)
				{
					LOG_ERROR << "SQL: " << sql ;
					LOG_ERROR << "query ERROR: " << mysql_error(m_Mysql);
				}
			}
			else
			{
				LOG_ERROR << "SQL: " << sql ;
				LOG_ERROR << "query ERROR: " << mysql_error(m_Mysql);
				return NULL;
			}            
        }

		LOG_INFO << "call mysql_store_result";
        result = mysql_store_result(m_Mysql);

        rowCount = mysql_affected_rows(m_Mysql);
        fieldCount = mysql_field_count(m_Mysql);
        // end guarded block
    }

    if (!result )
        return NULL;

  //  if (!rowCount)
  //  {
		//LOG_INFO << "call mysql_free_result";
  //      mysql_free_result(result);
  //      return NULL;
  //  }

    QueryResult *queryResult = new QueryResult(result, rowCount, fieldCount);

    queryResult->NextRow();

    return queryResult;
}

QueryResult* CDatabaseMysql::PQuery(const char *format,...)
{
    if(!format) return NULL;

    va_list ap;
    char szQuery [MAX_QUERY_LEN];
    va_start(ap, format);
    int res = vsnprintf( szQuery, MAX_QUERY_LEN, format, ap );
    va_end(ap);

    if(res==-1)
    {
        LOG_ERROR << "SQL Query truncated (and not execute) for format: " << format;
        return NULL;
    }

    return Query(szQuery);
}

bool CDatabaseMysql::Execute(const char* sql)
{
    if (!m_Mysql)
        return false;

    {
		int iTempRet = mysql_query(m_Mysql, sql);
		if(iTempRet)
		{
			unsigned int uErrno = mysql_errno(m_Mysql);
			LOG_INFO << "CDatabaseMysql::Query, mysql is abnormal, errno : " << uErrno;
			if(CR_SERVER_GONE_ERROR == uErrno)
			{
				LOG_INFO << "CDatabaseMysql::Query, mysql is disconnected!";
				if(false == Initialize(m_DBInfo.strHost, m_DBInfo.strUser,
					m_DBInfo.strPwd, m_DBInfo.strDBName))
				{
					return false;
				}
				LOG_INFO << sql;
				iTempRet = mysql_real_query(m_Mysql, sql, strlen(sql));
				if(iTempRet)
				{
					LOG_ERROR << "SQL: " << sql ;
					LOG_ERROR << "query ERROR: " << mysql_error(m_Mysql);
				}
			}
			else
			{
				LOG_ERROR << "SQL: " << sql ;
				LOG_ERROR << "query ERROR: " << mysql_error(m_Mysql);
			}
			return false;
		}
    }

    return true;
}

bool CDatabaseMysql::Execute(const char* sql, uint32_t& uAffectedCount, int& nErrno)
{
	if (!m_Mysql)
		return false;

	{
		int iTempRet = mysql_query(m_Mysql, sql);
		if(iTempRet)
		{
			unsigned int uErrno = mysql_errno(m_Mysql);
			LOG_ERROR << "CDatabaseMysql::Query, mysql is abnormal, errno : " << uErrno;
			if(CR_SERVER_GONE_ERROR == uErrno)
			{
				LOG_ERROR << "CDatabaseMysql::Query, mysql is disconnected!";
				if(false == Initialize(m_DBInfo.strHost, m_DBInfo.strUser,
					m_DBInfo.strPwd, m_DBInfo.strDBName))
				{
					return false;
				}
				LOG_INFO << sql;
				iTempRet = mysql_query(m_Mysql, sql);
				nErrno = iTempRet;
				if(iTempRet)
				{
					LOG_ERROR << "SQL: " << sql ;
					LOG_ERROR << "query ERROR: " << mysql_error(m_Mysql);
				}
			}
			else
			{
				LOG_ERROR << "SQL: " << sql ;
				LOG_ERROR << "query ERROR: " << mysql_error(m_Mysql);
			}
			return false;
		}
		uAffectedCount = static_cast<uint32_t>(mysql_affected_rows(m_Mysql));
	}

	return true;
}

bool CDatabaseMysql::PExecute(const char * format,...)
{
    if (!format)
        return false;

    va_list ap;
    char szQuery [MAX_QUERY_LEN];
    va_start(ap, format);
    int res = vsnprintf( szQuery, MAX_QUERY_LEN, format, ap );
    va_end(ap);

    if(res==-1)
    {
        LOG_ERROR << "SQL Query truncated (and not execute) for format: " << format;
        return false;
    }

    if (!m_Mysql)
        return false;

    {
		int iTempRet = mysql_query(m_Mysql, szQuery);
		if(iTempRet)
		{
			unsigned int uErrno = mysql_errno(m_Mysql);
			LOG_ERROR << "CDatabaseMysql::Query, mysql is abnormal, errno : " << uErrno;
			if(CR_SERVER_GONE_ERROR == uErrno)
			{
				LOG_ERROR << "CDatabaseMysql::Query, mysql is disconnected!";
				if(false == Initialize(m_DBInfo.strHost, m_DBInfo.strUser,
					m_DBInfo.strPwd, m_DBInfo.strDBName))
				{
					return false;
				}
				LOG_INFO << szQuery;
				iTempRet = mysql_query(m_Mysql, szQuery);
				if(iTempRet)
				{
					LOG_ERROR << "SQL: " << szQuery ;
					LOG_ERROR << "query ERROR: " << mysql_error(m_Mysql);
				}
			}
			else
			{
				LOG_ERROR << "SQL: " << szQuery ;
				LOG_ERROR << "query ERROR: " << mysql_error(m_Mysql);
			}
			return false;
		}
    }

    return true;
}

void CDatabaseMysql::ClearStoredResults()
{
	if(!m_Mysql)
	{
		return;
	}

	MYSQL_RES* result = NULL;
	while(!mysql_next_result(m_Mysql))
	{
		if((result = mysql_store_result(m_Mysql)) != NULL)
		{
			mysql_free_result(result);
		}
	}
}

uint32_t CDatabaseMysql::GetInsertID()
{
	return (uint32_t)mysql_insert_id(m_Mysql);
}

int32_t CDatabaseMysql::EscapeString(char* szDst, const char* szSrc, uint32_t uSize)
{
	if (m_Mysql == NULL)
	{
		return 0;
	}
	if (szDst == NULL || szSrc == NULL)
	{
		return 0;
	}

	return mysql_real_escape_string(m_Mysql, szDst, szSrc, uSize);
}