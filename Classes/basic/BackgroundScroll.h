//
// Created by jun zhao on 2018/12/22.
//

#ifndef PROJ_ANDROID_BACKGROUNDSCROLL_H
#define PROJ_ANDROID_BACKGROUNDSCROLL_H

#include "cocos2d.h"
#include "JNITools.h"

using namespace cocos2d;

class BackgroundScroll : public Scene {

public:
    Sprite *bg1;
    Sprite *bg2;
    int speedY = 1;

public:

    static Scene *createScene();

    virtual bool init();

    void update(float dt);

    CREATE_FUNC(BackgroundScroll)
};

#endif //PROJ_ANDROID_BACKGROUNDSCROLL_H
