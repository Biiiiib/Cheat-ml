#pragma once

struct sAim {
    struct sHelper {
        struct sSkills {
            bool Basic;
            bool Spell;
            bool Skill1;
            bool Skill2;
            bool Skill3;
            bool Skill4;
			bool Execute;
        };
        sSkills Skills{0};

        struct sPriority {
            int Target = 0;
			bool AutoTakeSword;
        };
        sPriority Priority{0};
        
        struct sAutoCombo {
            //Auto Combo 1
            bool Gusion;
            bool Paquito;
            bool Benedetta;
            bool Lunox1;
            bool Lunox2;
            //Autom Combo 2
            bool Tigreal;
            bool Atlas;
            bool Franco1;
            bool Lolita;
            //Auto Combo 3
            bool Selena;
            bool Badang;
            bool Saber1;
            bool Harith;
            //Auto Combo 4
            bool Brody;
            bool Franco2;
            bool Xavier;
            bool Saber2;
        };
        sAutoCombo AutoCombo{0};
        
        struct sMoreFeature {
            bool Chou;
            bool Pharsa;
            bool Kimmy;
			bool FlameShoot;
			bool Alucards;
			bool Vales2;
			bool Vexanas;
			bool Ling;
			bool Arlot; //1+2+2+3 
        };
        sMoreFeature MoreFeature{0};
        
        struct sAutoUltimate {
            //1
            bool Beatrix;
            bool Xavier;
            bool Granger;
            bool Balmond;
            //2
            bool Layla;
            bool Moskov;
            bool Nana;
            bool Gord;
            //3
            bool Hilda;
            bool Martis;
            bool Thamuz;
            bool Argus;
        };
        sAutoUltimate AutoUltimate{0};
        
        struct sAutoDefense {
            bool Executed;
            bool FlameShoot;
            bool Vengeance;
            bool Flicker;
            bool Aegis;
        };
        sAutoDefense AutoDefense{0};
        
        struct sAutoRetribution {
            bool Buff;
            bool Turtle;
            bool Lord;
            bool Crab;
            bool Litho;
        };
        sAutoRetribution AutoRetribution{0};
        
    };
    sHelper Helper{0};
};
sAim Aim{0};

