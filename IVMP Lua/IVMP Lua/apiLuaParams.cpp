#include "stdafx.h"
#include "apiLuaParams.h"
#include <iostream>
#include "easylogging++.h"

bool apiLuaParams::paramCheck(lua_State* l, int params, const char* paramTypes)
{
	int args = lua_gettop(l);
	if(args != params) return false;

	int t = -1;
	for(int i = 1; i <= args; i++)
	{
		char buf[2] = {paramTypes[i - 1]};
		t = lua_type(l, i);
		if(t == LUA_TSTRING && buf[0] != 's') return false;
		else if(t == LUA_TBOOLEAN && buf[0] != 'b') return false;
		if(t == LUA_TNUMBER)
		{
			double n = lua_tonumber(l, i);
			if(buf[0] != 'd' && buf[0] == 'i' && n != (long long)n) return false;
		}
	}
	return true;
}

int apiLuaParams::lError(lua_State* l, const char* s)
{
	//LINFO << "API Error: " << s;
	std::cout << s << std::endl;
	mlog(s);
	lua_pushnil(l);
	return 1;
}