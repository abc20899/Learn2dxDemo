//
// Created by jun zhao on 2018/12/20.
//

#include "MainScene.h"

namespace snake {

    Scene *MainScene::createScene() {
        return MainScene::create();
    }

    bool MainScene::init() {
        if (!Scene::init()) {
            return false;
        }

        winSize = Director::getInstance()->getVisibleSize();
        auto origin = Director::getInstance()->getVisibleOrigin();

        log("winSize--%f,%f", winSize.width, winSize.height);
        auto bg = Sprite::create("snake/sake_bg.png"); //锚点为0.5，0.5
//        bg->setContentSize(Size(winSize.width, winSize.height));
        bg->setScale(2.0f);
        bg->setPosition(Vec2(winSize.width / 2 + origin.x, winSize.height / 2 + origin.y));
        log("bg--%f,%f", bg->getContentSize().width, bg->getContentSize().height);
        addChild(bg);

        auto gameMenu = Menu::create(
                MenuItemImage::create("snake/start_btn.png", "snake/start_btn.png",
                                      [&](Ref *pSender) {
                                          Director::getInstance()->replaceScene(
                                                  TransitionFadeDown::create(0.5f,
                                                                             GameScene::createScene()));
                                      }), NULL);
        gameMenu->setPosition(Vec2(winSize.width / 2, 50));



        ////////////返回按钮////////////
        auto labelMenu = Label::createWithTTF("Back", "fonts/arial.ttf", 20.0f);
        auto menu = Menu::create(
                MenuItemLabel::create(labelMenu, [](Ref *pSender) {
                    Director::getInstance()->popScene(); //退出当前场景
                }), NULL);
        menu->setPosition(30, 120);
        addChild(menu);
        addChild(gameMenu);
        return true;
    }
}