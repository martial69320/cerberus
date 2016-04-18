/*
 * Copyright (C) 2008-2016 TrinityCore <http://www.trinitycore.org/>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

// This is where scripts' loading functions should be declared:
void AddSC_Transmogrification();
void AddSC_GOMove_commandscript();
void AddSC_LearnSpellsOnLevelUp();
void AddSC_script_store();
void AddSC_Reini_NPC();
void AddSC_arena_spectator_script();
void Add_SC_Custom_Rates();
// The name of this function should match:
// void Add${NameOfDirectory}Scripts()
void AddCustomScripts()
{
    AddSC_Transmogrification();
	AddSC_GOMove_commandscript();
	AddSC_LearnSpellsOnLevelUp();
	AddSC_script_store();
	AddSC_Reini_NPC();
	AddSC_arena_spectator_script();
	Add_SC_Custom_Rates();
}
