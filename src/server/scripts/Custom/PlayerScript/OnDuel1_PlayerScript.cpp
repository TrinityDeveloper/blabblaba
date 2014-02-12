#include "scriptPCH.h"
#include "MapManager.h"
#include "Chat.h"
#include "Pet.h"
#include "Config.h"
#include "WorldSession.h"
#include "World.h"

/* SQL (Only if you use Rating System) (Characters database)
ALTER TABLE `characters`
ADD COLUMN `duelW` int(10) UNSIGNED NOT NULL DEFAULT '0',
ADD COLUMN `duelL` int(10) UNSIGNED NOT NULL DEFAULT '0',
ADD COLUMN `duelR` int(10) UNSIGNED NOT NULL DEFAULT '1000';
*/

/* WorldConf (At the end of the file) 
# Duel_Reward.Cata_User
#        Default:     0 - (Disabled)
#                     1 - (Enabled)

Duel_Reward.Cata_User = 0

# Duel_Reward.Wotlk_User
#        Default:     0 - (Disabled)
#                     1 - (Enabled)

Duel_Reward.Wotlk_User = 0

# Duel_Reward.Rating
#        Default:     0 - (Disabled)
#                     1 - (Enabled)

Duel_Reward.Rating = 0

# Duel_Reward.Security
#        Default:     1 - (Enabled)
#                     0 - (Disabled)

Duel_Reward.Security = 1

# Duel_Phasing.Activation
#        Default:     0 - (Disabled)
#                     1 - (Enabled)

Duel_Phasing.Activation = 0
*/

/*
Ultimate Duel Script (Reward/Rating/Phasing/Security/Zoned & Reset)
Author : Philippe
Version : V1.3
Release Date : 14/01/14
Script Complete : 100 %
Version : 3.3.5 & 4.3.4
TrinityCore based.
Tested on 4.3.4 Works Well

Note :
-Reward Part is explain you need to read. 
-For the Rating system please use SQL given. You can add a Top for you're website or create a rating npc. 

-Phasing system isn't done by me, Credits go to Deathmane1337 (Ac-Web) & Rewrite by Rochet & Tommy (EmuDevs)
Rochet & Tommy (EmuDevs) : 
http://emudevs.com/showthread.php/2316-new-phaseing-out-duel-dont-work-100?highlight=duel
http://emudevs.com/showthread.php/2282-phase-out-dueling-error/page2
*/

// Need both to work.
enum Zone_ID
{
	Zone_ID_1 = 12 // Change Zone ID
};

enum Area_ID
{
	Area_ID_1 = 12 // Change Area ID
};

#define Item_Reward_ID 241 // Currency ID For Cata User Or Item ID For Wotlk

#define Token_Winner 3 // Reward Count (Winner)
#define Token_loser 1 // Reward Count (Loser)


// Rating Info Setup Config
void RatingInfo(Player* player)
{
	if(sConfigMgr->GetBoolDefault("Duel_Reward.Rating", 1))
	{
		QueryResult result = CharacterDatabase.PQuery("SELECT duelW,duelL,duelR FROM characters WHERE guid = '%u'", player->GetGUID());
		if(!result)
			return;

		Field * fields = NULL;
		do
		{
			fields = result->Fetch();
			uint32 duelW = fields[0].GetUInt32();
			uint32 duelL = fields[1].GetUInt32();
			uint32 duelR = fields[2].GetUInt32();
			char msg[250];
			snprintf(msg, 250, "[System Information] - [Duel Stats] : |cffFFFF00%u |cFF90EE90Duel win & |cffFFFF00%u |cFF90EE90Duel lose  |cffff6060[Rating] : |cffFFFF00%u \n", duelW,duelL,duelR);					
			ChatHandler(player->GetSession()).PSendSysMessage(msg);
		}
		while(result->NextRow());
	}
}

class Duel_Reset : public PlayerScript
{
public:
	Duel_Reset() : PlayerScript("Duel_Reset") {}

	void RevivePlayer(Player* player)
	{
		player->SetHealth(player->GetMaxHealth());
		if(player->getPowerType() == POWER_MANA)
			player->SetPower(POWER_MANA, player->GetMaxPower(POWER_MANA));
		if(player->getPowerType() == POWER_ENERGY)
			player->SetPower(POWER_ENERGY, player->GetMaxPower(POWER_ENERGY));
	}

	void OnDuelStart(Player *player, Player *plTarget)
	{
		// Duel Start Reset (Hp/Mana etc)	
		RevivePlayer(player);
		RevivePlayer(plTarget);
		player->SetPower(POWER_RAGE, 0);
		plTarget->SetPower(POWER_RAGE, 0);
		player->SetPower(POWER_RUNIC_POWER, 0);
		plTarget->SetPower(POWER_RUNIC_POWER, 0);

		if(sConfigMgr->GetBoolDefault("Duel_Reward.Rating", 1))
		{
			// Rating checkup
			RatingInfo(player);
			RatingInfo(plTarget);
		}
	}	

