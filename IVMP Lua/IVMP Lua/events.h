#include "apiPlayer.h"

namespace events
{
	bool onPlayerConnect(int playerid);
	bool onPlayerCredentials(int playerid);
	void onPlayerLeft(int playerid, int reason);
	void onPlayerAfk(int playerid, bool status);

	void onPlayerEnteredVehicle(int playerid, int vehicleId, int seatId);
	void onPlayerExitVehicle(int playerid, int vehicleId, int seatId);
	void onPlayerRequestVehicleEntry(int playerid, int vehicleId, int seatId, bool carjack);

	bool onPlayerSwapWeapons(int playerid, int weapon, int ammo);
	bool onPlayerWeaponsArrived(int playerid);

	void onPlayerChat(int playerid, const char* chat);

	bool onPlayerSpawn(int playerid);
	void onPlayerDeath(int playerid, int agentType, int agentId);
	void onPlayerHpChange(int playerid, int agentType, int agentId, int bone);
	void onPlayerArmourChange(int playerid, int agentType, int agentId, int bone);

	void onPlayerEnterCheckPoint(int playerid, int checkPointId);
	void onPlayerExitCheckPoint(int playerid, int checkPointId);

	void onPlayerDialogResponse(int playerid, unsigned int dialogId, int buttonId, int rowId, int customId);

	void onPlayerCheckSumArrive(int playerid, const char* path, unsigned int sum);
	void onPlayerHacks(int playerid, bool h);
	void onKeyPress(apiPlayer::player& player, unsigned int virtualKey, bool keyUp);

	void onChatUpdate(int playerid, int chat_id, int chat_op);

	bool onTeamSpeak(int playerid, int type, int msg);

	void npcStopped(int npc, bool willRepeat);

	void onPlayerSpawnEntity(int playerid, int spawned, int agentType, int agentId);
}