//
// Created by jun zhao on 2018/12/20.
//

#ifndef PROJ_ANDROID_BODY_H
#define PROJ_ANDROID_BODY_H

#include "cocos2d.h"
#include "GameDefine.h"

using namespace cocos2d;

namespace snake {
    class Body : public Sprite {

    public:
        float scaleRate;
        Size winSize;
        Vec2 origin;
        float x, y;//位置坐标
        bool isHead;

    public:
        //更新自己
        void updateBody(bool isHead, float x, float y);

        virtual bool init();

        void move();

        Vec2 Grid2Pos(float x, float y); //根据自定义的坐标得到实际应该显示的cocos2d-x坐标位置

        CREATE_FUNC(Body);
    };
}

#endif //PROJ_ANDROID_BODY_H
