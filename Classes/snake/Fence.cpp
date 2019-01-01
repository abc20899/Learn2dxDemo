//
// Created by jun zhao on 2018/12/21.
//

#include "Fence.h"

namespace snake {

    bool Fence::init() {
        Sprite::init();
        scaleRate = Director::getInstance()->getContentScaleFactor();
        winSize = Director::getInstance()->getVisibleSize();
        origin = Director::getInstance()->getVisibleOrigin();
        return true;
    }

    //循环添加格子
    void Fence::fenceGenerator(int bound, std::function<Vec2(int)> lambdaCallBabck) {
        for (int i = -bound; i < bound + 1; ++i) {
            auto fence = Sprite::create("snake/fence.png");
            if (lambdaCallBabck) {
                Vec2 pos = lambdaCallBabck(i);
                fence->setPosition(pos); //设置坐标
                addChild(fence); //精灵节点添加精灵
                fenceArray.pushBack(fence); //添加进集合
            }
        }
    }

    //rowBound  5 距离原点5 的一行
    //colBound 8 列
    void Fence::fenceAll(int rowBound, int colBound) {
        //up 上面围墙
        fenceGenerator(colBound, [&](int i) -> Vec2 {
            log("fenceGenerator-- %d,%d", i, rowBound);
            return Grid2Pos(i, rowBound); //-8,5  -7,5 ... 8,5
        });
        //down 下面墙
        fenceGenerator(colBound, [&](int i) -> Vec2 {
            log("fenceGenerator-- %d,%d", i, -rowBound);
            return Grid2Pos(i, -rowBound); //-8,-5  -7,-5 ... 8,-5
        });
        //left
        fenceGenerator(rowBound, [&](int i) -> Vec2 {
            return Grid2Pos(-colBound, i); //-8,-5  -8,-4... -8,5
        });
        //right
        fenceGenerator(rowBound, [&](int i) -> Vec2 {
            return Grid2Pos(colBound, i); //8,-5  8,-4 ... 8,5
        });
    }

    bool Fence::checkCollide(float x, float y) {
        if (abs((int) x) >= FENCE_COL || abs((int) y) >= FENCE_ROW) {
            return true;
        } else {
            return false;
        }
    }

    //销毁Fence
    void Fence::reset() {
        Sprite *sp;
        for (auto it = fenceArray.begin(); it != fenceArray.end(); it++) {
            sp = *it;
            this->removeChild(sp, true);
        }
        fenceArray.clear(); //清空集合
    }

    //计算body块的坐标
    Vec2 Fence::Grid2Pos(float x, float y) {
        Vec2 newPos;
        newPos.x = winSize.width / 2 + origin.x + x * GRID_SIZE / scaleRate;
        newPos.y = winSize.height / 2 + origin.y + y * GRID_SIZE / scaleRate;
        log("body-22-  %f,%f", newPos.x, newPos.y);
        return newPos;
    }
}
