#include "stdafx.h"
#include "events.h"
#include "apiLua.h"
#include "apiLuaParams.h"
#include "apiColoredChat.h"
#include "apiPlayer.h"
#include "easylogging++.h"

std::vector<std::string> pEvents;
size_t pEventSize = 0;

bool events::onPlayerConnect(int playerid)
{
	lua_State* l = apiLua::getEventFunctions("onPlayerConnect", pEventSize, pEvents);
	if(pEventSize == 0) return true;
	bool b = true;
	for(size_t i = 0; i < pEventSize; i++)
	{
		lua_getglobal(l, pEvents[i].c_str());
		lua_pushinteger(l, playerid);
		if(lua_pcall(l, 1, 1, 0) != 0)
		{
			std::string error = "Event " + pEvents[i] + std::string(": ") + lua_tostring(l, -1);
			apiLuaParams::lError(l, error.c_str());
		}
		else if(lua_isboolean(l, -1) && lua_toboolean(l, -1) == false) b = false;
		lua_pop(l, lua_gettop(l));
	}
	return b;
}

bool events::onPlayerCredentials(int playerid)
{
	lua_State* l = apiLua::getEventFunctions("onPlayerCredential", pEventSize, pEvents);
	if(pEventSize == 0) return true;
	//bool b = true;
	for(size_t i = 0; i < pEventSize; i++)
	{
		lua_getglobal(l, pEvents[i].c_str());
		lua_pushinteger(l, playerid);
		if(lua_pcall(l, 1, 1, 0) != 0)
		{
			std::string error = "Event " + pEvents[i] + std::string(": ") + lua_tostring(l, -1);
			apiLuaParams::lError(l, error.c_str());
		}
		lua_pop(l, lua_gettop(l));
		//if(lua_isboolean(l, -1) && lua_toboolean(l, 1) == false) b = false;
	}
	return true;
}

void events::onPlayerLeft(int playerid, int reason)
{
	lua_State* l = apiLua::getEventFunctions("onPlayerLeft", pEventSize, pEvents);
	if(pEventSize == 0) return;
	for(size_t i = 0; i < pEventSize; i++)
	{
		lua_getglobal(l, pEvents[i].c_str());
		lua_pushinteger(l, playerid);
		lua_pushinteger(l, reason);
		if(lua_pcall(l, 2, 0, 0) != 0)
		{
			std::string error = "Event " + pEvents[i] + std::string(": ") + lua_tostring(l, -1);
			apiLuaParams::lError(l, error.c_str());
		}
	}
}

void events::onPlayerAfk(int playerid, bool status)
{
	lua_State* l = apiLua::getEventFunctions("onPlayerAfk", pEventSize, pEvents);
	if(pEventSize == 0) return;
	for(size_t i = 0; i < pEventSize; i++)
	{
		lua_getglobal(l, pEvents[i].c_str());
		lua_pushinteger(l, playerid);
		lua_pushboolean(l, status);
		if(lua_pcall(l, 2, 0, 0) != 0)
		{
			std::string error = "Event " + pEvents[i] + std::string(": ") + lua_tostring(l, -1);
			apiLuaParams::lError(l, error.c_str());
		}
	}
}

void events::onPlayerEnteredVehicle(int playerid, int vehicleId, int seatId)
{
	lua_State* l = apiLua::getEventFunctions("onPlayerEnteredVehicle", pEventSize, pEvents);
	if(pEventSize == 0) return;
	for(size_t i = 0; i < pEventSize; i++)
	{
		lua_getglobal(l, pEvents[i].c_str());
		lua_pushinteger(l, playerid);
		lua_pushinteger(l, vehicleId);
		lua_pushinteger(l, seatId);
		if(lua_pcall(l, 3, 0, 0) != 0)
		{
			std::string error = "Event " + pEvents[i] + std::string(": ") + lua_tostring(l, -1);
			apiLuaParams::lError(l, error.c_str());
		}
	}
}

