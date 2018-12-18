//
// Created by jun zhao on 2018/12/17.
//

#include "LearnUIScene.h"

Scene *LearnUI::createScene() {
    return LearnUI::create();
}

bool LearnUI::init() {
    if (!Scene::init()) {
        return false;
    }
    winSize = Director::getInstance()->getVisibleSize();

    //对话框
//    MessageBox("消息内容", "标题");


    auto label = Label::create();
//    label->setBMFontFilePath()

    //内容输入
    auto tf = TextFieldTTF::textFieldWithPlaceHolder("在这里输入", Size(100, 35),
                                                     TextHAlignment::CENTER,
                                                     "宋体", 20);
    tf->setPosition(winSize.width / 2, winSize.height / 2);
//    addChild(tf);
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = [tf](Touch *touch, Event *event) {
        if (event->getCurrentTarget()->getBoundingBox().containsPoint(touch->getLocation())) {
            tf->attachWithIME(); //开启键盘
        } else {
            tf->detachWithIME(); //关闭键盘
        }
        return false;
    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener,
                                                                                          this);


    //menu typedef std::function<void(Ref*)> ccMenuCallback
    auto menu = Menu::create(
            MenuItemImage::create("start_btn.png", "start_btn.png", [](Ref *pSender) {
                log("game 游戏开始了");
            }), NULL);
    menu->setPosition(winSize.width / 2, winSize.height / 2);
    addChild(menu);

    //TableView 使用扩展库


    return true;
}