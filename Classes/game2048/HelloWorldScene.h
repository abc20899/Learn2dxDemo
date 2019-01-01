#ifndef __HELLOWORLD2048_SCENE_H__
#define __HELLOWORLD2048_SCENE_H__

#include "cocos2d.h"
#include "CardSprite.h"

USING_NS_CC;

namespace game2048 {

    class HelloWorld : public Scene {

    public:

        static Scene *createScene();

        virtual bool init();

        bool doLeft();

        bool doRight();

        bool doUp();

        bool doDown();

        //创建卡片  size屏幕大小
        void createCardSprite(Size size);

        //自动生成卡片
        void autoCreateCardNumber();

        //判断游戏是否结束
        void doCheckGameOver();

        //游戏总分
        int score;

        //定义显示分数的控件
        Label *labelTTFCardNumber;

        CREATE_FUNC(HelloWorld);
    private:
        int firstX, firstY, endX, endY;

        //定义一个卡片的二维数组
        CardSprite *cardArr[4][4];
    };
}

#endif // __HELLOWORLD2048_SCENE_H__