void events::onPlayerExitVehicle(int playerid, int vehicleId, int seatId)
{
	lua_State* l = apiLua::getEventFunctions("onPlayerExitVehicle", pEventSize, pEvents);
	if(pEventSize == 0) return;
	for(size_t i = 0; i < pEventSize; i++)
	{
		lua_getglobal(l, pEvents[i].c_str());
		lua_pushinteger(l, playerid);
		lua_pushinteger(l, vehicleId);
		lua_pushinteger(l, seatId);
		if(lua_pcall(l, 3, 0, 0) != 0)
		{
			std::string error = "Event " + pEvents[i] + std::string(": ") + lua_tostring(l, -1);
			apiLuaParams::lError(l, error.c_str());
		}
	}
}

void events::onPlayerRequestVehicleEntry(int playerid, int vehicleId, int seatId, bool carjack)
{
	lua_State* l = apiLua::getEventFunctions("onPlayerRequestVehicleEntry", pEventSize, pEvents);
	if(pEventSize == 0) return;
	for(size_t i = 0; i < pEventSize; i++)
	{
		lua_getglobal(l, pEvents[i].c_str());
		lua_pushinteger(l, playerid);
		lua_pushinteger(l, vehicleId);
		lua_pushinteger(l, seatId);
		lua_pushboolean(l, carjack);
		if(lua_pcall(l, 4, 0, 0) != 0)
		{
			std::string error = "Event " + pEvents[i] + std::string(": ") + lua_tostring(l, -1);
			apiLuaParams::lError(l, error.c_str());
		}
	}
}

bool events::onPlayerSwapWeapons(int playerid, int weapon, int ammo)
{
	lua_State* l = apiLua::getEventFunctions("onPlayerSwitchWeapons", pEventSize, pEvents);
	if(pEventSize == 0) return true;
	bool b = true;
	for(size_t i = 0; i < pEventSize; i++)
	{
		lua_getglobal(l, pEvents[i].c_str());
		lua_pushinteger(l, playerid);
		lua_pushinteger(l, weapon);
		lua_pushinteger(l, ammo);
		if(lua_pcall(l, 3, 1, 0) != 0)
		{
			std::string error = "Event " + pEvents[i] + std::string(": ") + lua_tostring(l, -1);
			apiLuaParams::lError(l, error.c_str());
		}
		else if(lua_isboolean(l, -1) && lua_toboolean(l, -1) == false) b = false;
		lua_pop(l, lua_gettop(l));
	}
	return b;
}

bool events::onPlayerWeaponsArrived(int playerid)
{
	lua_State* l = apiLua::getEventFunctions("onPlayerWeaponsArrived", pEventSize, pEvents);
	if(pEventSize == 0) return true;
	//bool b = true;
	for(size_t i = 0; i < pEventSize; i++)
	{
		lua_getglobal(l, pEvents[i].c_str());
		lua_pushinteger(l, playerid);
		if(lua_pcall(l, 1, 0, 0) != 0)
		{
			std::string error = "Event " + pEvents[i] + std::string(": ") + lua_tostring(l, -1);
			apiLuaParams::lError(l, error.c_str());
		}
		//if(lua_isboolean(l, -1) && lua_toboolean(l, 1) == false) b = false;
	}
	return true;
}

