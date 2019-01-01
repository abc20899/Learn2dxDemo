//
// Created by jun zhao on 2018/12/19.
//

#ifndef PROJ_ANDROID_NUMBERTILED_H
#define PROJ_ANDROID_NUMBERTILED_H

#include "cocos2d.h"
#include "GameDefine.h"

using namespace cocos2d;

class NumberTiled : public Node {

public:
    // 存储行列位置 及 该位置的数字值
    int num_col, num_row;
    int number;

public:
    // 移动到r,c 这个位置
    void moveTo(int r, int c);

    void doubleNumber();

    virtual bool init();

    CREATE_FUNC(NumberTiled);
};

#endif //PROJ_ANDROID_NUMBERTILED_H
