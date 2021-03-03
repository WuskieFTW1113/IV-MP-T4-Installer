#include <exporting.h>
#include "stdafx.h"
#include "apiLua.h"
#include "apiLuaParams.h"
#include "playerFunctions.h"
#include <map>
#include <iostream>
#include <time.h>
#include "apiMysql.h"
#include "easylogging++.h"
//#include <fstream>

#if linux
//-pthread to Linker Command and add "dl" to additional libs
#include <dlfcn.h>
#endif

lua_State* state;

std::map<std::string, std::string> events; //LUA function name, event name

struct luaArgs
{
	int luaType;
	
	double lDouble;
	long long lInt;
	std::string lString;
	bool lBool;
};

struct luaTimer
{
	std::string functionName;
	clock_t interval;
	unsigned int repetitions;

	clock_t lastCall;
	unsigned int iterations;

	std::vector<luaArgs> args;

	luaTimer(){}
	~luaTimer(){}
	luaTimer(std::string functionName, clock_t interval, unsigned int repetitions)
	{
		this->functionName = functionName;
		this->interval = interval;
		this->repetitions = repetitions;

		this->iterations = 0;
		this->lastCall = clock();
	}
};

std::vector<luaTimer> timers;
std::vector<apiLua::LuaFuncStruct> funcs;

void apiLua::addFunc(LuaFuncStruct f)
{
	funcs.push_back(f);
}

std::string errorBuf;
static int l_my_print(lua_State* L)
{
	int nargs = lua_gettop(L);
	for(int i = 1; i <= nargs; ++i) {
		errorBuf.append(lua_tostring(L, i));
	}
	mlog(errorBuf.c_str());
	std::cout << errorBuf << std::endl;
	errorBuf.clear();
	return 0;
}

static int l_my_log(lua_State* L)
{
	int nargs = lua_gettop(L);
	for(int i = 1; i <= nargs; ++i) {
		errorBuf.append(lua_tostring(L, i));
	}
	mlog(errorBuf.c_str());
	errorBuf.clear();
	return 0;
}

static const struct luaL_Reg printlib[] = {
	{"print", l_my_print},
	{"log", l_my_log},
{NULL, NULL} /* end of array */
};

void lua_print_error(lua_State* state)
{
	mlog(lua_tostring(state, -1));
	std::cout << lua_tostring(state, -1) << std::endl;
	lua_pop(state, 1);
}

int apiLua::setTimer(lua_State* l)
{
	int top = lua_gettop(l);
	if(top < 3) return apiLuaParams::lError(l, "setTimer must have atleast 3 arguments");

	if(!lua_isstring(l, 1)) return apiLuaParams::lError(l, "Invalid function name at setTimer");
	if(!lua_isnumber(l, 2)) return apiLuaParams::lError(l, "Invalid interval at setTimer");
	if(!lua_isnumber(l, 3)) return apiLuaParams::lError(l, "Invalid repetitions at setTimer");

	luaTimer t(lua_tostring(l, 1), (clock_t)lua_tointeger(l, 2), (unsigned int)lua_tointeger(l, 3));
	int lt = -1;
	for(int i = 4; i <= top; i++)
	{
		//lt = lua_type(l, i);
		luaArgs arg;
		arg.luaType = lua_type(l, i);
		bool push = true;

		if(arg.luaType == LUA_TSTRING) arg.lString = lua_tostring(l, i);
		else if(arg.luaType == LUA_TBOOLEAN) arg.lBool = lua_toboolean(l, i);
		else if(arg.luaType == LUA_TNUMBER)
		{
			double n = lua_tonumber(l, i);
			if(n == (long long)n)
			{
				arg.luaType = LUA_TINTEGER;
				arg.lInt = lua_tointeger(l, i);
			}
			else
			{
				arg.lDouble = lua_tonumber(l, i);
			}
		}
		else
		{
			push = false;
		}

		if(push) t.args.push_back(arg);
	}

	timers.push_back(t);
	lua_pushinteger(l, timers.size() - 1);
	return 1;
}

int deleteTimer(lua_State* l)
{
	if(!apiLuaParams::paramCheck(state, 1, "i")) return apiLuaParams::lError(state, "Invalid deleteTimer params");
	int id = (int)lua_tointeger(l, 1);
	int s = (int)timers.size();
	if(id > -1 && id < s) {
		timers.erase(timers.begin() + id);
	}
	return 0;
}

int apiLua::registerEvent(lua_State* state)
{
	if(!apiLuaParams::paramCheck(state, 2, "ss")) return apiLuaParams::lError(state, "Invalid registerEvent params");
	events[lua_tostring(state, 1)] = lua_tostring(state, 2);
	lua_pushboolean(state, true);
	return 1;
}

int apiLua::unregisterEvent(lua_State* state)
{
	if(!apiLuaParams::paramCheck(state, 1, "s")) return apiLuaParams::lError(state, "Invalid removeEvent params");
	deleteEvent(lua_tostring(state, 1));
	return 0;
}

void apiLua::deleteEvent(std::string functionName)
{
	if(events.find(functionName) != events.end()) events.erase(functionName);
}

lua_State* apiLua::getEventFunctions(std::string eventName, size_t& size, std::vector<std::string>& buf)
{
	buf.clear();
	for(std::map<std::string, std::string>::iterator i = events.begin(); i != events.end(); ++i)
	{
		if(i->second == eventName)
		{
			//std::cout << "Pushing event: " << i->first << std::endl; 
			buf.push_back(i->first);
		}
	}
	size = buf.size();
	return state;
}

