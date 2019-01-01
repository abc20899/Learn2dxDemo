//
//  CardSprite.h
//  my2048
//
//  Created by junechiu on 14-4-18.
//
//

#ifndef __my2048__CardSprite__
#define __my2048__CardSprite__

#include "cocos2d.h"

USING_NS_CC;

class CardSprite : public Sprite {

public:
    virtual bool init();

    //设置数字
    void setNumber(int _number);

    int getNumber();

    //初始化卡片的方法  参数numbers 不能和变量number的名字一样
    void addCard(int number, int width, int height, float cardSpriteX,
                 float cardSpriteY);

    CREATE_FUNC(CardSprite);

private:
    //显示在界面上的数字
    int number;

    //显示数字的控件
    Label *cardLabel;

    //显示背景
    LayerColor *colorBG;
};

#endif /* defined(__my2048__CardSprite__) */
