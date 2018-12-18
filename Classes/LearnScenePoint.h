//
// Created by jun zhao on 2018/12/16.
//

#ifndef __LEARNPOINT_SCENE_H__
#define __LEARNPOINT_SCENE_H__

#include "cocos2d.h"

using namespace cocos2d;

class LearnScenePoint:public Scene{

public:
    static Scene *createScene();
    virtual bool init();

    void rotation(float delay); //旋转

    // implement the "static create()" method manually
    CREATE_FUNC(LearnScenePoint);
};

#endif //__LEARNPOINT_SCENE_H__
