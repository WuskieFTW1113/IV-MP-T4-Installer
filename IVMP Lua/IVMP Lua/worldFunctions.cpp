#include "stdafx.h"
#include "playerFunctions.h"
#include "apiLuaParams.h"
#include "apiWorld.h"
#include "apiLua.h"
#include "apiCheckPoints.h"
#include "apiVehicle.h"
#include "apiPlayer.h"
#include "apiObjects.h"
#include "apiNpc.h"

#define isValidWorld(luaVm) if(!apiWorld::isWorld((unsigned int)lua_tointeger(l, 1))) {lua_pushnil(luaVm); return 1;}

int world_isWorld(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 1, "i")) return apiLuaParams::lError(l, "Invalid isValidWorld params");
	lua_pushboolean(l, apiWorld::isWorld((int)lua_tointeger(l, 1)));
	return 1;
}

int world_createWorld(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 5, "iiiii")) return apiLuaParams::lError(l, "Invalid createWorld params");
	int world = (unsigned int)lua_tointeger(l, 1);
	if(!apiWorld::isWorld(world))
	{
		apiWorld::createWorld(world, (unsigned int)lua_tointeger(l, 2), (unsigned int)lua_tointeger(l, 3),
			(unsigned int)lua_tointeger(l, 4), (unsigned int)lua_tointeger(l, 5));
		lua_pushboolean(l, true);
	}
	else lua_pushboolean(l, false);
	return 1;
}

int world_deleteWorld(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 1, "i")) return apiLuaParams::lError(l, "Invalid deleteWorld params");
	isValidWorld(l);
	apiWorld::deleteWorld((unsigned int)lua_tointeger(l, 1));
	return 0;
}

int world_changeWorld(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 2, "ii")) return apiLuaParams::lError(l, "Invalid setWorldWeather params");
	isValidWorld(l);
	apiWorld::virtualWorld* v = apiWorld::getWorld((unsigned int)lua_tointeger(l, 1));
	//v->setTime((unsigned int)lua_tointeger(l, 2), (unsigned int)lua_tointeger(l, 3));
	v->setWeather((unsigned int)lua_tointeger(l, 2));
	v->streamWorldChanges();
	return 0;
}

int world_changeTime(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 3, "iii")) return apiLuaParams::lError(l, "Invalid setWorldTime params");
	isValidWorld(l);
	apiWorld::virtualWorld* v = apiWorld::getWorld((unsigned int)lua_tointeger(l, 1));
	v->setTime((unsigned int)lua_tointeger(l, 2), (unsigned int)lua_tointeger(l, 3));
	v->streamWorldChanges();
	return 0;
}

int world_minDur(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 2, "ii")) return apiLuaParams::lError(l, "Invalid setWorldMinuteDuration");
	isValidWorld(l);
	apiWorld::virtualWorld* v = apiWorld::getWorld((unsigned int)lua_tointeger(l, 1));
	v->setMinuteDuration((unsigned int)lua_tointeger(l, 2));
	return 0;
}


int world_entityStream(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 3, "iif")) return apiLuaParams::lError(l, "Invalid setEntityStreamDistance");
	int type = (int)lua_tointeger(l, 1), entity = (int)lua_tointeger(l, 2);
	float dis = (float)lua_tonumber(l, 3);

	if(type == 0 )
	{
		if(apiPlayer::isOn(entity)) apiPlayer::get(entity).setStreamDistance(dis);
	}
	else if(type == 1)
	{
		if(apiVehicle::isVehicle(entity)) apiVehicle::getVehicle(entity).setStreamDistance(dis);
	}
	else if(type == 2)
	{
		if(apiCheckPoint::isValid(entity)) apiCheckPoint::get(entity)->setStream(dis);
	}
	else if(type == 3)
	{
		if(apiObjects::isValid(entity)) apiObjects::get(entity)->setStreamDis(dis);
	}
	else if(type == 4)
	{
		if(apiNpc::isValid(entity)) apiNpc::setStreamDis(entity, dis);
	}
	return 0;
}

void playerFuncs::loadWorld(lua_State* l)
{
	apiLua::addFunc(apiLua::LuaFuncStruct(world_isWorld, "isValidWorld", "i", "b"));
	apiLua::addFunc(apiLua::LuaFuncStruct(world_createWorld, "createWorld", "iiiii", "b"));
	apiLua::addFunc(apiLua::LuaFuncStruct(world_deleteWorld, "deleteWorld", "i", ""));
	apiLua::addFunc(apiLua::LuaFuncStruct(world_changeWorld, "setWorldWeather", "ii", ""));
	apiLua::addFunc(apiLua::LuaFuncStruct(world_changeTime, "setWorldTime", "iii", ""));
	apiLua::addFunc(apiLua::LuaFuncStruct(world_minDur, "setWorldMinuteDuration", "ii", ""));
	apiLua::addFunc(apiLua::LuaFuncStruct(world_entityStream, "setEntityStreamDistance", "iif", ""));
}