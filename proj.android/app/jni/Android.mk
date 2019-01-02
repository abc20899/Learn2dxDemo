LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/cocos)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/cocos/audio/include)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/external/Box2D/include)

LOCAL_MODULE := MyGame_shared

LOCAL_MODULE_FILENAME := libMyGame

#查找项目目录下的cpp
define all-cpp-files
$(patsubst jni/%,%, $(shell find $(LOCAL_PATH)/../../../Classes/ $(LOCAL_PATH)/hellocpp -name "*.cpp"))
endef
LOCAL_SRC_FILES := $(call all-cpp-files)

# LOCAL_SRC_FILES := $(LOCAL_PATH)/hellocpp/main.cpp \
#                    $(LOCAL_PATH)/../../../Classes/AppDelegate.cpp \
#                    $(LOCAL_PATH)/../../../Classes/MainScene.cpp \
#                    $(LOCAL_PATH)/../../../Classes/HelloWorldScene.cpp \
#                    $(LOCAL_PATH)/../../../Classes/LearnScenePoint.cpp \
#                    $(LOCAL_PATH)/../../../Classes/LearnSceneMath.cpp \
#                    $(LOCAL_PATH)/../../../Classes/BallSpriteScene.cpp \
#                    $(LOCAL_PATH)/../../../Classes/Ball.cpp \
#                    $(LOCAL_PATH)/../../../Classes/LearnEventScene.cpp \
#                    $(LOCAL_PATH)/../../../Classes/LearnUIScene.cpp \
#                    $(LOCAL_PATH)/../../../Classes/JoyStick.cpp \
#                    $(LOCAL_PATH)/../../../Classes/JoyStickScene.cpp \
#                    $(LOCAL_PATH)/../../../Classes/RollBallScene.cpp \
#                    $(LOCAL_PATH)/../../../Classes/RollBall.cpp \


LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../../Classes

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


LOCAL_STATIC_LIBRARIES := cocos2dx_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-add-path, $(LOCAL_PATH)/../../../cocos2d)
$(call import-module, cocos)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END
