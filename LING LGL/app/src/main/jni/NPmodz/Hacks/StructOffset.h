#pragma once
#include "NPmodz/IL2CppSDKGenerator/stdafx.h"
#include "NPmodz/IL2CppSDKGenerator/il2cpp_kr.h"

#pragma once


#define Camera_get_main (uintptr_t) IL2Cpp::Il2CppGetMethodOffset(OBFUSCATE("UnityEngine.dll"), OBFUSCATE("UnityEngine"), OBFUSCATE("Camera"), OBFUSCATE("get_main"), 0)
#define Camera_WorldToScreenPoint (uintptr_t) IL2Cpp::Il2CppGetMethodOffset(OBFUSCATE("UnityEngine.dll"), OBFUSCATE("UnityEngine"), OBFUSCATE("Camera"), OBFUSCATE("WorldToScreenPoint"), 1)
#define Camera_get_fieldOfView (uintptr_t) IL2Cpp::Il2CppGetMethodOffset(OBFUSCATE("UnityEngine.dll"), OBFUSCATE("UnityEngine"), OBFUSCATE("Camera"), OBFUSCATE("get_fieldOfView"), 0)
#define Camera_set_fieldOfView (uintptr_t) IL2Cpp::Il2CppGetMethodOffset(OBFUSCATE("UnityEngine.dll"), OBFUSCATE("UnityEngine"), OBFUSCATE("Camera"), OBFUSCATE("set_fieldOfView"), 1)
#define Screen_set_Resolution (uintptr_t) IL2Cpp::Il2CppGetMethodOffset(OBFUSCATE("UnityEngine.dll"), OBFUSCATE("UnityEngine"), OBFUSCATE("Screen"), OBFUSCATE("SetResolution"), 3)

void *get_main() {
    return reinterpret_cast<void *(__fastcall *)()>(Camera_get_main)();
}

Vector3 WorldToScreen(Vector3 position) {
    return reinterpret_cast<Vector3(__fastcall *)(void *, Vector3)>(Camera_WorldToScreenPoint)(get_main(), position);
}

float get_fieldOfView() {
    return reinterpret_cast<float(__fastcall *)(void *)>(Camera_get_fieldOfView)(get_main());
}

void *set_fieldOfView(float value) {
    return reinterpret_cast<void *(__fastcall *)(void *, float)>(Camera_set_fieldOfView)(get_main(), value);
}

//Class LogicBattleManager
#define LogicBattleManager_GetBattleState (uintptr_t) IL2Cpp::Il2CppGetMethodOffset("Assembly-CSharp.dll", "", "LogicBattleManager", "GetBattleState")

int GetBattleState(void* instance) {
	return reinterpret_cast<int(__fastcall *)(void*)>(LogicBattleManager_GetBattleState)(instance);
}

//Class SystemData
#define SystemData_m_uiID (uintptr_t) IL2Cpp::Il2CppGetStaticFieldOffset("Assembly-CSharp.dll","","SystemData","m_uiID")

#define SystemData_GetBattlePlayerInfo (uintptr_t) IL2Cpp::Il2CppGetMethodOffset("Assembly-CSharp.dll", "", "SystemData", "GetBattlePlayerInfo")


//Class SystemData.RoomData
#define SystemData_RoomData_iCamp (uintptr_t) IL2Cpp::Il2CppGetFieldOffset("Assembly-CSharp.dll", "", "SystemData/RoomData", "iCamp")
#define SystemData_RoomData__sName (uintptr_t) IL2Cpp::Il2CppGetFieldOffset("Assembly-CSharp.dll", "", "SystemData/RoomData", "_sName")
#define SystemData_RoomData__steamSimpleName (uintptr_t) IL2Cpp::Il2CppGetFieldOffset("Assembly-CSharp.dll", "", "SystemData/RoomData", "_steamSimpleName")
#define SystemData_RoomData__steamName (uintptr_t) IL2Cpp::Il2CppGetFieldOffset("Assembly-CSharp.dll", "", "SystemData/RoomData", "_steamName")
#define SystemData_RoomData_uiRankLevel (uintptr_t) IL2Cpp::Il2CppGetFieldOffset("Assembly-CSharp.dll", "", "SystemData/RoomData", "uiRankLevel")
#define SystemData_RoomData_iMythPoint (uintptr_t) IL2Cpp::Il2CppGetFieldOffset("Assembly-CSharp.dll", "", "SystemData/RoomData", "iMythPoint")
#define SystemData_RoomData_heroid (uintptr_t) IL2Cpp::Il2CppGetFieldOffset("Assembly-CSharp.dll", "", "SystemData/RoomData", "heroid")
#define SystemData_RoomData_summonSkillId (uintptr_t) IL2Cpp::Il2CppGetFieldOffset("Assembly-CSharp.dll", "", "SystemData/RoomData", "summonSkillId")
#define SystemData_RoomData_lUid (uintptr_t) IL2Cpp::Il2CppGetFieldOffset("Assembly-CSharp.dll", "", "SystemData/RoomData", "lUid")
#define SystemData_RoomData_uiZoneId (uintptr_t) IL2Cpp::Il2CppGetFieldOffset("Assembly-CSharp.dll", "", "SystemData/RoomData", "uiZoneId")


