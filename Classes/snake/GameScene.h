//
// Created by jun zhao on 2018/12/20.
//

#ifndef PROJ_SNAKE_GAMESCENE_H
#define PROJ_SNAKE_GAMESCENE_H

#include "cocos2d.h"
#include "MainScene.h"
#include "Body.h"
#include "Snake.h"
#include "Fence.h"
#include "AppleFactory.h"

using namespace cocos2d;

namespace snake {

    class GameScene : public Scene {

    public:
        int state = GAME_RUNING;//游戏状态 0失败1正在运行
        float scaleRate;
        Size winSize;
        Vec2 origin;
        Label *scoreLabel;
        int score = 0;
        float down_x, down_y;
        bool m_startMove; //m_startMove 判断是否开始触摸，并且在一个滑动结束前，不允许再次获取触摸
    public:
        static Scene *createScene();

        virtual bool init();

        void gameUpdate(float dt); //游戏更新

        Vec2 Grid2Pos(float x, float y); //根据自定义的坐标得到实际应该显示的cocos2d-x坐标位置

        void callback();

        void setScore();

        /**
         * 死亡后，直接重新开始就行了，可以来个死亡动画后再开始游戏
         * 死亡后，界面仍在刷新，我们需要设置一个程序运行状态
         * 死亡后，我们希望，蛇能够重新生成，开始（因为我们以后的蛇，如果边长了，我们重来，蛇将依然是初始长度）
         * */
        CREATE_FUNC(GameScene);
    };
}

#endif //PROJ_ANDROID_GAMESCENE_H
