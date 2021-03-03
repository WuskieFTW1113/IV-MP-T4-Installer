#include "stdafx.h"
#include "playerFunctions.h"
#include "apiLuaParams.h"
#include "apiPlayer.h"
#include "playerList.h"
#include "apiLua.h"
#include "apiDialog.h"
#include "apiColoredChat.h"
#include "sha.h"

#define isValidPlayer(luaVm) if(!apiPlayer::isOn((int)lua_tointeger(l, 1))) {lua_pushnil(luaVm); return 1;}

int getPlayersOnline(lua_State* l)
{
	lua_newtable(l);
	for(int i = 1; i < 33; i++)
	{
		if(apiPlayer::isOn(i))
		{
			lua_pushinteger(l, i);
			lua_rawseti(l, -2, i);
		}
	}
	return 1;
}

int sendMsgToAll(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 2, "si")) return apiLuaParams::lError(l, "Invalid sendMsgToAll params");
	apiPlayer::sendMsgToAll(lua_tostring(l, 1), (unsigned int)lua_tointeger(l, 2));
	return 0;
}

//int sendColoredMsgToAll(lua_State* l);

int isPlayer(lua_State* l)
{
	bool push = false;
	if(apiLuaParams::paramCheck(l, 1, "i"))
	{
		push = apiPlayer::isOn((int)lua_tointeger(l, 1));
	}
	lua_pushboolean(l, push);
	return 1;
}

int getPos(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 1, "i")) return apiLuaParams::lError(l, "Invalid getPlayerPos params");
	isValidPlayer(l);
	apiMath::Vector3 v = apiPlayer::get((int)lua_tointeger(l, 1)).getPos();
	lua_pushnumber(l, v.x);
	lua_pushnumber(l, v.y);
	lua_pushnumber(l, v.z);
	return 3;
}

int setPos(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 4, "iddd")) return apiLuaParams::lError(l, "Invalid setPlayerPos params");
	isValidPlayer(l);
	apiMath::Vector3 v(apiMath::Vector3((float)lua_tonumber(l, 2), (float)lua_tonumber(l, 3), (float)lua_tonumber(l, 4)));
	apiPlayer::get((int)lua_tointeger(l, 1)).setPos(v);
	return 0;
}

int getNick(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 1, "i")) return apiLuaParams::lError(l, "Invalid getPlayerName params");
	isValidPlayer(l);
	lua_pushstring(l, apiPlayer::get((int)lua_tointeger(l, 1)).getNick());
	return 1;
}

int setNick(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 2, "is")) return apiLuaParams::lError(l, "Invalid setPlayerName params");
	isValidPlayer(l);
	apiPlayer::get((int)lua_tointeger(l, 1)).setNick(lua_tostring(l, 2));
	return 0;
}

int sendMsg(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 3, "isi")) return apiLuaParams::lError(l, "Invalid sendPlayerMsg params");
	isValidPlayer(l);
	apiPlayer::get((int)lua_tointeger(l, 1)).sendMsg(lua_tostring(l, 2), (unsigned int)lua_tointeger(l, 3));
	return 0;
}

int sendMsg2(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 4, "isii")) return apiLuaParams::lError(l, "Invalid sendCustomMsg params");
	isValidPlayer(l);
	apiPlayer::get((int)lua_tointeger(l, 1)).sendMsg(lua_tostring(l, 2), (unsigned int)lua_tointeger(l, 3), (int)lua_tointeger(l, 4));
	return 0;
}

//int sendColoredMsg(lua_State* l);

int setSkin(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 2, "ii")) return apiLuaParams::lError(l, "Invalid setPlayerSkin params");
	isValidPlayer(l);
	int skin = (int)lua_tointeger(l, 2);
	if(!playerList::isValidModel(skin))
	{
		lua_pushnil(l);
		return 1;
	}
	apiPlayer::get((int)lua_tointeger(l, 1)).setSkin(playerList::getModel(skin));
	return 0;
}

int getSkin(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 1, "i")) return apiLuaParams::lError(l, "Invalid getPlayerSkin params");
	unsigned int hash = apiPlayer::get((int)lua_tointeger(l, 1)).getSkin();
	lua_pushinteger(l, playerList::getIdByHash(hash));
	return 1;
}

int setWorld(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 2, "ii")) return apiLuaParams::lError(l, "Invalid sendPlayerWorld params");
	isValidPlayer(l);
	apiPlayer::get((int)lua_tointeger(l, 1)).setWorld((unsigned int)lua_tointeger(l, 2));
	return 0;
}

int getWorld(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 1, "i")) return apiLuaParams::lError(l, "Invalid getPlayerWorld params");
	isValidPlayer(l);
	lua_pushinteger(l, apiPlayer::get((int)lua_tointeger(l, 1)).getWorld());
	return 1;
}

int giveWeapon(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 3, "iii")) return apiLuaParams::lError(l, "Invalid givePlayerWeapon params");
	isValidPlayer(l);
	apiPlayer::get((int)lua_tointeger(l, 1)).giveWeapon((int)lua_tointeger(l, 2), (int)lua_tointeger(l, 3));
	return 0;
}

int removeWeapon(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 2, "ii")) return apiLuaParams::lError(l, "Invalid removePlayerWeapon params");
	isValidPlayer(l);
	apiPlayer::get((int)lua_tointeger(l, 1)).removeWeapon((int)lua_tointeger(l, 2));
	return 0;
}

