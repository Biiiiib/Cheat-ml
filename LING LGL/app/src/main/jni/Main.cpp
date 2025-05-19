#include <iostream>
#include <stdio.h>
#include <string>
#include <unistd.h>
#include <stdint.h>
#include <inttypes.h>
#include <vector>
#include <map>
#include <chrono>
#include <fstream>
#include <thread>
#include <pthread.h>
#include <dirent.h>
#include <libgen.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/uio.h>
#include <fcntl.h>
#include <jni.h>
#include <android/log.h>
#include <elf.h>
#include <dlfcn.h>
#include <sys/system_properties.h>
#include <EGL/egl.h>
#include <GLES3/gl3.h>
#include "dobby/dobby.h"
#include "Includes/obfuscate.h"
#include "Unity/Call_Unity.h"
#include "NPmodz/Call_Me.h"
#include "Includes/Logger.h"
#include "Includes/Utils.h"
#include "Menu/Setup.h"

#include "config/Setup.h"
#include "strenc.h"
#define enc(str) OBFUSCATE(str)

static bool setupDone = false;
static bool setupImguiDone = false;
static const char *done = "";
static bool isRoomInfo = false;

extern "C" JNIEXPORT jstring
JNICALL
Java_com_android_support_Main_Login(JNIEnv *env, jobject thiz) {
    return env->NewStringUTF((enc("https://pastebin.com/raw/0yAqb9QC")));
}

