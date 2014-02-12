# Copyright (C) 2008-2014 TrinityCore <http://www.trinitycore.org/>
#
# This file is free software; as a special exception the author gives
# unlimited permission to copy and/or distribute it, with or without
# modifications, as long as this notice is preserved.
#
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY, to the extent permitted by law; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

set(scripts_STAT_SRCS
  ${scripts_STAT_SRCS}
  Custom/PlayerScript/OnLogin_PlayerScript.cpp
  Custom/PlayerScript/OnSave_PlayerScript.cpp
  Custom/PlayerScript/OnKill_PlayerScript.cpp
  Custom/PlayerScript/OnDuel1_PlayerScript.cpp
  Custom/OnKillstreak_PlayerScript.cpp
  
  Custom/WorldScript/OnUpdate_WorldScript.cpp
  
  Custom/CreatureScript/Choose_Gear_NPC_CreatureScript.cpp
  Custom/CreatureScript/Teleporter_NPC_CreatureScript.cpp
  Custom/CreatureScript/Enchanter_NPC_CreatureScript.cpp
  Custom/CreatureScript/Enchanter_NPC_CreatureScript1.cpp
  Custom/CreatureScript/Professions_NPC_CreatureScript.cpp
  
  Custom/Transmogrification.cpp
  Custom/Transmogrification.h
  Custom/Transmogrifier.cpp
  Custom/npc_symbolixdev.cpp
  Custom/multi.cpp
  Custom/Change.cpp
)

message("  -> Prepared: Custom")
