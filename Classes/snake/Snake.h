//
// Created by jun zhao on 2018/12/20.
//

#ifndef PROJ_ANDROID_SNAKE_H
#define PROJ_ANDROID_SNAKE_H

#include "cocos2d.h"
#include "Body.h"
#include "GameDefine.h"

using namespace cocos2d;

namespace snake {

    class Snake : public Sprite {

    public:
        MOVE_DIR dir; //移动方向
        int cInitLen = 3; //初始化长度
        Vector<Body *> bodyArray; //body数组

    public:
        virtual bool init();

        void initBody();

        //取出蛇尾body 获取坐标
        Vec2 getTailPos();

        //取出蛇头获取坐标
        Vec2 getHeadPos();

        //根据方向改变坐标
        Vec2 offsetBodyByDir(float x, float y, MOVE_DIR dir);

        void changeHeadTexture(MOVE_DIR dir); //根据方向改变蛇头朝向图片

        //死亡之后的闪烁效果
        void blinkAction();

        void killSnake();

        bool eatSelf(); //是否咬到自己

        //增长方法
        void grow(bool isHead);

        void update();//更新

        CREATE_FUNC(Snake);
    };
}

#endif //PROJ_ANDROID_SNAKE_H
