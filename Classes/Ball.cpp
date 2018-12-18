//
// Created by jun zhao on 2018/12/17.
//

#include "Ball.h"

bool Ball::init() {
    Sprite::initWithFile("ball.png"); //调用父类的方法进行初始化
    speedX = rand_0_1() * 10 - 5;  //[-5,5] x轴速度
    speedY = rand_0_1() * 10 - 5;  //[-5,5] y轴速度
    return true;
}

void Ball::move() {
    this->setPosition(this->getPositionX() + speedX, this->getPositionY() + speedY);
}