int setHealth(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 2, "ii")) return apiLuaParams::lError(l, "Invalid setPlayerHealth params");
	isValidPlayer(l);
	apiPlayer::get((int)lua_tointeger(l, 1)).setHealth((int)lua_tointeger(l, 2));
	return 0;
}

int getHealth(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 1, "i")) return apiLuaParams::lError(l, "Invalid getPlayerHealth params");
	isValidPlayer(l);
	lua_pushinteger(l, apiPlayer::get((int)lua_tointeger(l, 1)).getHealth());
	return 1;
}

int setColor(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 2, "ii")) return apiLuaParams::lError(l, "Invalid setPlayerColor params");
	isValidPlayer(l);
	apiPlayer::get((int)lua_tointeger(l, 1)).setColor((unsigned int)lua_tointeger(l, 2));
	return 0;
}

int getColor(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 1, "i")) return apiLuaParams::lError(l, "Invalid getPlayerColor params");
	isValidPlayer(l);
	lua_pushinteger(l, apiPlayer::get((int)lua_tointeger(l, 1)).getColor());
	return 1;
}

int spawn(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 4, "iddd")) return apiLuaParams::lError(l, "Invalid spawnPlayer params");
	isValidPlayer(l);
	apiMath::Vector3 v(apiMath::Vector3((float)lua_tonumber(l, 2), (float)lua_tonumber(l, 3), (float)lua_tonumber(l, 4)));
	apiPlayer::get((int)lua_tointeger(l, 1)).spawn(v);
	return 0;
}

int setRespawnPos(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 4, "iddd")) return apiLuaParams::lError(l, "Invalid setPlayerRespawnPos params");
	isValidPlayer(l);
	apiMath::Vector3 v(apiMath::Vector3((float)lua_tonumber(l, 2), (float)lua_tonumber(l, 3), (float)lua_tonumber(l, 4)));
	apiPlayer::get((int)lua_tointeger(l, 1)).setRespawnPos(v);
	return 0;
}

int getDriving(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 1, "i")) return apiLuaParams::lError(l, "Invalid getPlayerDriving params");
	isValidPlayer(l);
	lua_pushinteger(l, apiPlayer::get((int)lua_tointeger(l, 1)).getDriving());
	return 1;
}

int getPassenger(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 1, "i")) return apiLuaParams::lError(l, "Invalid getPlayerPassenger params");
	isValidPlayer(l);
	int vehicle = 0, seat = 0;
	apiPlayer::get((int)lua_tointeger(l, 1)).getPassenger(vehicle, seat);
	lua_pushinteger(l, vehicle);
	lua_pushinteger(l, seat);
	return 2;
}

int isInVehicle(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 1, "i")) return apiLuaParams::lError(l, "Invalid isPlayerInAnyVehicle params");
	isValidPlayer(l);
	lua_pushinteger(l, apiPlayer::get((int)lua_tointeger(l, 1)).isInVehicle());
	return 1;
}

int putInVehicle(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 3, "iii")) return apiLuaParams::lError(l, "Invalid warpPlayerIntoVehicle params");
	isValidPlayer(l);
	apiPlayer::get((int)lua_tointeger(l, 1)).putInVehicle((int)lua_tointeger(l, 2), (int)lua_tointeger(l, 3));
	return 0;
}

int removeFromVehicle(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 1, "i")) return apiLuaParams::lError(l, "Invalid removePlayerFromVehicle params");
	isValidPlayer(l);
	apiPlayer::get((int)lua_tointeger(l, 1)).removeFromVehicle();
	return 0;
}

int drawText(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 9, "iiddddsii")) return apiLuaParams::lError(l, "Invalid drawText params");
	isValidPlayer(l);
	apiPlayer::get((int)lua_tointeger(l, 1)).drawText((int)lua_tointeger(l, 2), (float)lua_tonumber(l, 3),
		(float)lua_tonumber(l, 4), (float)lua_tonumber(l, 5), (float)lua_tonumber(l, 6), lua_tostring(l, 7),
		(int)lua_tointeger(l, 8), (unsigned int)lua_tointeger(l, 9));
	return 0;
}

int updateText(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 4, "iisi")) return apiLuaParams::lError(l, "Invalid updateText params");
	isValidPlayer(l);
	apiPlayer::get((int)lua_tointeger(l, 1)).updateText((int)lua_tointeger(l, 2), lua_tostring(l, 3), (unsigned int)lua_tointeger(l, 4));
	return 0;
}

int drawInfoText(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 3, "isi")) return apiLuaParams::lError(l, "Invalid drawInfotext params");
	isValidPlayer(l);
	apiPlayer::get((int)lua_tointeger(l, 1)).drawInfoText(lua_tostring(l, 2), (unsigned int)lua_tointeger(l, 3));
	return 0;
}

int drawRect(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 7, "iiddddi")) return apiLuaParams::lError(l, "Invalid drawRect params");
	isValidPlayer(l);
	apiPlayer::get((int)lua_tointeger(l, 1)).drawRect((int)lua_tointeger(l, 2), (float)lua_tonumber(l, 3),
		(float)lua_tonumber(l, 4), (float)lua_tonumber(l, 5), (float)lua_tonumber(l, 6), (unsigned int)lua_tointeger(l, 7));
	return 0;
}

int wipeDrawClass(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 2, "ii")) return apiLuaParams::lError(l, "Invalid wipeDrawClass params");
	isValidPlayer(l);
	apiPlayer::get((int)lua_tointeger(l, 1)).wipeDrawClass((int)lua_tointeger(l, 2));
	return 0;
}

