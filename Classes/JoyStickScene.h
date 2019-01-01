#ifndef __JoyStick_SCENE_H__
#define __JoyStick_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class JoyStick;

class JoyStickScene : public cocos2d::Layer {

public:
    static cocos2d::Scene *createScene();

    virtual bool init();

    CREATE_FUNC(JoyStickScene);

    void schedulePos(float dt);

private:
    JoyStick *rocker;
};

#endif // __HELLOWORLD_SCENE_H__