EGLBoolean (*orig_eglSwapBuffers)(EGLDisplay dpy, EGLSurface surface);
EGLBoolean _eglSwapBuffers(EGLDisplay dpy, EGLSurface surface) {
    
    eglQuerySurface(dpy, surface, EGL_WIDTH, &glWidth);
    eglQuerySurface(dpy, surface, EGL_HEIGHT, &glHeight);
    
    if (glWidth <= 0 || glHeight <= 0) {
        return eglSwapBuffers(dpy, surface);
    }
    
    if (!setupImguiDone) {
        ImGui::CreateContext();
        
        ImGuiStyle* style = &ImGui::GetStyle();
        style->WindowRounding = 5.3f;
        style->FrameRounding = 2.3f;
        style->ScrollbarRounding = 0;
        style->WindowTitleAlign = ImVec2(0.5, 0.5);
        style->WindowMinSize = ImVec2(400, 180);
        style->FramePadding = ImVec2(8, 6);
        style->ScaleAllSizes(1.0f);
        style->ScrollbarSize /= 1;
        
        ImGui_ImplAndroid_Init();
        ImGui_ImplOpenGL3_Init(OBFUSCATE("#version 300 es"));
        //ImGui::StyleColorsDark();
    //    SetBlackGoldTheme();
        //embraceTheDarkness();
        
        ImGuiIO& io = ImGui::GetIO();
        io.ConfigWindowsMoveFromTitleBarOnly = true;
        io.IniFilename = NULL;
        
        static const ImWchar icons_ranges[] = {0x0020, 0x00FF, 0x3000, 0x30FF, 0x31F0, 0x31FF, 0xFF00, 0xFFEF, 0x4e00, 0x9FAF, 0};
        ImFontConfig icons_config;

        ImFontConfig CustomFont;
        CustomFont.FontDataOwnedByAtlas = false;

        icons_config.MergeMode = true;
        icons_config.PixelSnapH = true;
        icons_config.OversampleH = 2.5;
        icons_config.OversampleV = 2.5;

        io.Fonts->AddFontFromMemoryTTF(const_cast<std::uint8_t*>(Custom), sizeof(Custom), 21.f, &CustomFont);
        io.Fonts->AddFontFromMemoryCompressedTTF(font_awesome_data, font_awesome_size, 19.0f, &icons_config, icons_ranges);
        
        ImFontConfig font_cfg;
        font_cfg.SizePixels = 22.0f;
        io.Fonts->AddFontDefault(&font_cfg);
        
        setupImguiDone = true;
    }
    
    
    ImGuiIO* io = &ImGui::GetIO();
    
    static bool WantTextInputLast = false;
    if (io->WantTextInput && !WantTextInputLast)
        ShowSoftKeyboardInput();
    WantTextInputLast = io->WantTextInput;

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplAndroid_NewFrame(glWidth, glHeight);
    ImGui::NewFrame();
    
    if(setupDone && Config.ESP.Player.Line)
    {
       DrawESP(ImGui::GetBackgroundDrawList(), get_width(), get_height());
    }
    
    //OnTouchEvent();  
	
	Skin();
    
	if (isRoomInfo) {
    ImGui::SetNextWindowSize(ImVec2((float) get_width() * 0.50f, (float) get_height() * 0.20f), ImGuiCond_Once);     
        if(ImGui::BeginTabBar("Tab", ImGuiTabBarFlags_FittingPolicyScroll)) {
            
            if (ImGui::BeginTabItem("Room Info")) {
			RoomInfoList();
                ImGui::TextColored(ImVec4(0.0f, 0.8f, 1.0f, 1.0f), "Team");
                if (ImGui::BeginTable("##Team", 6, ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersInner)) {
                    ImGui::TableSetupColumn("Name", 0, 150);
                    ImGui::TableSetupColumn("User ID", 0, 160);
                    ImGui::TableSetupColumn("Squad", 0, 190);
                    ImGui::TableSetupColumn("Rank", 0, 180);
                    ImGui::TableSetupColumn("Hero", 0, 130);
                    ImGui::TableSetupColumn("Spell", 0, 120);
                    ImGui::TableHeadersRow();
                    for (int row = 0; row < 5; row++) {
                        ImGui::TableNextRow();
                        for (int column = 0; column < 6; column++) {
                            ImGui::TableSetColumnIndex(column);
                            char buf[32];
                            if (column == 0) {
                                sprintf(buf, "%s", RoomInfo.PlayerB[row].Name.c_str());
                                ImGui::TextUnformatted(buf);
                            } else if (column == 1) {
                                sprintf(buf, "%s", RoomInfo.PlayerB[row].UserID.c_str());
                                ImGui::TextUnformatted(buf);
                            } else if (column == 2) {
                                sprintf(buf, "%s", RoomInfo.PlayerB[row].Squad.c_str());
                                ImGui::TextUnformatted(buf);
                            } else if (column == 3) {
                                sprintf(buf, "%s", RoomInfo.PlayerB[row].Rank.c_str());
                                ImGui::TextUnformatted(buf);
                            } else if (column == 4) {
                                sprintf(buf, "%s", RoomInfo.PlayerB[row].Hero.c_str());
                                ImGui::TextUnformatted(buf);
                            } else if (column == 5) {
                                sprintf(buf, "%s", RoomInfo.PlayerB[row].Spell.c_str());
                                ImGui::TextUnformatted(buf);
                            }
                        }
                    }
                    ImGui::EndTable();
                }
                ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "Enemy");
                if (ImGui::BeginTable("##Enemy", 6, ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersInner)) {
                    ImGui::TableSetupColumn("Name", 0, 150);
                    ImGui::TableSetupColumn("User ID", 0, 160);
                    ImGui::TableSetupColumn("Squad", 0, 190);
                    ImGui::TableSetupColumn("Rank", 0, 180);
                    ImGui::TableSetupColumn("Hero", 0, 130);
                    ImGui::TableSetupColumn("Spell", 0, 120);
                    ImGui::TableHeadersRow();
                    for (int row = 0; row < 5; row++) {
                        ImGui::TableNextRow();
                        for (int column = 0; column < 6; column++) {
                            ImGui::TableSetColumnIndex(column);
                            char buf[32];
                            if (column == 0) {
                                sprintf(buf, "%s", RoomInfo.PlayerR[row].Name.c_str());
                                ImGui::TextUnformatted(buf);
                            } else if (column == 1) {
                                sprintf(buf, "%s", RoomInfo.PlayerR[row].UserID.c_str());
                                ImGui::TextUnformatted(buf);
                            } else if (column == 2) {
                                sprintf(buf, "%s", RoomInfo.PlayerR[row].Squad.c_str());
                                ImGui::TextUnformatted(buf);
                            } else if (column == 3) {
                                sprintf(buf, "%s", RoomInfo.PlayerR[row].Rank.c_str());
                                ImGui::TextUnformatted(buf);
                            } else if (column == 4) {
                                sprintf(buf, "%s", RoomInfo.PlayerR[row].Hero.c_str());
                                ImGui::TextUnformatted(buf);
                            } else if (column == 5) {
                                sprintf(buf, "%s", RoomInfo.PlayerR[row].Spell.c_str());
                                ImGui::TextUnformatted(buf);
                            }
                        }
                    }
                    ImGui::EndTable();
                }
                ImGui::EndTabItem();
            }
            ImGui::EndTabBar();
        }
    }
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    if (clearMousePos) {
        io->MousePos = ImVec2(-1, -1);
        clearMousePos = false;
    }
    return orig_eglSwapBuffers(dpy, surface);
}