int getWeapon(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 1, "i")) return apiLuaParams::lError(l, "Invalid getPlayerWeapon params");
	isValidPlayer(l);
	lua_pushinteger(l, apiPlayer::get((int)lua_tointeger(l, 1)).getWeapon());
	return 1;
}

int getAmmo(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 1, "i")) return apiLuaParams::lError(l, "Invalid getPlayeAmmo params");
	isValidPlayer(l);
	lua_pushinteger(l, apiPlayer::get((int)lua_tointeger(l, 1)).getAmmo());
	return 1;
}

int setFrozen(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 2, "ib")) return apiLuaParams::lError(l, "Invalid setPlayerFrozen params");
	isValidPlayer(l);
	apiPlayer::get((int)lua_tointeger(l, 1)).setFrozen(lua_toboolean(l, 2));
	return 0;
}

int debugPlayer(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 2, "ii")) return apiLuaParams::lError(l, "Invalid debugPlayer params");
	isValidPlayer(l);
	apiPlayer::get((int)lua_tointeger(l, 1)).debugPlayer((int)lua_tointeger(l, 2));
	return 0;
}

int debugVehicle(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 2, "ii")) return apiLuaParams::lError(l, "Invalid debugVehicle params");
	isValidPlayer(l);
	apiPlayer::get((int)lua_tointeger(l, 1)).debugVehicle((int)lua_tointeger(l, 2));
	return 0;
}

int disconnect(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 1, "i")) return apiLuaParams::lError(l, "Invalid disconnectPlayer params");
	isValidPlayer(l);
	apiPlayer::get((int)lua_tointeger(l, 1)).disconnect();
	return 0;
}

int getPing(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 2, "ib")) return apiLuaParams::lError(l, "Invalid getPlayerPing params");
	isValidPlayer(l);
	lua_pushinteger(l, apiPlayer::get((int)lua_tointeger(l, 1)).getPing(lua_toboolean(l, 2)));
	return 1;
}

int getAnim(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 1, "i")) return apiLuaParams::lError(l, "Invalid getPlayerAnim params");
	isValidPlayer(l);
	lua_pushinteger(l, apiPlayer::get((int)lua_tointeger(l, 1)).getAnim());
	return 1;
}

int showDialogList(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 2, "ii")) return apiLuaParams::lError(l, "Invalid showDialogList params");
	isValidPlayer(l);
	unsigned int dialog = (unsigned int)lua_tointeger(l, 2);
	if(!apiDialog::isValid(dialog)) return apiLuaParams::lError(l, "The dialog requested doesnt exist");
	apiPlayer::get((int)lua_tointeger(l, 1)).showDialogList(dialog);
	return 0;
}

int setClothes(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 3, "iii")) return apiLuaParams::lError(l, "Invalid setPlayerClothes params");
	isValidPlayer(l);
	unsigned int slot = (unsigned int)lua_tointeger(l, 2);
	if(slot > 8) return apiLuaParams::lError(l, "setPlayerClothes slots are 0-8");
	apiPlayer::get((int)lua_tointeger(l, 1)).setClothes(slot, (unsigned int)lua_tointeger(l, 3));
	return 0;
}

int setProperty(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 3, "iii")) return apiLuaParams::lError(l, "Invalid setPlayerProperty params");
	isValidPlayer(l);
	unsigned int slot = (unsigned int)lua_tointeger(l, 2);
	if(slot > 1) return apiLuaParams::lError(l, "setPlayerProperty slots are 0-1");
	apiPlayer::get((int)lua_tointeger(l, 1)).setProperty(slot, (unsigned int)lua_tointeger(l, 3));
	return 0;
}

int forceAnim(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 4, "issb")) return apiLuaParams::lError(l, "Invalid forcePlayerAnim params");
	isValidPlayer(l);
	apiPlayer::get((int)lua_tointeger(l, 1)).forceAnim(lua_tostring(l, 2), lua_tostring(l, 3), lua_toboolean(l, 4));
	return 0;
}

int stopAnims(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 1, "i")) return apiLuaParams::lError(l, "Invalid stopAnims params");
	isValidPlayer(l);
	apiPlayer::get((int)lua_tointeger(l, 1)).stopAnims();
	return 0;
}

int setKeyHook(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 3, "iib")) return apiLuaParams::lError(l, "Invalid setPlayerKeyHook params");
	isValidPlayer(l);
	apiPlayer::get((int)lua_tointeger(l, 1)).setKeyHook((unsigned int)lua_tointeger(l, 2), lua_toboolean(l, 3));
	return 0;
}

int getIp(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 1, "i")) return apiLuaParams::lError(l, "Invalid getPlayerIp params");
	isValidPlayer(l);
	lua_pushstring(l, apiPlayer::get((int)lua_tointeger(l, 1)).getIp());
	return 1;
}

int showBlip(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 3, "iib")) return apiLuaParams::lError(l, "Invalid showBlipForPlayer params");
	isValidPlayer(l);
	apiPlayer::get((int)lua_tointeger(l, 1)).showBlip((int)lua_tointeger(l, 2), lua_toboolean(l, 3));
	return 0;
}

int cam_setPos(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 5, "idddi")) return apiLuaParams::lError(l, "Invalid setPlayerCamPos params");
	isValidPlayer(l);
	apiMath::Vector3 v(apiMath::Vector3((float)lua_tonumber(l, 2), (float)lua_tonumber(l, 3), (float)lua_tonumber(l, 4)));
	apiPlayer::get((int)lua_tointeger(l, 1)).cam_setPos(&v, (unsigned int)lua_tointeger(l, 5));
	return 0;
}

