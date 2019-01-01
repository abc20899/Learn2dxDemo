//
// Created by jun zhao on 2018/12/22.
//

#include "AppleFactory.h"

namespace snake {

    bool AppleFactory::init() {
        Sprite::init();
        scaleRate = Director::getInstance()->getContentScaleFactor();
        winSize = Director::getInstance()->getVisibleSize();
        origin = Director::getInstance()->getVisibleOrigin();
        return true;
    }

    //计算body块的坐标
    Vec2 AppleFactory::Grid2Pos(float x, float y) {
        Vec2 newPos;
        newPos.x = winSize.width / 2 + origin.x + x * GRID_SIZE / scaleRate;
        newPos.y = winSize.height / 2 + origin.y + y * GRID_SIZE / scaleRate;
        log("body-22-  %f,%f", newPos.x, newPos.y);
        return newPos;
    }

    //获取随机位置
    Vec2 AppleFactory::getRandomPos(int row, int col) {
        Vec2 pos;
        pos.x = random(-col, col);
        pos.y = random(-row, row);
        appleX = pos.x;
        appleY = pos.y;
        return pos;
    }

    //生成苹果
    void AppleFactory::generateApple() {
        this->removeAllChildren(); //先移除所有node
        auto appleSprite = Sprite::create("snake/apple.png");
        Vec2 pos = getRandomPos(FENCE_ROW - 1, FENCE_COL - 1); //不能与墙的坐标重复
        log("apple-- %f,%f", pos.x, pos.y);
        addChild(appleSprite);
        appleSprite->setPosition(Grid2Pos(pos.x, pos.y));
    }

    //是否吃到苹果
    bool AppleFactory::eatApple(float x, float y) {
        if (x == appleX && y == appleY) {
            log("apple-- eat apple");
            return true;
        }
        return false;
    }
}