char playerChat[150];
void events::onPlayerChat(int playerid, const char* chat)
{
	if(chat[0] == '/')
	{
		lua_State* l = apiLua::getEventFunctions("onPlayerCommand", pEventSize, pEvents);
		if(pEventSize == 0) return;
		for(size_t i = 0; i < pEventSize; i++)
		{
			lua_getglobal(l, pEvents[i].c_str());
			lua_pushinteger(l, playerid);
			lua_pushstring(l, chat);
			if(lua_pcall(l, 2, 0, 0) != 0)
			{
				std::string error = "Event " + pEvents[i] + std::string(": ") + lua_tostring(l, -1);
				apiLuaParams::lError(l, error.c_str());
			}
		}
		return;
	}
	
	lua_State* l = apiLua::getEventFunctions("onPlayerChat", pEventSize, pEvents);
	//if(pEventSize == 0) return;
	bool cancel = false;
	for(size_t i = 0; i < pEventSize; i++)
	{
		lua_getglobal(l, pEvents[i].c_str());
		lua_pushinteger(l, playerid);
		lua_pushstring(l, chat);
		if(lua_pcall(l, 2, 1, 0) != 0)
		{
			std::string error = "Event " + pEvents[i] + std::string(": ") + lua_tostring(l, -1);
			apiLuaParams::lError(l, error.c_str());
		}
		else if(lua_isboolean(l, -1) && lua_toboolean(l, -1) == false) cancel = true;
		lua_pop(l, lua_gettop(l));
	}
	//LINFO << "Return " << (int)cancel;
	if(!cancel && apiPlayer::isOn(playerid))
	{
		apiColoredChat::create(1);
		apiPlayer::player& player = apiPlayer::get(playerid);
		unsigned int rgba = player.getColor();
		unsigned int argb = (rgba << 24) | (rgba >> 8);

		snprintf(playerChat, 150, "%s(%i):", player.getNick(), playerid);
		apiColoredChat::addMsg(1, playerChat, argb);

		snprintf(playerChat, 150, " %s", chat);
		apiColoredChat::addMsg(1, playerChat, 0xFFFFFFFF);

		apiPlayer::sendColoredMsgToAll(1);
		apiColoredChat::dispose(1);
	}
}

bool events::onPlayerSpawn(int playerid)
{
	lua_State* l = apiLua::getEventFunctions("onPlayerSpawn", pEventSize, pEvents);
	if(pEventSize == 0) return true;
	//bool b = true;
	for(size_t i = 0; i < pEventSize; i++)
	{
		lua_getglobal(l, pEvents[i].c_str());
		lua_pushinteger(l, playerid);
		if(lua_pcall(l, 1, 0, 0) != 0)
		{
			std::string error = "Event " + pEvents[i] + std::string(": ") + lua_tostring(l, -1);
			apiLuaParams::lError(l, error.c_str());
		}
		//if(lua_isboolean(l, -1) && lua_toboolean(l, 1) == false) b = false;
	}
	return true;
}

void events::onPlayerDeath(int playerid, int agentType, int agentId)
{
	lua_State* l = apiLua::getEventFunctions("onPlayerDeath", pEventSize, pEvents);
	if(pEventSize == 0) return;
	for(size_t i = 0; i < pEventSize; i++)
	{
		lua_getglobal(l, pEvents[i].c_str());
		lua_pushinteger(l, playerid);
		lua_pushinteger(l, agentType);
		lua_pushinteger(l, agentId);
		if(lua_pcall(l, 3, 0, 0) != 0)
		{
			std::string error = "Event " + pEvents[i] + std::string(": ") + lua_tostring(l, -1);
			apiLuaParams::lError(l, error.c_str());
		}
	}
}

void events::onPlayerHpChange(int playerid, int agentType, int agentId, int bone)
{
	lua_State* l = apiLua::getEventFunctions("onPlayerHpChange", pEventSize, pEvents);
	if(pEventSize == 0) return;
	for(size_t i = 0; i < pEventSize; i++)
	{
		lua_getglobal(l, pEvents[i].c_str());
		lua_pushinteger(l, playerid);
		lua_pushinteger(l, agentType);
		lua_pushinteger(l, agentId);
		lua_pushinteger(l, bone);
		if(lua_pcall(l, 4, 0, 0) != 0)
		{
			std::string error = "Event " + pEvents[i] + std::string(": ") + lua_tostring(l, -1);
			apiLuaParams::lError(l, error.c_str());
		}
	}
}

