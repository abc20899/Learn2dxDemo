//
// Created by jun zhao on 2018/12/17.
//

#include "RollBall.h"

bool RollBall::init() {
    Sprite::initWithFile("ball_2.png"); //调用父类的方法进行初始化
    winSize = Director::getInstance()->getVisibleSize();
    speedX = rand_0_1() * 10 - 5; //[-5 5]
    speedY = rand_0_1() * 10 - 5;

    scheduleUpdate();
    return true;
}

void RollBall::move() {
    this->setPosition(this->getPositionX() + speedX, this->getPositionY() + speedY);
//    if (this->getPositionX() > winSize.width + this->getContentSize().width / 2) {
//        this->setPosition(0, this->getPositionY() + speedY);
//    }

    //边界回弹
    if (getPositionX() < winSize.width / 2) {
        speedX = fabsf(speedX);
    }
    if (getPositionX() > winSize.width - getContentSize().width / 2) {
        speedX = -fabs(speedX); //相反方向
    }
    if (getPositionY() < winSize.height / 2) {
        speedY = fabs(speedY);
    }
    if (getPositionY() > winSize.height - getContentSize().height / 2) {
        speedY = -fabs(speedY);//相反方向
    }
}

void RollBall::update(float dt) {
    this->move();
}