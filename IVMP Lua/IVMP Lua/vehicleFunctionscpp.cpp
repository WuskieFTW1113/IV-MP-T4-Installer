#include "stdafx.h"
#include "playerFunctions.h"
#include "apiLuaParams.h"
#include "apiVehicle.h"
#include "vehicleList.h"
#include "apiLua.h"

#define isValidVehicle(luaVm) if(!apiVehicle::isVehicle((int)lua_tointeger(l, 1))) {lua_pushnil(luaVm); return 1;}

int addVehicle(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 12, "iddddddiiiii")) return apiLuaParams::lError(l, "Invalid createVehicle params");
	int vModel = (int)lua_tointeger(l, 1);
	if(!vehicleList::isValidModel(vModel)) return apiLuaParams::lError(l, "Invalid vehicle model at createVehicle");
	lua_pushinteger(l, apiVehicle::addVehicle(vModel,
		apiMath::Vector3((float)lua_tonumber(l, 2), (float)lua_tonumber(l, 3), (float)lua_tonumber(l, 4)),
		apiMath::Vector3((float)lua_tonumber(l, 5), (float)lua_tonumber(l, 6), (float)lua_tonumber(l, 7)),
		(int)lua_tointeger(l, 8), (int)lua_tointeger(l, 9), (int)lua_tointeger(l, 10), (int)lua_tointeger(l, 11),
		(int)lua_tointeger(l, 12)));
	return 1;
}

int deleteVehicle(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 1, "i")) return apiLuaParams::lError(l, "Invalid deleteVehicle params");
	isValidVehicle(l);
	apiVehicle::deleteVehicle((int)lua_tointeger(l, 1));
	return 0;
}

int isVehicle(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 1, "i")) return apiLuaParams::lError(l, "Invalid isVehicle params");
	lua_pushboolean(l, apiVehicle::isVehicle((int)lua_tointeger(l, 1)));
	return 1;
}

int vgetPosition(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 1, "i")) return apiLuaParams::lError(l, "Invalid getVehiclePos params");
	isValidVehicle(l);
	apiMath::Vector3 v = apiVehicle::getVehicle((int)lua_tointeger(l, 1)).getPosition();
	lua_pushnumber(l, v.x);
	lua_pushnumber(l, v.y);
	lua_pushnumber(l, v.z);
	return 3;
}

int getVelocity(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 1, "i")) return apiLuaParams::lError(l, "Invalid getVehicleVelocity params");
	isValidVehicle(l);
	apiMath::Vector3 v = apiVehicle::getVehicle((int)lua_tointeger(l, 1)).getVelocity();
	lua_pushnumber(l, v.x);
	lua_pushnumber(l, v.y);
	lua_pushnumber(l, v.z);
	return 3;
}

int getRotation(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 1, "i")) return apiLuaParams::lError(l, "Invalid getVehicleRotation params");
	isValidVehicle(l);
	apiMath::Vector3 v = apiVehicle::getVehicle((int)lua_tointeger(l, 1)).getRotation();
	lua_pushnumber(l, v.x);
	lua_pushnumber(l, v.y);
	lua_pushnumber(l, v.z);
	return 3;
}

int getDriver(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 1, "i")) return apiLuaParams::lError(l, "Invalid getVehicleDriver params");
	isValidVehicle(l);
	lua_pushinteger(l, apiVehicle::getVehicle((int)lua_tointeger(l, 1)).getDriver());
	return 1;
}

int setTune(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 3, "iib")) return apiLuaParams::lError(l, "Invalid setVehicleComponent params");
	isValidVehicle(l);
	int part = (int)lua_tointeger(l, 2);
	if(part < 0 || part > 9) return apiLuaParams::lError(l, "setVehicleComponent tunes are 0-9");
	apiVehicle::getVehicle((int)lua_tointeger(l, 1)).setTune(part, lua_toboolean(l, 3));
	return 0;
}

int isTuned(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 2, "ii")) return apiLuaParams::lError(l, "Invalid doesVehicleHaveComponent params");
	isValidVehicle(l);
	int part = (int)lua_tointeger(l, 2);
	if(part < 0 || part > 9) return apiLuaParams::lError(l, "doesVehicleHaveComponent tunes are 0-9");
	lua_pushboolean(l, apiVehicle::getVehicle((int)lua_tointeger(l, 1)).isTuned(part));
	return 1;
}

