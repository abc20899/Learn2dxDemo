//
// Created by jun zhao on 2018/12/30.
//

#include "Sprite3DScene.h"

Scene *Sprite3DScene::createScene() {
    return Sprite3DScene::create();
}

bool Sprite3DScene::init() {
    if (!Scene::init()) {
        return false;
    }

    Size winSize = Director::getInstance()->getVisibleSize();

    auto s = Sprite3D::create("tortoise.c3b");
    s->setScale(0.1);
    s->setPosition(Vec2(winSize / 2));
    addChild(s);

//    s->runAction(RepeatForever::create(RotateBy::create(1, Vec3(45, 45, 0))));

    auto anim = Animate3D::create(Animation3D::create("tortoise.c3b"), 0, 1.93);
    s->runAction(RepeatForever::create(anim));

    // 3d转换工具 /Users/junzhao/cocos2d/cocos2d-x-3.17/tools/fbx-conv/mac/fbx-conv
    // maya创建好模型保存成 myobj.fbx
    //创建光源
//    auto l = DirectionLight::create(Vec3(0, 0, -1000), Color3B(255, 255, 255));
//    addChild(l);

    ////////////返回按钮////////////
    auto labelMenu = Label::createWithTTF("Back", "fonts/arial.ttf", 20.0f);
    auto menu2 = Menu::create(
            MenuItemLabel::create(labelMenu, [](Ref *pSender) {
                Director::getInstance()->popScene(); //退出当前场景
            }), NULL);
    menu2->setPosition(winSize.width - 20, 50);
    addChild(menu2);
    return true;
}