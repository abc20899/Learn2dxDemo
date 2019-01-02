//
// Created by jun zhao on 2019/1/2.
//

#ifndef PROJ_BLACKWHITE_GAMESCENE_H
#define PROJ_BLACKWHITE_GAMESCENE_H

#include "cocos2d.h"
#include "Block.h"
#include "../basic/JNITools.h"

USING_NS_CC;

namespace blackwhite {

    class GameScene : public Scene {

    public:
        Size winSize;
        Vec2 origin;
        Vector<Block *> blockes;
        int lineCount; //记录移动的行数
        bool isEnd; //是否结束
        Label *timerLabel;
        bool isTimerRunning;
        long startTime;
        double m_time;
    public:
        static Scene *createScene();

        virtual bool init();

        void startGame();

        void addStartLine();

        void addEndLine();

        void addNormalLine(int lineNum);

        void moveDown();//移动块

        void startTimer();

        void stopTimer();

        virtual void update(float dt);

        double getMillSecond();

        void timeOver();

        bool touchBeganHandler(Touch *touch, Event *event);

        CREATE_FUNC(GameScene);
    };
}

#endif //PROJ_ANDROID_GAMESCENE_H