int cam_setLookAt(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 4, "iddd")) return apiLuaParams::lError(l, "Invalid setPlayerCamLookAt params");
	isValidPlayer(l);
	apiMath::Vector3 v(apiMath::Vector3((float)lua_tonumber(l, 2), (float)lua_tonumber(l, 3), (float)lua_tonumber(l, 4)));
	apiPlayer::get((int)lua_tointeger(l, 1)).cam_setLookAt(v);
	return 0;
}

int cam_attachOnPlayer(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 2, "ii")) return apiLuaParams::lError(l, "Invalid attachCamOnPlayer params");
	isValidPlayer(l);
	apiPlayer::get((int)lua_tointeger(l, 1)).cam_attachOnPlayer((int)lua_tointeger(l, 2));
	return 0;
}

int closeMods(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 1, "i")) return apiLuaParams::lError(l, "Invalid checkPlayerHacks params");
	isValidPlayer(l);
	apiPlayer::get((int)lua_tointeger(l, 1)).checkHacks();
	return 0;
}

int checkSum(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 2, "is")) return apiLuaParams::lError(l, "Invalid playerCheckSum params");
	isValidPlayer(l);
	apiPlayer::get((int)lua_tointeger(l, 1)).checkSum(lua_tostring(l, 2));
	return 0;
}

int isObjectSpawned(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 2, "ii")) return apiLuaParams::lError(l, "Invalid isObjectSpawnedForPlayer params");
	isValidPlayer(l);
	lua_pushinteger(l, apiPlayer::get((int)lua_tointeger(l, 1)).isObjectSpawned((int)lua_tointeger(l, 2)));
	return 1;
}

int isVehicleSpawned(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 2, "ii")) return apiLuaParams::lError(l, "Invalid isVehiclepawnedForPlayer params");
	isValidPlayer(l);
	lua_pushinteger(l, apiPlayer::get((int)lua_tointeger(l, 1)).isVehicleSpawned((int)lua_tointeger(l, 2)));
	return 1;
}

int requestWeapons(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 1, "i")) return apiLuaParams::lError(l, "Invalid requestPlayerWeapons params");
	isValidPlayer(l);
	apiPlayer::get((int)lua_tointeger(l, 1)).requestWeapons();
	return 0;
}

int getWeaponsSize(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 1, "i")) return apiLuaParams::lError(l, "Invalid getPlayerWeapons params");
	isValidPlayer(l);
	apiPlayer::player& p = apiPlayer::get((int)lua_tointeger(l, 1));
	unsigned int s = p.getWeaponsSize();
	if(s == 0)
	{
		lua_pushnil(l);
	}
	else
	{
		lua_createtable(l, 2, 0);
		int weapon = 0, ammo = 0;
		for(unsigned int i = 0; i < s; i++)
		{
			p.getWeaponData(i, weapon, ammo);
			lua_pushnumber(l, weapon);
			lua_pushinteger(l, ammo);
			lua_rawset(l, -3);
		}
	}
	return 1;
}

int getRoomKey(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 1, "i")) return apiLuaParams::lError(l, "Invalid getPlayerRoom params");
	isValidPlayer(l);
	lua_pushinteger(l, apiPlayer::get((int)lua_tointeger(l, 1)).getRoomKey());
	return 1;
}

int playStreamPos(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 5, "isddd")) return apiLuaParams::lError(l, "Invalid playStreamAtPos params");
	isValidPlayer(l);
	apiMath::Vector3 v(apiMath::Vector3((float)lua_tonumber(l, 3), (float)lua_tonumber(l, 4), (float)lua_tonumber(l, 5)));
	apiPlayer::get((int)lua_tointeger(l, 1)).playStream(lua_tostring(l, 2), &v);
	return 0;
}

int playStream(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 2, "is")) return apiLuaParams::lError(l, "Invalid playStreamFrontend params");
	isValidPlayer(l);
	apiPlayer::get((int)lua_tointeger(l, 1)).playStream(lua_tostring(l, 2), NULL);
	return 0;
}

int stopStreams(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 1, "i")) return apiLuaParams::lError(l, "Invalid stopStreams params");
	isValidPlayer(l);
	apiPlayer::get((int)lua_tointeger(l, 1)).stopStreams();
	return 0;
}

int setArmor(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 2, "ii")) return apiLuaParams::lError(l, "Invalid setPlayerArmor params");
	isValidPlayer(l);
	apiPlayer::get((int)lua_tointeger(l, 1)).setArmor((int)lua_tointeger(l, 2));
	return 0;
}

int getArmor(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 1, "i")) return apiLuaParams::lError(l, "Invalid getPlayerArmor params");
	isValidPlayer(l);
	lua_pushinteger(l, apiPlayer::get((int)lua_tointeger(l, 1)).getArmor());
	return 1;
}

int setMoney(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 2, "ii")) return apiLuaParams::lError(l, "Invalid setPlayerCash params");
	isValidPlayer(l);
	apiPlayer::get((int)lua_tointeger(l, 1)).setMoney((int)lua_tointeger(l, 2));
	return 0;
}

