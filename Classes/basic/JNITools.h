//
// Created by jun zhao on 2018/12/19.
//

#ifndef PROJ_ANDROID_JNITOOLS_H
#define PROJ_ANDROID_JNITOOLS_H

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#include <android/log.h>

#endif

#include "cocos2d.h"

using namespace cocos2d;

class JNITools {

public:
    JNITools();
    ~JNITools();
    static void changeActivityOrientation(int orientation);//通过JNI调用JAVA静态函数，实现屏幕横竖切换
};

#endif //PROJ_ANDROID_JNITOOLS_H
