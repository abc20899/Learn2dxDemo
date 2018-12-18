//
// Created by jun zhao on 2018/12/16.
//

#ifndef __LEARNMATH_SCENE_H__
#define __LEARNMATH_SCENE_H__

#include "cocos2d.h"

using namespace cocos2d;

//简单的三角函数
/**
 * sin 对边/斜边   1/2  sin(30)
 *      计算机中角度转换为弧度  360角度=2PI弧度   180角度=PI弧度
 * sin(30*PI/180)
 *
 *
 *
 * */

class LearnSceneMath : public Scene {

public:
    float angle = 0; //角度
    Vec2 direction;//运动点
    Size visibleSize;//屏幕大小

    static Scene *createScene();

    virtual bool init();

    void dotRun(float delay);
    // implement the "static create()" method manually
    CREATE_FUNC(LearnSceneMath);
};

#endif //__LEARNMATH_SCENE_H__
