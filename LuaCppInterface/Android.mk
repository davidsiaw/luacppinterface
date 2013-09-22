LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

BOOST_PATH := ../boost
LUA_PATH := ../lua

LOCAL_MODULE := luacppinterface

LOCAL_CFLAGS := -std=c++11 -fexceptions -frtti

LOCAL_C_INCLUDES := $(LOCAL_PATH)/$(LUA_PATH)/src \
	$(LOCAL_PATH)/$(BOOST_PATH)

LOCAL_SRC_FILES := luacoroutine.cpp \
					luacppinterface.cpp \
					luafunction.cpp \
					luareference.cpp \
					luatable.cpp


include $(BUILD_STATIC_LIBRARY)
