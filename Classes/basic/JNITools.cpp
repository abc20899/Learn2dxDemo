//
// Created by jun zhao on 2018/12/19.
//

#include "JNITools.h"

JNITools::JNITools() {}

JNITools::~JNITools() {}

//orientation: 1横屏 2竖屏
void JNITools::changeActivityOrientation(int orientation) {

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) //判断当前是否为Android平台
    JniMethodInfo changeOritation;
    bool isHave = JniHelper::getStaticMethodInfo(changeOritation, "cn/junechiu/learn/AppActivity",
                                                 "changeActivityOrientation", "(I)V");
    if (!isHave) {
        log("jni:changeActivityOrientation is null");
    } else {
        //调用此函数
        changeOritation.env->CallStaticVoidMethod(changeOritation.classID, changeOritation.methodID,
                                                  orientation);
    }
#endif
}