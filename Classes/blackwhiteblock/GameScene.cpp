//
// Created by jun zhao on 2019/1/2.
//

#include "GameScene.h"

namespace blackwhite {

    Scene *GameScene::createScene() {
        return GameScene::create();
    }

    bool GameScene::init() {
        if (!Scene::init()) {
            return false;
        }

        winSize = Director::getInstance()->getVisibleSize();
        origin = Director::getInstance()->getVisibleOrigin();
        log("winSize--%f,%f", winSize.width, winSize.height);

        startGame();

        //计时标签
        timerLabel = Label::create();
        timerLabel->setTextColor(Color4B::BLUE);
        timerLabel->setSystemFontSize(48);
        timerLabel->setPosition(winSize.width / 2, winSize.height - 100);
//        addChild(timerLabel);
        return true;
    }

    void GameScene::startGame() {
        lineCount = 0;
        isEnd = false;
        this->removeAllChildren();
        addChild(LayerColor::create(Color4B(246, 246, 246, 255)));
        addStartLine();
        addNormalLine(1);
        addNormalLine(2);
        addNormalLine(3);

        auto listener = EventListenerTouchOneByOne::create();
//        listener->onTouchBegan = CC_CALLBACK_2(GameScene::touchBeganHandler, this);
        listener->onTouchBegan = [this](Touch *touch, Event *event) {
            Block *block;
            for (auto it = blockes.begin(); it != blockes.end(); it++) {
                block = *it;
                if (block->lineIndex == 1 &&
                    block->getBoundingBox().containsPoint(touch->getLocation())) {
                    if (block->getColor() == Color3B::BLACK) {
                        if (!isTimerRunning) { //点击开始计时
                            this->startTimer();
                        }
                        // 触摸到黑色块，就让它变成灰色
                        block->setColor(Color3B::GRAY);
                        this->moveDown();
                        break; //停止循环
                    } else {
                        // 未触摸到该行黑色块，就提示 游戏失败
                        addEndLine();
                        stopTimer();
                        break; //停止循环
                    }
                }
            }
            return false;
        };
        Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(
                listener, this);
    }

    void GameScene::addNormalLine(int lineNum) {
        int blockIndex = rand() % 4;
        for (int i = 0; i < 4; ++i) {
            //-2 作为间隙
            auto block = Block::createBlock(
                    Size(winSize.width / 4.0f - 2, winSize.height / 4.0f - 2),
                    blockIndex == i ? Color3B::BLACK : Color3B::WHITE,
                    "",
                    20,
                    Color4B::BLACK
            );
            addChild(block);
            block->setPosition(
                    Vec2(origin.x + i * winSize.width / 4.0f,
                         origin.y + lineNum * winSize.height / 4.0f));
            block->lineIndex = lineNum;
            blockes.pushBack(block);
        }
    }

    //开始行
    void GameScene::addStartLine() {
        auto block = Block::createBlock(Size(winSize.width, winSize.height / 4.0f), Color3B::YELLOW,
                                        "", 20, Color4B::BLACK);
        block->lineIndex = 0;
        block->setPosition(Vec2(origin.x, origin.y));
        addChild(block);

        blockes.pushBack(block);

        log("block**,%f,%f--%f,%f--,%f,%f",
            block->getPosition().x,
            block->getPosition().y,
            block->getAnchorPoint().x,
            block->getAnchorPoint().y,
            block->getContentSize().width,
            block->getContentSize().height);
    }

    void GameScene::addEndLine() {
        this->removeAllChildren();
        auto block = Block::createBlock(winSize, Color3B::GREEN, "Game Over", 32, Color4B::BLACK);
        block->lineIndex = 4;
        addChild(block);
        block->setPosition(origin.x, origin.y);

        ////////////返回按钮////////////
        auto labelMenu = Label::createWithTTF("Back", "fonts/arial.ttf", 20.0f);
        auto menu2 = Menu::create(
                MenuItemLabel::create(labelMenu, [](Ref *pSender) {
                    Director::getInstance()->popScene(); //退出当前场景
                    JNITools::changeActivityOrientation(1); //横屏
                }), NULL);
        menu2->setPosition(winSize.width - 20, 50);
        addChild(menu2);
    }

    bool GameScene::touchBeganHandler(Touch *touch, Event *event) {
        Block *block;
        for (auto it = blockes.begin(); it != blockes.end(); it++) {
            block = *it;
            if (block->lineIndex == 1 &&
                block->getBoundingBox().containsPoint(touch->getLocation())) {
                if (block->getColor() == Color3B::BLACK) {
                    // 触摸到黑色块，就让它变成灰色
                    block->setColor(Color3B::GRAY);
                    this->moveDown();
                    break;  //停止循环
                } else {
                    // 未触摸到该行黑色块，就提示 游戏失败
                    addEndLine();
                    break; //停止循环
                }
            }
        }
        return false;
    }

    void GameScene::moveDown() {
        //产生新的一行
//        if (lineCount < 50) { //小于50行
        addNormalLine(4);
//            lineCount += 1;
//        } else if (isEnd) {  //时间模式
//            addEndLine();
//            isEnd = false;
//        }
        //所有块执行向下移动，最下面一行消除
        Block *block;
        for (auto it = blockes.begin(); it != blockes.end(); it++) {
            block = (*it);
            block->moveDown([this, block]() {
                if (block->lineIndex < 0) { //行号小于0的移除集合和场景
                    block->removeBlock();
                    blockes.eraseObject(block);
                }
            });
        }
    }

    double GameScene::getMillSecond() {
        struct timeval tv;
        gettimeofday(&tv, nullptr);
        log("CurrentTime MillSecond %f", (double) tv.tv_sec * 1000 + (double) tv.tv_usec / 1000);
        return (double) tv.tv_sec * 1000 + (double) tv.tv_usec / 1000;
    }

    void GameScene::startTimer() {
        if (!isTimerRunning) {
            scheduleUpdate();
            m_time = 20.0;
            startTime = getMillSecond(); //获取到时间戳
            isTimerRunning = true;
        }
    }

    void GameScene::stopTimer() {
        if (isTimerRunning) {
            unscheduleUpdate();
            isTimerRunning = false;
        }
    }

    void GameScene::update(float dt) {
        //时间的偏差
        long offset = getMillSecond() - startTime;
        log("offset--%lu", offset);
        timerLabel->setString(StringUtils::format("%.2f", m_time - offset / 1000));
        if (m_time - offset / 1000 <= 0) {
            isEnd = true;
            timeOver();
        }
    }

    //时间到 addEnd
    void GameScene::timeOver() {
        if (isTimerRunning) {
            unscheduleUpdate();
            isTimerRunning = false;
        }
        timerLabel->setString("0.00");
//        this->scheduleOnce(schedule_selector(modeLimitTime::gameOver), 3.0f);
    }
}