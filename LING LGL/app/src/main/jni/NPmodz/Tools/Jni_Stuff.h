#pragma once

//
// Created by GHr_Ryuuka on 05/12/2021.
//

#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_android.h"
#include <curl/curl.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <jni.h>
#include <string>
#include <iostream>
#include <string>

size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* s) {
    size_t newLength = size * nmemb;
    try {
        s->append((char*)contents, newLength);
    } catch (std::bad_alloc& e) {
        // Handle memory problem
        return 0;
    }
    return newLength;
}

const char *internetLink = OBFUSCATE("http://apkcombo.com");
const char *worldTimeLink = OBFUSCATE("http://worldtimeapi.org/api/timezone/Etc/UTC");

bool checkInternetConnection() {
    CURL* curl;
    CURLcode res;
    bool isConnected = false;

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, internetLink);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        res = curl_easy_perform(curl);
        if (res == CURLE_OK) {
            isConnected = true;
        }
        curl_easy_cleanup(curl);
    }

    return isConnected;
}



std::string getCurrentDateFromAPI() {
    
    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, worldTimeLink);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        if (res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
            return "";
        }
    }

    // Find the start and end of the "utc_datetime" field in the response
    std::string datetimeKey = "\"utc_datetime\":\"";
    size_t datetimeStart = readBuffer.find(datetimeKey);
    if (datetimeStart == std::string::npos) {
        std::cerr << "Failed to find datetime in response." << std::endl;
        return "";
    }
    datetimeStart += datetimeKey.length();

    size_t datetimeEnd = readBuffer.find("\"", datetimeStart);
    if (datetimeEnd == std::string::npos) {
        std::cerr << "Failed to parse datetime in response." << std::endl;
        return "";
    }

    // Extract datetime substring
    std::string datetime = readBuffer.substr(datetimeStart, datetimeEnd - datetimeStart);

    // Extract the date part (first 10 characters)
    std::string date = datetime.substr(0, 10);

    return date;
    
}
    


JavaVM *jvm;

using json = nlohmann::json;
std::string g_Token, g_Auth;
bool bValid = false;

bool bInitDone;

struct MemoryStruct {
	char *memory;
	size_t size;
};

static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp) {
	size_t realsize = size * nmemb;
	struct MemoryStruct *mem = (struct MemoryStruct *) userp;
	
	mem->memory = (char *) realloc(mem->memory, mem->size + realsize + 1);
	if (mem->memory == NULL) {
		return 0;
	}
	memcpy(&(mem->memory[mem->size]), contents, realsize);
	mem->size += realsize;
	mem->memory[mem->size] = 0;
	return realsize;
}

int ShowSoftKeyboardInput() {
	jint result;
	jint flags = 0;
	
	JNIEnv *env;
	jvm->AttachCurrentThread(&env, NULL);
	
	jclass looperClass = env->FindClass(OBFUSCATE("android/os/Looper"));
	auto prepareMethod = env->GetStaticMethodID(looperClass, OBFUSCATE("prepare"), OBFUSCATE("()V"));
	env->CallStaticVoidMethod(looperClass, prepareMethod);
	
	jclass activityThreadClass = env->FindClass(OBFUSCATE("android/app/ActivityThread"));
	jfieldID sCurrentActivityThreadField = env->GetStaticFieldID(activityThreadClass, OBFUSCATE("sCurrentActivityThread"), OBFUSCATE("Landroid/app/ActivityThread;"));
	jobject sCurrentActivityThread = env->GetStaticObjectField(activityThreadClass, sCurrentActivityThreadField);
	
	jfieldID mInitialApplicationField = env->GetFieldID(activityThreadClass, OBFUSCATE("mInitialApplication"), OBFUSCATE("Landroid/app/Application;"));
	jobject mInitialApplication = env->GetObjectField(sCurrentActivityThread, mInitialApplicationField);
	
	jclass contextClass = env->FindClass(OBFUSCATE("android/content/Context"));
	jfieldID fieldINPUT_METHOD_SERVICE = env->GetStaticFieldID(contextClass, OBFUSCATE("INPUT_METHOD_SERVICE"), OBFUSCATE("Ljava/lang/String;"));
	jobject INPUT_METHOD_SERVICE = env->GetStaticObjectField(contextClass, fieldINPUT_METHOD_SERVICE);
	jmethodID getSystemServiceMethod = env->GetMethodID(contextClass, OBFUSCATE("getSystemService"), OBFUSCATE("(Ljava/lang/String;)Ljava/lang/Object;"));
	jobject callObjectMethod = env->CallObjectMethod(mInitialApplication, getSystemServiceMethod, INPUT_METHOD_SERVICE);
	
	jclass classInputMethodManager = env->FindClass(OBFUSCATE("android/view/inputmethod/InputMethodManager"));
    jmethodID toggleSoftInputId = env->GetMethodID(classInputMethodManager, OBFUSCATE("toggleSoftInput"), OBFUSCATE("(II)V"));
	
	if (result) {
		env->CallVoidMethod(callObjectMethod, toggleSoftInputId, 2, flags);
	} else {
		env->CallVoidMethod(callObjectMethod, toggleSoftInputId, flags, flags);
	}
	
	env->DeleteLocalRef(classInputMethodManager);
	env->DeleteLocalRef(callObjectMethod);
	env->DeleteLocalRef(contextClass);
    env->DeleteLocalRef(mInitialApplication);
    env->DeleteLocalRef(activityThreadClass);
	jvm->DetachCurrentThread();
	
	return result;
}

