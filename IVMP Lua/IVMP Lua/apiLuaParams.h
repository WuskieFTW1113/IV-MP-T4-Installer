#include <lua.hpp>

namespace apiLuaParams
{
	bool paramCheck(lua_State* l, int params, const char* paramTypes);
	int lError(lua_State* l, const char* s);
}