int setDoorStat(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 6, "iidddb")) return apiLuaParams::lError(l, "Invalid setDoorStatus params");
	isValidPlayer(l);
	apiMath::Vector3 v(apiMath::Vector3((float)lua_tonumber(l, 3), (float)lua_tonumber(l, 4), (float)lua_tonumber(l, 5)));
	apiPlayer::get((int)lua_tointeger(l, 1)).setDoorStat((unsigned int)lua_tointeger(l, 2), &v, lua_toboolean(l, 6));
	return 0;
}

int setAllDoorStat(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 2, "ib")) return apiLuaParams::lError(l, "Invalid setKnownDoorStatus params");
	isValidPlayer(l);
	apiPlayer::get((int)lua_tointeger(l, 1)).setDoorStat(0, NULL, lua_toboolean(l, 2));
	return 0;
}

int getGame(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 1, "i")) return apiLuaParams::lError(l, "Invalid getPlayerGame params");
	isValidPlayer(l);
	lua_pushinteger(l, apiPlayer::get((int)lua_tointeger(l, 1)).getGame());
	return 1;
}

int sendChatOptions(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 3, "iii")) return apiLuaParams::lError(l, "Invalid sendChatOptions params");
	isValidPlayer(l);
	apiPlayer::get((int)lua_tointeger(l, 1)).customChat((int)lua_tointeger(l, 2), (int)lua_tointeger(l, 3));
	return 0;
}

int newColoredMsg(lua_State* l)
{
	int args = lua_gettop(l);
	if(args < 3 || !lua_isinteger(l, 1) || !lua_isstring(l, 2) || !lua_isinteger(l, 3)) {
		return apiLuaParams::lError(l, "newColorMsg must have at least 3 params: int, string, int");
	}
	int chatId = (int)lua_tointeger(l, 1);
	if((args - 1) % 2 != 0) return apiLuaParams::lError(l, "newColorMsg invalid sequence of params");
	apiColoredChat::create(chatId);
	for(int i = 2; i < args; i += 2)
	{
		//printf("Adding: %i, %s, %u\n", chatId, lua_tostring(l, i), (unsigned int)lua_tointeger(l, i + 1));
		apiColoredChat::addMsg(chatId, lua_tostring(l, i), (unsigned int)lua_tointeger(l, i + 1));
	}
	return 0;
}

int sendColoredMsg(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 2, "ii")) return apiLuaParams::lError(l, "Invalid sendColoredMsg params");
	int chat = (int)lua_tointeger(l, 1);
	if(!apiColoredChat::isValid(chat)) return apiLuaParams::lError(l, "Invalid color msg ID");
	int id = (int)lua_tointeger(l, 2);
	if(id == -1) apiPlayer::sendColoredMsgToAll(chat);
	else if(apiPlayer::isOn(id)) apiPlayer::get(id).sendColoredMsg(chat);
	return 0;
}

int getHeading(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 1, "i")) return apiLuaParams::lError(l, "Invalid getPlayerHeading params");
	isValidPlayer(l);
	lua_pushnumber(l, apiPlayer::get((int)lua_tointeger(l, 1)).getHeading());
	return 1;
}

int setHeading(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 2, "if")) return apiLuaParams::lError(l, "Invalid setPlayerHeading params");
	isValidPlayer(l);
	apiPlayer::get((int)lua_tointeger(l, 1)).setHeading((float)lua_tonumber(l, 2));
	return 0;
}

int createExplosion(lua_State* l)
{
	//apiMath::Vector3& pos, int typ, float radius, bool audio, bool invisible, float cam
	if(!apiLuaParams::paramCheck(l, 7, "idddidd")) return apiLuaParams::lError(l, "Invalid createExplosion params");
	isValidPlayer(l);
	apiMath::Vector3 v((float)lua_tonumber(l, 2), (float)lua_tonumber(l, 3), (float)lua_tonumber(l, 4));
	apiPlayer::get((int)lua_tointeger(l, 1)).explodeAt(v, (int)lua_tointeger(l, 5), (float)lua_tonumber(l, 6),
		true, true, (float)lua_tonumber(l, 7));

	return 0;
}

int forceSitNow(lua_State* l)
{
	//apiMath::Vector3& pos, int typ, float radius, bool audio, bool invisible, float cam
	if(!apiLuaParams::paramCheck(l, 1, "i")) return apiLuaParams::lError(l, "Invalid forceSitNow params");
	isValidPlayer(l);
	apiPlayer::get((int)lua_tointeger(l, 1)).forceSitNow();
	return 0;
}

int setSitIdleAnim(lua_State* l)
{
	//apiMath::Vector3& pos, int typ, float radius, bool audio, bool invisible, float cam
	if(!apiLuaParams::paramCheck(l, 4, "issi")) return apiLuaParams::lError(l, "Invalid setSitIdleAnim params");
	isValidPlayer(l);
	apiPlayer::get((int)lua_tointeger(l, 1)).setSitIdleAnim(lua_tostring(l, 2), lua_tostring(l, 3), (int)lua_tointeger(l, 4));
	return 0;
}

int playSound(lua_State* l)
{
	int params = lua_gettop(l);
	if(params != 3 && params != 6)  return apiLuaParams::lError(l, "Invalid playSound params");
	isValidPlayer(l);
	int soundId = (int)lua_tointeger(l, 3);
	const char* name = lua_tostring(l, 2);
	apiPlayer::player& p = apiPlayer::get((int)lua_tointeger(l, 1));

	if(params == 3) p.playSound(name, soundId, NULL);
	else {
		apiMath::Vector3 pos((float)lua_tonumber(l, 4), (float)lua_tonumber(l, 5), (float)lua_tonumber(l, 6));
		p.playSound(name, soundId, &pos);
	}
	return 0;
}

