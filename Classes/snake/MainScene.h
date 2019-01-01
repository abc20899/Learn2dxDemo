//
// Created by jun zhao on 2018/12/20.
//

#ifndef PROJ_SNAKE_MAINSCENE_H
#define PROJ_SNAKE_MAINSCENE_H

#include "cocos2d.h"
#include "GameScene.h"

using namespace cocos2d;

namespace snake {
    class MainScene : public Scene {

    private:
        Size winSize;

    public:
        static Scene *createScene();

        virtual bool init();

        CREATE_FUNC(MainScene);
    };
}

#endif //PROJ_ANDROID_MAINSCENE_H

