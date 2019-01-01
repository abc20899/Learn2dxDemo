//
// Created by jun zhao on 2018/12/18.
//

#ifndef __ROLLBALLSCENE_H
#define __ROLLBALLSCENE_H

#include "cocos2d.h"
#include "RollBall.h"

using namespace cocos2d;

class RollBallScene : public Scene {

public:
    static Scene *createScene();

    virtual bool init();

    virtual void update(float dt);

    void addBall(float x, float y);

    CREATE_FUNC(RollBallScene);
private:
    Size winSize;
//    Sprite *ball;
    Vector<RollBall *> balls; //小球集合
};

#endif //__ROLLBALLSCENE_H