/*std::string typeToName(char c)
{
	if(c == 'd' || c == 'f') return "Float";
	else if(c == 'i') return "Int";
	else if(c == 'b') return "Bool";
	else if(c == 's') return "String";
	return std::string("" + c);
}*/

void apiLua::createVm()
{
	state = luaL_newstate();

#if linux
	dlopen("Test", RTLD_LAZY); //Must be here otherwise lib DL doesnt get loaded, go figure
#endif

	luaL_openlibs(state);

	lua_getglobal(state, "_G");
	luaL_setfuncs(state, printlib, 0);
	lua_pop(state, 1);

	/*lua_register(state, "registerEvent", registerEvent);
	lua_register(state, "unregisterEvent", unregisterEvent);
	lua_register(state, "setTimer", setTimer);*/

	apiLua::addFunc(apiLua::LuaFuncStruct(registerEvent, "registerEvent", "ss", "b"));
	apiLua::addFunc(apiLua::LuaFuncStruct(unregisterEvent, "unregisterEvent", "s", ""));
	apiLua::addFunc(apiLua::LuaFuncStruct(setTimer, "setTimer", "sii", "i"));
	apiLua::addFunc(apiLua::LuaFuncStruct(deleteTimer, "deleteTimer", "i", ""));

	playerFuncs::load(state);
	playerFuncs::loadVehicle(state);
	playerFuncs::loadCps(state);
	playerFuncs::loadObjs(state);
	playerFuncs::loadBlips(state);
	playerFuncs::loadWorld(state);
	playerFuncs::loadDialog(state);
	playerFuncs::loadSha(state);
	playerFuncs::loadNpcs(state);
	apiMysql::push();

	size_t funcsSize = funcs.size();
	for(size_t i = 0; i < funcsSize; i++)
	{
		lua_register(state, funcs[i].name.c_str(), funcs[i].f);
		
		/*std::ofstream myfile("WIKI/" + funcs[i].name + ".md");
		if(myfile.is_open())
		{
			myfile << "## **Description** ##" << std::endl << "..." << std::endl << std::endl;
			myfile << "## **Parameters** ##" << std::endl << "```" << std::endl;
			size_t s = funcs[i].params.size();
			for(size_t j = 0; j < s; j++)
			{	
				myfile << typeToName(funcs[i].params[j]) + std::string(" unk") + std::to_string(j);
				if(j + 1 < s) myfile << ", ";
			}
			myfile << std::endl << "```" << std::endl;
			for(size_t j = 0; j < s; j++)
			{
				myfile << typeToName(funcs[i].params[j]) + std::string(" unk") + std::to_string(j) << std::endl << std::endl;
			}
			
			myfile << std::endl << "## **Return values** ##" << std::endl << "```" << std::endl;
			s = funcs[i].returns.size();
			for(size_t j = 0; j < s; j++)
			{
				myfile << typeToName(funcs[i].returns[j]) + std::string(" unk") + std::to_string(j);
				if(j + 1 < s) myfile << ", ";
			}
			myfile << std::endl << "```" << std::endl << std::endl << "## **Example** ##";
		}*/
	}

	int result = luaL_loadfile(state, "main.lua");
	if(result != LUA_OK)
	{
		lua_print_error(state);
		return;
	}

	result = lua_pcall(state, 0, LUA_MULTRET, 0);
	if(result != LUA_OK)
	{
		lua_print_error(state);
		return;
	}
}

lua_State* apiLua::getVm()
{
	return state;
}

void apiLua::pulseVm(long cTime)
{
	try
	{
		size_t s = timers.size();
		size_t i = 0;
		while(i < s)
		{
			if(cTime >= timers[i].lastCall + timers[i].interval)
			{
				timers[i].lastCall = cTime;
				timers[i].iterations++;

				lua_getglobal(state, timers[i].functionName.c_str());
				size_t args = timers[i].args.size();
				for(size_t k = 0; k < args; k++)
				{
					if(timers[i].args[k].luaType == LUA_TSTRING) lua_pushstring(state, timers[i].args[k].lString.c_str());
					else if(timers[i].args[k].luaType == LUA_TINTEGER) lua_pushinteger(state, timers[i].args[k].lInt);
					else if(timers[i].args[k].luaType == LUA_TNUMBER) lua_pushnumber(state, timers[i].args[k].lDouble);
					else if(timers[i].args[k].luaType == LUA_TBOOLEAN) lua_pushinteger(state, timers[i].args[k].lBool);
				}
				if(lua_pcall(state, args, 0, 0) != 0)
				{
					std::string error = std::string("Timer call ") + timers[i].functionName + std::string(": ") + lua_tostring(state, -1);
					apiLuaParams::lError(state, error.c_str());
				}
				lua_pop(state, lua_gettop(state));

				if(timers[i].repetitions != 0 && timers[i].iterations >= timers[i].repetitions)
				{
					timers.erase(timers.begin() + i);
					s--;
					continue;
				}
			}
			i++;
		}
	}
	catch(std::exception& e)
	{
		std::string error = "Timer manager error: " + std::string(e.what());
		apiLuaParams::lError(state, error.c_str());
	}
}
