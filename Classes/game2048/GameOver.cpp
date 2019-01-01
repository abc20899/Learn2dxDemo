//
// Created by jun zhao on 2018/12/19.
//

#include "GameOver.h"

namespace game2048 {

    Scene *GameOver::createScene() {
        return GameOver::create();
    }

    bool GameOver::init() {
        if (!Scene::init()) {
            return false;
        }

        auto winSize = Director::getInstance()->getVisibleSize();
        auto origin = Director::getInstance()->getVisibleOrigin();

        // 重新开始游戏
        auto restartItem = MenuItemFont::create(" Restart ",
                                                CC_CALLBACK_1(GameOver::menuRestartCallback, this));
        restartItem->setPosition(Vec2(winSize.width / 2, winSize.height / 2));

        // 退出游戏
        auto exit = MenuItemFont::create(" Exit ", CC_CALLBACK_1(GameOver::menuExitCallback, this));
        exit->setPosition(Vec2(winSize.width / 2, winSize.height / 3));

        auto menu = Menu::create(restartItem, exit, NULL);
        menu->setPosition(Point::ZERO);
        this->addChild(menu);

        return true;
    }

    void GameOver::menuRestartCallback(Ref *pSender) {
        auto scene = GameScene::create();
        Director::getInstance()->replaceScene(TransitionProgressRadialCCW::create(1, scene));
    }

    void GameOver::menuExitCallback(Ref *pSender) {
        Director::getInstance()->end();
    }
}