	void OnDuelEnd(Player *player, Player * plTarget, DuelCompleteType type)
	{
		//Removing all Cooldown	
		player->RemoveAllSpellCooldown();
		plTarget->RemoveAllSpellCooldown();
		// Duel Reset (Hp/Mana etc)	
		RevivePlayer(player);
		RevivePlayer(plTarget);
		// Stopping Combat (Auto Hit/Cast/Range Auto Hit) Break (Useful) 		
		player->CombatStop();
		plTarget->CombatStop();

		player->InterruptSpell(CURRENT_AUTOREPEAT_SPELL); // break Auto Shot and auto hit
		plTarget->InterruptSpell(CURRENT_CHANNELED_SPELL);  // break channelled spells

		player->AttackStop();
		plTarget->AttackStop();
	}

};

class Duel_Token_Reward : public PlayerScript
{
public:
	Duel_Token_Reward() : PlayerScript("Duel_Token_Reward") { }

	void OnDuelEnd(Player *winner, Player *looser, DuelCompleteType type)
	{
		//Zone & Area Check Please change value in enum.
		if ((winner->GetZoneId() == Zone_ID_1 && looser->GetZoneId() == Zone_ID_1 || winner->GetAreaId() == Area_ID_1 &&  looser->GetAreaId() == Area_ID_1) && type == DUEL_WON)
		{
			if(sConfigMgr->GetBoolDefault("Duel_Reward.Security", 1))
			{
				// Level Check if player is not MaxLevel (80+) 
				if (winner->getLevel() >= 1 && looser->getLevel() <= 79 && (type == DUEL_WON || type == DUEL_INTERRUPTED || type == DUEL_FLED))
				{
					return;
				}
				// Check Latency of both (Not Really needed) 
				if (looser->GetSession()->GetLatency() > 350 && (type == DUEL_WON || type == DUEL_INTERRUPTED || type == DUEL_FLED))
				{
					ChatHandler(winner->GetSession()).PSendSysMessage("|cFFFFFC00[System]|cFF00FFFF  !! ALERT !! One of you has a latency superior to 350");
					ChatHandler(looser->GetSession()).PSendSysMessage("|cFFFFFC00[System]|cFF00FFFF  !! ALERT !! One of you has a latency superior to 350");
					return;
				}
				// Used if player didn't reach less than 10 life. 
				if (looser->GetHealth() > 10)
				{
					ChatHandler(looser->GetSession()).PSendSysMessage("|cFFFFFC00[System]|cFF00FFFF No one killed the other !");
					ChatHandler(winner->GetSession()).PSendSysMessage("|cFFFFFC00[System]|cFF00FFFF No one killed the other !");
				}
				// Used For Test Versus GM
				if (looser->GetSession()->GetSecurity() >= 2 && (type == DUEL_WON || type == DUEL_INTERRUPTED || type == DUEL_FLED))
				{
					ChatHandler(winner->GetSession()).PSendSysMessage("|cFFFFFC00[System]|cFF00FFFF You Can't Claim Reward When you're versus a GameMaster !");
					ChatHandler(looser->GetSession()).PSendSysMessage("|cFFFFFC00[System]|cFF00FFFF You Can't Claim Reward When you're versus a GameMaster !" );
					return;
				}
				if (winner->GetSession()->GetSecurity() >= 2 && (type == DUEL_WON || type == DUEL_INTERRUPTED || type == DUEL_FLED))
				{
					ChatHandler(winner->GetSession()).PSendSysMessage("|cFFFFFC00[System]|cFF00FFFF You Can't Claim Reward When you're versus a GameMaster !");
					ChatHandler(looser->GetSession()).PSendSysMessage("|cFFFFFC00[System]|cFF00FFFF You Can't Claim Reward When you're versus a GameMaster !");
					return;
				}
				// Used for Cata user if player doesn't have enough gear equipped based on (Stamina/life)
				// *Could be adapted for Wotlk Users. 
				if (looser->GetStat(STAT_STAMINA) < 4000 && type == DUEL_WON)
				{
					ChatHandler(winner->GetSession()).PSendSysMessage("|cFFFFFC00[Cheating System]|cFF00FFFF The player you are fighting doesn't have enough gear equipped !");
					ChatHandler(looser->GetSession()).PSendSysMessage("|cFFFFFC00[Cheating System]|cFF00FFFF you don't have enough gear equipped  !");
					return;
				}
				// Used for Local Connections, same IP
				if (winner->GetSession()->GetRemoteAddress() == looser->GetSession()->GetRemoteAddress())
				{
					ChatHandler(winner->GetSession()).SendGlobalGMSysMessage("|cFFFFFC00[Cheating System]|cFF00FFFF A player is trying to cheat in duel Area !");
					ChatHandler(winner->GetSession()).PSendSysMessage("|cFFFFFC00[Cheating System]|cFF00FFFF you can't claim reward versus a same ip address !");
					ChatHandler(looser->GetSession()).PSendSysMessage("|cFFFFFC00[Cheating System]|cFF00FFFF you can't claim reward versus a same ip address !");
				}
			}
			//If everything is passed then reward will be. 
			else 
			{
			//To make it work please make sure the worldserver.conf is correctly configurate
			// Start : If you are a WOTLK User delete between Start & Stop or comment it with /**/
				/*--------------Cataclysm Users------------*/
				if(sConfigMgr->GetBoolDefault("Duel_Reward.Cata_User", 1))
				{
					winner->ModifyCurrency(Item_Reward_ID, Token_Winner, true,true);
					looser->ModifyCurrency(Item_Reward_ID, Token_loser, true,true);
				}
				// STOP 
				/*----------------Wotlk Users---------------*/ 
				if(sConfigMgr->GetBoolDefault("Duel_Reward.Wotlk_User", 1))
				{
					winner->AddItem(Item_Reward_ID, Token_Winner);
					looser->AddItem(Item_Reward_ID, Token_loser);
				}

				/*Duel Rating*/
				//Duel Ratio, Win/lose 
				if(sConfigMgr->GetBoolDefault("Duel_Reward.Rating", 1))
				{
					//Duel Rating, Win/lose (Change Points Manually)
					CharacterDatabase.PExecute("UPDATE characters SET duelW = (duelW+1), duelR = (duelR+14) WHERE guid = '%u'", winner->GetGUID());
					CharacterDatabase.PExecute("UPDATE characters SET duelL = (duelL+1), duelR = (duelR-7) WHERE guid = '%u'", looser->GetGUID());
					//Duel Announcement, Win/lose (Change Points Manually.
					ChatHandler(winner->GetSession()).PSendSysMessage("|cFFFFFC00[System Information]|cFF00FFFF Well done you won 14 Points !");
					ChatHandler(looser->GetSession()).PSendSysMessage("|cFFFFFC00[System Information]|cFF00FFFF Ow you lose 7 Points !");
				}
				winner->SaveToDB();
				looser->SaveToDB();
			}
		}
	}
};

