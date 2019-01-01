//
//  CardSprite.cpp
//  my2048
//
//  Created by junechiu on 14-4-18.
//
//

#include "CardSprite.h"

bool CardSprite::init() {
    if (!Sprite::init()) {
        return false;
    }
    return true;
}

void CardSprite::addCard(int numbers, int width, int height, float cardSpriteX, float cardSpriteY) {
    //初始化数字
    number = numbers;
    //加入卡片的背景颜色
    colorBG = LayerColor::create(Color4B(200, 190, 180, 255), width - 15, height - 15);
    colorBG->setPosition(Vec2(cardSpriteX, cardSpriteY));

    //进行显示的判断  如果>0 就显示   否则不显示
    if (number > 0) {
        //加入中间数字
        TTFConfig config("fonts/HelloKitty.ttf", 30);
        cardLabel = Label::createWithTTF(config, StringUtils::format("%d", this->number));
        cardLabel->setPosition(
                Vec2(colorBG->getContentSize().width / 2, colorBG->getContentSize().height / 2));
        colorBG->addChild(cardLabel);
    } else {
        TTFConfig config("fonts/HelloKitty.ttf", 30);
        cardLabel = Label::createWithTTF(config, "");
        cardLabel->setPosition(
                Point(colorBG->getContentSize().width / 2, colorBG->getContentSize().height / 2));
        colorBG->addChild(cardLabel);
    }

    addChild(colorBG);
}

//设置数字
void CardSprite::setNumber(int _number) {
//    //判断数字的大小来调整字体
//    if (number >= 0) {
//        labelTTFCardNumber->setFontSize(100);
//    }
//    if (number >= 16) {
//        labelTTFCardNumber->setFontSize(90);
//    }
//    if(number >= 128){
//        labelTTFCardNumber->setFontSize(60);
//    }
//    if(number >= 1024){
//        labelTTFCardNumber->setFontSize(40);
//    }


//    
    number = _number;

    //判断数字的大小来调整颜色
    if (number == 0) {
        colorBG->setColor(cocos2d::Color3B(200, 190, 180));
    }
    if (number == 2) {
        colorBG->setColor(cocos2d::Color3B(240, 230, 220));
    }
    if (number == 4) {
        colorBG->setColor(cocos2d::Color3B(240, 220, 200));
    }
    if (number == 8) {
        colorBG->setColor(cocos2d::Color3B(240, 180, 120));
    }
    if (number == 16) {
        colorBG->setColor(cocos2d::Color3B(240, 140, 90));
    }
    if (number == 32) {
        colorBG->setColor(cocos2d::Color3B(240, 120, 90));
    }
    if (number == 64) {
        colorBG->setColor(cocos2d::Color3B(240, 90, 60));
    }
    if (number == 128) {
        colorBG->setColor(cocos2d::Color3B(240, 90, 60));
    }
    if (number == 256) {
        colorBG->setColor(cocos2d::Color3B(240, 200, 70));
    }
    if (number == 512) {
        colorBG->setColor(cocos2d::Color3B(240, 200, 70));
    }
    if (number == 1024) {
        colorBG->setColor(cocos2d::Color3B(0, 130, 0));
    }
    if (number == 2048) {
        colorBG->setColor(cocos2d::Color3B(0, 130, 0));
    }

    if (number > 0) {
        cardLabel->setString(__String::createWithFormat("%i", number)->getCString());
    } else {
        cardLabel->setString("");
    }

}

//获取数字
int CardSprite::getNumber() {
    return number;
}