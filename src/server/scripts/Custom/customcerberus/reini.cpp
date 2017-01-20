#include "Define.h"
#include "GossipDef.h"
#include "Item.h"
#include "Language.h"
#include "Player.h"
#include "ScriptedGossip.h"
#include "ScriptMgr.h"
#include "Spell.h"
#include "Transmogrification.h"
class Reini_NPC : public CreatureScript
{
public:
    Reini_NPC() : CreatureScript("Reini_NPC")
    {
    }
 
    bool OnGossipHello(Player *player, Creature *creature)
    {
        player->PlayerTalkClass->ClearMenus();
        AddGossipItemFor(player, 0, "Reinitialiser les instances", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
        SendGossipMenuFor(player, sTransmogrification->SetNpcReiniText, creature->GetGUID());
        return true;
    }
 
   bool OnGossipSelect(Player *player, Creature *creature, uint32 /*sender*/, uint32 action)
    {
        if (!player)
            return true;
 
        switch (action)
        {
            {
        case GOSSIP_ACTION_INFO_DEF + 1:
            for (uint8 i = 0; i < MAX_DIFFICULTY; ++i)
            {
                Player::BoundInstancesMap &binds = player->GetBoundInstances(Difficulty(i));
                for (Player::BoundInstancesMap::iterator itr = binds.begin(); itr != binds.end();)
                {
                    player->UnbindInstance(itr, Difficulty(i));
                }
            }
            player->GetSession()->SendAreaTriggerMessage("Vos ID d'instances sont supprimer");
            CloseGossipMenuFor(player);
            break;
            }
            return true;
        }
    }
 
};
 
void AddSC_Reini_NPC()
{
    new Reini_NPC();
}