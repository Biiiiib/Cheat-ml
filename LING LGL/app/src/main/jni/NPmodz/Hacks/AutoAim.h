#pragma once
bool AutoRetriRed;
bool AutoRetriBlue;
bool AutoRetriLord;
bool AutoRetriTurtle;
bool AutoRetriLitho;


bool SixCrab;
bool SixxCrabExp;
bool TestBool;
bool BoolMinions;
bool Minionmns;

bool Basic;
bool Spell;
bool Skill1;
bool Skill2;
bool Skill3;
bool Skill4;
int Target = 0;
static float RangeFOV = 10.0f;
bool Maphack;
bool Skin1;
bool Clear = false;

static float TargetMyHealth = 2500;
static float TargetHP = 1000.0f;
static float TargetDistance = 3.0f;
//static float RangeFOV = 10.0f;
static float HealthHero = 500.0f;
static float Auto = 1000.0f;
static float Execute = 500.0f;
static float Argus = 1000.0f;
static float DisRet = 5.0f;

void (*oQblvs)(void *instance, int Icon);
void Qblvs(void *instance, int Icon) {
    if (instance != nullptr) {
        if (Maphack) {
           return;
        }
    }
    oQblvs(instance, Icon);
}

void (*orig_TryUseSkill)(...);
void TryUseSkill(void *instance, int skillId, Vector3 dir, bool dirDefault, Vector3 pos, bool bCommonAtk, bool bAuto, bool bAlong, bool bCache, bool isInFirstDragRange) {
    bool isDoneAim = false;
    if (instance != NULL) {
        float MaxDist = std::numeric_limits<float>::infinity();
        float MaxEnemyHP = std::numeric_limits<float>::infinity();
        float MaxPercentHP = std::numeric_limits<float>::infinity();
        float MaxSwordDist = std::numeric_limits<float>::infinity();
        Vector3 EntityPos = Vector3::zero();
        Vector3 SwordPos = Vector3::zero();
        void *BattleManager_Instance;
        IL2Cpp::Il2CppGetStaticFieldValue("Assembly-CSharp.dll", "", "BattleManager", "Instance", &BattleManager_Instance);
        if (BattleManager_Instance) {
            auto m_LocalPlayerShow = *(uintptr_t *) ((uintptr_t)BattleManager_Instance + BattleManager_m_LocalPlayerShow);
            if (m_LocalPlayerShow) {
				//auto m_ID = *(int *) ((uintptr_t)Pawn + Bullet_m_Id);
                auto selfPos = *(Vector3 *) ((uintptr_t)m_LocalPlayerShow + ShowEntity__Position);
                auto HeroID = *(int *) ((uintptr_t)m_LocalPlayerShow + EntityBase_m_ID);
                if (selfPos != Vector3::zero()) {
                    monoList<void **> *m_ShowPlayers = *(monoList<void **> **) ((uintptr_t)BattleManager_Instance + BattleManager_m_ShowPlayers);
                    if (m_ShowPlayers) {
                        for (int i = 0; i < m_ShowPlayers->getSize(); i++) {
                            auto Pawn = m_ShowPlayers->getItems()[i];
                            if (!Pawn) continue;
                            auto m_bSameCampType = *(bool *) ((uintptr_t)Pawn + EntityBase_m_bSameCampType);
                            if (m_bSameCampType) continue;
                            auto m_bDeath = *(bool *) ((uintptr_t)Pawn + EntityBase_m_bDeath);
                            if (m_bDeath) continue;
                            auto m_IsDeathProgress = *(bool *) ((uintptr_t)Pawn + EntityBase_m_IsDeathProgress);
                            if (m_IsDeathProgress) continue;
                            auto _Position = *(Vector3 *) ((uintptr_t)Pawn + ShowEntity__Position);
                            float Distance = (int) Vector3::Distance(selfPos, _Position);
                            float EnemyDistance = Vector3::Distance(selfPos, _Position);
                            float CurHP = *(int *) ((uintptr_t)Pawn + EntityBase_m_Hp);
                            float MaxHP = *(int *) ((uintptr_t)Pawn + EntityBase_m_HpMax);
                            float MyHealth = *(int *) ((uintptr_t)m_LocalPlayerShow + EntityBase_m_Hp);
                            float PercentHP = CurHP * 100 / MaxHP;
                            if (!m_bDeath && !m_IsDeathProgress) {
                            if (Distance < RangeFOV || EnemyDistance < TargetDistance || CurHP <= TargetHP) {
                                if (Target == 0 && Distance < MaxDist) {
                                    EntityPos = _Position;
                                    MaxDist = Distance;
                                }
                                if (Target == 1 && CurHP < MaxEnemyHP) {
                                    EntityPos = _Position;
                                    MaxDist = CurHP;
                                }
                                if (Target == 2 && PercentHP < MaxPercentHP) {
                                    EntityPos = _Position;
                                    MaxPercentHP = PercentHP;
                                }
							}
						}
						}
                        if (EntityPos != Vector3::zero()) {
                        auto targetLockPos = Vector3::Normalized(EntityPos - selfPos);
                        if (Basic) {
                            if (skillId == 100 * HeroID + 00) {
                                isDoneAim = true;
                                orig_TryUseSkill(instance, skillId, targetLockPos, dirDefault, pos, bCommonAtk, bAuto, bAlong, bCache, isInFirstDragRange);
                            }
                        }
                        //Spell
                        if (Spell) {
                            if (skillId == 20100 || skillId == 20140) {
                                isDoneAim = true;
                                orig_TryUseSkill(instance, skillId, targetLockPos, dirDefault, pos, bCommonAtk, bAuto, bAlong, bCache, isInFirstDragRange);
                            }
                        }
                        //Skill 1
                        if (Skill1) {
                            if (skillId == 100 * HeroID + 10) {
                                isDoneAim = true;
                                orig_TryUseSkill(instance, skillId, targetLockPos, dirDefault, pos, bCommonAtk, bAuto, bAlong, bCache, isInFirstDragRange);
                            }
                        }
                        //Skill 2
                        if (Skill2) {
                            if (skillId == 100 * HeroID + 20 || skillId == 2010520 /*Beatrix Skill2*/) {
                                isDoneAim = true;
                                orig_TryUseSkill(instance, skillId, targetLockPos, dirDefault, pos, bCommonAtk, bAuto, bAlong, bCache, isInFirstDragRange);
                            }
                        }
                        //Skill 3
                        if (Skill3) {
                            if (skillId == 100 * HeroID + 30 || skillId == 2010530 /*Beatrix Ulti*/) {
                                isDoneAim = true;
                                orig_TryUseSkill(instance, skillId, targetLockPos, dirDefault, pos, bCommonAtk, bAuto, bAlong, bCache, isInFirstDragRange);
                            }
                        }
                        //Skill 4
                        if (Skill4) {
                            if (skillId == 100 * HeroID + 40) {
                                isDoneAim = true;
                                orig_TryUseSkill(instance, skillId, targetLockPos, dirDefault, pos, bCommonAtk, bAuto, bAlong, bCache, isInFirstDragRange);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    if (!isDoneAim) {
        orig_TryUseSkill(instance, skillId, dir, dirDefault, pos, bCommonAtk, bAuto, bAlong, bCache, isInFirstDragRange);
    }
}

/*
void (*orig_TryUseSkill)(...);
void TryUseSkill(void *instance, int skillId, Vector3 dir, bool dirDefault, Vector3 pos, bool bCommonAttack, bool bAlong, bool isInFirstDragRange, bool bIgnoreQueue, uint dragTime) {
    bool isDoneAim = false;
    if (instance != NULL) {
        float MaxDist = std::numeric_limits<float>::infinity();
        float MaxEnemyHP = std::numeric_limits<float>::infinity();
        float MaxPercentHP = std::numeric_limits<float>::infinity();
        float MaxSwordDist = std::numeric_limits<float>::infinity();
        
        Vector3 EntityPos = Vector3::zero();
        Vector3 SwordPos = Vector3::zero();

        void *BattleManager_Instance;
        IL2Cpp::Il2CppGetStaticFieldValue("Assembly-CSharp.dll", "", "BattleManager", "Instance", &BattleManager_Instance);
        if (Tools::IsPtrValid(BattleManager_Instance)) {
            auto m_LocalPlayerShow = *(uintptr_t *) ((uintptr_t)BattleManager_Instance + BattleManager_m_LocalPlayerShow);
            if (m_LocalPlayerShow) {
                auto selfPos = *(Vector3 *) ((uintptr_t)m_LocalPlayerShow + ShowEntity__Position);
                auto HeroID = *(int *) ((uintptr_t)m_LocalPlayerShow + EntityBase_m_ID);
                if (selfPos != Vector3::zero()) {
                    monoList<void **> *m_ShowPlayers = *(monoList<void **> **) ((uintptr_t)BattleManager_Instance + BattleManager_m_ShowPlayers);
                    if (Tools::IsPtrValid(m_ShowPlayers)) {
                        for (int i = 0; i < m_ShowPlayers->getSize(); i++) {
                            auto Pawn = m_ShowPlayers->getItems()[i];
                            if (!Pawn) continue;
                            auto m_bSameCampType = *(bool *) ((uintptr_t)Pawn + EntityBase_m_bSameCampType);
                            if (m_bSameCampType) continue;
                            auto m_bDeath = *(bool *) ((uintptr_t)Pawn + EntityBase_m_bDeath);
                            if (m_bDeath) continue;
                            auto _Position = *(Vector3 *) ((uintptr_t)Pawn + ShowEntity__Position);
                            float Distance = (int) Vector3::Distance(selfPos, _Position);
                            float CurHP = *(int *) ((uintptr_t)Pawn + EntityBase_m_Hp);
                            float MaxHP = *(int *) ((uintptr_t)Pawn + EntityBase_m_HpMax);
                            float PercentHP = CurHP * 100 / MaxHP;
                            
                            if (Distance < RangeFOV) {
                                if (Target == 0 && Distance < MaxDist) {
                                    EntityPos = _Position;
                                    MaxDist = Distance;
                                }
                                if (Target == 1 && CurHP < MaxEnemyHP) {
                                    EntityPos = _Position;
                                    MaxDist = CurHP;
                                }
                                if (Target == 2 && PercentHP < MaxPercentHP) {
                                    EntityPos = _Position;
                                    MaxPercentHP = PercentHP;
                                }
                            }
                        }
                    }
                    if (EntityPos != Vector3::zero()) {
                        auto KN = Vector3::Normalized(EntityPos - selfPos);
                        //Basic
                        if (Basic) {
                            if (skillId == 100 * HeroID + 00) {
                                isDoneAim = true;
                                orig_TryUseSkill(instance, skillId, KN, dirDefault, pos, bCommonAttack, bAlong, isInFirstDragRange, bIgnoreQueue);
                            }
                        }                
                        //Skill 1
                        if (Skill1) {
                            if (skillId == 100 * HeroID + 10) {
                                isDoneAim = true;
                                orig_TryUseSkill(instance, skillId, KN, dirDefault, pos, bCommonAttack, bAlong, isInFirstDragRange, bIgnoreQueue);
                            }
                        }
                        //Skill 2
                        if (Skill2) {
                            if (skillId == 100 * HeroID + 20 || skillId == 2010520 /*Beatrix Skill2*//*) {
                                isDoneAim = true;
                                orig_TryUseSkill(instance, skillId, KN, dirDefault, pos, bCommonAttack, bAlong, isInFirstDragRange, bIgnoreQueue);
                            }
                        }
                        //Skill 3
                        if (Skill3) {
                            if (skillId == 100 * HeroID + 30 || skillId == 2010530 /*Beatrix Ulti*//*) {
                                isDoneAim = true;
                                orig_TryUseSkill(instance, skillId, KN, dirDefault, pos, bCommonAttack, bAlong, isInFirstDragRange, bIgnoreQueue);
                            }
                        }
                        //Skill 4
                        if (Skill4) {
                            if (skillId == 100 * HeroID + 40) {
                                isDoneAim = true;
                                orig_TryUseSkill(instance, skillId, KN, dirDefault, pos, bCommonAttack, bAlong, isInFirstDragRange, bIgnoreQueue);
                            }
                        }
                    }

                }
            }
        }
    }
    if (!isDoneAim) {
        orig_TryUseSkill(instance, skillId, dir, dirDefault, pos, bCommonAttack, bAlong, isInFirstDragRange, bIgnoreQueue);
    }
}
*/
int CalculateRetriDamage(int m_Level, int m_KillWildTimes) {
    if (m_Level < 5) {
        return 530 + (80 * m_Level);
    } else {
        return 1.5 * (530 + (80 * m_Level)); + (380 + (40 * m_Level)) - 120;  
    }
}

void (*orig_UpdateRetribution)(void *master);
void UpdateRetribution(void *master) {

     if (AutoRetriRed || AutoRetriBlue || AutoRetriLord || AutoRetriTurtle || AutoRetriLitho) {
        if (master != NULL) {
            void *BattleManager_Instance;
            if (BattleManager_Instance) {
                auto m_LocalPlayerShow = *(uintptr_t *) ((uintptr_t)BattleManager_Instance + BattleManager_m_LocalPlayerShow);
                if (m_LocalPlayerShow) {
                    auto selfPos = *(Vector3 *) ((uintptr_t)m_LocalPlayerShow + ShowEntity__Position);
                    if (selfPos != Vector3::zero()) {
                        auto m_Level1 = *(int *) ((uintptr_t)m_LocalPlayerShow + EntityBase_m_Level);
                        auto _logicFighter = *(uintptr_t *) ((uintptr_t)m_LocalPlayerShow + ShowEntity__logicFighter);
                        int iCalculateDamage;
                        if (_logicFighter) {
                            auto m_KillWildTimes = *(int *) ((uintptr_t)_logicFighter + LogicPlayer_m_KillWildTimes);
                            iCalculateDamage = CalculateRetriDamage(m_Level1, m_KillWildTimes);
                        }//Created By Owner Jhamz
                        monoList<void **> *m_ShowMonsters = *(monoList<void **> **) ((uintptr_t)BattleManager_Instance + BattleManager_m_ShowMonsters);
                        if (m_ShowMonsters) {
                            for (int i = 0; i < m_ShowMonsters->getSize(); i++) {
                                auto Pawnprojhamz = m_ShowMonsters->getItems()[i];
                                if (!Pawnprojhamz) continue;
                                auto m_ID = *(int *) ((uintptr_t)Pawnprojhamz + EntityBase_m_ID);
                                if (MonsterToString(m_ID) == "") continue;
                                auto m_bSameCampType = *(bool *) ((uintptr_t)Pawnprojhamz + EntityBase_m_bSameCampType);
                                if (m_bSameCampType) continue;
                                auto m_bDeath = *(bool *) ((uintptr_t)Pawnprojhamz + EntityBase_m_bDeath);
                                if (m_bDeath) continue;
                                auto _Position = *(Vector3 *) ((uintptr_t)Pawnprojhamz + ShowEntity__Position);
                                float Distance = (int) Vector3::Distance(selfPos, _Position);
                                float CurHP = *(int *) ((uintptr_t)Pawnprojhamz + EntityBase_m_Hp);
                                float MaxHP = *(int *) ((uintptr_t)Pawnprojhamz + EntityBase_m_HpMax);
                                if (Distance < 5.4f && CurHP < MaxHP) {
                                    if (CurHP <= iCalculateDamage) {
                                        if (m_ID == 2004 && AutoRetriRed /*Red Buff*/ || m_ID == 2005 && AutoRetriBlue /*Blue Buff*/ || m_ID == 2002 && AutoRetriLord /*Lord*/ || m_ID == 2003 && AutoRetriTurtle /*Turtle*/ || m_ID == 2056 && AutoRetriLitho || m_ID == 2013 && SixxCrabExp || m_ID == 2011 && SixCrab/*Blue Buff*/) {
                                            if (Vector3::Normalized(_Position - selfPos) != Vector3::zero()) {
                                                orig_TryUseSkill(master, 20020, Vector3::Normalized(_Position - selfPos), true, Vector3::zero(), false, true);
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    orig_UpdateRetribution(master);
}


