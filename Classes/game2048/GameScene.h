//
// Created by jun zhao on 2018/12/19.
//

#ifndef PROJ_ANDROID_GAMESCENE_H
#define PROJ_ANDROID_GAMESCENE_H

#include "cocos2d.h"
#include "MainScene.h"
#include "GameDefine.h"
#include "NumberTiled.h"
#include "GameOver.h"
#include "SimpleAudioEngine.h"


using namespace cocos2d;
using namespace CocosDenshion;

namespace game2048 {

    class GameScene : public Scene {

    public:
        static Scene *createScene();

        virtual bool init();

        void newNumberTiled();

        void moveUp();

        void moveDown();

        void moveLeft();

        void moveRight();

        void judgeMove();

        CREATE_FUNC(GameScene);
    private:
        int score = 0;
        bool sound_clear;
        bool isMoveUp, isMoveDown, isMoveRight, isMoveLeft;
        LayerColor *colorBlack;
        Size winSize;
        int map[GAME_ROWS][GAME_COLS]; //保存格子的二维数组
        Vector<NumberTiled *> allTiled;
        int m_x, m_y; //m_x和m_y 的作用是 记录屏幕开始触摸时的坐标
        bool m_startMove; //m_startMove 判断是否开始触摸，并且在一个滑动结束前，不允许再次获取触摸
        void moveAllTiled(MOVE_DIR dir); //就是根据滑动的方向，对相应方向的数字块 进行合并或者移动
    };
}

#endif //PROJ_ANDROID_GAMESCENE_H