static float RangeFOV = 10.0f;
static float TargetHP = 1000.0f;
static float TargetDistance = 3.0f;

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
        Il2CppGetStaticFieldValue("Assembly-CSharp.dll", "", "BattleManager", "Instance", &BattleManager_Instance);
        if (BattleManager_Instance) {
            auto m_LocalPlayerShow = *(uintptr_t *) ((uintptr_t)BattleManager_Instance + BattleManager_m_LocalPlayerShow);
            if (m_LocalPlayerShow) {
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
                                if (Aim.Helper.Priority.Target == 0 && Distance < MaxDist) {
                                    EntityPos = _Position;
                                    MaxDist = Distance;
                                }
                                if (Aim.Helper.Priority.Target == 1 && CurHP < MaxEnemyHP) {
                                    EntityPos = _Position;
                                    MaxEnemyHP = CurHP;
                                }
                                if (Aim.Helper.Priority.Target == 2 && PercentHP < MaxPercentHP) {
                                    EntityPos = _Position;
                                    MaxPercentHP = PercentHP;
                                }
                                if (EntityPos != Vector3::zero()) {
                                    auto iTargetPos = Vector3::Normalized(_Position - selfPos);
                                    //Auto Combo
                                    if (Aim.Helper.AutoCombo.Gusion) {
                                        if (EnemyDistance < TargetDistance && skillId == 5600) {
                                            if (_Position != Vector3::zero()) {
                                                orig_TryUseSkill(instance, 5620, iTargetPos, true, _Position, false, true);
                                                orig_TryUseSkill(instance, 5610, iTargetPos, true, _Position, false, true);
                                                if (EnemyDistance < TargetDistance && skillId == 5600) {
                                                    if (_Position != Vector3::zero()) {
                                                        orig_TryUseSkill(instance, 5630, iTargetPos, true, _Position, false, true);
                                                        orig_TryUseSkill(instance, 5620, iTargetPos, true, _Position, false, true);
                                                        orig_TryUseSkill(instance, 5610, iTargetPos, true, _Position, false, true);
                                                    }
                                                }
                                            }
                                        }
                                    }
									
									
									
                                    if (Aim.Helper.AutoCombo.Paquito) {
                                        if (EnemyDistance < TargetDistance && skillId == 10300) {
                                            if (_Position != Vector3::zero()) {
                                                orig_TryUseSkill(instance, 10320, iTargetPos, true, _Position, false, true);
                                                orig_TryUseSkill(instance, 10330, iTargetPos, true, _Position, false, true);
                                                if (EnemyDistance < TargetDistance && skillId == 10300) {
                                                    if (_Position != Vector3::zero()) {
                                                        orig_TryUseSkill(instance, 10320, iTargetPos, true, _Position, false, true);
                                                        orig_TryUseSkill(instance, 10310, iTargetPos, true, selfPos, false, true);
                                                        orig_TryUseSkill(instance, 10330, iTargetPos, true, _Position, false, true);
                                                    }
                                                }
                                            }
                                        }
                                    }
                                    if (Aim.Helper.AutoCombo.Benedetta) {
                                        if (EnemyDistance < TargetDistance && skillId == 9700) {
                                            if (_Position != Vector3::zero()) {
                                                orig_TryUseSkill(instance, 9720, iTargetPos, true, _Position, false, true);
                                                orig_TryUseSkill(instance, 9710, iTargetPos, true, _Position, false, true);
                                                if (EnemyDistance < TargetDistance && skillId == 9700) {
                                                    if (_Position != Vector3::zero()) {
                                                        orig_TryUseSkill(instance, 9730, iTargetPos, true, _Position, false, true);
                                                        orig_TryUseSkill(instance, 9700, iTargetPos, true, _Position, false, true);
                                                        orig_TryUseSkill(instance, 9700, iTargetPos, true, _Position, false, true);
                                                    }
                                                }
                                            }
                                        }
                                    }
                                    if (Aim.Helper.AutoCombo.Lunox1) {
                                        if (EnemyDistance < TargetDistance && skillId == 6800) {
                                            if (_Position != Vector3::zero()) {
                                                orig_TryUseSkill(instance, 6830, iTargetPos, true, _Position, false, true);
                                                orig_TryUseSkill(instance, 6840, iTargetPos, true, _Position, false, true);
                                                if (EnemyDistance < TargetDistance && skillId == 6800) {
                                                    if (_Position != Vector3::zero()) {
                                                        orig_TryUseSkill(instance, 6810, iTargetPos, true, _Position, false, true);
                                                    }
                                                }
                                            }
                                        }
                                    }
                                    if (Aim.Helper.AutoCombo.Lunox2) {
                                        if (EnemyDistance < TargetDistance && skillId == 6800) {
                                            if (_Position != Vector3::zero()) {
                                                orig_TryUseSkill(instance, 6840, iTargetPos, true, _Position, false, true);
                                                orig_TryUseSkill(instance, 6830, iTargetPos, true, _Position, false, true);
                                                if (EnemyDistance < TargetDistance && skillId == 6800) {
                                                    if (_Position != Vector3::zero()) {
                                                        orig_TryUseSkill(instance, 6820, iTargetPos, true, _Position, false, true);
                                                        sleep(0.5);
                                                        orig_TryUseSkill(instance, 6820, iTargetPos, true, _Position, false, true);
                                                        sleep(0.5);
                                                        orig_TryUseSkill(instance, 6820, iTargetPos, true, _Position, false, true);
                                                        sleep(0.5);
                                                        orig_TryUseSkill(instance, 6820, iTargetPos, true, _Position, false, true);
                                                        sleep(0.5);
                                                        orig_TryUseSkill(instance, 6820, iTargetPos, true, _Position, false, true);
                                                        sleep(0.5);
                                                        orig_TryUseSkill(instance, 6820, iTargetPos, true, _Position, false, true);
                                                        break;
                                                    }
                                                }
                                            }
                                        }
                                    }
                                    //Auto Combo 2
                                    if (Aim.Helper.AutoCombo.Tigreal) {
                                        if (EnemyDistance < TargetDistance && skillId == 20100) {
                                            orig_TryUseSkill(instance, 20100, iTargetPos, true, _Position, false, true);
                                            orig_TryUseSkill(instance, 630, iTargetPos, true, selfPos, false, true);
                                        }
                                    }
                                    if (Aim.Helper.AutoCombo.Atlas) {
                                        if (EnemyDistance < TargetDistance && skillId == 20100) {
                                            orig_TryUseSkill(instance, 20100, iTargetPos, true, _Position, false, true);
                                            orig_TryUseSkill(instance, 9330, iTargetPos, true, selfPos, false, true);
                                        }
                                    }
                                    if (Aim.Helper.AutoCombo.Franco1) {
                                        if (EnemyDistance < TargetDistance && skillId == 20100) {
                                            orig_TryUseSkill(instance, 20100, iTargetPos, true, _Position, false, true);
                                            orig_TryUseSkill(instance, 1030, iTargetPos, true, selfPos, false, true);
                                        }
                                    }
                                    if (Aim.Helper.AutoCombo.Lolita) {
                                        if (EnemyDistance < TargetDistance && skillId == 20100) {
                                            orig_TryUseSkill(instance, 20100, iTargetPos, true, _Position, false, true);
                                            orig_TryUseSkill(instance, 2030, iTargetPos, true, _Position, false, true);
                                        }
                                    }
                                    //Auto Combo 3
                                    if (Aim.Helper.AutoCombo.Selena) {
                                        if (EnemyDistance < TargetDistance && skillId == 6310) {
                                            orig_TryUseSkill(instance, 6310, iTargetPos, true, selfPos, false, true);
                                            orig_TryUseSkill(instance, 6320, iTargetPos, true, _Position, false, true);
                                        }
                                    }
                                    if (Aim.Helper.AutoCombo.Badang) {
                                        if (EnemyDistance < TargetDistance && skillId == 7720) {
                                            orig_TryUseSkill(instance, 7720, iTargetPos, true, _Position, false, true);
                                            orig_TryUseSkill(instance, 7730, iTargetPos, true, _Position, false, true);
                                        }
                                    }
                                    if (Aim.Helper.AutoCombo.Saber1) {
                                        if (EnemyDistance < TargetDistance && skillId == 320) {
                                            orig_TryUseSkill(instance, 320, iTargetPos, true, _Position, false, true);
                                            orig_TryUseSkill(instance, 330, iTargetPos, true, selfPos, false, true);
                                        }
                                    }
                                    if (Aim.Helper.AutoCombo.Harith) {
                                        if (EnemyDistance < TargetDistance && skillId == 100 * HeroID + 00) {
                                            orig_TryUseSkill(instance, skillId == 100 * HeroID + 00, iTargetPos, true, _Position, false, true);
                                            orig_TryUseSkill(instance, 7320, iTargetPos, true, _Position, false, true);
                                        }
                                    }
                                    //Auto Combo 4
                                    if (Aim.Helper.AutoCombo.Brody) {
                                        if (EnemyDistance < TargetDistance && skillId == 10010) {
                                            orig_TryUseSkill(instance, 10010, iTargetPos, true, _Position, false, true);
                                            orig_TryUseSkill(instance, 10030, iTargetPos, true, _Position, false, true);
                                        }
                                    }
                                    if (Aim.Helper.AutoCombo.Franco2) {
                                        if (EnemyDistance < TargetDistance && skillId == 1010) {
                                            orig_TryUseSkill(instance, 1010, iTargetPos, true, _Position, false, true);
                                            orig_TryUseSkill(instance, 1030, iTargetPos, true, selfPos, false, true);
                                        }
                                    }
                                    if (Aim.Helper.AutoCombo.Xavier) {
                                        if (EnemyDistance < TargetDistance && skillId == 11510) {
                                            orig_TryUseSkill(instance, 11510, iTargetPos, true, _Position, false, true);
                                            orig_TryUseSkill(instance, 11520, iTargetPos, true, _Position, false, true);
                                        }
                                    }
                                    if (Aim.Helper.AutoCombo.Saber2) {
                                        if (EnemyDistance < TargetDistance && skillId == 310) {
                                            orig_TryUseSkill(instance, 310, iTargetPos, true, _Position, false, true);
                                            orig_TryUseSkill(instance, 330, iTargetPos, true, selfPos, false, true);
                                        }
                                    }
                                    //More Feature
                                    if (Aim.Helper.MoreFeature.Chou) {
                                        if (EnemyDistance < TargetDistance && skillId == 2630) {
                                            orig_TryUseSkill(instance, 2630, iTargetPos, true, selfPos, false, true);
                                            orig_TryUseSkill(instance, 20100, iTargetPos, true, _Position, false, true);
                                        }
                                    }
                                    if (Aim.Helper.MoreFeature.Pharsa) {
                                        if (EnemyDistance < TargetDistance && skillId == 5230) {
                                            if (_Position != Vector3::zero()) {
                                                orig_TryUseSkill(instance, 5230, iTargetPos, true, _Position, false, true);
                                                sleep(0.5);
                                                orig_TryUseSkill(instance, 5230, iTargetPos, true, _Position, false, true);
                                                sleep(0.5);
                                                orig_TryUseSkill(instance, 5230, iTargetPos, true, _Position, false, true);
                                                if (EnemyDistance < TargetDistance && skillId == 5230) {
                                                    if (_Position != Vector3::zero()) {
                                                        orig_TryUseSkill(instance, 5230, iTargetPos, true, _Position, false, true);
                                                        sleep(0.5);
                                                        orig_TryUseSkill(instance, 5230, iTargetPos, true, _Position, false, true);
                                                        sleep(0.5);
                                                        orig_TryUseSkill(instance, 5230, iTargetPos, true, _Position, false, true);
                                                        break;
                                                    }
                                                }
                                            }
                                        }
                                    }
                                    if (Aim.Helper.MoreFeature.Kimmy) {
                                        if (_Position != Vector3::zero() && Distance < 6.5f) {  
                                            orig_TryUseSkill(instance, 7113, Vector3::Normalized(_Position - selfPos), true, selfPos, false, true);
                                        } else if (_Position != Vector3::zero() && Distance < 6.5f) {
                                            orig_TryUseSkill(instance, 7110, Vector3::Normalized(_Position - selfPos), true, selfPos, false, true);
                                        }
                                    }
                                    //Auto Ultimate V1
                                    if (Aim.Helper.AutoUltimate.Beatrix) {
                                        if (EnemyDistance < TargetDistance && CurHP <= TargetHP) {
                                            if (Vector3::Normalized(_Position - selfPos) != Vector3::zero()) {
                                                orig_TryUseSkill(instance, 2010530, iTargetPos, true, _Position, false, true);
                                            }
                                        }
                                    }
                                    if (Aim.Helper.AutoUltimate.Xavier) {
                                        if (EnemyDistance < TargetDistance && CurHP <= TargetHP) {
                                            if (Vector3::Normalized(_Position - selfPos) != Vector3::zero()) {
                                                orig_TryUseSkill(instance, 11530, iTargetPos, true, _Position, false, true);
                                            }
                                        }
                                    }
                                    if (Aim.Helper.AutoUltimate.Granger) {
                                        if (EnemyDistance < TargetDistance && CurHP <= TargetHP) {
                                            if (Vector3::Normalized(_Position - selfPos) != Vector3::zero()) {
                                                orig_TryUseSkill(instance, 7930, iTargetPos, true, _Position, false, true);
                                                sleep(0.5);
                                                orig_TryUseSkill(instance, 7930, iTargetPos, true, _Position, false, true);
                                                sleep(0.5);
                                                orig_TryUseSkill(instance, 7930, iTargetPos, true, _Position, false, true);
                                                sleep(0.5);
                                                orig_TryUseSkill(instance, 7930, iTargetPos, true, _Position, false, true);
                                                break;
                                            }
                                        }
                                    }
                                    if (Aim.Helper.AutoUltimate.Balmond) {
                                        if (EnemyDistance < TargetDistance && CurHP <= TargetHP) {
                                            if (Vector3::Normalized(_Position - selfPos) != Vector3::zero()) {
                                                orig_TryUseSkill(instance, 230, iTargetPos, true, _Position, false, true);
                                            }
                                        }
                                    }
									//Vale2
                            if (Aim.Helper.MoreFeature.Vales2) {
                            if (skillId == 6620 && Distance < 6.0f) { 
                                if (_Position != Vector3::zero()) {
                                orig_TryUseSkill(instance, 6620, Vector3::Normalized(_Position - selfPos), true, _Position, false, true);
                                orig_TryUseSkill(instance, 6610, Vector3::Normalized(_Position - selfPos), true, _Position, false, true);
                                }}}
                                    //Auto Ultimate V2
                                    if (Aim.Helper.AutoUltimate.Layla) {
                                        if (EnemyDistance < TargetDistance && CurHP <= TargetHP) {
                                            if (Vector3::Normalized(_Position - selfPos) != Vector3::zero()) {
                                                orig_TryUseSkill(instance, 1830, iTargetPos, true, _Position, false, true);
                                            }
                                        }
                                    }
                                    if (Aim.Helper.AutoUltimate.Moskov) {
                                        if (EnemyDistance < TargetDistance && CurHP <= TargetHP) {
                                            if (Vector3::Normalized(_Position - selfPos) != Vector3::zero()) {
                                                orig_TryUseSkill(instance, 3130, iTargetPos, true, _Position, false, true);
                                            }
                                        }
                                    }
                                    if (Aim.Helper.AutoUltimate.Nana) {
                                        if (EnemyDistance < TargetDistance && CurHP <= TargetHP) {
                                            if (Vector3::Normalized(_Position - selfPos) != Vector3::zero()) {
                                                orig_TryUseSkill(instance, 530, iTargetPos, true, _Position, false, true);
                                            }
                                        }
                                    }
                                    if (Aim.Helper.AutoUltimate.Gord) {
                                        if (EnemyDistance < TargetDistance && CurHP <= TargetHP) {
                                            if (Vector3::Normalized(_Position - selfPos) != Vector3::zero()) {
                                                orig_TryUseSkill(instance, 2330, iTargetPos, true, _Position, false, true);
                                            }
                                        }
                                    }
                                    //Auto Ultimate V3
                                    if (Aim.Helper.AutoUltimate.Hilda) {
                                        if (EnemyDistance < TargetDistance && CurHP <= TargetHP) {
                                            if (Vector3::Normalized(_Position - selfPos) != Vector3::zero()) {
                                                orig_TryUseSkill(instance, 3530, iTargetPos, true, _Position, false, true);
                                            }
                                        }
                                    }
                                    if (Aim.Helper.AutoUltimate.Martis) {
                                        if (EnemyDistance < TargetDistance && CurHP <= TargetHP) {
                                            if (Vector3::Normalized(_Position - selfPos) != Vector3::zero()) {
                                                orig_TryUseSkill(instance, 5830, iTargetPos, true, selfPos, false, true);
                                            }
                                        }
                                    }
                                    if (Aim.Helper.AutoUltimate.Thamuz) {
                                        if (EnemyDistance < TargetDistance && MyHealth <= 2500) {
                                            if (Vector3::Normalized(_Position - selfPos) != Vector3::zero()) {
                                                orig_TryUseSkill(instance, 7230, iTargetPos, true, selfPos, false, true);
                                            }
                                        }
                                    }
                                    if (Aim.Helper.AutoUltimate.Argus) {
                                        if (EnemyDistance < TargetDistance && MyHealth <= 2500) {
                                            if (Vector3::Normalized(_Position - selfPos) != Vector3::zero()) {
                                                orig_TryUseSkill(instance, 4530, iTargetPos, true, selfPos, false, true);
                                            }
                                        }
                                    }
                                    //Auto Defense
                                    if (Aim.Helper.AutoDefense.Executed) {
                                        if (EnemyDistance < TargetDistance && CurHP <= TargetHP) {
                                            if (Vector3::Normalized(_Position - selfPos) != Vector3::zero()) {
                                                orig_TryUseSkill(instance, 20150, iTargetPos, true, selfPos, false, true);
                                            }
                                        }
                                    }
                                    //Flameshot Auto
     if (Aim.Helper.MoreFeature.FlameShoot) {
        if (Distance < 16.0f ) {
        if (PercentHP <= 15) {
        if (_Position != Vector3::zero()) {
       orig_TryUseSkill(instance, 20140, Vector3::Normalized(_Position - selfPos), true, selfPos, false, true);
     
  }}}}
  
  if (Aim.Helper.MoreFeature.Alucards) {
        if (skillId == 710 && Distance < 5) {
        if (_Position != Vector3::zero()) {     
        orig_TryUseSkill(instance, 710, Vector3::Normalized(_Position - selfPos), true, _Position, false, true);
        orig_TryUseSkill(instance, 720, Vector3::Normalized(_Position - selfPos), true, selfPos, false, true);
        }}}
		
		
		////Vexana 2+1
      if (Aim.Helper.MoreFeature.Vexanas) {
                            if (skillId == 3820 && Distance < 6.0f) { 
                                if (_Position != Vector3::zero()) {
                                orig_TryUseSkill(instance, 3820, Vector3::Normalized(_Position - selfPos), true, _Position, false, true);
                                orig_TryUseSkill(instance, 3810, Vector3::Normalized(_Position - selfPos), true, _Position, false, true);
                                }}}
        
   
								
								
								
	    if  (Aim.Helper.MoreFeature.Arlot) {
        if (skillId ==  11900&& Distance<8) {
        if (_Position != Vector3::zero()) {     
                                isDoneAim = true;
        orig_TryUseSkill(instance, 11910, Vector3::Normalized(_Position - selfPos), true, selfPos, false, true);
        orig_TryUseSkill(instance, 11920, Vector3::Normalized(_Position - selfPos), true, selfPos, false, true);
        if (skillId ==  11900&& Distance<8) {
        if (_Position != Vector3::zero()) {     
        isDoneAim = true;
        orig_TryUseSkill(instance, 11920, Vector3::Normalized(_Position - selfPos), true, selfPos, false, true);
        orig_TryUseSkill(instance, 11930, Vector3::Normalized(_Position - selfPos), true, selfPos, false, true);
        }
        }}}}
		
		
		
		
	        /////Auto Skill Within Low Hp Player////////
              if (Aim.Helper.Skills.Execute) {
              if (Distance < 10 && CurHP < MaxHP) {
              if (CurHP <= 550 ) {
              isDoneAim = true;
              orig_TryUseSkill(instance, 20150, Vector3::Normalized(_Position - selfPos), true, Vector3::zero(), false, true);
              }}}
                                    if (Aim.Helper.AutoDefense.Vengeance) {
                                        if (EnemyDistance < TargetDistance && MyHealth <= 2500) {
                                            if (Vector3::Normalized(_Position - selfPos) != Vector3::zero()) {
                                                orig_TryUseSkill(instance, 20150, iTargetPos, true, selfPos, false, true);
                                            }
                                        }
                                    }
                                    if (Aim.Helper.AutoDefense.Flicker) {
                                        if (EnemyDistance < TargetDistance && MyHealth <= 2500) {
                                            if (Vector3::Normalized(_Position - selfPos) != Vector3::zero()) {
                                                orig_TryUseSkill(instance, 20140, iTargetPos, true, selfPos, false, true);
                                            }
                                        }
                                    }
                                    if (Aim.Helper.AutoDefense.Aegis) {
                                        if (EnemyDistance < TargetDistance && MyHealth <= 2500) {
                                            if (Vector3::Normalized(_Position - selfPos) != Vector3::zero()) {
                                                orig_TryUseSkill(instance, 20140, iTargetPos, true, selfPos, false, true);
                                                }
                                            }
                                        }
										
										
			        monoList<void **> *_RunBullets;
                    Il2CppGetStaticFieldValue("Assembly-CSharp.dll", "", "BattleManager", "_RunBullets", &_RunBullets);
                      if (_RunBullets) {
                        for (int i = 0; i < _RunBullets->getSize(); i++) {
                            auto Pawn = _RunBullets->getItems()[i];
                            if (!Pawn) continue;
                            auto m_ID = *(int *) ((uintptr_t)Pawn + Bullet_m_Id);
                            if (m_ID != 8452) continue;
                            auto transform = *(Transform **) ((uintptr_t)Pawn + Bullet_transform);
                            float Distance = (int) Vector3::Distance(selfPos, transform->get_position());
                            if (Distance < 5) {
                                if (Aim.Helper.Priority.AutoTakeSword && Distance < MaxSwordDist) {
                                    SwordPos = transform->get_position();
                                    MaxSwordDist = Distance;
                                }
                            }//EntityPos
                        }//Aim
                    }//Aim
                }}}}//Aim
				
                        //Basic
                        if (EntityPos != Vector3::zero()) {
                        auto targetLockPos = Vector3::Normalized(EntityPos - selfPos);
                        if (Aim.Helper.Skills.Basic) {
                            if (skillId == 100 * HeroID + 00) {
                                isDoneAim = true;
                                orig_TryUseSkill(instance, skillId, targetLockPos, dirDefault, pos, bCommonAtk, bAuto, bAlong, bCache, isInFirstDragRange);
                            }
                        }
                        //Spell
                        if (Aim.Helper.Skills.Spell) {
                            if (skillId == 20100 || skillId == 20140) {
                                isDoneAim = true;
                                orig_TryUseSkill(instance, skillId, targetLockPos, dirDefault, pos, bCommonAtk, bAuto, bAlong, bCache, isInFirstDragRange);
                            }
                        }
                        //Skill 1
                        if (Aim.Helper.Skills.Skill1) {
                            if (skillId == 100 * HeroID + 10) {
                                isDoneAim = true;
                                orig_TryUseSkill(instance, skillId, targetLockPos, dirDefault, pos, bCommonAtk, bAuto, bAlong, bCache, isInFirstDragRange);
                            }
                        }
                        //Skill 2
                        if (Aim.Helper.Skills.Skill2) {
                            if (skillId == 100 * HeroID + 20 || skillId == 2010520 /*Beatrix Skill2*/) {
                                isDoneAim = true;
                                orig_TryUseSkill(instance, skillId, targetLockPos, dirDefault, pos, bCommonAtk, bAuto, bAlong, bCache, isInFirstDragRange);
                            }
                        }
                        //Skill 3
                        if (Aim.Helper.Skills.Skill3) {
                            if (skillId == 100 * HeroID + 30 || skillId == 2010530 /*Beatrix Ulti*/) {
                                isDoneAim = true;
                                orig_TryUseSkill(instance, skillId, targetLockPos, dirDefault, pos, bCommonAtk, bAuto, bAlong, bCache, isInFirstDragRange);
                            }
                        }
                        //Skill 4
                        if (Aim.Helper.Skills.Skill4) {
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

int CalculateRetriDamage(int m_Level, int m_KillWildTimes) {
    if (m_KillWildTimes < 5) {
        return 520 + (80 * m_Level);
    } else {
        return 1.5 * (520 + (80 * m_Level));
    }
}

void (*orig_UpdateRetribution)(void *instance);
void UpdateRetribution(void *instance) {
	
	
	
	if (Aim.Helper.MoreFeature.Ling) {  
float MaxDist = std::numeric_limits<float>::infinity();
        Vector3 EntityPos = Vector3::zero();
        Vector3 Hp;
        float MaxEnemyHP = std::numeric_limits<float>::infinity();
        void *BattleManager_Instance;
        Il2CppGetStaticFieldValue("Assembly-CSharp.dll", "", "BattleManager", "Instance", &BattleManager_Instance);
        if (BattleManager_Instance) {
            auto m_LocalPlayerShow = *(uintptr_t *) ((uintptr_t)BattleManager_Instance + BattleManager_m_LocalPlayerShow);
            if (m_LocalPlayerShow) {
                auto selfPos = *(Vector3 *) ((uintptr_t)m_LocalPlayerShow + ShowEntity__Position);
                auto LogicPlayerFighter = *(void **)((long)m_LocalPlayerShow + ShowEntity__logicFighter);  
                auto HeroID = *(int *) ((uintptr_t)m_LocalPlayerShow + EntityBase_m_ID);
                if (selfPos != Vector3::zero()) {
                    monoList<void **> *_RunBullets;
                    Il2CppGetStaticFieldValue("Assembly-CSharp.dll", "", "BattleManager", "_RunBullets", &_RunBullets);
                       if (_RunBullets) {
                        for (int i = 1; i < _RunBullets->getSize(); i++) {
                            auto Pawn = _RunBullets->getItems()[i];
                            if (!Pawn) continue;
                            auto m_ID = *(int *) ((uintptr_t)Pawn + Bullet_m_Id);
                            if (m_ID != 8452) continue;
                            
                            auto _Position = *(Transform **) ((uintptr_t)Pawn + Bullet_transform);
                            float Distance = (int) Vector3::Distance(selfPos, _Position->get_position());                        
                             if (Distance < 5.0f) {
                                    EntityPos = _Position->get_position();
                            }
                         if (EntityPos != Vector3::zero()) {
orig_TryUseSkill(instance, 8420, Vector3::Normalized(EntityPos - selfPos), true, Vector3::Distance(selfPos, _Position->get_position()), true, true);
                         }
}}}}}}
	
	
	
	
	
	
	
	
    if (Aim.Helper.AutoRetribution.Buff || Aim.Helper.AutoRetribution.Lord || Aim.Helper.AutoRetribution.Turtle || Aim.Helper.AutoRetribution.Crab || Aim.Helper.AutoRetribution.Litho) {
        if (instance != NULL) {
            void *BattleManager_Instance;
            Il2CppGetStaticFieldValue("Assembly-CSharp.dll", "", "BattleManager", "Instance", &BattleManager_Instance);
            if (BattleManager_Instance) {
                auto m_LocalPlayerShow = *(uintptr_t *) ((uintptr_t)BattleManager_Instance + BattleManager_m_LocalPlayerShow);
                if (m_LocalPlayerShow) {
                    auto selfPos = *(Vector3 *) ((uintptr_t)m_LocalPlayerShow + ShowEntity__Position);
                    if (selfPos != Vector3::zero()) {
                        auto m_Level = *(int *) ((uintptr_t)m_LocalPlayerShow + EntityBase_m_Level);
                        auto _logicFighter = *(uintptr_t *) ((uintptr_t)m_LocalPlayerShow + ShowEntity__logicFighter);
                        int iCalculateDamage;
                        if (_logicFighter) {
                            auto m_KillWildTimes = *(int *) ((uintptr_t)_logicFighter + LogicPlayer_m_KillWildTimes);
                            iCalculateDamage = CalculateRetriDamage(m_Level, m_KillWildTimes);
                        }
                        monoList<void **> *m_ShowMonsters = *(monoList<void **> **) ((uintptr_t)BattleManager_Instance + BattleManager_m_ShowMonsters);
                        if (m_ShowMonsters) {
                            for (int i = 0; i < m_ShowMonsters->getSize(); i++) {
                                auto Pawn = m_ShowMonsters->getItems()[i];
                                if (!Pawn) continue;
                                auto m_ID = *(int *) ((uintptr_t)Pawn + EntityBase_m_ID);
                                if (MonsterToString(m_ID) == "") continue;
                                auto m_bSameCampType = *(bool *) ((uintptr_t)Pawn + EntityBase_m_bSameCampType);
                                if (m_bSameCampType) continue;
                                auto m_bDeath = *(bool *) ((uintptr_t)Pawn + EntityBase_m_bDeath);
                                if (m_bDeath) continue;
                                auto m_IsDeathProgress = *(bool *) ((uintptr_t)Pawn + EntityBase_m_IsDeathProgress);
                                if (m_IsDeathProgress) continue;
                                auto _Position = *(Vector3 *) ((uintptr_t)Pawn + ShowEntity__Position);
                                float Distance = (int) Vector3::Distance(selfPos, _Position);
                                float CurHP = *(int *) ((uintptr_t)Pawn + EntityBase_m_Hp);
                                float MaxHP = *(int *) ((uintptr_t)Pawn + EntityBase_m_HpMax);
                                if (!m_bDeath && !m_IsDeathProgress) {
                                    if (Distance < 8.0f && CurHP < MaxHP) {
                                        if (CurHP <= iCalculateDamage) {
                                            if (m_ID == 2004 && Aim.Helper.AutoRetribution.Buff || m_ID == 2005 && Aim.Helper.AutoRetribution.Buff || m_ID == 2002 && Aim.Helper.AutoRetribution.Lord || m_ID == 2003 && Aim.Helper.AutoRetribution.Turtle || m_ID == 2013 && Aim.Helper.AutoRetribution.Crab || m_ID == 2011 && Aim.Helper.AutoRetribution.Crab || m_ID == 2072 && Aim.Helper.AutoRetribution.Litho || m_ID == 2056 && Aim.Helper.AutoRetribution.Litho) {
                                                if (Vector3::Normalized(_Position - selfPos) != Vector3::zero()) {
                                                    orig_TryUseSkill(instance, 20020, Vector3::Normalized(_Position - selfPos), true, Vector3::zero(), false, true);
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
    }
    orig_UpdateRetribution(instance);
}