//Class BattleBridge
#define BattleBridge_bStartBattle (uintptr_t) IL2Cpp::Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE(""), OBFUSCATE("BattleBridge"), OBFUSCATE("bStartBattle"))
#define BattleBridge_SetMapEntityIconPos (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE(""), OBFUSCATE("BattleBridge"), OBFUSCATE("SetMapEntityIconPos"), 3)

//Class BattleManager
#define BattleManager_m_LocalPlayerShow (uintptr_t) IL2Cpp::Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE(""), OBFUSCATE("BattleManager"), OBFUSCATE("m_LocalPlayerShow"))
#define BattleManager_m_ShowPlayers (uintptr_t) IL2Cpp::Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE(""), OBFUSCATE("BattleManager"), OBFUSCATE("_showPlayers"))
#define BattleManager_m_ShowMonsters (uintptr_t) IL2Cpp::Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE(""), OBFUSCATE("BattleManager"), OBFUSCATE("_showMonsters"))

//Class ShowEntity
#define ShowEntity__Position (uintptr_t) IL2Cpp::Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE(""), OBFUSCATE("ShowEntity"), OBFUSCATE("m_vCachePosition"))
#define ShowEntity_m_RoleName (uintptr_t) IL2Cpp::Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE(""), OBFUSCATE("ShowEntity"), OBFUSCATE("m_RoleName"))
#define ShowEntity__logicFighter (uintptr_t) IL2Cpp::Il2CppGetFieldOffset("Assembly-CSharp.dll", "", "ShowEntity", "_logicFighter")


//Class ShowEntity
#define EntityBase_m_bSameCampType (uintptr_t) IL2Cpp::Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE(""), OBFUSCATE("ShowEntity"), OBFUSCATE("m_bSameCampType"))
#define EntityBase_m_bDeath (uintptr_t) IL2Cpp::Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE(""), OBFUSCATE("ShowEntity"), OBFUSCATE("m_bDeath"))
#define EntityBase_canSight (uintptr_t) IL2Cpp::Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE(""), OBFUSCATE("ShowEntity"), OBFUSCATE("canSight"))
#define EntityBase_m_Hp (uintptr_t) IL2Cpp::Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE(""), OBFUSCATE("ShowEntity"), OBFUSCATE("m_Hp"))
#define EntityBase_m_HpMax (uintptr_t) IL2Cpp::Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE(""), OBFUSCATE("ShowEntity"), OBFUSCATE("m_HpMax"))
#define EntityBase_m_ID (uintptr_t) IL2Cpp::Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE(""), OBFUSCATE("ShowEntity"), OBFUSCATE("m_ID"))
#define EntityBase_m_uGuid (uintptr_t) IL2Cpp::Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE(""), OBFUSCATE("ShowEntity"), OBFUSCATE("m_uGuid"))
#define EntityBase_m_dMoveSpeed (uintptr_t) IL2Cpp::Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE(""), OBFUSCATE("ShowEntity"), OBFUSCATE("m_dMoveSpeed"))

//Class ShowPlayer
#define ShowPlayer_m_HeroName (uintptr_t) IL2Cpp::Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE(""), OBFUSCATE("ShowPlayer"), OBFUSCATE("m_HeroName"))

//Class LogicFighter
#define LogicFighter_m_SkillComp (uintptr_t) IL2Cpp::Il2CppGetFieldOffset("Assembly-CSharp.dll", "Battle", "LogicFighter", "m_SkillComp")

