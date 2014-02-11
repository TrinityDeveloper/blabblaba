
 #include "ScriptPCH.h"
 
static const uint32 buffIdstools[] = { 421562, 1126, 20217, };
static const uint32 healstools[] = { 633, 774, 139 }; //for test
 
class npc_symbolixdev : public CreatureScript
{
public:
    npc_symbolixdev() : CreatureScript("npc_symbolixdev") { }
 
    bool OnGossipHello(Player * player, Creature * creature)
    {
        if (player->IsInCombat())
        {
            player->GetSession()->SendNotification("You are in Combat");
            return true;
        }
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Heal me", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Buff me", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+3);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Reset my Talents", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+4);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Remove my Sickness", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+5);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Reset my CDs", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+6);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Repair Items", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+7);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Reset Instances", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+9);
        player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
        return true;
    }
 
    bool OnGossipSelect(Player* player, Creature * creature, uint32 sender, uint32 actions)
    {
        player->PlayerTalkClass->ClearMenus();
 
        if (sender != GOSSIP_SENDER_MAIN || actions <= GOSSIP_ACTION_INFO_DEF)
        {
            player->CLOSE_GOSSIP_MENU();
            return true;
        }
 
        switch (actions)
        {
		
		case GOSSIP_ACTION_INFO_DEF+2:
            for (int i = 0; i < sizeof(healstools) / sizeof(*healstools); ++i)
                player->CastSpell(player, healstools[i]);
            break;
 
		
        case GOSSIP_ACTION_INFO_DEF+3:
            for (int i = 0; i < sizeof(buffIdstools) / sizeof(*buffIdstools); ++i)
                player->CastSpell(player, buffIdstools[i]);
            break;
 
        case GOSSIP_ACTION_INFO_DEF+4: // Reset Talents
            player->resetTalents(true);
            player->SendTalentsInfoData(false);
            player->GetSession()->SendAreaTriggerMessage("Your talents has been reset.", player->GetGUID(), true);
            break;
 
        case GOSSIP_ACTION_INFO_DEF+5: //Remove my siccness
	   if (player->HasAura(15007))
	       player->RemoveAura(15007);
   	    creature->MonsterWhisper("Your Sickness Removed", player->GetGUID(), true);
	    break;
 
		case GOSSIP_ACTION_INFO_DEF+6; // reset my CD'S
			player->SetHealth(player->GetMaxHealth());
			player->SetMana(player->GetMaxMana());
			player->RemoveAllSpellCooldown();
			creature->MonsterWhisper("Your CD's is Reset.", player->GetGUID(), true);
			break;
 
		case GOSSIP_ACTION_INFO_DEF+7; // repair my items
			player->DurabilityRepairAll(false, 0, false);
			creature->MonsterWhisper("Your item's Repaired.", player->GetGUID(), true);
			break;
 
        case GOSSIP_ACTION_INFO_DEF+9: // Reset all Instances For PvE 
            for (uint8 i = 0; i < MAX_DIFFICULTY; ++i)
            {
                Player::BoundInstancesMap &binds = player->GetBoundInstances(Difficulty(i));
                for (Player::BoundInstancesMap::iterator itr = binds.begin(); itr != binds.end();)
                {
                    player->UnbindInstance(itr, Difficulty(i));
                }
            }
            break;
 
        default: // Close
            player->CLOSE_GOSSIP_MENU();
            return true;
        }
 
        OnGossipHello(player, creature);
        return true;
    }
};
 
void AddSC_npc_symbolixdev()
{
    new npc_symbolixdev;
}