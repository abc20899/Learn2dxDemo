//
// Created by jun zhao on 2018/12/22.
//

#ifndef PROJ_ANDROID_PUZZLE_H
#define PROJ_ANDROID_PUZZLE_H

#include "cocos2d.h"

using namespace cocos2d;

class Puzzle : public Scene {

public:
    Size visibleSize;
    int size = 1080;
    int rows = 3, cols = 3;
    int width, height;
    Vector<Sprite *> allSp; //存储切片对象
    Vector<Sprite *> allSp2; //散乱切片集合
    int touchCount = 0;
    Sprite *swap1; //要交换的第一个切片
    Sprite *swap2; //要交换的第二个切片

    bool checkFinish(); //检查是否拼接完成

    void randomSp(); //打乱切片

    static Scene *createScene();

    virtual bool init();

    CREATE_FUNC(Puzzle)
};

#endif //PROJ_ANDROID_PUZZLE_H