#define LogicSkillComp_m_CoolDownComp (uintptr_t) IL2Cpp::Il2CppGetFieldOffset("Assembly-CSharp.dll", "Battle", "LogicSkillComp", "m_CoolDownComp")

//Class CoolDownComp
#define CoolDownComp_m_DicCoolInfo (uintptr_t) IL2Cpp::Il2CppGetFieldOffset("Assembly-CSharp.dll", "Battle", "CoolDownComp", "m_DicCoolInfo")

#define CoolDownData_GetCoolTime (uintptr_t) IL2Cpp::Il2CppGetFieldOffset("Assembly-CSharp.dll", "Battle", "CoolDownData", "GetCoolTime")

#define LogicPlayer_m_KillWildTimes (uintptr_t) IL2Cpp::Il2CppGetFieldOffset("Assembly-CSharp.dll", "Battle", "LogicPlayer", "<m_KillWildTimes>k__BackingField")

#define EntityBase_m_Level (uintptr_t) IL2Cpp::Il2CppGetFieldOffset("Assembly-CSharp.dll", "Battle", "ShowEntityBase", "m_Level")

//Class ShowSelfPlayer
//Class ShowUnitAIComp
#define ShowSelfPlayer_Update (uintptr_t) Il2CppGetMethodOffset("Assembly-CSharp.dll", "", "ShowSelfPlayer", "OnUpdate", 0)
#define ShowUnitAIComp_Update (uintptr_t) IL2Cpp::Il2CppGetMethodOffset("Assembly-CSharp.dll", "Battle", "ShowUnitAIComp", "Update")
#define ShowUnitAIComp_TryUseSkill (uintptr_t) IL2Cpp::Il2CppGetMethodOffset("Assembly-CSharp.dll", "Battle", "ShowUnitAIComp", "TryUseSkill", 13)


#define EntityBase_m_IsDeathProgress (uintptr_t) IL2Cpp::Il2CppGetFieldOffset("Assembly-CSharp.dll", "Battle", "EntityBase", "m_IsDeathProgress")

//Unlock Skin -> Mencoba
//Class UIRankHero.ChangeShow
#define UIRankHero_ChangeShow_iSelfHero (uintptr_t) IL2Cpp::Il2CppGetFieldOffset("Assembly-CSharp.dll", "", "UIRankHero/ChangeShow", "iSelfHero")

//Class BattlePlayerInfo
#define BattlePlayerInfo_lUid (uintptr_t) IL2Cpp::Il2CppGetFieldOffset("Assembly-CSharp.dll", "MTTDProto", "BattlePlayerInfo", "lUid")
#define BattlePlayerInfo_uiSelHero (uintptr_t) IL2Cpp::Il2CppGetFieldOffset("Assembly-CSharp.dll", "MTTDProto", "BattlePlayerInfo", "uiSelHero")
#define BattlePlayerInfo_uiSkinId (uintptr_t) IL2Cpp::Il2CppGetFieldOffset("Assembly-CSharp.dll", "MTTDProto", "BattlePlayerInfo", "uiSkinId")

//Class CmdHeroSkin
#define CmdHeroSkin__ctor (uintptr_t) (uintptr_t) IL2Cpp::Il2CppGetMethodOffset("Assembly-CSharp.dll", "MTTDProto", "CmdHeroSkin", ".ctor")

//Class CmdHeroStatue
#define CmdHeroStatue__ctor (uintptr_t) (uintptr_t) IL2Cpp::Il2CppGetMethodOffset("Assembly-CSharp.dll", "MTTDProto", "CmdHeroStatue", ".ctor")