void events::onPlayerArmourChange(int playerid, int agentType, int agentId, int bone)
{
	lua_State* l = apiLua::getEventFunctions("onPlayerArmorChange", pEventSize, pEvents);
	if(pEventSize == 0) return;
	for(size_t i = 0; i < pEventSize; i++)
	{
		lua_getglobal(l, pEvents[i].c_str());
		lua_pushinteger(l, playerid);
		lua_pushinteger(l, agentType);
		lua_pushinteger(l, agentId);
		lua_pushinteger(l, bone);
		if(lua_pcall(l, 4, 0, 0) != 0)
		{
			std::string error = "Event " + pEvents[i] + std::string(": ") + lua_tostring(l, -1);
			apiLuaParams::lError(l, error.c_str());
		}
	}
}

void events::onPlayerEnterCheckPoint(int playerid, int checkPointId)
{
	lua_State* l = apiLua::getEventFunctions("onPlayerEnterCheckPoint", pEventSize, pEvents);
	if(pEventSize == 0) return;
	for(size_t i = 0; i < pEventSize; i++)
	{
		lua_getglobal(l, pEvents[i].c_str());
		lua_pushinteger(l, playerid);
		lua_pushinteger(l, checkPointId);
		if(lua_pcall(l, 2, 0, 0) != 0)
		{
			std::string error = "Event " + pEvents[i] + std::string(": ") + lua_tostring(l, -1);
			apiLuaParams::lError(l, error.c_str());
		}
	}
}

void events::onPlayerExitCheckPoint(int playerid, int checkPointId)
{
	lua_State* l = apiLua::getEventFunctions("onPlayerExitCheckPoint", pEventSize, pEvents);
	if(pEventSize == 0) return;
	for(size_t i = 0; i < pEventSize; i++)
	{
		lua_getglobal(l, pEvents[i].c_str());
		lua_pushinteger(l, playerid);
		lua_pushinteger(l, checkPointId);
		if(lua_pcall(l, 2, 0, 0) != 0)
		{
			std::string error = "Event " + pEvents[i] + std::string(": ") + lua_tostring(l, -1);
			apiLuaParams::lError(l, error.c_str());
		}
	}
}

void events::onPlayerDialogResponse(int playerid, unsigned int dialogId, int buttonId, int rowId, int customId)
{
	lua_State* l = apiLua::getEventFunctions("onPlayerDialogResponse", pEventSize, pEvents);
	if(pEventSize == 0) return;
	for(size_t i = 0; i < pEventSize; i++)
	{
		lua_getglobal(l, pEvents[i].c_str());
		lua_pushinteger(l, playerid);
		lua_pushinteger(l, dialogId);
		lua_pushinteger(l, buttonId);
		lua_pushinteger(l, rowId);
		lua_pushinteger(l, customId);
		if(lua_pcall(l, 5, 0, 0) != 0)
		{
			std::string error = "Event " + pEvents[i] + std::string(": ") + lua_tostring(l, -1);
			apiLuaParams::lError(l, error.c_str());
		}
	}
}

void events::onPlayerCheckSumArrive(int playerid, const char* path, unsigned int sum)
{
	lua_State* l = apiLua::getEventFunctions("onPlayerCheckSumArrive", pEventSize, pEvents);
	if(pEventSize == 0) return;
	for(size_t i = 0; i < pEventSize; i++)
	{
		lua_getglobal(l, pEvents[i].c_str());
		lua_pushinteger(l, playerid);
		lua_pushstring(l, path);
		lua_pushinteger(l, sum);
		if(lua_pcall(l, 3, 0, 0) != 0)
		{
			std::string error = "Event " + pEvents[i] + std::string(": ") + lua_tostring(l, -1);
			apiLuaParams::lError(l, error.c_str());
		}
	}
}

void events::onPlayerHacks(int playerid, bool h)
{
	lua_State* l = apiLua::getEventFunctions("onPlayerHacksCheck", pEventSize, pEvents);
	if(pEventSize == 0) return;
	for(size_t i = 0; i < pEventSize; i++)
	{
		lua_getglobal(l, pEvents[i].c_str());
		lua_pushinteger(l, playerid);
		lua_pushboolean(l, h);
		if(lua_pcall(l, 2, 0, 0) != 0)
		{
			std::string error = "Event " + pEvents[i] + std::string(": ") + lua_tostring(l, -1);
			apiLuaParams::lError(l, error.c_str());
		}
	}
}

