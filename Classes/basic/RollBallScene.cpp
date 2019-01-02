//
// Created by jun zhao on 2018/12/18.
//

#include "RollBallScene.h"

Scene *RollBallScene::createScene() {
    return RollBallScene::create();
}

bool RollBallScene::init() {
    if (!Scene::init()) {
        return false;
    }

    winSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

//    ball = Sprite::create("ball_2.png");
//    ball->setPosition(Vec2(100, 100));
//    addChild(ball);
    //每一秒移动100个像素
//    ball->runAction(RepeatForever::create(MoveBy::create(1, Vec2(100, 0))));


//    addBall(100,100);
//    addBall(100,150);
//    addBall(100,200);
//    addBall(100,250);

//    scheduleUpdate();


    for (int i = 0; i < 30; ++i) {
        auto ball = RollBall::create();
        ball->setPosition(Vec2(rand_0_1() * 200 + 100, rand_0_1() * 200 + 100));
        addChild(ball);
    }



    ////////////返回按钮////////////
    auto labelMenu = Label::createWithTTF("Back", "fonts/arial.ttf", 20.0f);
    auto menu2 = Menu::create(
            MenuItemLabel::create(labelMenu, [](Ref *pSender) {
                Director::getInstance()->popScene(); //退出当前场景
            }), NULL);
//    menu2->setAnchorPoint(Vec2(0.5, 0.5)); 锚点默认为0，0 不能设置锚点
    menu2->setPosition(30, 50);
    addChild(menu2);
    return true;
}

void RollBallScene::addBall(float x, float y) {
    auto ball = RollBall::create();
    ball->setPosition(Vec2(x, y));
    addChild(ball);
    balls.pushBack(ball); //添加进集合
}

void RollBallScene::update(float dt) {
//    ball->setPositionX(ball->getPositionX() + 5); //每帧移动5像素
//    if (ball->getPositionX() > winSize.width + ball->getContentSize().width / 2) {
//        ball->setPositionX(-ball->getContentSize().width / 2); //从0继续移动
//    }

//    for (auto it = balls.begin(); it != balls.end(); it++) {
//        (*it)->move(); //获取到小球开始移动
//    }
}