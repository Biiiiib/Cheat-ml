LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

# ============================================================================#
LOCAL_MODULE            := libdobby
LOCAL_SRC_FILES         := Dobby/libraries/$(TARGET_ARCH_ABI)/libdobby.a
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/dobby/
include $(PREBUILT_STATIC_LIBRARY)

# ============================================================================#

include $(CLEAR_VARS)

LOCAL_MODULE            := MyLibName
LOCAL_CFLAGS            := -Wno-error=format-security -fvisibility=hidden -ffunction-sections -fdata-sections -w
LOCAL_CFLAGS            += -fno-rtti -fno-exceptions -fpermissive
LOCAL_CPPFLAGS          := -Wno-error=format-security -fvisibility=hidden -ffunction-sections -fdata-sections -w -Werror -s -std=c++17
LOCAL_CPPFLAGS          += -Wno-error=c++11-narrowing -fms-extensions -fno-rtti -fno-exceptions -fpermissive
LOCAL_LDFLAGS           += -Wl,--gc-sections,--strip-all, -llog
LOCAL_ARM_MODE          := arm
LOCAL_LDLIBS            := -llog -landroid -lEGL -lGLESv3 -lGLESv2 -lGLESv1_CM -lz

LOCAL_C_INCLUDES        += $(LOCAL_PATH)

LOCAL_C_INCLUDES       += $(LOCAL_PATH)
LOCAL_C_INCLUDES       := $(LOCAL_PATH)/NPmodz/Tools/curl/curl-android-$(TARGET_ARCH_ABI)/include
LOCAL_C_INCLUDES       += $(LOCAL_PATH)/NPmodz/Tools/curl/openssl-android-$(TARGET_ARCH_ABI)/include


LOCAL_C_INCLUDES += $(LOCAL_PATH)
LOCAL_C_INCLUDES += $(LOCAL_PATH)/ImGui
LOCAL_C_INCLUDES += $(LOCAL_PATH)/ImGui/backends

FILE_LIST              := $(wildcard $(LOCAL_PATH)/Imgui/*.c*)
FILE_LIST              += $(wildcard $(LOCAL_PATH)/NPmodz/IL2CppSDKGenerator/*.c*)
FILE_LIST              += $(wildcard $(LOCAL_PATH)/NPmodz/Tools/*.c*)
FILE_LIST              += $(wildcard $(LOCAL_PATH)/*.c*)

LOCAL_SRC_FILES        := $(FILE_LIST:$(LOCAL_PATH)/%=%)

LOCAL_STATIC_LIBRARIES  := libdobby
LOCAL_CPP_FEATURES     := exceptions

include $(BUILD_SHARED_LIBRARY)
# ============================================================================ #
