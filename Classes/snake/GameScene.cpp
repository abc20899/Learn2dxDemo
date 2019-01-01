//
// Created by jun zhao on 2018/12/20.
//

#include "GameScene.h"

namespace snake {
    Scene *GameScene::createScene() {
        return GameScene::create();
    }

    bool GameScene::init() {
        if (!Scene::init()) {
            return false;
        }
        scaleRate = Director::getInstance()->getContentScaleFactor();
        winSize = Director::getInstance()->getVisibleSize();
        origin = Director::getInstance()->getVisibleOrigin();

        //分数版
        auto scoreSp = Sprite::create("snake/score.png");
        addChild(scoreSp);
        scoreSp->setPosition(Vec2(winSize.width - 50, winSize.height / 2));
        TTFConfig ttfConfig("fonts/arial.ttf", 20);
        scoreLabel = Label::createWithTTF(ttfConfig, "0");
        addChild(scoreLabel);
        scoreLabel->setPosition(Vec2(winSize.width - 50, winSize.height / 2 - 20));


        //创建围墙
        auto fence = Fence::create();
        fence->fenceAll(FENCE_ROW, FENCE_COL);
        addChild(fence);

        //add Snake
        auto snake = Snake::create();
        addChild(snake);

        //add apple
        auto apple = AppleFactory::create();
        apple->generateApple(); //随机添加一个苹果
        addChild(apple);

        //定时器 每0.3秒更新一次
//        const std::function<void(float)> &callback,float interval,unsigned int repeat,float delay,const std::string &key
        schedule([=](float dt) { //任何变量按值捕获
            if (state == GAME_RUNING) {
                snake->update();
                Vec2 pos = snake->getHeadPos();
                if (fence->checkCollide(pos.x, pos.y) || snake->eatSelf()) { //蛇与围墙相撞
                    log("game-- collide fence");
                    fence->reset();
                    snake->blinkAction();
                    snake->killSnake();
                    state = GAME_OVER;
                }
                if (apple->eatApple(pos.x, pos.y)) { //是否吃到苹果
                    apple->generateApple(); //重新生产苹果
                    snake->grow(false); //蛇变长
                    score += 1;
                }
            } else {
                //重新开始
                score = 0;
                fence->fenceAll(FENCE_ROW, FENCE_COL);
                snake->initBody();
                apple->generateApple();
                state = GAME_RUNING;
            }
            setScore(); //设置分数
        }, 0.3f, -1, 1, "snake"); //1秒后执行
//        schedule(schedule_selector(GameScene::gameUpdate), 0.3f, -1, 1);

//        auto actionCall = Sequence::create(Blink::create(3, 5), CallFunc::create(
//                CC_CALLBACK_0(GameScene::callback, this)), NULL);

        //触摸监听
        auto listener = EventListenerTouchOneByOne::create();
        listener->onTouchBegan = [&](Touch *touch, Event *event) {
            down_x = touch->getLocation().x;
            down_y = touch->getLocation().y;
            m_startMove = true;
            return true;
        };
        listener->onTouchMoved = [&, snake](Touch *touch, Event *event) {
            float x = touch->getLocation().x;
            float y = touch->getLocation().y;
            int distanceX = abs(down_x - x); //x轴移动距离
            int distanceY = abs(down_y - y);//y轴移动距离
            //x轴或者y轴移动距离大于10像素作为一次移动
            if (m_startMove && (distanceX > 10 || distanceY > 10)) {
                m_startMove = false;
                MOVE_DIR dir; //判断移动方向
                if (distanceX > distanceY) { //x轴移动
                    //判断左右
                    if (x > down_x) {
                        dir = MOVE_DIR::RIGHT;
                    } else {
                        dir = MOVE_DIR::LEFT;
                    }
                } else {
                    //判断上下
                    if (y > down_y) {
                        dir = MOVE_DIR::UP;
                    } else {
                        dir = MOVE_DIR::DOWN;
                    }
                }
                snake->dir = dir;
                snake->changeHeadTexture(dir);//改变头body图片
            }
        };
        Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(
                listener, this);

        ////////////返回按钮////////////
        auto labelMenu = Label::createWithTTF("Back", "fonts/arial.ttf", 20.0f);
        auto menu = Menu::create(
                MenuItemLabel::create(labelMenu, [](Ref *pSender) {
                    Director::getInstance()->replaceScene(MainScene::createScene()); //退出当前场景
                }), NULL);
        menu->setPosition(30, 120);
        addChild(menu);
        return true;
    }

    //
    void GameScene::gameUpdate(float dt) {
//        log("gameUpdate****%d,%d", fence->rowBound, fence->colBound);
//        snake->update();
//        Vec2 pos = snake->getHeadPos();
////        log("gameUpdate****%d,%d,%d", (int) pos.x, (int) pos.y, fence->colBound);
//        if (fence->checkCollide(pos.x, pos.y)) { //蛇与围墙相撞
////            log("gameUpdate****collide fence");
//        }
    }

    //计算body块的坐标
    Vec2 GameScene::Grid2Pos(float x, float y) {
        Vec2 newPos;
        newPos.x = winSize.width / 2 + origin.x + x * GRID_SIZE * scaleRate;
        newPos.y = winSize.height / 2 + origin.y + y * GRID_SIZE * scaleRate;
        return newPos;
    }

    void GameScene::setScore() {
        scoreLabel->setString(__String::createWithFormat("%d", this->score)->getCString());
    }

    void GameScene::callback() {}
}