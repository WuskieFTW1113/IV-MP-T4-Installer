#include "stdafx.h"
#include "playerFunctions.h"
#include "apiLuaParams.h"
#include "apiBlips.h"
#include "apiLua.h"

#define isValidBlip(luaVm) if(!apiBlips::isValid((int)lua_tointeger(l, 1))) {lua_pushnil(luaVm); return 1;}

int blip_add(lua_State* l)
{
	//apiMath::Vector3 pos, int type, unsigned int color, unsigned int world, unsigned int streamDistance, bool showAll
	if(!apiLuaParams::paramCheck(l, 8, "dddiiiib") && !apiLuaParams::paramCheck(l, 9, "dddiiiibs")) {
		return apiLuaParams::lError(l, "Invalid createBlip params");
	}
	std::string name = lua_gettop(l) == 9 ? lua_tostring(l, 9) : "";
	lua_pushinteger(l, apiBlips::add(
		apiMath::Vector3((float)lua_tonumber(l, 1), (float)lua_tonumber(l, 2), (float)lua_tonumber(l, 3)),
		(int)lua_tointeger(l, 4), (unsigned int)lua_tointeger(l, 5), (unsigned int)lua_tointeger(l, 6),
		(unsigned int)lua_tointeger(l, 7), lua_toboolean(l, 8), name.c_str()));
	return 1;
}

int blip_remove(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 1, "i")) return apiLuaParams::lError(l, "Invalid deleteBlip params");
	isValidBlip(l);
	apiBlips::remove((int)lua_tointeger(l, 1));
	return 0;
}

int blip_setName(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 2, "is")) return apiLuaParams::lError(l, "Invalid setBlipName params");
	isValidBlip(l);
	apiBlips::setName((int)lua_tointeger(l, 1), lua_tostring(l, 2));
	return 0;
}

void playerFuncs::loadObjs(lua_State* l)
{
	apiLua::addFunc(apiLua::LuaFuncStruct(blip_add, "createBlip", "dddiiiib", "i"));
	apiLua::addFunc(apiLua::LuaFuncStruct(blip_remove, "deleteBlip", "i", ""));
	apiLua::addFunc(apiLua::LuaFuncStruct(blip_setName, "setBlipName", "is", ""));
}