//
// Created by jun zhao on 2018/12/17.
//

#ifndef __BALLSPRITE_SCENE_H__
#define __BALLSPRITE_SCENE_H__

#include "cocos2d.h"
#include "Ball.h"

using namespace cocos2d;

class BallSprite : public Scene {

private:
    Size winSize;
    Vector<Ball *> balls;

public:
    static Scene *createScene();

    virtual bool init();

    void addBall(float dt);

    void update(float dt);

    // implement the "static create()" method manually
    CREATE_FUNC(BallSprite);
};

#endif // __BALLSPRITE_SCENE_H__