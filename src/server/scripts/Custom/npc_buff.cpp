#include "ScriptPCH.h"

	enum spells
	{
		BUFF_MARK_OF_THE_WILD		48469
		BUFF_THORNS					53307
		BUFF_ARCANE_INTELLECT		42955
		BUFF_BLESSING_OF_WISDOM		48938
		BUFF_BLESSING_OF_KINGS		25898
		BUFF_BLESSING_OF_SANCTUARY 	25899
		BUFF_BLESSING_OF_MIGHT		48932
		BUFF_DIVINE_SPIRIT			48073
		BUFF_POWER_WORD_FORTITUDE	48161
		BUFF_SHADOW_PROTECTION		48169
	};

	class npc_buff : public CreatureScript
	{
		public:
			npc_buff() : CreatureScript("npc_buff"){ }

			bool OnGossipHello(Player * Player, Creature * Creature)
			{
				if (player->IsInCombat())
				{
					player->GetSession()->SendNotification("You are in Combat");
					return true;
				}
				bool GossipHello_npc_buff(Player *player, Creature *_Creature)
				{
				player->ADD_GOSSIP_ITEM(8, "Mark of the Wild", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
				player->ADD_GOSSIP_ITEM(8, "Thorns", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
				player->ADD_GOSSIP_ITEM(2, "Arcane intellect", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
				player->ADD_GOSSIP_ITEM(3, "Blessing of Wisdom", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
				player->ADD_GOSSIP_ITEM(3, "Blessing of Kings", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
				player->ADD_GOSSIP_ITEM(3, "Blessing of Sanctuary", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6);
				player->ADD_GOSSIP_ITEM(3, "Blessing of Might", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 7);
				player->ADD_GOSSIP_ITEM(6, "Divine spirit", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 8);
				player->ADD_GOSSIP_ITEM(6, "Power word: Fortitude", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 9);
				player->ADD_GOSSIP_ITEM(6, "Shadow Protection", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 10);
				player->ADD_GOSSIP_ITEM(6, "Close", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 0);
				player->SEND_GOSSIP_MENU(1, _Creature->GetGUID());
					return true;
				}
				bool OnGossipSelect(Player * Player, Creature * Creature, uint32 /*uiSender*/, uint32 uiAction)
				{
					player->PlayerTalkClass->ClearMenus();
					switch (action)
				{
					
					{
					case GOSSIP_ACTION_INFO_DEF + 1: //Mark of the Wild (Rank 9)
						player->CLOSE_GOSSIP_MENU();
						_Creature->CastSpell(player, BUFF_MARK_OF_THE_WILD, false);
						break;
					case GOSSIP_ACTION_INFO_DEF + 2: //Thorns (Rank 8)
						player->CLOSE_GOSSIP_MENU();
						_Creature->CastSpell(player, BUFF_THORNS, false);
						break;
					case GOSSIP_ACTION_INFO_DEF + 3: //Arcane intellect (Rank 7)
						player->CLOSE_GOSSIP_MENU();
						_Creature->CastSpell(player, BUFF_ARCANE_INTELLECT, false);
						break;
					case GOSSIP_ACTION_INFO_DEF + 4: //Blessing of Wisdom (Rank 5)
						player->CLOSE_GOSSIP_MENU();
						_Creature->CastSpell(player, BUFF_BLESSING_OF_WISDOM, false);
						break;
					case GOSSIP_ACTION_INFO_DEF + 5: //Blessing of Kings
						player->CLOSE_GOSSIP_MENU();
						_Creature->CastSpell(player, BUFF_BLESSING_OF_KINGS, false);
						break;
					case GOSSIP_ACTION_INFO_DEF + 6: //Blessing of Sanctuary
						player->CLOSE_GOSSIP_MENU();
						_Creature->CastSpell(player, BUFF_BLESSING_OF_SANCTUARY, false);
						break;
					case GOSSIP_ACTION_INFO_DEF + 7: //Blessing of Might (Rank 10)
						player->CLOSE_GOSSIP_MENU();
						_Creature->CastSpell(player, BUFF_BLESSING_OF_MIGHT, false);
						break;
					case GOSSIP_ACTION_INFO_DEF + 8: //Divine spirit (Rank 6)
						player->CLOSE_GOSSIP_MENU();
						_Creature->CastSpell(player, BUFF_DIVINE_SPIRIT, false);
						break;
					case GOSSIP_ACTION_INFO_DEF + 9: //Power word: Fortitude (Rank 8)
						player->CLOSE_GOSSIP_MENU();
						_Creature->CastSpell(player, BUFF_POWER_WORD_FORTITUDE, false);
						break;
					case GOSSIP_ACTION_INFO_DEF + 10: //Shadow Protection (Rank 5)
						player->CLOSE_GOSSIP_MENU();
						_Creature->CastSpell(player, BUFF_SHADOW_PROTECTION, false);
						break;
					case GOSSIP_ACTION_INFO_DEF + 0: //Menu close
						player->CLOSE_GOSSIP_MENU();
						break;
					}
					return true;
				}

void AddSC_npc_buff()
{
new npc_buff();
}