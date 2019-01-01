//
// Created by jun zhao on 2018/12/19.
//
#include "MainScene.h"
#include "GameScene.h"

namespace game2048 {

    Scene *MainScene::createScene() {
        return MainScene::create();
    }

    bool MainScene::init() {
        if (!Scene::init()) {
            return false;
        }

        //std::function<void(float)>& callback
//        scheduleOnce([this](float dt) {
//            this->winSize = Director::getInstance()->getVisibleSize();
//            log("winSize %f,%f", winSize.width, winSize.height); //竖屏 width: 270  height: 480
//        }, 1, ""); //1秒后获取


        winSize = Director::getInstance()->getVisibleSize();
        log("winSize %f,%f", winSize.width, winSize.height); //竖屏 width: 270  height: 480

        TTFConfig config("fonts/HelloKitty.ttf", 30);
        auto labelGame = Label::createWithTTF(config, "2048");
        Size labelGameSize = labelGame->getContentSize();
        log("labelGameSize %f,%f", labelGameSize.width, labelGameSize.height);
        labelGame->setPosition(winSize.width / 2 + labelGameSize.width / 3, winSize.height / 1.4);
        labelGame->setScale(1.5);
        addChild(labelGame);


        ////////////返回按钮////////////
        auto labelMenu = Label::createWithTTF("Back", "fonts/arial.ttf", 20.0f);
        auto menu = Menu::create(
                MenuItemLabel::create(labelMenu, [](Ref *pSender) {
                    Director::getInstance()->popScene(); //退出当前场景
                    JNITools::changeActivityOrientation(1); //横屏
                }), NULL);
        menu->setPosition(winSize.width - 20, 20);


        ///////////////开始按钮////////////
        auto startLabel = Label::createWithTTF("Start", "fonts/arial.ttf", 28.0f);
        auto gameMenu = Menu::create(
                MenuItemLabel::create(startLabel, [](Ref *pSender) {
                    auto scene = GameScene::createScene();
                    Director::getInstance()->replaceScene(TransitionFadeDown::create(0.5f, scene));
                }), NULL);
        gameMenu->setPosition(winSize.width / 2 + startLabel->getContentSize().width / 3,
                              winSize.height / 2);

        addChild(menu);
        addChild(gameMenu);

        //横竖屏切换时延时1秒可以正确获取宽高
//        scheduleOnce(schedule_selector(MainScene::initView), 1.0f);
        return true;
    };
}