int vsetColor(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 5, "iiiii")) return apiLuaParams::lError(l, "Invalid setVehicleColors params");
	isValidVehicle(l);
	apiVehicle::getVehicle((int)lua_tointeger(l, 1)).setColor((int)lua_tointeger(l, 2), (int)lua_tointeger(l, 3),
		(int)lua_tointeger(l, 4), (int)lua_tointeger(l, 5));
	return 0;
}

int vgetColor(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 1, "i")) return apiLuaParams::lError(l, "Invalid getVehicleColors params");
	isValidVehicle(l);
	apiVehicle::vehicle& v = apiVehicle::getVehicle((int)lua_tointeger(l, 1));
	for(unsigned int i = 0; i < 4; i++)
	{
		lua_pushinteger(l, v.getColor(i));
	}
	return 4;
}

int setIndicator(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 3, "iib")) return apiLuaParams::lError(l, "Invalid setVehicleIndicator params");
	isValidVehicle(l);
	int part = (int)lua_tointeger(l, 2);
	if(part < 0 || part > 1) return apiLuaParams::lError(l, "setVehicleIndicator ids are 0-1");
	apiVehicle::getVehicle((int)lua_tointeger(l, 1)).setIndicator(part, lua_toboolean(l, 3));
	return 0;
}

int getIndicator(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 2, "ii")) return apiLuaParams::lError(l, "Invalid getVehicleIndicator params");
	isValidVehicle(l);
	int part = (int)lua_tointeger(l, 2);
	if(part < 0 || part > 1) return apiLuaParams::lError(l, "getVehicleIndicator tunes are 0-9");
	lua_pushboolean(l, apiVehicle::getVehicle((int)lua_tointeger(l, 1)).getIndicator(part));
	return 1;
}

int vsetPosition(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 4, "iddd")) return apiLuaParams::lError(l, "Invalid setVehiclePos params");
	isValidVehicle(l);
	apiMath::Vector3 v(apiMath::Vector3((float)lua_tonumber(l, 2), (float)lua_tonumber(l, 3), (float)lua_tonumber(l, 4)));
	apiVehicle::getVehicle((int)lua_tointeger(l, 1)).setPosition(v);
	return 0;
}

int setRotation(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 4, "iddd")) return apiLuaParams::lError(l, "Invalid setVehicleRotation params");
	isValidVehicle(l);
	apiMath::Vector3 v(apiMath::Vector3((float)lua_tonumber(l, 2), (float)lua_tonumber(l, 3), (float)lua_tonumber(l, 4)));
	apiVehicle::getVehicle((int)lua_tointeger(l, 1)).setRotation(v);
	return 0;
}

int setVelocity(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 4, "iddd")) return apiLuaParams::lError(l, "Invalid setVehicleVelocity params");
	isValidVehicle(l);
	apiMath::Vector3 v(apiMath::Vector3((float)lua_tonumber(l, 2), (float)lua_tonumber(l, 3), (float)lua_tonumber(l, 4)));
	apiVehicle::getVehicle((int)lua_tointeger(l, 1)).setVelocity(v);
	return 0;
}

int setLivery(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 2, "ii")) return apiLuaParams::lError(l, "Invalid setVehicleLivery params");
	isValidVehicle(l);
	apiVehicle::getVehicle((int)lua_tointeger(l, 1)).setLivery((int)lua_tointeger(l, 2));
	return 0;
}

int setDirtLevel(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 2, "id")) return apiLuaParams::lError(l, "Invalid setVehicleDirtLevel params");
	isValidVehicle(l);
	apiVehicle::getVehicle((int)lua_tointeger(l, 1)).setDirtLevel((float)lua_tonumber(l, 2));
	return 0;
}

int getEngineHealth(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 1, "i")) return apiLuaParams::lError(l, "Invalid getVehicleEngineHp params");
	isValidVehicle(l);
	lua_pushinteger(l, apiVehicle::getVehicle((int)lua_tointeger(l, 1)).getEngineHealth());
	return 1;
}

int setEngineHealth(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 3, "iib")) return apiLuaParams::lError(l, "Invalid setVehicleEngineHp params");
	isValidVehicle(l);
	apiVehicle::getVehicle((int)lua_tointeger(l, 1)).setEngineHealth((int)lua_tointeger(l, 2), lua_toboolean(l, 3));
	return 0;
}

