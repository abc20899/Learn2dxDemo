//
// Created by jun zhao on 2018/12/17.
//

#include "BallSpriteScene.h"

Scene *BallSprite::createScene() {
    return BallSprite::create();
}

bool BallSprite::init() {
    if (!Scene::init()) {
        return false;
    }
    winSize = Director::getInstance()->getVisibleSize();

    //每0.1秒添加一个小球
    schedule(schedule_selector(BallSprite::addBall), 0.1f);

    scheduleUpdate(); //更新每一帧
    return true;
}

void BallSprite::update(float dt) {
    Ball *b;
    for (auto it = balls.begin(); it != balls.end(); it++) {
        b = *it;
        b->move();
        //如果超出边界则移除屏幕和集合
        if (b->getPositionX() < 0 ||
            b->getPositionX() > winSize.width ||
            b->getPositionY() < 0 ||
            b->getPositionY() > winSize.height) {
            removeChild(b);  //移除屏幕
            balls.eraseObject(b);  //移除集合
        }
    }
}

void BallSprite::addBall(float dt) {
    auto ball = Ball::create();
    balls.pushBack(ball); //添加进集合
    addChild(ball); //添加进场景
    ball->setPosition(Vec2(winSize.width / 2, winSize.height / 2)); //添加到屏幕中间
}