void *hack_thread(void *) {
    
    Tools::Hook((void *) DobbySymbolResolver(OBFUSCATE("/system/lib/libEGL.so"), OBFUSCATE("eglSwapBuffers")), (void *) _eglSwapBuffers, (void **) &orig_eglSwapBuffers);
 
    while (!m_IL2CPP) {
        m_IL2CPP = Tools::GetBaseAddress(m_IL2CPPLIB);
        sleep(0.5);
    }
    
    
    IL2Cpp::Il2CppAttach(m_IL2CPPLIB);
    sleep(5);
    
    setupDone = true;
    
    done = "DONE";
	

   	Tools::Hook((void *) (uintptr_t)IL2Cpp::Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), "", OBFUSCATE("ShowEntity") , OBFUSCATE("CanSight"), 1), (void *) Qblvs, (void **) &oQblvs);

    Tools::Hook((void *) SystemData_GetHeroSkin, (void *) GetHeroSkin, (void **) &oGetHeroSkin);  
    Tools::Hook((void *) SystemData_GetMCLimitSkin, (void *) GetMCLimitSkin, (void **) &oGetMCLimitSkin);  
    Tools::Hook((void *) SystemData_GetHeroHolyStatue, (void *) GetHeroHolyStatue, (void **) &oGetHeroHolyStatue); 
    Tools::Hook((void *) SystemData_IsCanUseSkin, (void *) IsCanUseSkin, (void **) &oIsCanUseSkin);  
    Tools::Hook((void *) SystemData_IsHaveSkin, (void *) IsHaveSkin, (void **) &oIsHaveSkin); 
    Tools::Hook((void *) SystemData_IsHaveSkinForever, (void *) IsHaveSkinForever, (void **) &oIsHaveSkinForever);
    Tools::Hook((void *) SystemData_IsHaveStatue, (void *) IsHaveStatue, (void **) &oIsHaveStatue);
    Tools::Hook((void *) SystemData_IsHaveStatueForever, (void *) IsHaveStatueForever, (void **) &oIsHaveStatueForever);
    Tools::Hook((void *) SystemData_IsForbidStatue, (void *) IsForbidStatue, (void **) &oIsForbidStatue);
    Tools::Hook((void *) SystemData_IsForbidSkin, (void *) IsForbidSkin, (void **) &oIsForbidSkin);
    Tools::Hook((void *) SystemData_IsForbidARSkin, (void *) IsForbidARSkin, (void **) &oIsForbidARSkin);
    Tools::Hook((void *) UIChooseHero_SendSelectSkin, (void *) SendSelectSkin, (void **) &oSendSelectSkin);
    Tools::Hook((void *) UIChooseHero_SendSelectSkin2, (void *) SendSelectSkin2, (void **) &oSendSelectSkin2);
    Tools::Hook((void *) UIChooseHero_ShowSkinExpiryDate, (void *) ShowSkinExpiryDate, (void **) &oShowSkinExpiryDate);
    Tools::Hook((void *) UIRankHero_BatttleSelectSkin, (void *) BatttleSelectSkin, (void **) &oBatttleSelectSkin);
    Tools::Hook((void *) UIRankHero_BatttleSelectSkin2, (void *) BatttleSelectSkin2, (void **) &oBatttleSelectSkin2);
    Tools::Hook((void *) UIRankHero_ChangeShow_SendUseSkin, (void *) SendUseSkin, (void **) &oSendUseSkin);
    Tools::Hook((void *) BattleReceiveMessage_SetPlayerData, (void *) SetPlayerData, (void **) &oSetPlayerData);
    Tools::Hook((void *) BattleReceiveMessage_AddPlayerInfo, (void *) AddPlayerInfo, (void **) &oAddPlayerInfo); 
    
    
    return NULL;
}

