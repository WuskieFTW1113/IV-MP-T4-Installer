#ifndef __HANDLER_H
#define __HANDLER_H

#include <map>
#include <string>
#include "sresult.h"
#include <lua.hpp>

class MySQL
{
public:
	MySQL(const char* ip, const char* user, const char* pw, const char* db, int port, bool ac);
	~MySQL();

	void Connect();
	void Close();

	const bool OK( ) { return m_ok; }
	const unsigned int Errno( ) { return mysql_errno( m_handle ); }
	const char* Error( ) { return mysql_error( m_handle ); }

	//const size_t EscapeString( const char* str, char* dest, size_t len );
	//const bool Ping( );

	bool Query(const char* query, bool store);

	std::string getResult(const char* column);
	bool luaRS(lua_State* l);

	const int InsertID( );
	const int AffectedRows( );
	void rollback();
	void commit();
private:
	std::string ip, user, pw, db;
	int port;
	MYSQL* m_handle;
	MYSQL_RES* res;
	MYSQL_ROW row;
	bool autocommit;
	
	std::map<std::string, const char*> rs;

	bool m_ok;
};

#endif
