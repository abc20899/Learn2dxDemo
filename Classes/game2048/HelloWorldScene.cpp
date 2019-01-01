#include "HelloWorldScene.h"

USING_NS_CC;

namespace game2048 {

    Scene *HelloWorld::createScene() {
        return HelloWorld::create();
    }

    bool HelloWorld::init() {
        if (!Scene::init()) {
            return false;
        }

        Size visiableSzie = Director::getInstance()->getVisibleSize();

        auto bg = LayerColor::create(Color4B(180, 170, 160, 255));
        this->addChild(bg);

        //加入“分数”label
        TTFConfig config("fonts/HelloKitty.ttf", 30);
        auto labelTTFCardNumberName = Label::createWithTTF(config, "SCORE");

        labelTTFCardNumberName->setPosition(
                Vec2(visiableSzie.width * 0.3, visiableSzie.height - 40));
        addChild(labelTTFCardNumberName);

        //加入具体的分数
        labelTTFCardNumber = Label::createWithTTF(config, "0");
        labelTTFCardNumber->setPosition(Vec2(visiableSzie.width * 0.6, visiableSzie.height - 40));
        addChild(labelTTFCardNumber);

        //单点触摸
        auto touchListener = EventListenerTouchOneByOne::create();
        touchListener->onTouchBegan = [&](Touch *touch, Event *event) {
            auto point = touch->getLocation();
            firstX = point.x;
            firstY = point.y;
            return true;
        };
        touchListener->onTouchEnded = [&](Touch *touch, Event *event) {
            auto endPoint = touch->getLocation();
            endX = firstX - endPoint.x;
            endY = firstY - endPoint.y;

            //进行判断 包括 斜线滑动   如果endX的绝对值等于endY的绝对值就是左右滑动  则上下滑动
            if (abs(endX) > abs(endY)) {
                if (endX + 5 > 0) {  //5是误差值
                    //如果数字合并了 则再次进行随机产生
                    if (doLeft()) {
                        autoCreateCardNumber();
                        doCheckGameOver();
                    }
                } else {
                    if (doRight()) {
                        autoCreateCardNumber();
                        doCheckGameOver();
                    }
                }
            } else {
                if (endY + 5 > 0) {
                    if (doDown()) {
                        autoCreateCardNumber();
                        doCheckGameOver();
                    }
                } else {
                    if (doUp()) {
                        autoCreateCardNumber();
                        doCheckGameOver();
                    }
                }
            }
        };
        _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

        //创建卡片
        createCardSprite(visiableSzie);

        //产生两个数字
        autoCreateCardNumber();
        autoCreateCardNumber();
        return true;
    }

    void HelloWorld::autoCreateCardNumber() {
        int i = CCRANDOM_0_1() * 4;
        int j = CCRANDOM_0_1() * 4;

        //判断是否已经存在的位置 如果有数字则再进行随机
        if (cardArr[i][j]->getNumber() > 0) {
            autoCreateCardNumber();
        } else {
            // 会生成 2和4两个数字   比例是  1比9
            cardArr[i][j]->setNumber(CCRANDOM_0_1() * 10 < 1 ? 4 : 2);
        }
    }