void events::onKeyPress(apiPlayer::player& player, unsigned int virtualKey, bool keyUp)
{
	lua_State* l = apiLua::getEventFunctions("onPlayerKeyPress", pEventSize, pEvents);
	if(pEventSize == 0) return;
	for(size_t i = 0; i < pEventSize; i++)
	{
		lua_getglobal(l, pEvents[i].c_str());
		lua_pushinteger(l, player.getID());
		lua_pushinteger(l, virtualKey);
		lua_pushboolean(l, keyUp);
		if(lua_pcall(l, 3, 0, 0) != 0)
		{
			std::string error = "Event " + pEvents[i] + std::string(": ") + lua_tostring(l, -1);
			apiLuaParams::lError(l, error.c_str());
		}
	}
}

void events::onChatUpdate(int playerid, int chat_id, int chat_op)
{
	lua_State* l = apiLua::getEventFunctions("onPlayerChatUpdate", pEventSize, pEvents);
	if(pEventSize == 0) return;
	for(size_t i = 0; i < pEventSize; i++)
	{
		lua_getglobal(l, pEvents[i].c_str());
		lua_pushinteger(l, playerid);
		lua_pushinteger(l, chat_id);
		lua_pushinteger(l, chat_op);
		if(lua_pcall(l, 3, 0, 0) != 0)
		{
			std::string error = "Event " + pEvents[i] + std::string(": ") + lua_tostring(l, -1);
			apiLuaParams::lError(l, error.c_str());
		}
	}
}

bool events::onTeamSpeak(int playerid, int type, int msg)
{
	lua_State* l = apiLua::getEventFunctions("onPlayerTeamSpeakResponse", pEventSize, pEvents);
	if(pEventSize == 0) return true;
	for(size_t i = 0; i < pEventSize; i++)
	{
		lua_getglobal(l, pEvents[i].c_str());
		lua_pushinteger(l, playerid);
		lua_pushinteger(l, type);
		lua_pushinteger(l, type == 0 ? msg : msg - 2);
		if(lua_pcall(l, 3, 0, 0) != 0)
		{
			std::string error = "Event " + pEvents[i] + std::string(": ") + lua_tostring(l, -1);
			apiLuaParams::lError(l, error.c_str());
		}
	}
	return true;
}

void events::npcStopped(int npc, bool willRepeat)
{
	lua_State* l = apiLua::getEventFunctions("onNpcFinishTasks", pEventSize, pEvents);
	if(pEventSize == 0) return;
	bool b = true;
	for(size_t i = 0; i < pEventSize; i++)
	{
		lua_getglobal(l, pEvents[i].c_str());
		lua_pushinteger(l, npc);
		lua_pushboolean(l, willRepeat);
		if(lua_pcall(l, 2, 0, 0) != 0)
		{
			std::string error = "Event " + pEvents[i] + std::string(": ") + lua_tostring(l, -1);
			apiLuaParams::lError(l, error.c_str());
		}
	}
}

void events::onPlayerSpawnEntity(int playerid, int spawned, int agentType, int agentId)
{
	lua_State* l = apiLua::getEventFunctions("onPlayerSpawnEntity", pEventSize, pEvents);
	if(pEventSize == 0) return;
	for(size_t i = 0; i < pEventSize; i++)
	{
		lua_getglobal(l, pEvents[i].c_str());
		lua_pushinteger(l, playerid);
		lua_pushboolean(l, spawned == 1);
		lua_pushinteger(l, agentType);
		lua_pushinteger(l, agentId);
		if(lua_pcall(l, 4, 0, 0) != 0)
		{
			std::string error = "Event " + pEvents[i] + std::string(": ") + lua_tostring(l, -1);
			apiLuaParams::lError(l, error.c_str());
		}
	}
}