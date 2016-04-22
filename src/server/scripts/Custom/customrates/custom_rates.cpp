#include "ScriptMgr.h"
#include "Chat.h"
#include "Language.h"

class CustomRates
{
private:
	static int32 GetRateFromDB(const Player *player, CharacterDatabaseStatements statement)
	{
		PreparedStatement *stmt = CharacterDatabase.GetPreparedStatement(statement);
		stmt->setUInt32(0, player->GetGUID().GetCounter());
		PreparedQueryResult result = CharacterDatabase.Query(stmt);

		if (result)
			return static_cast<int32>((*result)[0].GetUInt32());

		return -1;
	}

	static void SaveRateToDB(const Player *player, uint32 rate, bool update, CharacterDatabaseStatements uStmt, CharacterDatabaseStatements iStmt)
	{
		if (update)
		{
			PreparedStatement *stmt = CharacterDatabase.GetPreparedStatement(uStmt);
			stmt->setUInt32(0, rate);
			stmt->setUInt32(1, player->GetGUID().GetCounter());
			CharacterDatabase.Execute(stmt);
		}
		else
		{
			PreparedStatement *stmt = CharacterDatabase.GetPreparedStatement(iStmt);
			stmt->setUInt32(0, player->GetGUID().GetCounter());
			stmt->setUInt32(1, rate);
			CharacterDatabase.Execute(stmt);
		}
	}
public:
	static void DeleteRateFromDB(ObjectGuid guid, CharacterDatabaseStatements statement)
	{
		PreparedStatement *stmt = CharacterDatabase.GetPreparedStatement(statement);
		stmt->setUInt32(0, guid.GetCounter());
		CharacterDatabase.Execute(stmt);
	}

	static int32 GetXpRateFromDB(const Player *player)
	{
		return GetRateFromDB(player, CHAR_SEL_INDIVIDUAL_XP_RATE);
	}

	static int32 GetLootRateFromDB(const Player *player)
	{
		return GetRateFromDB(player, CHAR_SEL_INDIVIDUAL_LOOT_RATE);
	}

	static void SaveXpRateToDB(const Player *player, uint32 rate, bool update)
	{
		SaveRateToDB(player, rate, update, CHAR_UPD_INDIVIDUAL_XP_RATE, CHAR_INS_INDIVIDUAL_XP_RATE);
	}

	static void SaveLootRateToDB(const Player *player, uint32 rate, bool update)
	{
		SaveRateToDB(player, rate, update, CHAR_UPD_INDIVIDUAL_LOOT_RATE, CHAR_INS_INDIVIDUAL_LOOT_RATE);
	}
};

class add_del_rates : public PlayerScript
{
public:
	add_del_rates() : PlayerScript("add_del_rates")
	{
	}

	void OnDelete(ObjectGuid guid)
	{
		CustomRates::DeleteRateFromDB(guid, CHAR_DEL_INDIVIDUAL_XP_RATE);
		CustomRates::DeleteRateFromDB(guid, CHAR_DEL_INDIVIDUAL_LOOT_RATE);
	}

	void OnLogin(Player *player)
	{
		// show custom XP rate on login
		int32 rate = CustomRates::GetXpRateFromDB(player);

		if (rate != -1 && player->getLevel() != sWorld->getIntConfig(CONFIG_MAX_PLAYER_LEVEL))
		{
			uint32 uRate = static_cast<uint32>(rate);
			player->SetCustomXpRate(uRate);

			if (sWorld->getBoolConfig(CONFIG_PLAYER_INDIVIDUAL_XP_RATE_SHOW_ON_LOGIN))
			{
				if (uRate)
					ChatHandler(player->GetSession()).PSendSysMessage("|CFF7BBEF7[Custom Rates]|r: Your XP rate was set to %u.", uRate);
				else
					ChatHandler(player->GetSession()).SendSysMessage("|CFF7BBEF7[Custom Rates]|r: Your XP rate was set to 0. You won't gain any XP anymore.");
			}
		}

		// show custom loot rate on login
		rate = CustomRates::GetLootRateFromDB(player);
		if (rate != -1)
		{
			uint32 uRate = static_cast<uint32>(rate);
			player->SetCustomLootRate(uRate);

			if (sWorld->getBoolConfig(CONFIG_PLAYER_INDIVIDUAL_LOOT_RATE_SHOW_ON_LOGIN))
			{
				if (uRate)
					ChatHandler(player->GetSession()).PSendSysMessage("|CFF7BBEF7[Custom Rates]|r: Your loot rate was set to %u.", uRate);
				else
					ChatHandler(player->GetSession()).SendSysMessage("|CFF7BBEF7[Custom Rates]|r: Your loot rate was set to 0. You won't be able to loot anything.");
			}
		}
	}
};

class custom_rate_commands : public CreatureScript
{
private:
	
public:
	custom_rate_commands() : CreatureScript("custom_rate_commands") { }

