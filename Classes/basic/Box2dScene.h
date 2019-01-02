//
// Created by jun zhao on 2019/1/1.
//

#ifndef PROJ_ANDROID_BOX2DSCENE_H
#define PROJ_ANDROID_BOX2DSCENE_H

#include "cocos2d.h"
#include <Box2D/Box2D.h>
//在Android.mk文件中加入 $(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/external/Box2D/include)

#define RATIO 48.0f   //480/10 米

//换算： 像素=RATIO*米   米=像素/RATIO

USING_NS_CC;

class Box2dScene : public Scene, public b2ContactListener {
public:
    b2World *world;
    b2Body *groundBody;
public:
    static Scene *createScene();

    virtual bool init();

    virtual void update(float dt);

    void addRect(float x, float y, b2BodyType type); //单位米

    void addGround(); //添加地板

    virtual void BeginContact(b2Contact* contact);//物体开始碰撞

    CREATE_FUNC(Box2dScene);
};


#endif //PROJ_ANDROID_BOX2DSCENE_H