int PollUnicodeChars() {
	JNIEnv *env;
	jvm->AttachCurrentThread(&env, NULL);
	
	jclass looperClass = env->FindClass(OBFUSCATE("android/os/Looper"));
	auto prepareMethod = env->GetStaticMethodID(looperClass, OBFUSCATE("prepare"), OBFUSCATE("()V"));
	env->CallStaticVoidMethod(looperClass, prepareMethod);
	
	jclass activityThreadClass = env->FindClass(OBFUSCATE("android/app/ActivityThread"));
	jfieldID sCurrentActivityThreadField = env->GetStaticFieldID(activityThreadClass, OBFUSCATE("sCurrentActivityThread"), OBFUSCATE("Landroid/app/ActivityThread;"));
	jobject sCurrentActivityThread = env->GetStaticObjectField(activityThreadClass, sCurrentActivityThreadField);
	
	jfieldID mInitialApplicationField = env->GetFieldID(activityThreadClass, OBFUSCATE("mInitialApplication"), OBFUSCATE("Landroid/app/Application;"));
	jobject mInitialApplication = env->GetObjectField(sCurrentActivityThread, mInitialApplicationField);
	
	jclass keyEventClass = env->FindClass(OBFUSCATE("android/view/KeyEvent"));
	jmethodID getUnicodeCharMethod = env->GetMethodID(keyEventClass, OBFUSCATE("getUnicodeChar"), OBFUSCATE("(I)I"));
	
	ImGuiIO& io = ImGui::GetIO();
    
	int return_key = env->CallIntMethod(keyEventClass, getUnicodeCharMethod);
	
	env->DeleteLocalRef(keyEventClass);
	env->DeleteLocalRef(mInitialApplication);
    env->DeleteLocalRef(activityThreadClass);
	jvm->DetachCurrentThread();
	
	return return_key;
}

std::string getClipboard() {
    std::string result;
    JNIEnv *env;
    
    jvm->AttachCurrentThread(&env, NULL);
    
    auto looperClass = env->FindClass(OBFUSCATE("android/os/Looper"));
    auto prepareMethod = env->GetStaticMethodID(looperClass, OBFUSCATE("prepare"), OBFUSCATE("()V"));
    env->CallStaticVoidMethod(looperClass, prepareMethod);
    
    jclass activityThreadClass = env->FindClass(OBFUSCATE("android/app/ActivityThread"));
    jfieldID sCurrentActivityThreadField = env->GetStaticFieldID(activityThreadClass, OBFUSCATE("sCurrentActivityThread"), OBFUSCATE("Landroid/app/ActivityThread;"));
    jobject sCurrentActivityThread = env->GetStaticObjectField(activityThreadClass, sCurrentActivityThreadField);
    
    jfieldID mInitialApplicationField = env->GetFieldID(activityThreadClass, OBFUSCATE("mInitialApplication"), OBFUSCATE("Landroid/app/Application;"));
    jobject mInitialApplication = env->GetObjectField(sCurrentActivityThread, mInitialApplicationField);
    
    auto contextClass = env->FindClass(OBFUSCATE("android/content/Context"));
    auto getSystemServiceMethod = env->GetMethodID(contextClass, OBFUSCATE("getSystemService"), OBFUSCATE("(Ljava/lang/String;)Ljava/lang/Object;"));
    
    auto str = env->NewStringUTF(OBFUSCATE("clipboard"));
    auto clipboardManager = env->CallObjectMethod(mInitialApplication, getSystemServiceMethod, str);
    env->DeleteLocalRef(str);
    
    jclass ClipboardManagerClass = env->FindClass(OBFUSCATE("android/content/ClipboardManager"));
    auto getText = env->GetMethodID(ClipboardManagerClass, OBFUSCATE("getText"), OBFUSCATE("()Ljava/lang/CharSequence;"));

    jclass CharSequenceClass = env->FindClass(OBFUSCATE("java/lang/CharSequence"));
    auto toStringMethod = env->GetMethodID(CharSequenceClass, OBFUSCATE("toString"), OBFUSCATE("()Ljava/lang/String;"));

    auto text = env->CallObjectMethod(clipboardManager, getText);
    if (text) {
        str = (jstring) env->CallObjectMethod(text, toStringMethod);
        result = env->GetStringUTFChars(str, 0);
        env->DeleteLocalRef(str);
        env->DeleteLocalRef(text);
    }
    
    env->DeleteLocalRef(CharSequenceClass);
    env->DeleteLocalRef(ClipboardManagerClass);
    env->DeleteLocalRef(clipboardManager);
    env->DeleteLocalRef(contextClass);
    env->DeleteLocalRef(mInitialApplication);
    env->DeleteLocalRef(activityThreadClass);   
    jvm->DetachCurrentThread();
    return result.c_str();
}