jobjectArray GetFeatureList(JNIEnv *env, jobject context) {
	jobjectArray ret;
	
	const char *features[] = {
	    OBFUSCATE("Category_SAFE FEATURES"),
		OBFUSCATE("14_Toggle_MapHack Full Sight"),
        OBFUSCATE("15_Toggle_Unlock All Skins"),
	
		OBFUSCATE("Category_Esp Player"),
		OBFUSCATE("1_Toggle_Esp Line"),
		OBFUSCATE("2_Toggle_Esp Box"),
		OBFUSCATE("3_Toggle_Esp Health"),
		OBFUSCATE("4_Toggle_Esp Hero Name"),
		OBFUSCATE("5_Toggle_Esp Player Name"),
		OBFUSCATE("6_Toggle_Esp Distance"),
		OBFUSCATE("7_Toggle_Esp Alert"),
		OBFUSCATE("8_Toggle_Esp Visible"),
		
		OBFUSCATE("Category_Drone View"),
		OBFUSCATE("13_SeekBar_Drone View_0_50"),
		
		OBFUSCATE("Category_Esp Jungle"),
		OBFUSCATE("9_Toggle_Esp Monster Box"),
		OBFUSCATE("10_Toggle_Esp Monster Health"),
		OBFUSCATE("11_Toggle_Esp Monster Name"),
		OBFUSCATE("12_Toggle_Esp Monster Alert"),
		
        //OBFUSCATE("15_Toggle_Unlock All Skins"),
		
		//OBFUSCATE("Category_Room Info"),
        //OBFUSCATE("16_Toggle_Room Info [Imgui]"),
		
		OBFUSCATE("Category_AFTER THE GAME PLEASE DELETE"),
        OBFUSCATE("17_ButtonOnOff_Delete Fight History"),       
        OBFUSCATE("18_ButtonOnOff_Delete Battle Record"),
	       
	};
	
	int Total_Feature = (sizeof features / sizeof features[0]);
    ret = (jobjectArray)
            env->NewObjectArray(Total_Feature, env->FindClass(OBFUSCATE("java/lang/String")),
                                env->NewStringUTF(""));

    for (int i = 0; i < Total_Feature; i++)
        env->SetObjectArrayElement(ret, i, env->NewStringUTF(features[i]));

    return (ret);
}

void Changes(JNIEnv *env, jclass clazz, jobject obj, jint featNum, jstring featName, jint value, jboolean boolean, jstring str) {
	LOGD(OBFUSCATE("Feature name: %d - %s | Value: = %d | Bool: = %d | Text: = %s"), featNum, env->GetStringUTFChars(featName, 0), value, boolean, str != NULL ? env->GetStringUTFChars(str, 0) : "");
	
	switch (featNum) {

   case 1:
		Config.ESP.Player.Line = boolean;
        break;
   case 2:
		Config.ESP.Player.Box = boolean;
		break;	
   case 3:
		Config.ESP.Player.Health = boolean;
		break;	
   case 4:
	 	Config.ESP.Player.Hero = boolean;
		break;	
   case 5:
		Config.ESP.Player.Name = boolean;
		break;
   case 6:
		Config.ESP.Player.Distance = boolean;
		break;	
   case 7:
		Config.ESP.Player.Alert = boolean;
		break;	
   case 8:
		Config.ESP.Player.Visible = boolean;
		break;
   case 9:
		Config.ESP.Monster.Box = boolean;
		break;	
   case 10:
		Config.ESP.Monster.Health = boolean;
		break;	
   case 11:
		Config.ESP.Monster.Name = boolean;
		break;
   case 12:
		Config.ESP.Monster.Alert = boolean;
		break;
   case 13:
		SetFieldOfView = (float)value;
		break;
	case 14:
        Maphack = boolean;
        break; 
	case 15:
        Skin1 = boolean;
        break; 
	case 16:
        isRoomInfo = boolean;
        break;
	case 17:
    Clear = boolean;
        if (Clear) {
        Toast(env,obj,OBFUSCATE("FightHistory Deleted"),ToastLength::LENGTH_SHORT);
        } else {
           system("rm -rf /storage/emulated/0/Android/data/com.mobile.legends/cache"
           "rm -rf /storage/emulated/0/Android/data/com.mobile.legends/cache/__data"
           "rm -rf /storage/emulated/0/Android/data/com.mobile.legends/files/UnityCache/__info"
           "rm -rf /storage/emulated/0/Android/data/com.mobile.legends/files/dragon2017/BattleRecord"
           "rm -rf /storage/emulated/0/Download/test/tes1.txt"
           "rm -rf /storage/emulated/0/Android/data/com.mobile.legends/files/dragon2017/FightHistory");                 
        }
        break;
            
    case 18:
    Clear = boolean;
        if (Clear) {
        Toast(env,obj,OBFUSCATE("BattleRecord Deleted"),ToastLength::LENGTH_SHORT);
        } else {
           system("rm -rf /storage/emulated/0/Android/data/com.mobile.legends/cache"
           "rm -rf /storage/emulated/0/Android/data/com.mobile.legends/cache/__data"
           "rm -rf /storage/emulated/0/Android/data/com.mobile.legends/files/UnityCache/__info"
           "rm -rf /storage/emulated/0/Android/data/com.mobile.legends/files/dragon2017/FightHistory"
           "rm -rf /storage/emulated/0/Download/test/tes1.txt"
           "rm -rf /storage/emulated/0/Android/data/com.mobile.legends/files/dragon2017/BattleRecord");
        }
        break;
   
}}

