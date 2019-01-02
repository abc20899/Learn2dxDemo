//
// Created by jun zhao on 2018/12/18.
//

#ifndef __ROLLBALL_H
#define __ROLLBALL_H

#include "cocos2d.h"

using namespace cocos2d;

class RollBall : public Sprite {

public:
    virtual bool init();

    void move();

    void update(float dt);

    CREATE_FUNC(RollBall);
private:
    float speedX;
    float speedY;
    Size winSize;
};


#endif //__ROLLBALL_H
