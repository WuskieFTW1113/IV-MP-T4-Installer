#include "stdafx.h"
#include "playerFunctions.h"
#include "apiLuaParams.h"
#include "apiDialog.h"
#include "apiLua.h"

#define isValidDialog(luaVm) if(!apiDialog::isValid((unsigned int)lua_tointeger(l, 1))) {lua_pushnil(luaVm); return 1;}

int d_create(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 5, "isiss")) return apiLuaParams::lError(l, "Invalid createDialogList params");
	int id = (int)lua_tointeger(l, 1);
	if(apiDialog::isValid(id)) return apiLuaParams::lError(l, "Dialog ID already exists");
	std::string buf = std::string(lua_tostring(l, 2));
	char *cstr = &buf[0u];
	bool b = apiDialog::addNew(id, cstr, (unsigned int)lua_tointeger(l, 3));
	if(b)
	{
		apiDialog::get(id)->setBtnNames(lua_tostring(l, 4), lua_tostring(l, 5));
		apiDialog::get(id)->save();
	}
	lua_pushboolean(l, b);
	return 1;
}

int d_empty(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 1, "i")) return apiLuaParams::lError(l, "Invalid clearDialogRows params");
	isValidDialog(l);
	int id = (int)lua_tointeger(l, 1);
	apiDialog::get(id)->clearRows();
	apiDialog::get(id)->save();
	return 0;
}

int d_add(lua_State* l)
{
	int args = lua_gettop(l);
	if(args < 2) return apiLuaParams::lError(l, "Invalid addDialogRow params count");
	if(!lua_isinteger(l, 1) || !lua_isstring(l, 2)) return apiLuaParams::lError(l, "Invalid addDialogRow params");
	//if(!apiLuaParams::paramCheck(l, 2, "is")) return apiLuaParams::lError(l, "Invalid addDialogRow params");
	isValidDialog(l);
	int id = (int)lua_tointeger(l, 1);
	int customId = args == 3 && lua_isinteger(l, 3) ? (int)lua_tointeger(l, 3) : -1;
	apiDialog::get(id)->addRow(lua_tostring(l, 2), customId);
	apiDialog::get(id)->save();
	return 0;
}

int d_header(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 2, "is")) return apiLuaParams::lError(l, "Invalid setDialogListHeaders params");
	isValidDialog(l);
	int id = (int)lua_tointeger(l, 1);
	apiDialog::get(id)->setColumnsHeaders(lua_tostring(l, 2));
	apiDialog::get(id)->save();
	return 0;
}

int d_delete(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 1, "i")) return apiLuaParams::lError(l, "Invalid deleteDialogList params");
	isValidDialog(l);
	apiDialog::remove((int)lua_tointeger(l, 1));
	return 0;
}

void playerFuncs::loadDialog(lua_State* l)
{
	apiLua::addFunc(apiLua::LuaFuncStruct(d_create, "createDialogList", "isiss", "b"));
	apiLua::addFunc(apiLua::LuaFuncStruct(d_delete, "deleteDialogList", "i", ""));
	apiLua::addFunc(apiLua::LuaFuncStruct(d_empty, "clearDialogRows", "i", ""));
	apiLua::addFunc(apiLua::LuaFuncStruct(d_add, "addDialogRow", "is", ""));
	apiLua::addFunc(apiLua::LuaFuncStruct(d_header, "setDialogListHeaders", "is", ""));
}