#include "stdafx.h"
#include "playerFunctions.h"
#include "apiLuaParams.h"
#include "apiCheckPoints.h"
#include "apiLua.h"

#define isValidCp(luaVm) if(!apiCheckPoint::isValid((int)lua_tointeger(l, 1))) {lua_pushnil(luaVm); return 1;}

int cp_addNew(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 8, "ddddiiii")) return apiLuaParams::lError(l, "Invalid createCheckPoint params");
	lua_pushinteger(l, apiCheckPoint::addNew(
		apiMath::Vector3((float)lua_tonumber(l, 1), (float)lua_tonumber(l, 2), (float)lua_tonumber(l, 3)),
		(float)lua_tonumber(l, 4), (unsigned int)lua_tointeger(l, 5), (int)lua_tointeger(l, 6), (int)lua_tointeger(l, 7),
		(unsigned int)lua_tointeger(l, 8)));
	return 1;
}

int cp_remove(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 1, "i")) return apiLuaParams::lError(l, "Invalid deleteCheckPoint params");
	isValidCp(l);
	apiCheckPoint::remove((int)lua_tointeger(l, 1));
	return 0;
}

int cp_isValid(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 1, "i")) return apiLuaParams::lError(l, "Invalid isValidCheckPoint params");
	lua_pushboolean(l, apiCheckPoint::isValid((int)lua_tointeger(l, 1)));
	return 1;
}

int cp_setBlipTypeForPlayer(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 3, "iii")) return apiLuaParams::lError(l, "Invalid setCheckPointBlipForPlayer params");
	isValidCp(l);
	apiCheckPoint::setBlipTypeForPlayer((int)lua_tointeger(l, 1), (int)lua_tointeger(l, 2), (int)lua_tointeger(l, 3));
	return 0;
}

int cp_setShowingForPlayer(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 3, "iib")) return apiLuaParams::lError(l, "Invalid setCheckPointShowingForPlayer params");
	isValidCp(l);
	apiCheckPoint::setShowingForPlayer((int)lua_tointeger(l, 1), (int)lua_tointeger(l, 2), (int)lua_toboolean(l, 3));
	return 0;
}

void playerFuncs::loadCps(lua_State* l)
{
	apiLua::addFunc(apiLua::LuaFuncStruct(cp_addNew, "createCheckPoint", "ddddiiii", "i"));
	apiLua::addFunc(apiLua::LuaFuncStruct(cp_remove, "deleteCheckPoint", "i", ""));
	apiLua::addFunc(apiLua::LuaFuncStruct(cp_isValid, "isValidCheckPoint", "i", "b"));
	apiLua::addFunc(apiLua::LuaFuncStruct(cp_setBlipTypeForPlayer, "setCheckPointBlipForPlayer", "iii", ""));
	apiLua::addFunc(apiLua::LuaFuncStruct(cp_setShowingForPlayer, "setCheckPointShowingForPlayer", "iib", ""));
}