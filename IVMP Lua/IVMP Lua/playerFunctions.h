#include <lua.hpp>

namespace playerFuncs
{
	void load(lua_State* l);
	void loadVehicle(lua_State* l);
	void loadCps(lua_State* l);
	void loadObjs(lua_State* l);
	void loadBlips(lua_State* l);
	void loadWorld(lua_State* l);
	void loadDialog(lua_State* l);
	void loadSha(lua_State* l);
	void loadNpcs(lua_State* l);
}