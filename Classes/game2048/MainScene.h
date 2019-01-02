//
// Created by jun zhao on 2018/12/19.
//

#ifndef PROJ_ANDROID_MAINSCENE_H
#define PROJ_ANDROID_MAINSCENE_H

#include "cocos2d.h"
#include "../basic/JNITools.h"

using namespace cocos2d;

namespace game2048 {
    class MainScene : public Scene {

    public:
        static Scene *createScene();

        virtual bool init();

        CREATE_FUNC(MainScene);
    private:
        Size winSize;
    };
}

#endif //PROJ_ANDROID_MAINSCENE_H