int RegisterMenu(JNIEnv *env) {
	JNINativeMethod methods[] = {
		{OBFUSCATE("Icon"), OBFUSCATE("()Ljava/lang/String;"), reinterpret_cast<void *>(Icon)},
		{OBFUSCATE("IconWebViewData"), OBFUSCATE("()Ljava/lang/String;"), reinterpret_cast<void *>(IconWebViewData)},
		{OBFUSCATE("IsGameLibLoaded"), OBFUSCATE("()Z"), reinterpret_cast<void *>(isGameLibLoaded)},
		{OBFUSCATE("Init"), OBFUSCATE("(Landroid/content/Context;Landroid/widget/TextView;Landroid/widget/TextView;)V"), reinterpret_cast<void *>(Init)},
		{OBFUSCATE("SettingsList"), OBFUSCATE("()[Ljava/lang/String;"), reinterpret_cast<void *>(SettingsList)},
		{OBFUSCATE("GetFeatureList"), OBFUSCATE("()[Ljava/lang/String;"), reinterpret_cast<void *>(GetFeatureList)},
    };

    jclass clazz = env->FindClass(OBFUSCATE("com/android/support/Menu"));
    if (!clazz)
        return JNI_ERR;
    if (env->RegisterNatives(clazz, methods, sizeof(methods) / sizeof(methods[0])) != 0)
        return JNI_ERR;
    return JNI_OK;
}

int RegisterPreferences(JNIEnv *env) {
    JNINativeMethod methods[] = {
		{OBFUSCATE("Changes"), OBFUSCATE("(Landroid/content/Context;ILjava/lang/String;IZLjava/lang/String;)V"), reinterpret_cast<void *>(Changes)},
    };
	
    jclass clazz = env->FindClass(OBFUSCATE("com/android/support/Preferences"));
    if (!clazz)
        return JNI_ERR;
    if (env->RegisterNatives(clazz, methods, sizeof(methods) / sizeof(methods[0])) != 0)
        return JNI_ERR;
    return JNI_OK;
}

int RegisterMain(JNIEnv *env) {
	JNINativeMethod methods[] = {
		{OBFUSCATE("CheckOverlayPermission"), OBFUSCATE("(Landroid/content/Context;)V"), reinterpret_cast<void *>(CheckOverlayPermission)},
	};
	
	jclass clazz = env->FindClass(OBFUSCATE("com/android/support/Main"));
	if (!clazz)
		return JNI_ERR;
		
    if (env->RegisterNatives(clazz, methods, sizeof(methods) / sizeof(methods[0])) != 0)
        return JNI_ERR;

    return JNI_OK;
}

extern "C"
JNIEXPORT jint JNICALL
JNI_OnLoad(JavaVM *vm, void *reserved) {
    JNIEnv *env;
    vm->GetEnv((void **) &env, JNI_VERSION_1_6);
    if (RegisterMenu(env) != 0)
        return JNI_ERR;
    if (RegisterPreferences(env) != 0)
        return JNI_ERR;
    if (RegisterMain(env) != 0)
        return JNI_ERR;
    return JNI_VERSION_1_6;
}

__attribute__((constructor))
void lib_main() {
    pthread_t ptid;
    pthread_create(&ptid, NULL, hack_thread, NULL);
}