    void HelloWorld::createCardSprite(Size size) {
        //求出单元格的宽和高
        int lon = (size.width - 28) / 4;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                auto card = CardSprite::create();
                card->addCard(0, lon, lon, lon * i + 20,
                              lon * j + 20 + size.height / 6);
                addChild(card);
                //添加到 卡片中
                cardArr[i][j] = card;
            }
        }
    }

    //判断游戏是否还能继续
    void HelloWorld::doCheckGameOver() {
        bool isGameOver = true;

        for (int y = 0; y < 4; y++) {
            for (int x = 0; x < 4; x++) {
                if (cardArr[x][y]->getNumber() == 0 ||
                    (x > 0 && (cardArr[x][y]->getNumber() == cardArr[x - 1][y]->getNumber())) ||
                    (x < 3 && (cardArr[x][y]->getNumber() == cardArr[x + 1][y]->getNumber())) ||
                    (y > 0 && (cardArr[x][y]->getNumber() == cardArr[x][y - 1]->getNumber())) ||
                    (y < 3 && (cardArr[x][y]->getNumber() == cardArr[x][y + 1]->getNumber()))) {
                    isGameOver = false;
                }
            }
        }

        if (isGameOver) {
            //游戏结束，重新开始游戏
            log("游戏结束");
            Director::getInstance()->replaceScene(
                    TransitionFade::create(1, HelloWorld::createScene()));
        }
    }

    bool HelloWorld::doLeft() {
        bool isDo = false;

        for (int y = 0; y < 4; y++) {
            for (int x = 0; x < 4; x++) {
                //进行左右数字判断 前两层for为迭代
                for (int x1 = x + 1; x1 < 4; x1++) {  //右一排的数字
                    if (cardArr[x1][y]->getNumber() > 0) {  //右一排的数字大于0
                        if (cardArr[x][y]->getNumber() <= 0) { //如果左一排的数字等于0 说明没有数字 则向左移动
                            cardArr[x][y]->setNumber(cardArr[x1][y]->getNumber()); //左一排的数字设置为右一排的数字
                            cardArr[x1][y]->setNumber(0);  //右一排的数字设置成0

//                        log("右一排 大于0");
                            x--;
                            isDo = true;
                        } else if (cardArr[x][y]->getNumber() ==
                                   cardArr[x1][y]->getNumber()) {  //如果相等则相加
                            cardArr[x][y]->setNumber(
                                    cardArr[x][y]->getNumber() * 2);  //左一排的数字设置为相加的和
                            cardArr[x1][y]->setNumber(0);  //右一排的数字设置成0

                            //改变分数
                            score += cardArr[x][y]->getNumber();
                            labelTTFCardNumber->setString(
                                    __String::createWithFormat("%i", score)->getCString());

                            isDo = true;
                        }

                        break;
                    }
                }
            }
        }
        return isDo;
    }

    bool HelloWorld::doRight() {
        bool isDo = false;
        for (int y = 0; y < 4; y++) {
            for (int x = 3; x >= 0; x--) {  //从最右边开始遍历

                //进行左右数字判断 前两层for为迭代
                for (int x1 = x - 1; x1 >= 0; x1--) {  //左一排的数字
                    if (cardArr[x1][y]->getNumber() > 0) {  //左一排的数字大于0
                        if (cardArr[x][y]->getNumber() <= 0) { //如果右一排的数字等于0 说明没有数字 则被其左边的数字占领
                            cardArr[x][y]->setNumber(cardArr[x1][y]->getNumber()); //右一排的数字设置为左一排的数字
                            cardArr[x1][y]->setNumber(0);  //左一排的数字设置成0

                            x--;
                            isDo = true;
                        } else if (cardArr[x][y]->getNumber() ==
                                   cardArr[x1][y]->getNumber()) {  //如果相等则相加
                            cardArr[x][y]->setNumber(
                                    cardArr[x][y]->getNumber() * 2);  //右一排的数字设置为相加的和
                            cardArr[x1][y]->setNumber(0);  //左一排的数字设置成0

                            //改变分数
                            score += cardArr[x][y]->getNumber();
                            labelTTFCardNumber->setString(
                                    __String::createWithFormat("%i", score)->getCString());

                            isDo = true;
                        }

                        break;
                    }
                }
            }
        }
        return isDo;
    }

    bool HelloWorld::doUp() {
        bool isdo = false;
        for (int x = 0; x < 4; x++) {
            for (int y = 3; y >= 0; y--) {
                for (int y1 = y - 1; y1 >= 0; y1--) {
                    if (cardArr[x][y1]->getNumber() > 0) {
                        if (cardArr[x][y]->getNumber() <= 0) {
                            cardArr[x][y]->setNumber(cardArr[x][y1]->getNumber());
                            cardArr[x][y1]->setNumber(0);

                            y++;
                            isdo = true;
                        } else if (cardArr[x][y]->getNumber() == cardArr[x][y1]->getNumber()) {
                            cardArr[x][y]->setNumber(cardArr[x][y]->getNumber() * 2);
                            cardArr[x][y1]->setNumber(0);

                            //改变分数
                            score += cardArr[x][y]->getNumber();
                            labelTTFCardNumber->setString(
                                    __String::createWithFormat("%i", score)->getCString());

                            isdo = true;
                        }
                        break;
                    }
                }
            }
        }
        return isdo;
    }

    bool HelloWorld::doDown() {
        bool isDo = false;
        for (int x = 0; x < 4; x++) {
            for (int y = 0; y < 4; y++) {  //从最右边开始遍历
                //进行左右数字判断 前两层for为迭代
                for (int y1 = y + 1; y1 < 4; y1++) {  //左一排的数字  y--有关系
                    if (cardArr[x][y1]->getNumber() > 0) {  //左一排的数字大于0
                        if (cardArr[x][y]->getNumber() <= 0) { //如果右一排的数字等于0 说明没有数字 则被其左边的数字占领
                            cardArr[x][y]->setNumber(cardArr[x][y1]->getNumber()); //右一排的数字设置为左一排的数字
                            cardArr[y][y1]->setNumber(0);  //左一排的数字设置成0

                            y--;
                            isDo = true;
                        } else if (cardArr[x][y]->getNumber() ==
                                   cardArr[x][y1]->getNumber()) {  //如果相等则相加
                            cardArr[x][y]->setNumber(
                                    cardArr[x][y]->getNumber() * 2);  //右一排的数字设置为相加的和
                            cardArr[x][y1]->setNumber(0);  //左一排的数字设置成0

                            //改变分数
                            score += cardArr[x][y]->getNumber();
                            labelTTFCardNumber->setString(
                                    __String::createWithFormat("%i", score)->getCString());

                            isDo = true;
                        }

                        break;
                    }
                }
            }
        }
        return isDo;
    }
}