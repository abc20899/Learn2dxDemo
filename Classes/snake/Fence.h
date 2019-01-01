//
// Created by jun zhao on 2018/12/21.
//

#ifndef PROJ_SNAKE_FENCE_H
#define PROJ_SNAKE_FENCE_H

#include "cocos2d.h"
#include "GameDefine.h"

using namespace cocos2d;

namespace snake {

    class Fence : public Sprite {

    public:
        float scaleRate;
        Size winSize;
        Vec2 origin;
        Vector<Sprite *> fenceArray;

    public:
        virtual bool init();

        Vec2 Grid2Pos(float x, float y); //根据自定义的坐标得到实际应该显示的cocos2d-x坐标位置

        void fenceGenerator(int bound,
                            std::function<Vec2(int)> lambdaCallBabck); //bound格子数目 pos位置

        void fenceAll(int rowBound, int colBound);

        void reset(); //重置围墙

        bool checkCollide(float x, float y);

        CREATE_FUNC(Fence);
    };
}

#endif //PROJ_SNAKE_FENCE_H
