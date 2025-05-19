#pragma once

#include "StructOffset.h"
#include "Enum.h"

bool isPlayerLine;

struct sConfig {
    struct sESP {
        struct sPlayer {
            bool Line;
            bool Box;
            bool Health;
            bool Name;
            bool Distance;
            bool Hero;
            bool Alert;
            bool Visible;
        };
        sPlayer Player{0};

        struct sMonster {
            bool Box;
            bool Health;
            bool Name;
            bool Alert;
        };
        sMonster Monster{0};
		
		struct sColor {
            int Value = 0;
        };
        sColor Color{0};
		
    };
    sESP ESP{0};

};
sConfig Config{0};


void DrawCircleHealth(ImVec2 position, int health, int max_health, float radius) {
    float a_max = ((3.14159265359f * 2.0f));
    ImU32 healthColor = IM_COL32(0, 160, 0, 230); // GREEN
    if (health <= (max_health * 0.6)) {
        healthColor = IM_COL32(255, 255, 0, 110); // YELLOW
    }
    if (health < (max_health * 0.3)) {
        healthColor = IM_COL32(255, 0, 0, 255); // RED
    }
    ImGui::GetForegroundDrawList()->PathArcTo(position, radius, (-(a_max / 4.0f)) + (a_max / max_health) * (max_health - health), a_max - (a_max / 4.0f));
    ImGui::GetForegroundDrawList()->PathStroke(healthColor, ImDrawFlags_None, 4);
}

static float SetFieldOfView = 0, GetFieldOfView = 0;

void DroneView() {
    if (GetFieldOfView == 0) {
        GetFieldOfView = get_fieldOfView();
    }
    if (SetFieldOfView > 0 && GetFieldOfView != 0) {
        set_fieldOfView((float)GetFieldOfView + SetFieldOfView);
    }
    if (SetFieldOfView == 0 && GetFieldOfView != 0) {
        set_fieldOfView((float)GetFieldOfView);
    }
}



template <typename T>
struct monoArray
{
    void* klass;
    void* monitor;
    void* bounds;
    int   max_length;
    void* vector [1];
    int getLength()
    {
        return max_length;
    }
    T getPointer()
    {
        return (T)vector;
    }
};

template <typename T>
struct monoList {
    void *unk0;
    void *unk1;
    monoArray<T> *items;
    int size;
    int version;

    T getItems(){
        return items->getPointer();
    }

    int getSize(){
        return size;
    }

    int getVersion(){
        return version;
    }
};


