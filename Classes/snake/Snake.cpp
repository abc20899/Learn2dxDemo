//
// Created by jun zhao on 2018/12/20.
//

#include "Snake.h"

namespace snake {

    bool Snake::init() {
        Sprite::init();
        initBody();
        return true;
    }

    void Snake::initBody() {
        this->dir = MOVE_DIR::LEFT; //默认向左
        //初始化蛇
        for (int i = 0; i < cInitLen; ++i) {
            if (i == 0) { //head
                grow(true);
            } else {
                grow(false);
            }
        }
        log("sna size--%d", bodyArray.size());
    }

    //取出蛇尾位置
    Vec2 Snake::getTailPos() {
        if (bodyArray.size() == 0) {
            return Vec2(0, 0);
        } else {
            auto body = bodyArray.back(); //back返回最后一个元素
            return Vec2(body->x, body->y);
        }
    }

    //获取头位置
    Vec2 Snake::getHeadPos() {
        if (bodyArray.size() == 0) {
            return Vec2(0, 0);
        } else {
            auto body = bodyArray.front(); //front返回第一个元素
            return Vec2(body->x, body->y);
        }
    }

    void Snake::grow(bool isHead) {
        auto body = Body::create();
        Vec2 pos = getTailPos();
        log("grow--  %f,%f", pos.x, pos.y);
        body->updateBody(isHead, pos.x, pos.y);
        bodyArray.pushBack(body); //添加进集合
        addChild(body); //精灵节点添加精灵
    }

    Vec2 Snake::offsetBodyByDir(float x, float y, MOVE_DIR dir) {
        Vec2 pos(x, y);
        if (dir == MOVE_DIR::LEFT) {
            pos.x = x - 1;
            pos.y = y;
        } else if (dir == MOVE_DIR::RIGHT) {
            pos.x = x + 1;
            pos.y = y;
        } else if (dir == MOVE_DIR::UP) {
            pos.x = x;
            pos.y = y + 1;
        } else if (dir == MOVE_DIR::DOWN) {
            pos.x = x;
            pos.y = y - 1;
        }
        log("grow-off-  %f,%f", pos.x, pos.y);
        return pos;
    }

    void Snake::changeHeadTexture(MOVE_DIR dir) {
        auto body = bodyArray.front();
        if (dir == MOVE_DIR::LEFT) {
            body->setTexture("snake/head_left.png");
        } else if (dir == MOVE_DIR::RIGHT) {
            body->setTexture("snake/head_right.png");
        } else if (dir == MOVE_DIR::UP) {
            body->setTexture("snake/head_up.png");
        } else if (dir == MOVE_DIR::DOWN) {
            body->setTexture("snake/head_down.png");
        }
    }

    //根据一个移动方向，得到新的头部位置，然后从尾部到头部，每一个节点都更新成上一个节点
    void Snake::update() {
        if (bodyArray.size() == 0) {
            return;
        }

        for (int i = bodyArray.size() - 1; i > -1; --i) {
            log("sna index--%d", i);
            auto body = bodyArray.at(i); //从蛇尾开始获取body
            if (i == 0) { //蛇头位置与 方向，得到一个新的位置 存放蛇头
                Vec2 pos = offsetBodyByDir(body->x, body->y, this->dir);
                body->x = pos.x;
                body->y = pos.y;
            } else {
                //蛇尾的节点更新成前一个节点的坐标
                auto fontBody = bodyArray.at(i - 1);
                body->x = fontBody->x;
                body->y = fontBody->y;
            }
            body->move();
        }
    }

    //是否咬到自己
    bool Snake::eatSelf() {
        Vec2 pos = getHeadPos(); //头位置
        for (int i = 1; i < bodyArray.size(); i++) {
            auto body = bodyArray.at(i);
            if (pos.x == body->x && pos.y == body->y) {
                return true;
            }
        }
        return false;
    }

    void Snake::blinkAction() {
        for (int i = 0; i < bodyArray.size(); i++) {
            auto blink = Blink::create(3, 5);//闪烁动画
            auto body = bodyArray.at(i);
            body->runAction(blink);
        }
    }

    void Snake::killSnake() {
        Body *sp;
        for (auto it = bodyArray.begin(); it != bodyArray.end(); it++) {
            sp = *it;
            removeChild(sp, true);
        }
        bodyArray.clear(); //清空集合
    }
}