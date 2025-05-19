#pragma once

#define m_IL2CPPLIB "liblogic.so"
uintptr_t m_IL2CPP;
bool g_Initialized;
void *m_EGL;

/*Class Screen*/
#define Screen_get_width (uintptr_t) IL2Cpp::Il2CppGetMethodOffset("UnityEngine.dll", "UnityEngine", "Screen", "get_width")
#define Screen_get_height (uintptr_t) IL2Cpp::Il2CppGetMethodOffset("UnityEngine.dll", "UnityEngine", "Screen", "get_height")
#define Screen_get_dpi (uintptr_t) IL2Cpp::Il2CppGetMethodOffset("UnityEngine.dll", "UnityEngine", "Screen", "get_dpi")

int get_width() {
	return reinterpret_cast<int(__fastcall *)()>(Screen_get_width)();
}

int get_height() {
	return reinterpret_cast<int(__fastcall *)()>(Screen_get_height)();
}

int get_dpi() {
	return reinterpret_cast<int(__fastcall *)()>(Screen_get_dpi)();
}