#define DefineHook(RET, NAME, ARGS) \
    RET (*o ## NAME) ARGS; \
    RET NAME ARGS


void CalculateRainbowColors(ImVec4& color1, ImVec4& color2, ImVec4& color3, ImVec4& color4) {
    float frequency = 0.1f;
    float phase = ImGui::GetTime() * 0.1f;

    color1 = ImVec4(0.5f + 0.5f * cos(frequency * 0 + phase), 0.5f + 0.5f * cos(frequency * 120 + phase), 0.5f + 0.5f * cos(frequency * 240 + phase), 1.0f);
    color2 = ImVec4(0.5f + 0.5f * cos(frequency * 120 + phase), 0.5f + 0.5f * cos(frequency * 240 + phase), 0.5f + 0.5f * cos(frequency * 360 + phase), 1.0f);
    color3 = ImVec4(0.5f + 0.5f * cos(frequency * 240 + phase), 0.5f + 0.5f * cos(frequency * 360 + phase), 0.5f + 0.5f * cos(frequency * 480 + phase), 1.0f);
    color4 = ImVec4(0.5f + 0.5f * cos(frequency * 360 + phase), 0.5f + 0.5f * cos(frequency * 480 + phase), 0.5f + 0.5f * cos(frequency * 600 + phase), 1.0f);
}

void DrawRainbowQuad(ImDrawList* draw, const ImVec2& p1, const ImVec2& p2, const ImVec2& p3, const ImVec2& p4) {
    ImVec4 color1, color2, color3, color4;
    CalculateRainbowColors(color1, color2, color3, color4);

    draw->AddQuadFilled(p1, p2, p3, p4, IM_COL32(int(color1.x * 255), int(color1.y * 255), int(color1.z * 255), 255));
}
void DrawRainbowText(ImDrawList* draw, const ImVec2& position, const char* text) {
    ImVec2 charPos = position;
    float frequency = 0.1f;
    float phase = ImGui::GetTime() * 0.1f;

    for (int i = 0; i < strlen(text); ++i) {
        float hue = fmod(ImGui::GetTime() * 0.1f + i * 0.1f, 1.0f);
        ImVec4 tempColor;
        ImGui::ColorConvertHSVtoRGB(hue, 1.0f, 1.0f, tempColor.x, tempColor.y, tempColor.z);
        ImU32 charColor = IM_COL32(int(tempColor.x * 255), int(tempColor.y * 255), int(tempColor.z * 255), 255);

        char str[2] = { text[i], '\0' };
        draw->AddText(charPos, charColor, str);
        charPos.x += ImGui::CalcTextSize(str).x;
    }
}

void Draw_ESP(ImDrawList *draw, int screenWidth, int screenHeight) 
{
    void *BattleBridge_Instance;
    IL2Cpp::Il2CppGetStaticFieldValue("Assembly-CSharp.dll", "", "BattleData", "m_BattleBridge", &BattleBridge_Instance);
    if (BattleBridge_Instance) 
    {
        auto _bStartBattle = *(bool *) ((uintptr_t)BattleBridge_Instance + BattleBridge_bStartBattle);
        if (_bStartBattle) 
        {
			DroneView();
            void *BattleManager_Instance;
            IL2Cpp::Il2CppGetStaticFieldValue("Assembly-CSharp.dll", "", "BattleManager", "Instance", &BattleManager_Instance);
            if (BattleManager_Instance) 
            {
                auto m_LocalPlayerShow = *(uintptr_t *) ((uintptr_t)BattleManager_Instance + BattleManager_m_LocalPlayerShow);
                if (m_LocalPlayerShow) 
                {
                    auto selfPos = *(Vector3 *) ((uintptr_t)m_LocalPlayerShow + ShowEntity__Position);
                    if (selfPos != Vector3::zero()) 
                    {
                        auto SelfPosW2S = WorldToScreen(selfPos);
                        auto SelfPosVec2 = ImVec2(screenWidth - SelfPosW2S.x, SelfPosW2S.y);
                        if (SelfPosW2S.z > 0) 
                        {
                            SelfPosVec2 = ImVec2(SelfPosW2S.x, screenHeight - SelfPosW2S.y);
                        }
                        
                        monoList<void **> *m_ShowPlayers = *(monoList<void **> **) ((uintptr_t)BattleManager_Instance + BattleManager_m_ShowPlayers);
                        if (m_ShowPlayers) 
                        {
                            for (int i = 0; i < m_ShowPlayers->getSize(); i++) 
                            {
                                auto Pawn = m_ShowPlayers->getItems()[i];
                                if (!Pawn) continue;
                                auto m_bSameCampType = *(bool *) ((uintptr_t)Pawn + EntityBase_m_bSameCampType);
                                if (m_bSameCampType) continue;
                                auto m_bDeath = *(bool *) ((uintptr_t)Pawn + EntityBase_m_bDeath);
                                if (m_bDeath) continue;
                                auto canSight = *(bool *) ((uintptr_t)Pawn + EntityBase_canSight);
                                auto CurHP = *(int *) ((uintptr_t)Pawn + EntityBase_m_Hp);
                                auto MaxHP = *(int *) ((uintptr_t)Pawn + EntityBase_m_HpMax);
                                auto _Position = *(Vector3 *) ((uintptr_t)Pawn + ShowEntity__Position);

                                auto *m_RoleName = *(MonoString **) ((uintptr_t)Pawn + ShowEntity_m_RoleName);
                                auto *m_HeroName = *(MonoString **) ((uintptr_t)Pawn + ShowPlayer_m_HeroName);

                                auto HeroID = *(int *) ((uintptr_t)Pawn + EntityBase_m_ID);

                                int Distance = (int) Vector3::Distance(selfPos, _Position);
                                auto RootPosW2S = WorldToScreen(_Position);
                                auto RootPosVec2 = Vector2(screenWidth - RootPosW2S.x, RootPosW2S.y);
                                if (RootPosW2S.z > 0) 
                                {
                                    RootPosVec2 = Vector2(RootPosW2S.x, screenHeight - RootPosW2S.y);
                                }
                                
                                
                                auto HeadPosVec2 = Vector2(RootPosVec2.x, RootPosVec2.y - (screenHeight / 6.35));

                                //Esp Visible
                                if (Config.ESP.Player.Visible) 
                                {
                                    if (canSight && !isOutsideScreen(ImVec2(RootPosVec2.x, RootPosVec2.y), ImVec2(screenWidth, screenHeight)))
                                        continue;
                                }
                                
                                if (Config.ESP.Player.Line) {
    // Calculate rainbow color based on time
    ImColor rainbowColor = ImColor::HSV(ImGui::GetTime() / 5.0f, 1.0f, 1.0f);

    // Draw the line with rainbow color
    draw->AddLine(SelfPosVec2, ImVec2(RootPosVec2.x, RootPosVec2.y), IM_COL32(rainbowColor.Value.x * 255, rainbowColor.Value.y * 255, rainbowColor.Value.z * 255, 255), 1.7f);
}
                                
                               if (Config.ESP.Player.Box) {
    float boxHeight = abs(HeadPosVec2.y - RootPosVec2.y);
    float boxWidth = boxHeight * 0.70f;
    ImVec2 vStart = { HeadPosVec2.x - (boxWidth / 2), HeadPosVec2.y };
    ImVec2 vEnd = { vStart.x + boxWidth, vStart.y + boxHeight };

    // Calculate rainbow color based on time
    ImColor rainbowColor = ImColor::HSV(ImGui::GetTime() / 5.0f, 1.0f, 1.0f);

    // Draw the rectangle with rainbow color
    draw->AddRect(vStart, vEnd, IM_COL32(rainbowColor.Value.x * 255, rainbowColor.Value.y * 255, rainbowColor.Value.z * 255, 255), 1.7f);
}
                                
if (Config.ESP.Player.Health) {
    auto LineHealthStart = ImVec2(RootPosVec2.x + 55, RootPosVec2.y - 30);
    auto LineHealthEnd = ImVec2(LineHealthStart.x + 160, LineHealthStart.y);
    auto HealthStart = ImVec2(LineHealthStart.x, LineHealthStart.y - 20);
    auto HealthEnd = ImVec2(LineHealthEnd.x, LineHealthEnd.y - 5);
    float healthWidth = abs(HealthEnd.x - HealthStart.x);
    float PercentHP = ((float)CurHP * healthWidth) / (float)MaxHP;

    // Calculate damage taken
    float DamageTaken = MaxHP - CurHP;

    draw->AddLine(LineHealthStart, LineHealthEnd, IM_COL32(255, 255, 255, 155));
    draw->AddRectFilled(HealthStart, ImVec2(HealthStart.x + PercentHP, HealthEnd.y), IM_COL32(255, 0, 0, 255), 10);
    draw->AddRect(HealthStart, HealthEnd, IM_COL32(255, 255, 255, 255), 10);
	
	ImVec2 lineHeadDot = { LineHealthStart.x, LineHealthStart.y };
    draw->AddCircleFilled(lineHeadDot, 2.0f, IM_COL32(255, 255, 255, 255), 32);
	
	ImVec2 leftHealthDot = { HealthStart.x - 10, (HealthStart.y + HealthEnd.y) / 2 };
    ImVec2 rightHealthDot = { HealthEnd.x + 10, (HealthStart.y + HealthEnd.y) / 2 };
    draw->AddCircleFilled(leftHealthDot, 2.0f, IM_COL32(255, 255, 255, 255), 32);
    draw->AddCircleFilled(rightHealthDot, 2.0f, IM_COL32(255, 255, 255, 255), 32);

    // Add health remaining text
    char healthText[32];
    snprintf(healthText, sizeof(healthText), "%.0f%%", (PercentHP / healthWidth) * 100);
    ImVec2 textPos = ImVec2(HealthEnd.x + 5, HealthEnd.y - 10);
    draw->AddText(textPos, IM_COL32(255, 255, 255, 255), healthText);
	
	ImVec2 leftDot = { LineHealthStart.x - 20, LineHealthStart.y };
    ImVec2 centerLeftDot = { LineHealthStart.x - 40, LineHealthStart.y };
    ImVec2 rightDot = { LineHealthEnd.x + 20, LineHealthEnd.y };
    ImVec2 centerRightDot = { LineHealthEnd.x + 40, LineHealthEnd.y };
    draw->AddCircleFilled(leftDot, 3.0f, IM_COL32(255, 255, 255, 255), 32);
    draw->AddCircleFilled(centerLeftDot, 3.0f, IM_COL32(255, 255, 255, 255), 32);
    draw->AddCircleFilled(rightDot, 3.0f, IM_COL32(255, 255, 255, 255), 32);
    draw->AddCircleFilled(centerRightDot, 3.0f, IM_COL32(255, 255, 255, 255), 32);

    // Add damage taken text
    char curHPText[32];
    snprintf(curHPText, sizeof(curHPText), "Damage Taken: %.0f", DamageTaken);
    ImVec2 textPosition = ImVec2(LineHealthStart.x, LineHealthStart.y + 5);
	DrawRainbowText(draw, textPosition, curHPText);
}
                                
                                   if (Config.ESP.Player.Name || Config.ESP.Player.Hero) {
                                    if (Config.ESP.Player.Name && Config.ESP.Player.Hero) {
                                        if (m_RoleName && m_HeroName) {
                                            std::string strName = "(" + m_HeroName->toString() + ") " + m_RoleName->toString();
                                            auto textSize = ImGui::CalcTextSize2(strName.c_str(), 0, ((float) screenHeight / 39.0f));
                                            draw->AddText(NULL, ((float) screenHeight / 39.0f), {RootPosVec2.x - (textSize.x / 2), RootPosVec2.y + 25}, IM_COL32(255, 255, 255, 255), strName.c_str());
                                        }
                                        
                                    //Esp Player Name
                                    } else if (Config.ESP.Player.Name) {
                                        if (m_RoleName) {
                                            std::string strName = m_RoleName->toString();
                                            auto textSize = ImGui::CalcTextSize2(strName.c_str(), 0, ((float) screenHeight / 39.0f));
                                            draw->AddText(NULL, ((float) screenHeight / 39.0f), {RootPosVec2.x - (textSize.x / 2), RootPosVec2.y + 25}, IM_COL32(255, 255, 255, 255), strName.c_str());
                                        }
                                        
                                    //
                                    } else if (Config.ESP.Player.Hero) {
                                        if (m_HeroName) {
                                            std::string strName = "(" + m_HeroName->toString() + ")";
                                            auto textSize = ImGui::CalcTextSize2(strName.c_str(), 0, ((float) screenHeight / 39.0f));
                                            draw->AddText(NULL, ((float) screenHeight / 39.0f), {RootPosVec2.x - (textSize.x / 2), RootPosVec2.y + 25}, IM_COL32(255, 255, 255, 255), strName.c_str());
                                        }
                                    }
                                }
                                
                                if (Config.ESP.Player.Distance) 
                                {
                                    std::string strDistance = to_string(Distance) + "M";
                                    auto textSize = ImGui::CalcTextSize2(strDistance.c_str(), 0, ((float) screenHeight / 39.0f));
                                    draw->AddText(NULL, ((float) screenHeight / 39.0f), {RootPosVec2.x - (textSize.x / 2), RootPosVec2.y + 5}, IM_COL32(255, 255, 255, 255), strDistance.c_str());
                                }
                                        
                        
                               if (Config.ESP.Player.Alert && isOutsideScreen(ImVec2(RootPosVec2.x, RootPosVec2.y), ImVec2(screenWidth, screenHeight))) 
                                {
                                    ImVec2 hintDotRenderPos = pushToScreenBorder(ImVec2(RootPosVec2.x, RootPosVec2.y), ImVec2(screenWidth, screenHeight), - 50);
                                    ImVec2 hintTextRenderPos = pushToScreenBorder(ImVec2(RootPosVec2.x, RootPosVec2.y), ImVec2(screenWidth, screenHeight), - 50);
                                    draw->AddCircleFilled(hintDotRenderPos, 25, IM_COL32(255, 0, 0, 110));
                                    DrawCircleHealth(hintDotRenderPos, CurHP, MaxHP, 25);
                                    std::string strDistance = to_string(Distance) + " M";
                                    auto textSize = ImGui::CalcTextSize2(strDistance.c_str(), 0, ((float) screenHeight / 45.0f));
                                    draw->AddText(NULL, ((float) screenHeight / 45.0f), {hintTextRenderPos.x - (textSize.x / 2), hintTextRenderPos.y - 7}, IM_COL32(255, 255, 255, 255), strDistance.c_str());
                                    
                                    if (m_HeroName) 
                                    {
                                        std::string strName = m_HeroName->toString();
                                        auto textSize = ImGui::CalcTextSize2(strName.c_str(), 0, ((float) screenHeight / 39.0f));
                                        draw->AddText(NULL, ((float) screenHeight / 39.0f), {hintTextRenderPos.x - (textSize.x / 2), hintTextRenderPos.y + 30}, IM_COL32(255, 255, 255, 255), strName.c_str());
                                    }
                                }
                            }
                        }
                    }

                    monoList<void **> *m_ShowMonsters = *(monoList<void **> **) ((uintptr_t)BattleManager_Instance + BattleManager_m_ShowMonsters);
                    if (m_ShowMonsters) 
                    {
                        for (int i = 0; i < m_ShowMonsters->getSize(); i++) 
                        {
                            auto Pawn = m_ShowMonsters->getItems()[i];
                            if (!Pawn) continue;
                            auto m_ID = *(int *) ((uintptr_t)Pawn + EntityBase_m_ID);
                            if (MonsterToString(m_ID) == "") continue;
                            auto m_bSameCampType = *(bool *) ((uintptr_t)Pawn + EntityBase_m_bSameCampType);
                            if (m_bSameCampType) continue;
                            auto m_bDeath = *(bool *) ((uintptr_t)Pawn + EntityBase_m_bDeath);
                            if (m_bDeath) continue;
                            auto CurHP = *(int *) ((uintptr_t)Pawn + EntityBase_m_Hp);
                            auto MaxHP = *(int *) ((uintptr_t)Pawn + EntityBase_m_HpMax);
                            auto _Position = *(Vector3 *) ((uintptr_t)Pawn + ShowEntity__Position);
                            auto RootPosW2S = WorldToScreen(_Position);
                            auto RootPosVec2 = Vector2(screenWidth - RootPosW2S.x, RootPosW2S.y);
                            
                            if (RootPosW2S.z > 0) 
                            {
                                RootPosVec2 = Vector2(RootPosW2S.x, screenHeight - RootPosW2S.y);
                            }
                            
                            auto HeadPosVec2 = Vector2(RootPosVec2.x, RootPosVec2.y - (screenHeight / 6.35));
                            
                          if (Config.ESP.Monster.Box) {
                                float boxHeight = abs(HeadPosVec2.y - RootPosVec2.y);
                                float boxWidth = boxHeight * 0.75f;
                                ImVec2 vStart = {HeadPosVec2.x - (boxWidth / 2), HeadPosVec2.y};
                                ImVec2 vEnd = {vStart.x + boxWidth, vStart.y + boxHeight};
                                draw->AddRect(vStart, vEnd, IM_COL32(255, 0, 0, 255),1.7f);
                                }
                                
                            if (Config.ESP.Monster.Health) {
    auto LineHealthStart = ImVec2(RootPosVec2.x + 55, RootPosVec2.y - 30);
    auto LineHealthEnd = ImVec2(LineHealthStart.x + 160, LineHealthStart.y);
    auto HealthStart = ImVec2(LineHealthStart.x, LineHealthStart.y - 20);
    auto HealthEnd = ImVec2(LineHealthEnd.x, LineHealthEnd.y - 5);

    float healthWidth = abs(HealthEnd.x - HealthStart.x);
    float PercentHP = ((float)CurHP * healthWidth) / (float)MaxHP;

    // Draw line head dot
    ImVec2 lineHeadDot = { LineHealthStart.x, LineHealthStart.y };
    draw->AddCircleFilled(lineHeadDot, 3.0f, IM_COL32(255, 255, 255, 255), 32);

    // Draw line with dots
    draw->AddLine(LineHealthStart, LineHealthEnd, IM_COL32(255, 255, 255, 255));

    // Draw dots on the line
    ImVec2 leftDot = { LineHealthStart.x - 20, LineHealthStart.y };
    ImVec2 centerLeftDot = { LineHealthStart.x - 40, LineHealthStart.y };
    ImVec2 rightDot = { LineHealthEnd.x + 20, LineHealthEnd.y };
    ImVec2 centerRightDot = { LineHealthEnd.x + 40, LineHealthEnd.y };
    draw->AddCircleFilled(leftDot, 3.0f, IM_COL32(255, 255, 255, 255), 32);
    draw->AddCircleFilled(centerLeftDot, 3.0f, IM_COL32(255, 255, 255, 255), 32);
    draw->AddCircleFilled(rightDot, 3.0f, IM_COL32(255, 255, 255, 255), 32);
    draw->AddCircleFilled(centerRightDot, 3.0f, IM_COL32(255, 255, 255, 255), 32);

    // Draw health bar
    draw->AddRectFilled(HealthStart, ImVec2(HealthStart.x + PercentHP, HealthEnd.y), IM_COL32(255, 153, 0, 255));
    draw->AddRect(HealthStart, HealthEnd, IM_COL32(0, 0, 0, 255), 5);

    // Draw additional dots on the left and right of the health bar
    ImVec2 leftHealthDot = { HealthStart.x - 10, (HealthStart.y + HealthEnd.y) / 2 };
    ImVec2 rightHealthDot = { HealthEnd.x + 10, (HealthStart.y + HealthEnd.y) / 2 };
    draw->AddCircleFilled(leftHealthDot, 3.0f, IM_COL32(255, 255, 255, 255), 32);
    draw->AddCircleFilled(rightHealthDot, 3.0f, IM_COL32(255, 255, 255, 255), 32);

    // Draw CurHP in rainbow text
    char curHPText[16];
    sprintf(curHPText, "Health: %d", CurHP);
    ImVec2 textPosition = { HealthEnd.x + 20, (HealthStart.y + HealthEnd.y) / 2 };
    DrawRainbowText(draw, textPosition, curHPText);
}
                            
                                 if (Config.ESP.Monster.Name) {
                                std::string strName = MonsterToString(m_ID);
                                auto textSize = ImGui::CalcTextSize2(strName.c_str(), 0, ((float) screenHeight / 39.0f));
                                draw->AddText(NULL, ((float) screenHeight / 39.0f), {RootPosVec2.x - (textSize.x / 2), RootPosVec2.y + 25}, IM_COL32(255, 255, 255, 255), strName.c_str());
                                }
                            
                            if (Config.ESP.Monster.Alert) 
                            {
                                if (m_ID == 2002 && CurHP < MaxHP) 
                                {
                                    std::string strAlert = "[ALERT] Lord is under attack!";
                                    auto textSize = ImGui::CalcTextSize2(strAlert.c_str(), 0, ((float) screenHeight / 31.0f));
                                    draw->AddText(NULL, ((float) screenHeight / 31.0f), {(float)(screenWidth / 5) - (textSize.x / 2), (float)(screenHeight - screenHeight) + (float)(screenHeight / 8.7f)}, IM_COL32(255, 255, 255, 255), strAlert.c_str());
                                }
                                
                                if (m_ID == 2003 && CurHP < MaxHP) 
                                {
                                    std::string strAlert = "[ALERT] Turtle is under attack!";
                                    auto textSize = ImGui::CalcTextSize2(strAlert.c_str(), 0, ((float) screenHeight / 31.0f));
                                    draw->AddText(NULL, ((float) screenHeight / 31.0f), {(float)(screenWidth / 2) - (textSize.x / 2), (float)(screenHeight - screenHeight) + (float)(screenHeight / 8.7f)}, IM_COL32(255, 255, 255, 255), strAlert.c_str());
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

