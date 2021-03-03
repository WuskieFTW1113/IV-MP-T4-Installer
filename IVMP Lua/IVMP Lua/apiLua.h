#include <lua.hpp>
#include <string>
#include <vector>

namespace apiLua
{
	void createVm();
	lua_State* getVm();
	void pulseVm(long cTime);

	int setTimer(lua_State* state);

	int registerEvent(lua_State* state);
	int unregisterEvent(lua_State* state);
	void deleteEvent(std::string functionName);
	lua_State* getEventFunctions(std::string eventName, size_t& size, std::vector<std::string>& buf);

	typedef int(*LuaFunc)(lua_State* l);
	struct LuaFuncStruct
	{
		LuaFunc f;
		std::string name;
		std::string params;
		std::string returns;

		LuaFuncStruct(){}
		LuaFuncStruct(LuaFunc func, std::string fName, std::string fParams, std::string fReturns)
		{
			f = func;
			name = fName;
			params = fParams;
			returns = fReturns;
		}
	};
	void addFunc(LuaFuncStruct f);
}