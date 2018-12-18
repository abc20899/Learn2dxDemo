//
// Created by jun zhao on 2018/12/17.
//

#ifndef __LEARNEVENT_SCENE_H__
#define __LEARNEVENT_SCENE_H__

#include "cocos2d.h"

using namespace cocos2d;

class LearnEvent : public Scene {

private:
    Size winSize;

public:
    static Scene *createScene();

    virtual bool init();

    bool touchBeganHandler(Touch *touch,Event *event);

    // implement the "static create()" method manually
    CREATE_FUNC(LearnEvent);
};

#endif // __LEARNEVENT_SCENE_H__