	bool OnGossipHello(Player *player, Creature *creature)
        {
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Changer de rates", GOSSIP_SENDER_MAIN, 1);
                player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
                return true;
        }
        bool OnGossipSelect(Player *player, Creature *creature, uint32 /*sender*/, uint32 action)
        {
                player->PlayerTalkClass->ClearMenus();
                switch(action)
                {
                case 1: // ...Back
                        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Passer en Rate x1", GOSSIP_SENDER_MAIN, 2);
                        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Passer en Rate x3", GOSSIP_SENDER_MAIN, 3);
                        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Passer en Rate x5", GOSSIP_SENDER_MAIN, 4);
                        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Passer en Rate x10", GOSSIP_SENDER_MAIN, 5);
                        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Passer en Rate x15", GOSSIP_SENDER_MAIN, 6);
                        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Passer en Rate de base", GOSSIP_SENDER_MAIN, 7);
						CharacterDatabase.PExecute("INSERT IGNORE INTO character_loot_rate (xp_rate, GUID) VALUES (2, %u)", player->GetGUID());
						CharacterDatabase.PExecute("INSERT IGNORE INTO character_xp_rate (xp_rate, GUID) VALUES (2, %u)", player->GetGUID());
                        player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
                        break;
				case 2: //Exp x1
						CharacterDatabase.PExecute("UPDATE character_loot_rate SET loot_rate=1 WHERE GUID=%u", player->GetGUID());
						CharacterDatabase.PExecute("UPDATE character_xp_rate SET xp_rate=1 WHERE GUID=%u", player->GetGUID());
						player->GetSession()->SendAreaTriggerMessage("Rate x1");
						uint32 uRate = 1;
						player->SetCustomLootRate(1);
						int32 rateFromDB = CustomRates::GetLootRateFromDB(player);
						if (rateFromDB == -1)
						CustomRates::SaveLootRateToDB(player, 1, false);
						else
						CustomRates::SaveLootRateToDB(player, 1, true);
                        player->CLOSE_GOSSIP_MENU();
						break;
				case 3: //Exp x3
						CharacterDatabase.PExecute("UPDATE character_loot_rate SET loot_rate=3 WHERE GUID=%u", player->GetGUID());
						CharacterDatabase.PExecute("UPDATE character_xp_rate SET xp_rate=3 WHERE GUID=%u", player->GetGUID());
						player->GetSession()->SendAreaTriggerMessage("Rate x3");
						uint32 uRate = 3;
						player->SetCustomLootRate(3);
						int32 rateFromDB = CustomRates::GetLootRateFromDB(player);
						if (rateFromDB == -1)
						CustomRates::SaveLootRateToDB(player, 3, false);
						else
						CustomRates::SaveLootRateToDB(player, 3, true);
                        player->CLOSE_GOSSIP_MENU();
						break;
				case 4: //Exp x5
						CharacterDatabase.PExecute("UPDATE character_loot_rate SET loot_rate=5 WHERE GUID=%u", player->GetGUID());
						CharacterDatabase.PExecute("UPDATE character_xp_rate SET xp_rate=5 WHERE GUID=%u", player->GetGUID());
						player->GetSession()->SendAreaTriggerMessage("Rate x5");
						uint32 uRate = 5;
						player->SetCustomLootRate(5);
						int32 rateFromDB = CustomRates::GetLootRateFromDB(player);
						if (rateFromDB == -1)
						CustomRates::SaveLootRateToDB(player, 5, false);
						else
						CustomRates::SaveLootRateToDB(player, 5, true);
                        player->CLOSE_GOSSIP_MENU();
						break;
				case 5: //Exp x10
						CharacterDatabase.PExecute("UPDATE character_loot_rate SET loot_rate=10 WHERE GUID=%u", player->GetGUID());
						CharacterDatabase.PExecute("UPDATE character_xp_rate SET xp_rate=10 WHERE GUID=%u", player->GetGUID());
						player->GetSession()->SendAreaTriggerMessage("Rate x10");
						uint32 uRate = 10;
						player->SetCustomLootRate(10);
						int32 rateFromDB = CustomRates::GetLootRateFromDB(player);
						if (rateFromDB == -1)
						CustomRates::SaveLootRateToDB(player, 10, false);
						else
						CustomRates::SaveLootRateToDB(player, 10, true);
                        player->CLOSE_GOSSIP_MENU();
						break;
				case 6: //Exp x15
						CharacterDatabase.PExecute("UPDATE character_loot_rate SET loot_rate=15 WHERE GUID=%u", player->GetGUID());
						CharacterDatabase.PExecute("UPDATE character_xp_rate SET xp_rate=15 WHERE GUID=%u", player->GetGUID());
						player->GetSession()->SendAreaTriggerMessage("Rate x15");
						uint32 uRate = 15;
						player->SetCustomLootRate(15);
						int32 rateFromDB = CustomRates::GetLootRateFromDB(player);
						if (rateFromDB == -1)
						CustomRates::SaveLootRateToDB(player, 15, false);
						else
						CustomRates::SaveLootRateToDB(player, 15, true);
                        player->CLOSE_GOSSIP_MENU();
						break;
				case 7: //Exp x2
						CharacterDatabase.PExecute("UPDATE character_loot_rate SET loot_rate=2 WHERE GUID=%u", player->GetGUID());
						CharacterDatabase.PExecute("UPDATE character_xp_rate SET xp_rate=2 WHERE GUID=%u", player->GetGUID());
						player->GetSession()->SendAreaTriggerMessage("Rate x2");
						uint32 uRate = 2;
						player->SetCustomLootRate(2);
						int32 rateFromDB = CustomRates::GetLootRateFromDB(player);
						if (rateFromDB == -1;
						CustomRates::SaveLootRateToDB(player, 2, false);
						else
						CustomRates::SaveLootRateToDB(player, 2, true);
                        player->CLOSE_GOSSIP_MENU();
						break;
                }
                return true;
        }
};

void Add_SC_Custom_Rates()
{
	new add_del_rates();
	new custom_rate_commands();
}