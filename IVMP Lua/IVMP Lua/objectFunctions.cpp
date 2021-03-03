#include "stdafx.h"
#include "playerFunctions.h"
#include "apiLuaParams.h"
#include "apiObjects.h"
#include "apiLua.h"

#define isValidObject(luaVm) if(!apiObjects::isValid((int)lua_tointeger(l, 1))) {lua_pushnil(luaVm); return 1;}

int obj_addNew(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 12, "dddddddiibii")) return apiLuaParams::lError(l, "Invalid createObject params");
	lua_pushinteger(l, apiObjects::addNew(
		apiMath::Vector3((float)lua_tonumber(l, 1), (float)lua_tonumber(l, 2), (float)lua_tonumber(l, 3)),
		apiMath::Quaternion((float)lua_tonumber(l, 4), (float)lua_tonumber(l, 5), (float)lua_tonumber(l, 6), (float)lua_tonumber(l, 7)),
		(unsigned int)lua_tointeger(l, 8), (unsigned int)lua_tointeger(l, 9), lua_toboolean(l, 10), (unsigned int)lua_tointeger(l, 11),
		(int)lua_tointeger(l, 12)));
	return 1;
}

int obj_remove(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 1, "i")) return apiLuaParams::lError(l, "Invalid deleteObject params");
	isValidObject(l);
	apiObjects::remove((int)lua_tointeger(l, 1));
	return 0;
}

int obj_moveObject(lua_State* l)
{
	//int id, apiMath::Vector3 pos, apiMath::Quaternion rot, unsigned int time
	if(!apiLuaParams::paramCheck(l, 9, "idddddddi")) return apiLuaParams::lError(l, "Invalid moveObject params");
	isValidObject(l);
	apiObjects::moveObject((int)lua_tointeger(l, 1),
		apiMath::Vector3((float)lua_tonumber(l, 2), (float)lua_tonumber(l, 3), (float)lua_tonumber(l, 4)),
		apiMath::Quaternion((float)lua_tonumber(l, 5), (float)lua_tonumber(l, 6), (float)lua_tonumber(l, 7), (float)lua_tonumber(l, 8)),
		(unsigned int)lua_tointeger(l, 1));
	return 0;
}

void playerFuncs::loadBlips(lua_State* l)
{
	apiLua::addFunc(apiLua::LuaFuncStruct(obj_addNew, "createObject", "dddddddiibiii", "i"));
	apiLua::addFunc(apiLua::LuaFuncStruct(obj_remove, "deleteObject", "i", ""));
	apiLua::addFunc(apiLua::LuaFuncStruct(obj_moveObject, "moveObject", "idddddddi", ""));
}