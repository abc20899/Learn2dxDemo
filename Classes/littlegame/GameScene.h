//
// Created by jun zhao on 2019/1/1.
//

#ifndef PROJ_LITTLE_GAMESCENE_H
#define PROJ_LITTLE_GAMESCENE_H

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

namespace little {

    class GameScene : public Scene {

    public:
        Size winSize;
        Sprite *player;
        Vector<Sprite *> bulletes; //子弹集合
        Vector<Sprite *> ghostes;//幽灵集合

    public:
        static Scene *createScene();

        virtual bool init();

        void addGhost(float dt); //添加幽灵

        void update(float dt); //每帧更新

        void checkCollision(); //检测碰撞

        void movieCallbak(Node *node);//子弹移动完毕回调

        CREATE_FUNC(GameScene)
    };
}

#endif //PROJ_LITTLE_GAMESCENE_H
