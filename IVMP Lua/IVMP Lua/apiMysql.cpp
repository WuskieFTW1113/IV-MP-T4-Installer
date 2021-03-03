#include <exporting.h>
#include "apiMysql.h"
#if linux
#else

#include "stdafx.h"
#include "apiLuaParams.h"
#include "handler.h"
#include <vector>
#include "apiLua.h"

std::vector<MySQL*> mcons;

int apiMysql::define(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 6, "ssssib")) return apiLuaParams::lError(l, "Invalid params for mysql_new");
	MySQL* h = new MySQL(lua_tostring(l, 1), lua_tostring(l, 2), lua_tostring(l, 3), 
		lua_tostring(l, 4), (int)lua_tointeger(l, 5), lua_toboolean(l, 6));
	mcons.push_back(h);
	lua_pushinteger(l, mcons.size() - 1);
	return 1;
}

int apiMysql::connect(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 1, "i")) return apiLuaParams::lError(l, "Invalid params for mysql_connect");
	size_t id = (size_t)lua_tointeger(l, 1);
	if(id < 0 || id >= mcons.size()) return apiLuaParams::lError(l, "Invalid handle for mysql_connect");
	mcons[id]->Connect();
	lua_pushboolean(l, mcons[id]->OK());
	return 1;
}

int apiMysql::disconnect(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 1, "i")) return apiLuaParams::lError(l, "Invalid params for mysql_disconnect");
	size_t id = (size_t)lua_tointeger(l, 1);
	if(id < 0 || id >= mcons.size()) return apiLuaParams::lError(l, "Invalid handle for mysql_disconnect");
	mcons[id]->Close();
	return 0;
}

int apiMysql::query(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 3, "isb")) return apiLuaParams::lError(l, "Invalid params for mysql_query");
	size_t id = (size_t)lua_tointeger(l, 1);
	if(id < 0 || id >= mcons.size()) return apiLuaParams::lError(l, "Invalid handle for mysql_query");
	bool save = lua_toboolean(l, 3);
	bool b = mcons[id]->Query(lua_tostring(l, 2), save);

	if(save && b) mcons[id]->luaRS(l);
	else lua_pushboolean(l, b);
	return 1;
}

int apiMysql::inserted(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 1, "i")) return apiLuaParams::lError(l, "Invalid params for mysql_last_insert");
	size_t id = (size_t)lua_tointeger(l, 1);
	if(id < 0 || id >= mcons.size()) return apiLuaParams::lError(l, "Invalid handle for mysql_last_insert");
	lua_pushinteger(l, mcons[id]->InsertID());
	return 1;
}

int apiMysql::affected(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 1, "i")) return apiLuaParams::lError(l, "Invalid params for mysql_affected_rows");
	size_t id = (size_t)lua_tointeger(l, 1);
	if(id < 0 || id >= mcons.size()) return apiLuaParams::lError(l, "Invalid handle for mysql_affected_rows");
	lua_pushinteger(l, mcons[id]->AffectedRows());
	return 1;
}

int apiMysql::rollback(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 1, "i")) return apiLuaParams::lError(l, "Invalid params for mysql_rollback");
	size_t id = (size_t)lua_tointeger(l, 1);
	if(id < 0 || id >= mcons.size()) return apiLuaParams::lError(l, "Invalid handle for mysql_rollback");
	mcons[id]->rollback();
	return 0;
}

int apiMysql::commit(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 1, "i")) return apiLuaParams::lError(l, "Invalid params for mysql_commit");
	size_t id = (size_t)lua_tointeger(l, 1);
	if(id < 0 || id >= mcons.size()) return apiLuaParams::lError(l, "Invalid handle for mysql_commit");
	mcons[id]->commit();
	return 0;
}

int apiMysql::error(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 1, "i")) return apiLuaParams::lError(l, "Invalid params for mysql_commit");
	size_t id = (size_t)lua_tointeger(l, 1);
	if(id < 0 || id >= mcons.size()) return apiLuaParams::lError(l, "Invalid handle for mysql_commit");
	lua_pushinteger(l, mcons[id]->Errno());
	lua_pushstring(l, mcons[id]->Error());
	return 2;
}
#endif

void apiMysql::push()
{
#if linux
#else
	apiLua::addFunc(apiLua::LuaFuncStruct(define, "mysql_new", "ssssib", "i"));
	apiLua::addFunc(apiLua::LuaFuncStruct(connect, "mysql_connect", "i", "b"));
	apiLua::addFunc(apiLua::LuaFuncStruct(disconnect, "mysql_disconnect", "i", ""));
	apiLua::addFunc(apiLua::LuaFuncStruct(query, "mysql_query", "isb", "t"));
	apiLua::addFunc(apiLua::LuaFuncStruct(inserted, "mysql_insert_id", "i", "i"));
	apiLua::addFunc(apiLua::LuaFuncStruct(affected, "mysql_affected_rows", "i", "i"));
	apiLua::addFunc(apiLua::LuaFuncStruct(rollback, "mysql_rollback", "i", ""));
	apiLua::addFunc(apiLua::LuaFuncStruct(commit, "mysql_commit", "i", ""));
	apiLua::addFunc(apiLua::LuaFuncStruct(error, "mysql_error", "i", "is"));
#endif
}