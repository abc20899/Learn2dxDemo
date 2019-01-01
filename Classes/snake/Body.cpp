//
// Created by jun zhao on 2018/12/20.
//

#include "Body.h"

namespace snake {

    bool Body::init() {
        scaleRate = Director::getInstance()->getContentScaleFactor();
        winSize = Director::getInstance()->getVisibleSize();
        origin = Director::getInstance()->getVisibleOrigin();
        Sprite::initWithFile("snake/head_left.png"); //调用父类的方法进行初始化
        return true;
    }

    void Body::updateBody(bool isHead, float x, float y) {
        this->isHead;
        this->x = x;
        this->y = y;
        log("body--%f,%f", x, y);
        if (isHead) {
            this->setTexture("snake/head_left.png");
        } else {
            this->setTexture("snake/body.png");
        }
        this->setPosition(Grid2Pos(x, y)); //移动到正确位置
    }

    void Body::move() {
        this->setPosition(Grid2Pos(this->x, this->y));
    }

    //计算body块的坐标
    Vec2 Body::Grid2Pos(float x, float y) {
        Vec2 newPos;
        newPos.x = winSize.width / 2 + origin.x + x * GRID_SIZE / scaleRate;
        newPos.y = winSize.height / 2 + origin.y + y * GRID_SIZE / scaleRate;
        log("body-22-%f,%f", newPos.x, newPos.y);
        return newPos;
    }

}