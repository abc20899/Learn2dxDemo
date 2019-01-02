//
// Created by jun zhao on 2018/12/30.
//

#ifndef PROJ_ANDROID_SPRITE3DSCENE_H
#define PROJ_ANDROID_SPRITE3DSCENE_H

#include "cocos2d.h"

USING_NS_CC;

class Sprite3DScene : public Scene {

public:
    static Scene *createScene();

    virtual bool init();

    CREATE_FUNC(Sprite3DScene)
};

#endif //PROJ_ANDROID_SPRITE3DSCENE_H
