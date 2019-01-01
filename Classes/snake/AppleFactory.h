//
// Created by jun zhao on 2018/12/22.
//

#ifndef PROJ_SNAKE_APPLEFACTORY_H
#define PROJ_SNAKE_APPLEFACTORY_H

#include "cocos2d.h"
#include "GameDefine.h"

using namespace cocos2d;

namespace snake {

    class AppleFactory : public Sprite {

    public:
        float scaleRate;
        Size winSize;
        Vec2 origin;
        Sprite *appleSprite;
        int appleX, appleY; //记录apple的随机坐标
    public:
        virtual bool init();

        Vec2 getRandomPos(int row, int col); //获取随机坐标点

        void generateApple(); //在生成苹果之前先移除

        bool eatApple(float x, float y); //是否吃到苹果

        Vec2 Grid2Pos(float x, float y); //根据自定义的坐标得到实际应该显示的cocos2d-x坐标位置

        CREATE_FUNC(AppleFactory)
    };
}

#endif //PROJ_ANDROID_APPLEFACTORY_H