int getTire(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 2, "ii")) return apiLuaParams::lError(l, "Invalid getVehicleTireStatus params");
	isValidVehicle(l);
	int part = (int)lua_tointeger(l, 2);
	if(part < 0 || part > 5) return apiLuaParams::lError(l, "getVehicleTireStatus ids are 0-5");
	lua_pushboolean(l, apiVehicle::getVehicle((int)lua_tointeger(l, 1)).getTire(part));
	return 1;
}

int setTire(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 3, "iib")) return apiLuaParams::lError(l, "Invalid setVehicleTireStatus params");
	isValidVehicle(l);
	int part = (int)lua_tointeger(l, 2);
	if(part < 0 || part > 5) return apiLuaParams::lError(l, "setVehicleTireStatus ids are 0-5");
	apiVehicle::getVehicle((int)lua_tointeger(l, 1)).setTire(part, lua_toboolean(l, 3));
	return 0;
}

int getGasPedal(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 1, "i")) return apiLuaParams::lError(l, "Invalid getVehicleGasPedal params");
	isValidVehicle(l);
	lua_pushnumber(l, apiVehicle::getVehicle((int)lua_tointeger(l, 1)).getGasPedal());
	return 1;
}

int setEngineFlags(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 2, "ii")) return apiLuaParams::lError(l, "Invalid setVehicleEngineFlags params");
	isValidVehicle(l);
	apiVehicle::getVehicle((int)lua_tointeger(l, 1)).setEngineFlags((int)lua_tointeger(l, 2));
	return 0;
}

int getEngineFlags(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 1, "i")) return apiLuaParams::lError(l, "Invalid getVehicleEngineFlags parms");
	isValidVehicle(l);
	lua_pushinteger(l, apiVehicle::getVehicle((int)lua_tointeger(l, 1)).getEngineFlags());
	return 1;
}

int getVehicleId(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 1, "s")) return apiLuaParams::lError(l, "Invalid getVehicleModelId parms");
	lua_pushinteger(l, vehicleList::getIdByName(lua_tostring(l, 1)));
	return 1;
}

int setVehicleHood(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 2, "ib")) return apiLuaParams::lError(l, "Invalid setVehicleHood parms");
	isValidVehicle(l);
	apiVehicle::getVehicle((int)lua_tointeger(l, 1)).setTrunkHood(false, (int)lua_toboolean(l, 2));
	return 0;
}

int setVehicleTrunk(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 2, "ib")) return apiLuaParams::lError(l, "Invalid setVehicleTrunk parms");
	isValidVehicle(l);
	apiVehicle::getVehicle((int)lua_tointeger(l, 1)).setTrunkHood(true, (int)lua_toboolean(l, 2));
	return 0;
}

int getVehicleHood(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 1, "i")) return apiLuaParams::lError(l, "Invalid getVehicleHood parms");
	isValidVehicle(l);
	lua_pushboolean(l, apiVehicle::getVehicle((int)lua_tointeger(l, 1)).getTrunkHood(false));
	return 1;
}

int getVehicleTrunk(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 1, "i")) return apiLuaParams::lError(l, "Invalid getVehicleTrunk parms");
	isValidVehicle(l);
	lua_pushboolean(l, apiVehicle::getVehicle((int)lua_tointeger(l, 1)).getTrunkHood(true));
	return 1;
}

int getVehicleBreakOrGas(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 1, "i")) return apiLuaParams::lError(l, "Invalid getVehicleAnim parms");
	isValidVehicle(l);
	lua_pushinteger(l, apiVehicle::getVehicle((int)lua_tointeger(l, 1)).getBreakOrGas());
	return 1;
}

int getVehicleSteer(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 1, "i")) return apiLuaParams::lError(l, "Invalid getVehicleSteer parms");
	isValidVehicle(l);
	lua_pushnumber(l, apiVehicle::getVehicle((int)lua_tointeger(l, 1)).getSteering());
	return 1;
}

int getVehicleGasPedal(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 1, "i")) return apiLuaParams::lError(l, "Invalid getVehicleGasPedal parms");
	isValidVehicle(l);
	lua_pushnumber(l, apiVehicle::getVehicle((int)lua_tointeger(l, 1)).getGasPedal());
	return 1;
}

int getVehicleTurnVelocity(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 1, "i")) return apiLuaParams::lError(l, "InvalidgetVehicleTurnVelocity parms");
	isValidVehicle(l);
	apiMath::Vector3 v = apiVehicle::getVehicle((int)lua_tointeger(l, 1)).getTurnVelocity();
	lua_pushnumber(l, v.x);
	lua_pushnumber(l, v.y);
	lua_pushnumber(l, v.z);
	return 3;
}

