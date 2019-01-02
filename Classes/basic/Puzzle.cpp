//
// Created by jun zhao on 2018/12/22.
//

#include "Puzzle.h"

Scene *Puzzle::createScene() {
    return Puzzle::create();
}

bool Puzzle::init() {
    if (!Scene::init()) {
        return false;
    }

    visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

//    auto sp = Sprite::create("liangjingru3.jpeg");
//    sp->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
//    Size spSzie = sp->getContentSize();
//    log("spSzie--%f,%f", spSzie.width, spSzie.height);

    //分隔图片
//    auto sp1 = Sprite::create("liangjingru3.jpeg", Rect(0, 0, 100, 100));
//    sp1->setAnchorPoint(Vec2(0, 0));
//    Size sp1Szie = sp1->getContentSize();
//    log("sp1Szie--%f,%f", sp1Szie.width, sp1Szie.height);
//    sp1->setPosition(Vec2(origin.x + visibleSize.width / 2 - sp1Szie.width / 2,
//                          origin.y + visibleSize.height / 2 - sp1Szie.height / 2));
//    addChild(sp1);

//    auto sp2 = Sprite::create("liangjingru3.jpeg", Rect(1920 - 100, 1080 - 100, 100, 100));
//    sp2->setAnchorPoint(Vec2(0, 0));
//    Size sp2Szie = sp2->getContentSize();
//    log("sp2Szie--%f,%f", sp2Szie.width, sp2Szie.height);
//    sp2->setPosition(Vec2(origin.x + visibleSize.width / 2 - sp2Szie.width / 2 + 100,
//                          origin.y + visibleSize.height / 2 - sp2Szie.height));
//    addChild(sp2);

    auto bg = Director::getInstance()->getTextureCache()->addImage("liangjingru3.jpeg");
    auto bgSize = bg->getContentSize();
    if (bgSize.width > bgSize.height) {
        size = bgSize.height;
    } else {
        size = bgSize.width;
    }
    width = size / rows;
    height = size / cols;

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            //puzzle-- i:0,j:0 i:0,j:1  i:0,j:2  i:1,j:0 i:1,j:1 i:1,j:2  i:2,j:0 i:2,j:1 i:2,j:2
//            log("puzzle-- i:%d,j:%d,count:%d", i, j, count);
            //width - 1, height - 1 切片之间留空隙 1px
            auto sp = Sprite::createWithTexture(bg,
                                                Rect(i * width, j * height, width - 1, height - 1));
//            sp->setAnchorPoint(Vec2(0, 0));
            //createWithTexture 从图片的左上角开始剪裁 所以从左上角开始分配位置
//            Vec2 pos(i * width, visibleSize.height - height * (j + 1));
//            sp->setPosition(pos);
//            sp->setTag(count);
            allSp.pushBack(sp);
//            log("puzzle-- i:%f,j:%f", pos.x, pos.y);
//            addChild(sp);
        }
    }

    randomSp();

    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = [&](Touch *touch, Event *event) {
        //是否点击到切片
        Sprite *sp;
        for (auto it = allSp2.begin(); it != allSp2.end(); ++it) {
            sp = *it;
            if (sp->getBoundingBox().containsPoint(touch->getLocation())) {
                sp->setOpacity(110); //设置透明度
                if (touchCount == 0) {
                    swap1 = sp;
                } else {
                    swap2 = sp;
                }
            }
        }
        return true;
    };
    listener->onTouchEnded = [&](Touch *touch, Event *event) {
        touchCount += 1;
        log("touchCount: %d", touchCount);
        if (touchCount == 2) {
            touchCount = 0;
            //执行切片交换
            Vec2 pos1 = swap1->getPosition();
            Vec2 pos2 = swap2->getPosition();
            swap2->setPosition(pos1);
            swap1->setPosition(pos2);
            allSp2.swap(swap1, swap2); //集合里面进行交换

            //交换以后所有的切片去除透明度
            Sprite *sp;
            for (auto it = allSp2.begin(); it != allSp2.end(); ++it) {
                sp = *it;
                sp->setOpacity(255); //恢复透明度
            }
        }
        if (checkFinish()) {
            log("puzzle--finish hahaha");
        }
    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener,
                                                                                          this);


    ////////////返回按钮////////////
    auto labelMenu = Label::createWithTTF("Back", "fonts/arial.ttf", 20.0f);
    auto menu2 = Menu::create(
            MenuItemLabel::create(labelMenu, [](Ref *pSender) {
                Director::getInstance()->popScene(); //退出当前场景
            }), NULL);
    menu2->setPosition(visibleSize.width - 50, 50);
    addChild(menu2);
    return true;
}


void Puzzle::randomSp() {
    Vector<Sprite *> temp;
    temp.pushBack(allSp);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            int index = rand_0_1() * temp.size(); //0---size随机数
            auto sp = temp.at(index);
            Vec2 pos(i * width, visibleSize.height - height * (j + 1));
            sp->setAnchorPoint(Vec2(0, 0));
            sp->setPosition(pos);
            addChild(sp);
            allSp2.pushBack(sp);  //添加乱序切片
            temp.eraseObject(sp); //保证随机不重复 所有要移除sp
        }
    }
}

//集合1与集合2进行比较
bool Puzzle::checkFinish() {
    int count = 0;
    for (int i = 0; i < allSp.size(); ++i) {
        auto sp = allSp.at(i);
        auto sp2 = allSp2.at(i);
        if (sp == sp2) {
            count += 1;
        }
    }
    if (count == allSp.size()) {
        return true;
    }
    return false;
}