int stopSound(lua_State* l)
{
	//apiMath::Vector3& pos, int typ, float radius, bool audio, bool invisible, float cam
	if(!apiLuaParams::paramCheck(l, 2, "ii")) return apiLuaParams::lError(l, "Invalid stopSound params");
	isValidPlayer(l);
	apiPlayer::get((int)lua_tointeger(l, 1)).stopSound((int)lua_tointeger(l, 2));
	return 0;
}

int tsConnect(lua_State* l)
{
	//apiMath::Vector3& pos, int typ, float radius, bool audio, bool invisible, float cam
	if(!apiLuaParams::paramCheck(l, 2, "is")) return apiLuaParams::lError(l, "Invalid tsConnect params");
	isValidPlayer(l);
	apiPlayer::get((int)lua_tointeger(l, 1)).ts_connect(lua_tostring(l, 2));
	return 0;
}

int tsToggleVoice(lua_State* l)
{
	//apiMath::Vector3& pos, int typ, float radius, bool audio, bool invisible, float cam
	if(!apiLuaParams::paramCheck(l, 2, "ib")) return apiLuaParams::lError(l, "Invalid tsToggleVoice params");
	isValidPlayer(l);
	apiPlayer::get((int)lua_tointeger(l, 1)).ts_toggleVoice(lua_toboolean(l, 2));
	return 0;
}

int tsAllowWhisper(lua_State* l)
{
	//apiMath::Vector3& pos, int typ, float radius, bool audio, bool invisible, float cam
	if(!apiLuaParams::paramCheck(l, 3, "iib")) return apiLuaParams::lError(l, "Invalid tsAllowVoice params");
	isValidPlayer(l);
	apiPlayer::get((int)lua_tointeger(l, 1)).ts_allowVoiceTo((int)lua_tointeger(l, 2), lua_toboolean(l, 3));
	return 0;
}

int setPlayerDraw(lua_State* l)
{
	//apiMath::Vector3& pos, int typ, float radius, bool audio, bool invisible, float cam
	if(!apiLuaParams::paramCheck(l, 4, "iibb")) return apiLuaParams::lError(l, "Invalid setPlayerDraw params");
	isValidPlayer(l);
	apiPlayer::get((int)lua_tointeger(l, 1)).setDrawFlags((int)lua_tointeger(l, 2), lua_toboolean(l, 3), lua_toboolean(l, 4));
	return 0;
}

int setPlayerHud(lua_State* l)
{
	//apiMath::Vector3& pos, int typ, float radius, bool audio, bool invisible, float cam
	if(!apiLuaParams::paramCheck(l, 3, "ibb")) return apiLuaParams::lError(l, "Invalid setPlayerHud params");
	isValidPlayer(l);
	apiPlayer::get((int)lua_tointeger(l, 1)).setHudFlags(lua_toboolean(l, 2), lua_toboolean(l, 3));
	return 0;
}

int getPlayerSerials(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 1, "i")) return apiLuaParams::lError(l, "Invalid getPlayerSerials params");
	isValidPlayer(l);
	apiPlayer::player& p = apiPlayer::get((int)lua_tointeger(l, 1));
	unsigned int sSize = p.getSerialSize();
	if(sSize == 0) {
		lua_pushnil(l);
		return 1;
	}

	lua_newtable(l);
	char buf[65];

	for(unsigned int i = 0; i < sSize; i++)
	{
		getSha2(p.getSerial(i), buf);
		lua_pushstring(l, buf);
		lua_rawseti(l, -2, i + 1);
	}
	return 1;
}

int getPlayerAim(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 1, "i")) return apiLuaParams::lError(l, "Invalid getPlayerAim params");
	isValidPlayer(l);
	float aim[3];
	apiPlayer::get((int)lua_tointeger(l, 1)).copyAim(aim);
	lua_pushnumber(l, aim[0]);
	lua_pushnumber(l, aim[1]);
	lua_pushnumber(l, aim[2]);
	return 3;
}

int setVehicleColForPlayer(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 3, "iib")) return apiLuaParams::lError(l, "Invalid setVehicleColForPlayer params");
	isValidPlayer(l);
	apiPlayer::get((int)lua_tointeger(l, 1)).setVehicleCol((int)lua_tointeger(l, 2), lua_toboolean(l, 3));
	return 3;
}

int getPlayerClothes(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 1, "i")) return apiLuaParams::lError(l, "Invalid getPlayerClothes params");
	isValidPlayer(l);

	apiPlayer::player& p = apiPlayer::get((int)lua_tointeger(l, 1));
	lua_newtable(l);

	for(unsigned int i = 0; i < 8; i++)
	{
		lua_pushinteger(l, p.getClothes(i));
		lua_rawseti(l, -2, i);
	}
	return 1;
}

int getPlayerProperties(lua_State* l)
{
	if(!apiLuaParams::paramCheck(l, 1, "i")) return apiLuaParams::lError(l, "Invalid getPlayerProperties params");
	isValidPlayer(l);

	apiPlayer::player& p = apiPlayer::get((int)lua_tointeger(l, 1));
	lua_newtable(l);

	for(unsigned i = 0; i < 2; i++)
	{
		lua_pushinteger(l, p.getProperty(i));
		lua_rawseti(l, -2, i);
	}
	return 1;
}