//Class SystemData
#define SystemData_GetHeroSkin (uintptr_t) IL2Cpp::Il2CppGetMethodOffset("Assembly-CSharp.dll", "", "SystemData", "GetHeroSkin", 2)
#define SystemData_GetMCLimitSkin (uintptr_t) IL2Cpp::Il2CppGetMethodOffset("Assembly-CSharp.dll", "", "SystemData", "GetMCLimitSkin", 1)
#define SystemData_GetHeroHolyStatue (uintptr_t) IL2Cpp::Il2CppGetMethodOffset("Assembly-CSharp.dll", "", "SystemData", "GetHeroHolyStatue", 2)
#define SystemData_IsCanUseSkin (uintptr_t) IL2Cpp::Il2CppGetMethodOffset("Assembly-CSharp.dll", "", "SystemData", "IsCanUseSkin", 1)
#define SystemData_IsHaveSkin (uintptr_t) IL2Cpp::Il2CppGetMethodOffset("Assembly-CSharp.dll", "", "SystemData", "IsHaveSkin", 1)
#define SystemData_IsHaveSkinForever (uintptr_t) IL2Cpp::Il2CppGetMethodOffset("Assembly-CSharp.dll", "", "SystemData", "IsHaveSkinForever", 1)
#define SystemData_IsHaveStatue (uintptr_t) IL2Cpp::Il2CppGetMethodOffset("Assembly-CSharp.dll", "", "SystemData", "IsHaveStatue", 1)
#define SystemData_IsHaveStatueForever (uintptr_t) IL2Cpp::Il2CppGetMethodOffset("Assembly-CSharp.dll", "", "SystemData", "IsHaveStatueForever", 1)
#define SystemData_IsForbidStatue (uintptr_t) IL2Cpp::Il2CppGetMethodOffset("Assembly-CSharp.dll", "", "SystemData", "IsForbidStatue", 1)
#define SystemData_IsForbidSkin (uintptr_t) IL2Cpp::Il2CppGetMethodOffset("Assembly-CSharp.dll", "", "SystemData", "IsForbidSkin", 1)
#define SystemData_IsForbidARSkin (uintptr_t) IL2Cpp::Il2CppGetMethodOffset("Assembly-CSharp.dll", "", "SystemData", "IsForbidARSkin", 1)

//Class UIChooseHero
#define UIChooseHero_ShowSkinExpiryDate (uintptr_t) IL2Cpp::Il2CppGetMethodOffset("Assembly-CSharp.dll", "", "UIChooseHero", "ShowSkinExpiryDate",0 )   //CheckHeroDefaultSkin
#define UIChooseHero_SendSelectSkin (uintptr_t) IL2Cpp::Il2CppGetMethodOffset("Assembly-CSharp.dll", "", "ChooseHeroMgr", "SendSelectSkin", 2)
#define UIChooseHero_SendSelectSkin2 (uintptr_t) IL2Cpp::Il2CppGetMethodOffset("Assembly-CSharp.dll", "", "UIChooseHero", "CheckHeroDefaultSkin", 2)

//Class UIRankHero
#define UIRankHero_BatttleSelectSkin (uintptr_t) IL2Cpp::Il2CppGetMethodOffset("Assembly-CSharp.dll", "", "UIRankHero", "BatttleSelectSkin", 2)
#define UIRankHero_BatttleSelectSkin2 (uintptr_t) IL2Cpp::Il2CppGetMethodOffset("Assembly-CSharp.dll", "", "UIChooseHero", "BatttleSelectSkin", 2)

//Class UIRankHero.ChangeShow
#define UIRankHero_ChangeShow_SendUseSkin (uintptr_t) IL2Cpp::Il2CppGetMethodOffset("Assembly-CSharp.dll", "", "UIRankHero/ChangeShow", "SendUseSkin", 2)

//Class BattleReceiveMessage
#define BattleReceiveMessage_SetPlayerData (uintptr_t) IL2Cpp::Il2CppGetMethodOffset("Assembly-CSharp.dll", "", "BattleReceiveMessage", "SetPlayerData", 2)
#define BattleReceiveMessage_SetPlayerData_ (uintptr_t) IL2Cpp::Il2CppGetMethodOffset("Assembly-CSharp.dll", "", "BattleReceiveMessage", "SetPlayerData", 1)
#define BattleReceiveMessage_AddPlayerInfo (uintptr_t) IL2Cpp::Il2CppGetMethodOffset("Assembly-CSharp.dll", "", "BattleReceiveMessage", "AddPlayerInfo", 4)
#define BattleReceiveMessage_AddPlayerInfo_ (uintptr_t) IL2Cpp::Il2CppGetMethodOffset("Assembly-CSharp.dll", "", "BattleReceiveMessage", "AddPlayerInfo", 2)

//Class GameServerConfig
#define GameServerConfig_SendRawData (uintptr_t) IL2Cpp::Il2CppGetMethodOffset("Assembly-CSharp.dll", "", "GameServerConfig", "SendRawData", 7)


