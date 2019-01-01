//
// Created by jun zhao on 2018/12/30.
//

#ifndef PROJ_ANDROID_FINDPAIRSCENE_H
#define PROJ_ANDROID_FINDPAIRSCENE_H

#define ROWS 4
#define COLS 6

#include "cocos2d.h"

using namespace cocos2d;

class FindPairScene : public Scene {

public:
    Size winSize;
    std::vector<Vec2> points; //卡片位置数据
    ValueVector fileNames; //所有卡片名字
    Vector<Sprite *> cards;//存储卡片数据
    int cardWidth; //卡片宽、高
    int cardHeight;
    int rightIndex; //记录正确位置的card

public:
    static Scene *createScene();

    virtual bool init();

    void calPoints(); //计算位置

    void addCards(); //添加所有卡片

    void addCard(int index);//添加单个卡片

    CREATE_FUNC(FindPairScene)
};

#endif //PROJ_ANDROID_FINDPAIRSCENE_H