std::string GetDeviceModel() {
    JNIEnv *env;
    if (jvm->AttachCurrentThread(&env, NULL) != JNI_OK) {
        return ""; // Error attaching thread
    }

    jclass buildClass = env->FindClass("android/os/Build");
    if (!buildClass) {
        jvm->DetachCurrentThread();
        return ""; // Error finding class
    }

    jfieldID modelField = env->GetStaticFieldID(buildClass, "MODEL", "Ljava/lang/String;");
    if (!modelField) {
        env->DeleteLocalRef(buildClass);
        jvm->DetachCurrentThread();
        return ""; // Error finding field ID
    }

    jstring modelString = (jstring)env->GetStaticObjectField(buildClass, modelField);
    if (!modelString) {
        env->DeleteLocalRef(buildClass);
        jvm->DetachCurrentThread();
        return ""; // Error getting static object field
    }

    const char *modelChars = env->GetStringUTFChars(modelString, NULL);
    std::string model(modelChars);
    env->ReleaseStringUTFChars(modelString, modelChars);

    env->DeleteLocalRef(modelString);
    env->DeleteLocalRef(buildClass);
    jvm->DetachCurrentThread();

    return model;
}

std::string GetDeviceBrand() {
    JNIEnv *env;
    if (jvm->AttachCurrentThread(&env, NULL) != JNI_OK) {
        return ""; // Error attaching thread
    }

    jclass buildClass = env->FindClass("android/os/Build");
    if (!buildClass) {
        jvm->DetachCurrentThread();
        return ""; // Error finding class
    }

    jfieldID brandField = env->GetStaticFieldID(buildClass, "BRAND", "Ljava/lang/String;");
    if (!brandField) {
        env->DeleteLocalRef(buildClass);
        jvm->DetachCurrentThread();
        return ""; // Error finding field ID
    }

    jstring brandString = (jstring)env->GetStaticObjectField(buildClass, brandField);
    if (!brandString) {
        env->DeleteLocalRef(buildClass);
        jvm->DetachCurrentThread();
        return ""; // Error getting static object field
    }

    const char *brandChars = env->GetStringUTFChars(brandString, NULL);
    std::string brand(brandChars);
    env->ReleaseStringUTFChars(brandString, brandChars);

    env->DeleteLocalRef(brandString);
    env->DeleteLocalRef(buildClass);
    jvm->DetachCurrentThread();

    return brand;
}

//std::string credit;
std::string modname;
std::string esp;
//std::string token;
std::string expiredDate;
std::string modstatus;