class PhasedDueling : public PlayerScript
{
public:
	PhasedDueling() : PlayerScript("PhasedDueling") { }

	void OnDuelStart(Player* firstplayer, Player* secondplayer)
	{
		if(sConfigMgr->GetBoolDefault("Duel_Phasing.Activation", 1))
		{
			 Map* map = firstplayer->GetMap();
                uint32 usedPhases = 0; // used phases
                Map::PlayerList const& players = map->GetPlayers();
                for (Map::PlayerList::const_iterator iter = players.begin(); iter != players.end(); ++iter)
                {
                        Player* check = iter->GetSource();
                        if (!check || !check->GetSession())
                                continue;
                        usedPhases |= check->GetPhaseMask(); // insert player's phases to used phases
                }
 
                for (uint32 phase = 2; phase <= ULONG_MAX/2; phase *= 2) // loop all unique phases
                {
                        if (usedPhases & phase) // If phase in use
                                continue;
 
                        firstplayer->SetPhaseMask(phase, true);
                        secondplayer->SetPhaseMask(phase, true);
                        if (GameObject* go = map->GetGameObject(firstplayer->GetUInt64Value(PLAYER_DUEL_ARBITER)))
                                go->SetPhaseMask(phase, true);
 
                        return;
                }
                // Could not phase pet :(
		}
	}

	// Restore phases
	void OnDuelEnd(Player* firstplayer, Player* secondplayer, DuelCompleteType type)
	{
		if(sConfigMgr->GetBoolDefault("Duel_Phasing.Activation", 1))
		{
			{
				firstplayer->SetPhaseMask(GetPhase(firstplayer), true);
                if (Pet* pet = firstplayer->GetPet())
                        pet->SetPhaseMask(GetPhase(firstplayer), true);
                secondplayer->SetPhaseMask(GetPhase(secondplayer), true);
                if (Pet* pet = secondplayer->GetPet())
                        pet->SetPhaseMask(GetPhase(secondplayer), true);
			}
		}
	}

	// Attempt in storing the player phase with spell phases included.
	uint32 GetPhase(Player* player) const
	{
		if(sConfigMgr->GetBoolDefault("Duel_Phasing.Activation", 1))
		{
			if (player->IsGameMaster())
                        return uint32(PHASEMASK_ANYWHERE);
 
                // GetPhaseMaskForSpawn copy-paste
                uint32 phase = PHASEMASK_NORMAL;
                Player::AuraEffectList const& phases = player->GetAuraEffectsByType(SPELL_AURA_PHASE);
                if (!phases.empty())
                        phase = phases.front()->GetMiscValue();
                if (uint32 n_phase = phase & ~PHASEMASK_NORMAL)
                        return n_phase;

		}
		return PHASEMASK_NORMAL;
	}
};

void AddSC_Reset()
{
	new Duel_Token_Reward();
	new Duel_Reset();
	new PhasedDueling();
}