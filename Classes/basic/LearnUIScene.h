//
// Created by jun zhao on 2018/12/17.
//

#ifndef __LEARNUI_SCENE_H__
#define __LEARNUI_SCENE_H__

#include "cocos2d.h"
#include <cocos-ext.h>

USING_NS_CC_EXT; //using namespace cocos2d::extension
using namespace cocos2d;

class LearnUI : public Scene {

private:
    Size winSize;

public:
    static Scene *createScene();

    virtual bool init();

    void addSp(const std::string &filename);

    // implement the "static create()" method manually
    CREATE_FUNC(LearnUI);
};

#endif // __LEARNUI_SCENE_H__