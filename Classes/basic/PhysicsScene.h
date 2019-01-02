//
// Created by jun zhao on 2019/1/1.
//

#ifndef PROJ_ANDROID_PHYSICSSCENE_H
#define PROJ_ANDROID_PHYSICSSCENE_H

#include "cocos2d.h"

#define RED_MASK    0b0001
#define GREEN_MASK  0b0010
#define BLUE_MASK   0b0100
#define EDGE_MASK   0b1000

USING_NS_CC;

class PhysicsScene : public Layer {

public:
    Size winSize;

public:

    static Scene *createScene();

    virtual bool init();

    void addEdge();

    void addBall(float x, float y);

    void addRect(float x, float y);

    CREATE_FUNC(PhysicsScene)
};

#endif //PROJ_ANDROID_PHYSICSSCENE_H
