//
// Created by jun zhao on 2018/12/30.
//

#include "FindPairScene.h"

Scene *FindPairScene::createScene() {
    return FindPairScene::create();
}

bool FindPairScene::init() {
    if (!Scene::init()) {
        return false;
    }

    //随机种子
    srand(time(NULL));

    winSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

    cardWidth = winSize.width / COLS;
    cardHeight = winSize.height / ROWS;
    fileNames = FileUtils::getInstance()->getValueVectorFromFile("finpair/files.plist");

    calPoints();
    addCards();

//    auto sp = Sprite::create("finpair/f6.png");
//    sp->setAnchorPoint(Vec2(0, 0));
//    sp->setPosition(0.000000, cardHeight);
//    addChild(sp);

    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = [=](Touch *touch, Event *event) {
        //判断点击的卡片
        Sprite *card;
        for (auto it = cards.begin(); it != cards.end(); it++) {
            card = *it;
            if (card->getBoundingBox().containsPoint(touch->getLocation())) {
                int index = card->getTag();
                if (index == rightIndex) {
                    log("card---yes");
                    break;
                } else {
                    log("card---no");
                }
            }
        }
        return false;
    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener,
                                                                                          this);

    ////////////返回按钮////////////
    auto labelMenu = Label::createWithTTF("Back", "fonts/arial.ttf", 20.0f);
    auto menu2 = Menu::create(
            MenuItemLabel::create(labelMenu, [](Ref *pSender) {
                Director::getInstance()->popScene(); //退出当前场景
            }), NULL);
//    menu2->setAnchorPoint(Vec2(0.5, 0.5)); 锚点默认为0，0 不能设置锚点
    menu2->setPosition(30, 50);
    addChild(menu2);
    return true;
}

//生成点坐标
void FindPairScene::calPoints() {
    points.clear(); //先清空
    for (int i = 0; i < COLS; ++i) {  //列 6个x坐标
        for (int j = 0; j < ROWS; ++j) { //行 4个y坐标
            points.push_back(Vec2(i * cardWidth, (j + 1) * cardHeight)); //必须j+1  y轴不能为0
        }
    }
}

void FindPairScene::addCards() {
    for (int i = 0; i < fileNames.size(); ++i) {
        addCard(i);
    }

    //继续添加一张相同的卡片
    rightIndex = rand() % fileNames.size();
    addCard(rightIndex);
}

void FindPairScene::addCard(int index) {
    //获取随机位置
    int randIndex = rand() % points.size();
    Vec2 point = points.at(randIndex);

    auto fileName = fileNames.at(index).asString();
    auto card = Sprite::create(fileName);
    card->setAnchorPoint(Vec2(0, 0));
    card->setPosition(point);
    card->setTag(index);
    cards.pushBack(card);
    addChild(card);
    std::vector<Vec2>::iterator it = points.begin() + randIndex;
    points.erase(it);
}