void playerFuncs::load(lua_State* l)
{
	apiLua::addFunc(apiLua::LuaFuncStruct(newColoredMsg, "newColorMsg", "isi", ""));
	apiLua::addFunc(apiLua::LuaFuncStruct(sendColoredMsg, "sendColorMsg", "ii", ""));
	apiLua::addFunc(apiLua::LuaFuncStruct(getPlayersOnline, "getPlayers", "", "a"));
	apiLua::addFunc(apiLua::LuaFuncStruct(sendMsgToAll, "sendMsgToAll", "si", ""));
	apiLua::addFunc(apiLua::LuaFuncStruct(isPlayer, "isPlayerOnline", "i", "b"));
	apiLua::addFunc(apiLua::LuaFuncStruct(getPos, "getPlayerPos", "i", "fff"));
	apiLua::addFunc(apiLua::LuaFuncStruct(setPos, "setPlayerPos", "ifff", ""));
	apiLua::addFunc(apiLua::LuaFuncStruct(getNick, "getPlayerName", "i", "s"));
	apiLua::addFunc(apiLua::LuaFuncStruct(setNick, "setPlayerName", "is", ""));
	apiLua::addFunc(apiLua::LuaFuncStruct(getHeading, "getPlayerHeading", "i", "f"));
	apiLua::addFunc(apiLua::LuaFuncStruct(setHeading, "setPlayerHeading", "if", ""));
	apiLua::addFunc(apiLua::LuaFuncStruct(sendMsg, "sendPlayerMsg", "isi", ""));
	apiLua::addFunc(apiLua::LuaFuncStruct(sendMsg2, "sendCustomMsg", "isii", ""));
	apiLua::addFunc(apiLua::LuaFuncStruct(setSkin, "setPlayerSkin", "ii", ""));
	apiLua::addFunc(apiLua::LuaFuncStruct(getSkin, "getPlayerSkin", "i", ""));
	apiLua::addFunc(apiLua::LuaFuncStruct(setWorld, "setPlayerWorld", "ii", ""));
	apiLua::addFunc(apiLua::LuaFuncStruct(getWorld, "getPlayerWorld", "i", "i"));
	apiLua::addFunc(apiLua::LuaFuncStruct(giveWeapon, "givePlayerWeapon", "iii", ""));
	apiLua::addFunc(apiLua::LuaFuncStruct(removeWeapon, "removePlayerWeapon", "ii", ""));
	apiLua::addFunc(apiLua::LuaFuncStruct(setHealth, "setPlayerHealth", "ii", ""));
	apiLua::addFunc(apiLua::LuaFuncStruct(getHealth, "getPlayerHealth", "i", "i"));
	apiLua::addFunc(apiLua::LuaFuncStruct(setColor, "setPlayerColor", "ii", ""));
	apiLua::addFunc(apiLua::LuaFuncStruct(getColor, "getPlayerColor", "i", "i"));
	apiLua::addFunc(apiLua::LuaFuncStruct(spawn, "spawnPlayer", "ifff", ""));
	apiLua::addFunc(apiLua::LuaFuncStruct(setRespawnPos, "setPlayerRespawnPos", "ifff", ""));
	apiLua::addFunc(apiLua::LuaFuncStruct(getDriving, "getPlayerDriving", "i", "i"));
	apiLua::addFunc(apiLua::LuaFuncStruct(getPassenger, "getPlayerPassenger", "i", "ii"));
	apiLua::addFunc(apiLua::LuaFuncStruct(isInVehicle, "isPlayerInAnyVehicle", "i", "i"));
	apiLua::addFunc(apiLua::LuaFuncStruct(putInVehicle, "warpPlayerIntoVehicle", "iii", ""));
	apiLua::addFunc(apiLua::LuaFuncStruct(removeFromVehicle, "removePlayerFromVehicle", "i", ""));
	apiLua::addFunc(apiLua::LuaFuncStruct(drawText, "drawText", "iddddsii", ""));
	apiLua::addFunc(apiLua::LuaFuncStruct(updateText, "updateText", "iisi", ""));
	apiLua::addFunc(apiLua::LuaFuncStruct(drawInfoText, "drawInfoText", "isi", ""));
	apiLua::addFunc(apiLua::LuaFuncStruct(drawRect, "drawRect", "iiddddi", ""));
	apiLua::addFunc(apiLua::LuaFuncStruct(wipeDrawClass, "wipeDrawClass", "ii", ""));
	apiLua::addFunc(apiLua::LuaFuncStruct(getWeapon, "getPlayerWeapon", "i", "i"));
	apiLua::addFunc(apiLua::LuaFuncStruct(getAmmo, "getPlayerAmmo", "i", "i"));
	apiLua::addFunc(apiLua::LuaFuncStruct(setFrozen, "setPlayerFrozen", "ib", ""));
	apiLua::addFunc(apiLua::LuaFuncStruct(debugPlayer, "debugPlayer", "ii", ""));
	apiLua::addFunc(apiLua::LuaFuncStruct(debugVehicle, "debugVehicle", "ii", ""));
	apiLua::addFunc(apiLua::LuaFuncStruct(disconnect, "disconnectPlayer", "i", ""));
	apiLua::addFunc(apiLua::LuaFuncStruct(getPing, "getPlayerPing", "ib", "i"));
	apiLua::addFunc(apiLua::LuaFuncStruct(getAnim, "getPlayerAnim", "i", "i"));
	apiLua::addFunc(apiLua::LuaFuncStruct(showDialogList, "showDialogList", "ii", ""));
	apiLua::addFunc(apiLua::LuaFuncStruct(setClothes, "setPlayerClothes", "iii", ""));
	apiLua::addFunc(apiLua::LuaFuncStruct(setProperty, "setPlayerProperty", "iii", ""));
	apiLua::addFunc(apiLua::LuaFuncStruct(forceAnim, "forcePlayerAnim", "issb", ""));
	apiLua::addFunc(apiLua::LuaFuncStruct(stopAnims, "stopPlayerAnims", "i", ""));
	apiLua::addFunc(apiLua::LuaFuncStruct(setKeyHook, "setPlayerKeyHook", "iib", ""));
	apiLua::addFunc(apiLua::LuaFuncStruct(getIp, "getPlayerIp", "i", "s"));
	apiLua::addFunc(apiLua::LuaFuncStruct(showBlip, "showBlipForPlayer", "iib", ""));
	apiLua::addFunc(apiLua::LuaFuncStruct(cam_setPos, "setPlayerCamPos", "idddi", ""));
	apiLua::addFunc(apiLua::LuaFuncStruct(cam_setLookAt, "setPlayerCamLookAt", "iddd", ""));
	apiLua::addFunc(apiLua::LuaFuncStruct(cam_attachOnPlayer, "attachCamOnPlayer", "ii", ""));
	apiLua::addFunc(apiLua::LuaFuncStruct(closeMods, "checkPlayerHacks", "i", ""));
	apiLua::addFunc(apiLua::LuaFuncStruct(checkSum, "playerCheckSum", "is", ""));
	apiLua::addFunc(apiLua::LuaFuncStruct(isObjectSpawned, "isObjectSpawnedForPlayer", "ii", "b"));
	apiLua::addFunc(apiLua::LuaFuncStruct(isVehicleSpawned, "isVehicleSpawnedForPlayer", "ii", "b"));
	apiLua::addFunc(apiLua::LuaFuncStruct(requestWeapons, "requestPlayerWeapons", "i", ""));
	apiLua::addFunc(apiLua::LuaFuncStruct(getWeaponsSize, "getPlayerWeapons", "i", "t"));
	apiLua::addFunc(apiLua::LuaFuncStruct(getRoomKey, "getPlayerRoomKey", "i", "i"));
	apiLua::addFunc(apiLua::LuaFuncStruct(playStreamPos, "playStreamAtPos", "isfff", ""));
	apiLua::addFunc(apiLua::LuaFuncStruct(playStream, "playStreamFrontend", "is", ""));
	apiLua::addFunc(apiLua::LuaFuncStruct(stopStreams, "stopPlayerStreams", "i", ""));
	apiLua::addFunc(apiLua::LuaFuncStruct(setArmor, "setPlayerArmor", "ii", ""));
	apiLua::addFunc(apiLua::LuaFuncStruct(getArmor, "getPlayerArmor", "i", "i"));
	apiLua::addFunc(apiLua::LuaFuncStruct(setMoney, "setPlayerCash", "ii", ""));
	apiLua::addFunc(apiLua::LuaFuncStruct(setDoorStat, "setDoorStatus", "iidddb", ""));
	apiLua::addFunc(apiLua::LuaFuncStruct(setAllDoorStat, "setKnownDoorStatus", "ib", ""));
	apiLua::addFunc(apiLua::LuaFuncStruct(getGame, "getPlayerGame", "i", "i"));
	apiLua::addFunc(apiLua::LuaFuncStruct(sendChatOptions, "sendChatOptions", "iii", ""));
	apiLua::addFunc(apiLua::LuaFuncStruct(createExplosion, "createExplosion", "ifffifbbf", ""));
	apiLua::addFunc(apiLua::LuaFuncStruct(forceSitNow, "forceSitNow", "i", ""));
	apiLua::addFunc(apiLua::LuaFuncStruct(setSitIdleAnim, "setSitIdleAnim", "issi", ""));
	apiLua::addFunc(apiLua::LuaFuncStruct(playSound, "playSound", "isi", ""));
	apiLua::addFunc(apiLua::LuaFuncStruct(stopSound, "stopSound", "ii", ""));
	apiLua::addFunc(apiLua::LuaFuncStruct(setPlayerDraw, "setPlayerDraw", "iibb", ""));
	apiLua::addFunc(apiLua::LuaFuncStruct(setPlayerHud, "setPlayerHud", "ibb", ""));
	apiLua::addFunc(apiLua::LuaFuncStruct(getPlayerSerials, "getPlayerSerials", "i", "a"));
	apiLua::addFunc(apiLua::LuaFuncStruct(getPlayerAim, "getPlayerAim", "i", "fff"));
	apiLua::addFunc(apiLua::LuaFuncStruct(setVehicleColForPlayer, "setVehicleColForPlayer", "iib", ""));
	apiLua::addFunc(apiLua::LuaFuncStruct(getPlayerClothes, "getPlayerClothes", "i", "a"));
	apiLua::addFunc(apiLua::LuaFuncStruct(getPlayerProperties, "getPlayerProperties", "i", "a"));

	apiLua::addFunc(apiLua::LuaFuncStruct(tsConnect, "tsConnect", "s", ""));
	apiLua::addFunc(apiLua::LuaFuncStruct(tsToggleVoice, "tsToggleVoice", "ib", ""));
	apiLua::addFunc(apiLua::LuaFuncStruct(tsAllowWhisper, "tsAllowVoiceTo", "iib", ""));
}