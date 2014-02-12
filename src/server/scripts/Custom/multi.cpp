/*
<--------------------------------------------------------------------------->
- Developer(s): Ghostcrawler336
- Complete: %0
- ScriptName: 'Multi Vendor'
- Comment: N/A
<--------------------------------------------------------------------------->

class starter_gear : public CreatureScript
{
public:
    starter_gear() : CreatureScript("starter_gear") { }
 
        bool OnGossipHello(Player* player, Creature* creature)
               
        {
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Main Set", GOSSIP_SENDER_MAIN, 1);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Off Set", GOSSIP_SENDER_MAIN, 2);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Weapons", GOSSIP_SENDER_MAIN, 3);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Gems", GOSSIP_SENDER_MAIN, 4);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Glyphs", GOSSIP_SENDER_MAIN, 5);
				player->SEND_GOSSIP_MENU(1, creature->GetGUID());
                return true;   
        } 
 
       
        bool OnGossipSelect(Player* player, Creature* creature, uint32 /* sender */, uint32 actions)
	/*	{
			player->PlayerTalkClass->ClearMenus();
             WorldSession * PGS = player->GetSession();
			switch(actions)
		{
			case 1:
				PGS->SendListInventory(creature->GetGUID(), 500120);
			break;
  
			case 2:
				PGS->SendListInventory(creature->GetGUID(), 500120);
			break;

			case 3:
				PGS->SendListInventory(creature->GetGUID(), 500120);
			break;

			case 4:
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Red", GOSSIP_SENDER_MAIN, 11);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Blue", GOSSIP_SENDER_MAIN, 12);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Yellow", GOSSIP_SENDER_MAIN, 13);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Green", GOSSIP_SENDER_MAIN, 14);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Purple", GOSSIP_SENDER_MAIN, 15);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Orange", GOSSIP_SENDER_MAIN, 16);
			break;
			
			case 5:
				if (player->getClass() == CLASS_WARRIOR)
				  PGS->SendListInventory(creature->GetGUID(), 500111);
				else if (CLASS_PALADIN)
				  PGS->SendListInventory(creature->GetGUID(), 500068);
				else if (CLASS_DEATH_KNIGHT)
				   PGS->SendListInventory(creature->GetGUID(), 500026);
				else if (CLASS_DRUID)
				   PGS->SendListInventory(creature->GetGUID(), 500027);
				else if (CLASS_HUNTER)
					PGS->SendListInventory(creature->GetGUID(), 500046);
				else if (CLASS_MAGE)
					PGS->SendListInventory(creature->GetGUID(), 500057);
				else if (CLASS_ROGUE)
					PGS->SendListInventory(creature->GetGUID(), 500095);
				else if (CLASS_SHAMAN)
					PGS->SendListInventory(creature->GetGUID(), 500097);
				else if (CLASS_WARLOCK)
					PGS->SendListInventory(creature->GetGUID(), 500110);
				else if (CLASS_PRIEST)
					PGS->SendListInventory(creature->GetGUID(), 500113);
				break;


			case 11: // Red gems
				{
					 PGS->SendListInventory(creature->GetGUID(), 500111);
				}break;

			case 12: // Blue gems
				{
					 PGS->SendListInventory(creature->GetGUID(), 500111);
				}break;

			case 13: // Yellow gems
				{
					 PGS->SendListInventory(creature->GetGUID(), 500111);
				}break;

			case 14: // Green gems
				{
				    PGS->SendListInventory(creature->GetGUID(), 500111);
				}break;

			case 15: // Purple gems
				{
					 PGS->SendListInventory(creature->GetGUID(), 500111);
				}break;

			case 16: // Orange gems
				{
					 PGS->SendListInventory(creature->GetGUID(), 500111);
				}break;



		}
		
		}
};
 
void AddSC_starter_gear()
{
    new starter_gear;
}
*/