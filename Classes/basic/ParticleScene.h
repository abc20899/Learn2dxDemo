//
// Created by jun zhao on 2018/12/22.
//

#ifndef PROJ_ANDROID_PARTICLE_H
#define PROJ_ANDROID_PARTICLE_H

#include "cocos2d.h"
#include "JNITools.h"
#include "ImageFadeOut.h"

using namespace cocos2d;

class ParticleScene : public Scene {

public:

public:

    static Scene *createScene();

    virtual bool init();

    CREATE_FUNC(ParticleScene)
};

#endif //PROJ_ANDROID_PARTICLEL_H