std::string Login(const char *user_key) {
    JNIEnv *env;
    jvm->AttachCurrentThread(&env, 0);
    
        
    auto looperClass = env->FindClass(OBFUSCATE("android/os/Looper"));
    auto prepareMethod = env->GetStaticMethodID(looperClass, OBFUSCATE("prepare"), OBFUSCATE("()V"));
    env->CallStaticVoidMethod(looperClass, prepareMethod);
    
    jclass activityThreadClass = env->FindClass(OBFUSCATE("android/app/ActivityThread"));
    jfieldID sCurrentActivityThreadField = env->GetStaticFieldID(activityThreadClass, OBFUSCATE("sCurrentActivityThread"), OBFUSCATE("Landroid/app/ActivityThread;"));
    jobject sCurrentActivityThread = env->GetStaticObjectField(activityThreadClass, sCurrentActivityThreadField);
    
    jfieldID mInitialApplicationField = env->GetFieldID(activityThreadClass, OBFUSCATE("mInitialApplication"), OBFUSCATE("Landroid/app/Application;"));
    jobject mInitialApplication = env->GetObjectField(sCurrentActivityThread, mInitialApplicationField);
    
    std::string hwid = user_key;
    hwid += Tools::GetAndroidID(env, mInitialApplication);
    hwid += Tools::GetDeviceModel(env);
    hwid += Tools::GetDeviceBrand(env);
    std::string UUID = Tools::GetDeviceUniqueIdentifier(env, hwid.c_str());
    jvm->DetachCurrentThread();
    std::string errMsg;
    
    struct MemoryStruct chunk{};
    chunk.memory = (char *) malloc(1);
    chunk.size = 0;
    
    CURL *curl;
    CURLcode res;
    curl = curl_easy_init();
    
    if (curl) {
      
        std::string KAIFEE1 = OBFUSCATE ("https://");
        std::string KAIFEE2 = OBFUSCATE ("zfmodzbgmi.000webhostapp.com/");
        std::string KAIFEE3 = OBFUSCATE ("connect");     
        std::string KAIFEE = KAIFEE1+KAIFEE2+KAIFEE3;      
        curl_easy_setopt(curl, CURLOPT_URL ,KAIFEE.c_str());
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_DEFAULT_PROTOCOL, "https");
        
        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, OBFUSCATE("Content-Type: application/x-www-form-urlencoded"));
        
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        char data[4096];
        
        sprintf(data, OBFUSCATE("game=ML&user_key=%s&serial=%s"), user_key, UUID.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *) &chunk);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
        
        res = curl_easy_perform(curl);
        if (res == CURLE_OK) {
            try {
                json result = json::parse(chunk.memory);
                if (result[std::string(OBFUSCATE("status"))] == true) {
                    
                    std::string token = result[std::string(OBFUSCATE("data"))][std::string(OBFUSCATE("token"))].get<std::string>();
                    
                    time_t rng = result[std::string(OBFUSCATE("data"))][std::string(OBFUSCATE("rng"))].get<time_t>();
                    
                    //expiredDate = result[std::string(OBFUSCATE("data"))][std::string(OBFUSCATE("rng"))].get<time_t>();
                    expiredDate = result[std::string(OBFUSCATE("data"))][std::string(OBFUSCATE("EXP"))].get<std::string>();
         
                    //credit = result["data"]["credit"].get<std::string>();
                    //credit = result[std::string(OBFUSCATE("data"))][std::string(OBFUSCATE("credit"))].get<std::string>();
         
                    //modstatus = result["data"]["name2"].get<std::string>();
                    modstatus = result[std::string(OBFUSCATE("data"))][std::string(OBFUSCATE("mod_status"))].get<std::string>();
                    
                    esp = result[std::string(OBFUSCATE("data"))][std::string(OBFUSCATE("esp"))].get<std::string>();
         
         
                    //modname = result["data"]["modname"].get<std::string>();
                    modname = result[std::string(OBFUSCATE("data"))][std::string(OBFUSCATE("modname"))].get<std::string>();
         
                    //token = result["data"]["token"].get<std::string>();
                    
                    if (rng + 30 > time(0)) {
                        std::string auth = OBFUSCATE("ML");
                        auth += std::string(OBFUSCATE("-"));
                        auth += user_key;
                        auth += std::string(OBFUSCATE("-"));
                        auth += UUID;
                        auth += std::string(OBFUSCATE("-")); 
                        auth += std::string(OBFUSCATE("Vm8Lk7Uj2JmsjCPVPVjrLa7zgfx3uz9E"));
                        std::string outputAuth = Tools::CalcMD5(auth);
                        g_Token = token;
                        g_Auth = outputAuth;
                        
                        bValid = g_Token == g_Auth;
                        
                        if (bValid) {
                            bInitDone = true;
                        } else {
                            //exit(0);
                        }
                    }
                } else {
                    errMsg = result[std::string(OBFUSCATE("reason"))].get<std::string>();
                }
            } catch (json::exception &e) {
                errMsg = "{zfmodz";
                errMsg += e.what();
                errMsg += "}\n{";
                errMsg += chunk.memory;
                errMsg += "error}";
            }
        } else {
            errMsg = curl_easy_strerror(res);
        }
    }
    curl_easy_cleanup(curl);
    jvm->DetachCurrentThread();
    return bValid ? OBFUSCATE("ZFMODZ") : errMsg;
 
}
