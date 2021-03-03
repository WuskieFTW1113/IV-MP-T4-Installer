#include "exporting.h"
#if linux
#else
#include "stdafx.h"
#include "handler.h"
#include <iostream>
//#include <typeinfo>


MySQL::MySQL(const char* ip, const char* user, const char* pw, const char* db, int port, bool ac)
{
	m_ok = false;
	res = NULL;
	this->ip = ip, this->user = user, this->pw = pw, this->db = db, this->port = port, this->autocommit = ac;
}

MySQL::~MySQL( )
{	
	this->Close();
}

void MySQL::Connect()
{
	m_handle = mysql_init(0);
	if(m_handle)
	{
		if(mysql_real_connect(m_handle, ip.c_str(), user.c_str(), pw.c_str(), db.c_str(), port, 0, CLIENT_COMPRESS))
		{
			m_ok = !mysql_select_db(m_handle, db.c_str());
			mysql_autocommit(m_handle, autocommit);
		}
	}
}

void MySQL::Close()
{
	m_ok = false;
	if(m_handle)
	{
		if(res)
		{
			mysql_free_result(res);
		}
		mysql_close(m_handle);
		m_handle = NULL;
		res = NULL;
	}
}

/*const size_t MySQL::EscapeString( const char* str, char* dest, size_t len )
{
	return mysql_real_escape_string( m_handle, dest, str, static_cast< unsigned long >( len ) );
}

const bool MySQL::Ping( )
{
	return mysql_ping( m_handle ) == 0;
}*/

bool MySQL::Query(const char* query, bool store)
{
	if(res)
	{
		mysql_free_result(res);
		res = NULL;
	}
	
	if(mysql_real_query(m_handle, query, static_cast < unsigned long > ( strlen( query ) ) ) )
	{
		return false;
	}

	if(store)
	{
		res = mysql_store_result(m_handle);
		if(res == NULL && mysql_field_count(m_handle) > 0)
		{
			return false;
		}
	
		if(!rs.empty())
		{
			rs.clear();
		}
	}
	return true;
}

const int MySQL::InsertID()
{
	return static_cast < int > ( mysql_insert_id( m_handle ) );
}

const int MySQL::AffectedRows()
{
	return static_cast < int > ( mysql_affected_rows( m_handle ) );
}

void MySQL::rollback()
{
	mysql_rollback(m_handle);
}

void MySQL::commit()
{
	mysql_commit(m_handle);
}

bool MySQL::luaRS(lua_State* l)
{
	lua_createtable(l, 2, 0);
	if(res)
	{
		int count = 1;
		MYSQL_ROW row = mysql_fetch_row(res);
		//if(row) lua_createtable(l, 2, 0);
		while(row)
		{
			mysql_field_seek(res, 0);
			MYSQL_FIELD* field;
			int i = 0;

			int columns = mysql_field_count(m_handle);
			lua_pushnumber(l, count);
			lua_createtable(l, 0, columns);
			count++;

			for(field = mysql_fetch_field(res), i = 0; field != 0; field = mysql_fetch_field(res), i++)
			{
				lua_pushstring(l, (row[i] ? row[i] : ""));
				lua_setfield(l, -2, field->name);
			}
			lua_settable(l, -3);
			row = mysql_fetch_row(res);
		}
		//return 1;
	}
	return 1;
}

std::string MySQL::getResult(const char* column)
{
	if(rs.find(column) == rs.end())
	{
		return std::string("");
	}
	return std::string(rs[column]);
}
#endif