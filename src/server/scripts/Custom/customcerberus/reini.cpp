#include "Define.h"
#include "GossipDef.h"
#include "Item.h"
#include "Player.h"
#include "ScriptedGossip.h"
#include "ScriptMgr.h"
#include "Spell.h"
class Reini_NPC : public CreatureScript
{
public:
        Reini_NPC() : CreatureScript("Reini_NPC") { }
 
        bool OnGossipHello(Player *player, Creature *creature)
        {
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Reinitialiser les instances", GOSSIP_SENDER_MAIN, 73);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Au revoir", GOSSIP_SENDER_MAIN, 74);
                player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
                return true;
        }
        bool OnGossipSelect(Player *player, Creature *creature, uint32 /*sender*/, uint32 action)
        {
                player->PlayerTalkClass->ClearMenus();
                switch(action)
                {
                case 2: // Reset Instances
                        for (uint8 i = 0; i < MAX_DIFFICULTY; ++i)
                        {
                                Player::BoundInstancesMap &binds = player->GetBoundInstances(Difficulty(i));
                                for (Player::BoundInstancesMap::iterator itr = binds.begin(); itr != binds.end();)
                                {
                                        player->UnbindInstance(itr, Difficulty(i));
                                }
                        }
						player->GetSession()->SendAreaTriggerMessage("Vos ID d'instances sont supprimer");
                        player->CLOSE_GOSSIP_MENU();
                        break;
                case 73: // ...Back
                        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Reinitialiser les instances", GOSSIP_SENDER_MAIN, 2);
                        player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
                        break;
				case 74: // ...Back
                        player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
						player->CLOSE_GOSSIP_MENU();
                        break;
                }
                return true;
        }
};
 
void AddSC_Reini_NPC()
{
        new Reini_NPC();
}
