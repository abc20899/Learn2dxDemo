//
// Created by jun zhao on 2018/12/19.
//

#ifndef PROJ_ANDROID_GAMEOVER_H
#define PROJ_ANDROID_GAMEOVER_H

#include "cocos2d.h"
#include "GameScene.h"

using namespace cocos2d;

namespace game2048 {

    class GameOver : public Scene {

    public:
        static Scene *createScene();

        void menuRestartCallback(Ref *pSender);

        void menuExitCallback(Ref *pSender);

        virtual bool init();

        CREATE_FUNC(GameOver);
    };

}

#endif //PROJ_ANDROID_GAMEOVER_H