void playerFuncs::loadVehicle(lua_State* l)
{
	apiLua::addFunc(apiLua::LuaFuncStruct(addVehicle, "createVehicle", "iddddddiiiii", "i"));
	apiLua::addFunc(apiLua::LuaFuncStruct(deleteVehicle, "deleteVehicle", "i", ""));
	apiLua::addFunc(apiLua::LuaFuncStruct(isVehicle, "isVehicle", "i", "b"));
	apiLua::addFunc(apiLua::LuaFuncStruct(getVehicleId, "getVehicleModelId", "s", "i"));
	apiLua::addFunc(apiLua::LuaFuncStruct(vgetPosition, "getVehiclePos", "i", "ddd"));
	apiLua::addFunc(apiLua::LuaFuncStruct(getVelocity, "getVehicleVelocity", "i", "ddd"));
	apiLua::addFunc(apiLua::LuaFuncStruct(getRotation, "getVehicleRotation", "i", "ddd"));
	apiLua::addFunc(apiLua::LuaFuncStruct(getDriver, "getVehicleDriver", "i", "i"));
	apiLua::addFunc(apiLua::LuaFuncStruct(setTune, "setVehicleComponent", "iib", ""));
	apiLua::addFunc(apiLua::LuaFuncStruct(isTuned, "doesVehicleHaveComponent", "ii", "b"));
	apiLua::addFunc(apiLua::LuaFuncStruct(vsetColor, "setVehicleColors", "iiiii", ""));
	apiLua::addFunc(apiLua::LuaFuncStruct(vgetColor, "getVehicleColors", "i", "iiii"));
	apiLua::addFunc(apiLua::LuaFuncStruct(setIndicator, "setVehicleIndicator", "iib", ""));
	apiLua::addFunc(apiLua::LuaFuncStruct(getIndicator, "getVehicleIndicator", "ii", "b"));
	apiLua::addFunc(apiLua::LuaFuncStruct(vsetPosition, "setVehiclePos", "iddd", ""));
	apiLua::addFunc(apiLua::LuaFuncStruct(setVelocity, "setVehicleVelocity", "iddd", ""));
	apiLua::addFunc(apiLua::LuaFuncStruct(setRotation, "setVehicleRotation", "iddd", ""));
	apiLua::addFunc(apiLua::LuaFuncStruct(setLivery, "setVehicleLivery", "ii", ""));
	apiLua::addFunc(apiLua::LuaFuncStruct(setDirtLevel, "setVehicleDirtLevel", "id", ""));
	apiLua::addFunc(apiLua::LuaFuncStruct(getEngineHealth, "getVehicleEngineHp", "i", "i"));
	apiLua::addFunc(apiLua::LuaFuncStruct(setEngineHealth, "setVehicleEngineHp", "iib", ""));
	apiLua::addFunc(apiLua::LuaFuncStruct(setTire, "setVehicleTireStatus", "iib", ""));
	apiLua::addFunc(apiLua::LuaFuncStruct(getTire, "getVehicleTireStatus", "ii", "b"));
	apiLua::addFunc(apiLua::LuaFuncStruct(setEngineFlags, "setVehicleEngineFlags", "ii", ""));
	apiLua::addFunc(apiLua::LuaFuncStruct(getEngineFlags, "getVehicleEngineFlags", "i", "i"));
	apiLua::addFunc(apiLua::LuaFuncStruct(setVehicleHood, "setVehicleHood", "ib", ""));
	apiLua::addFunc(apiLua::LuaFuncStruct(setVehicleTrunk, "setVehicleTrunk", "ib", ""));
	apiLua::addFunc(apiLua::LuaFuncStruct(getVehicleHood, "getVehicleHood", "i", "b"));
	apiLua::addFunc(apiLua::LuaFuncStruct(getVehicleTrunk, "getVehicleTrunk", "i", "b"));
	apiLua::addFunc(apiLua::LuaFuncStruct(getVehicleBreakOrGas, "getVehicleAnim", "i", "i"));
	apiLua::addFunc(apiLua::LuaFuncStruct(getVehicleGasPedal, "getVehicleGasPedal", "i", "f"));
	apiLua::addFunc(apiLua::LuaFuncStruct(getVehicleSteer, "getVehicleSteer", "i", "f"));
	apiLua::addFunc(apiLua::LuaFuncStruct(getVehicleTurnVelocity, "getVehicleTurnVelocity", "i", "fff"));
}