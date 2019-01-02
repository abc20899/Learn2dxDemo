//
// Created by jun zhao on 2018/12/17.
//

#ifndef PROJ_ANDROID_BALL_H
#define PROJ_ANDROID_BALL_H

#include "cocos2d.h"

using namespace cocos2d;

class Ball : public Sprite {

private:
    int speedX, speedY;
public:
    virtual bool init();

    void move();

    CREATE_FUNC(Ball); //宏创建
};

#endif //PROJ_ANDROID_BALL_H