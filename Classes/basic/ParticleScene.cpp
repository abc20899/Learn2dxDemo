//
// Created by jun zhao on 2018/12/22.
//

#include "ParticleScene.h"


Scene *ParticleScene::createScene() {
    return ParticleScene::create();
}

bool ParticleScene::init() {
    if (!Scene::init()) {
        return false;
    }

    auto winSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

//    auto mofa = ParticleSystemQuad::create("particle/particle_texture_mofa.plist");
//    mofa->setPosition(origin.x + winSize.width / 2, origin.y + winSize.height / 2);
//    this->addChild(mofa);

//    auto galaxy = ParticleSystemQuad::create("particle/particle_galaxy.plist");
//    galaxy->setPosition(origin.x + winSize.width / 2, origin.y + winSize.height / 2);
//    this->addChild(galaxy);

    //彩虹糖效果
    auto imageFade = ImageFadeOut::create("liangjingru3.jpeg");
    addChild(imageFade);
    imageFade->setPosition(origin.x + winSize.width / 2, origin.y + winSize.height / 2);


//    auto fire = ParticleSystemQuad::create("particle/particle_fire.plist");
//    fire->setStartColor(color);
//    fire->setEndColor(color);
//    fire->setAutoRemoveOnFinish(true);
//    fire->setPosition(origin.x + winSize.width / 2, origin.y + winSize.height / 2);
//    addChild(fire);

    ////////////返回按钮////////////
    auto labelMenu = Label::createWithTTF("Back", "fonts/arial.ttf", 20.0f);
    auto menu2 = Menu::create(
            MenuItemLabel::create(labelMenu, [](Ref *pSender) {
                Director::getInstance()->popScene(); //退出当前场景
                JNITools::changeActivityOrientation(1); //横屏
            }), NULL);
    menu2->setPosition(winSize.width - 20, 50);
    addChild(menu2);
    return true;
}