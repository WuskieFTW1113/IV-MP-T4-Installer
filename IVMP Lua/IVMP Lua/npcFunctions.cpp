#include "stdafx.h"
#include "playerFunctions.h"
#include "apiLuaParams.h"
#include "apiLua.h"
#include "apiNpc.h"
#include "playerList.h"

int npc_create(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 9, "sifffisif")) return apiLuaParams::lError(l, "Invalid npcCreate params");
	apiMath::Vector3 v((float)lua_tonumber(l, 3), (float)lua_tonumber(l, 4), (float)lua_tonumber(l, 5));
	lua_pushinteger(l, apiNpc::createNpc(lua_tostring(l, 1), playerList::getModel((int)lua_tointeger(l, 2)), 
		v, (int)lua_tointeger(l, 6), lua_tostring(l, 7), (int)lua_tointeger(l, 8), (float)lua_tonumber(l, 9)));

	return 1;
}

int npc_delete(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 1, "i")) return apiLuaParams::lError(l, "Invalid npcDelete params");
	apiNpc::deleteNpc((int)lua_tointeger(l, 1));
	return 0;
}

int npc_clearTasks(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 1, "i")) return apiLuaParams::lError(l, "Invalid npcClearTasks params");
	apiNpc::clearNpcTaks((int)lua_tointeger(l, 1));
	return 0;
}

int npc_hasTasks(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 1, "i")) return apiLuaParams::lError(l, "Invalid npcHasTasks params");
	lua_pushboolean(l, apiNpc::tasksPlaying((int)lua_tointeger(l, 1)));
	return 1;
}

int npc_playTasks(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 2, "ib")) return apiLuaParams::lError(l, "Invalid npcPlayTasks params");
	apiNpc::playTasks((int)lua_tointeger(l, 1), lua_toboolean(l, 2));
	return 0;
}

int npc_addVehicleTask(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 15, "iifffffffffiffi")) return apiLuaParams::lError(l, "Invalid npcAddVehicleTask params");
	apiMath::Vector3 pos((float)lua_tonumber(l, 3), (float)lua_tonumber(l, 4), (float)lua_tonumber(l, 5));
	apiMath::Vector3 rot((float)lua_tonumber(l, 6), (float)lua_tonumber(l, 7), (float)lua_tonumber(l, 8));
	apiMath::Vector3 vel((float)lua_tonumber(l, 9), (float)lua_tonumber(l, 10), (float)lua_tonumber(l, 11));
	apiNpc::addVehicleTask((int)lua_tointeger(l, 1), (int)lua_tointeger(l, 2), pos, rot, vel, (int)lua_tointeger(l, 12),
		(float)lua_tonumber(l, 13), (float)lua_tonumber(l, 14), (int)lua_tointeger(l, 15));
	return 0;
}

int npc_addFootTask(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 11, "ifffffffiii")) return apiLuaParams::lError(l, "Invalid npcAddFootTask params");
	apiMath::Vector3 pos((float)lua_tonumber(l, 2), (float)lua_tonumber(l, 3), (float)lua_tonumber(l, 4));
	apiMath::Vector3 aim((float)lua_tonumber(l, 5), (float)lua_tonumber(l, 6), (float)lua_tonumber(l, 7));

	apiNpc::addFootTask((int)lua_tointeger(l, 1), pos, aim, (float)lua_tonumber(l, 8), (int)lua_tointeger(l, 9),
		(int)lua_tointeger(l, 10), (int)lua_tointeger(l, 11));

	return 0;
}

int npc_exists(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 1, "i")) return apiLuaParams::lError(l, "Invalid isValidNpc params");
	int i = (int)lua_tointeger(l, 1);
	lua_pushboolean(l, apiNpc::isValid(i));
	return 1;
}

int npc_setClothes(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 3, "iii")) return apiLuaParams::lError(l, "Invalid npcSetClothes params");
	int part = (int)lua_tointeger(l, 2);
	if(part < 0 || part > 8) return apiLuaParams::lError(l, "NPC clothes part must be 0-8");
	apiNpc::setClothes((int)lua_tointeger(l, 1), part, (int)lua_tointeger(l, 3));

	return 0;
}

int npc_setProperty(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 3, "iii")) return apiLuaParams::lError(l, "Invalid npcSetProperty params");
	int part = (int)lua_tointeger(l, 2);
	if(part < 0 || part > 1) return apiLuaParams::lError(l, "NPC property part must be 0-1");
	apiNpc::setProperty((int)lua_tointeger(l, 1), part, (int)lua_tointeger(l, 3));

	return 0;
}

void playerFuncs::loadNpcs(lua_State* l)
{
	apiLua::addFunc(apiLua::LuaFuncStruct(npc_create, "npcCreate", "siffisif", "i"));
	apiLua::addFunc(apiLua::LuaFuncStruct(npc_delete, "npcDelete", "i", ""));
	apiLua::addFunc(apiLua::LuaFuncStruct(npc_clearTasks, "npcClearTasks", "i", ""));
	apiLua::addFunc(apiLua::LuaFuncStruct(npc_hasTasks, "npcHasTasks", "i", "b"));
	apiLua::addFunc(apiLua::LuaFuncStruct(npc_playTasks, "npcPlayTasks", "ib", ""));
	apiLua::addFunc(apiLua::LuaFuncStruct(npc_addVehicleTask, "npcAddVehicleTask", "iifffffffffiffi", ""));
	apiLua::addFunc(apiLua::LuaFuncStruct(npc_addFootTask, "npcAddFootTask", "ifffffffiii", ""));
	apiLua::addFunc(apiLua::LuaFuncStruct(npc_exists, " isValidNpc", "i", "b"));
	apiLua::addFunc(apiLua::LuaFuncStruct(npc_setClothes, "npcSetClothes", "iii", ""));
	apiLua::addFunc(apiLua::LuaFuncStruct(npc_setProperty, "npcSetProperty", "iii", ""));
}