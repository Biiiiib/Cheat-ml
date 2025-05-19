#pragma once

#define targetLib OBFUSCATE("libil2cpp.so")
uintptr_t il2cppMap;

bool initImGui;

int s_Width = 0;
int s_Height = 0;
	
struct sConfig2 {
	struct sInitImGui {
		bool initImGui;
		bool bInitDone;
	};
	
	sInitImGui InitImGui;
	
	struct sESP {
		bool espLine;
		bool espBox;
		bool espHealth;
		bool espName;
		bool espDistance;
	};
	sESP ESPMenu;
	
	struct sOther {
		float getFieldOfView;
		float setFieldOfView = 0;
		bool mapHack;
		bool grass;
	};
	sOther OtherMenu;
	
};

sConfig2 Config2{0};
