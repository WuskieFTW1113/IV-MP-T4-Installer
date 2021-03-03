#include <lua.hpp>

namespace apiMysql
{
	int define(lua_State* l);
	int connect(lua_State* l);
	int disconnect(lua_State* l);

	int query(lua_State* l);
	int inserted(lua_State* l);
	int affected(lua_State* l);
	int rollback(lua_State* l);
	int commit(lua_State* l);
	int error(lua_State* l);

	void push();
}