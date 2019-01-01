//
// Created by jun zhao on 2018/12/18.
//

#ifndef __MAIN_SCENE_H__
#define __MAIN_SCENE_H__

#include "cocos2d.h"
#include <cocos-ext.h>
#include "BasicScene.h"
#include "LearnScenePoint.h"
#include "LearnSceneMath.h"
#include "BallSpriteScene.h"
#include "LearnEventScene.h"
#include "LearnUIScene.h"
#include "JoyStickScene.h"
#include "RollBallScene.h"
#include "game2048/MainScene.h"
#include "game2048/GameOver.h"
#include "game2048/HelloWorldScene.h"
#include "snake/MainScene.h"
#include "JNITools.h"
#include "BackgroundScroll.h"
#include "Puzzle.h"
#include "ParticleScene.h"
#include "findpair/FindPairScene.h"
#include "Sprite3DScene.h"
#include "littlegame/GameScene.h"

USING_NS_CC_EXT; //using namespace cocos2d::extension
USING_NS_CC;

class MainScene : public Scene, TableViewDataSource, TableViewDelegate {

private:
    Size visibleSize;

public:
    static Scene *createScene();

    virtual bool init();

    std::vector<std::string> _childTestNames;

    // 当滑动tableview时触发该方法 参数为当前的tableview对象
    virtual void scrollViewDidScroll(ScrollView *view) {};

    // 当tableview被放大或缩小时触发该方法  参数为当前tableview对象
    virtual void scrollViewDidZoom(ScrollView *view) {}

    // 当cell被点击时调用该方法 参数为当前的tableview对象与被点击的cell对象
    virtual void tableCellTouched(TableView *table, TableViewCell *cell);

    // 设置tableview的Cell大小
    virtual Size tableCellSizeForIndex(TableView *table, ssize_t idx);

    // 获取编号为idx的cell
    virtual TableViewCell *tableCellAtIndex(TableView *table, ssize_t idx);

    // 设置tableview中cell的个数
    virtual ssize_t numberOfCellsInTableView(TableView *table);

    void to2048(float dt);

    void toScrollbg(float dt);

    CREATE_FUNC(MainScene);
};


#endif //__MAIN_SCENE_H__
