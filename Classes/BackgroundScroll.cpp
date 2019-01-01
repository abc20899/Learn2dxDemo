//
// Created by jun zhao on 2018/12/22.
//

#include "BackgroundScroll.h"


Scene *BackgroundScroll::createScene() {
    return BackgroundScroll::create();
}

bool BackgroundScroll::init() {
    if (!Scene::init()) {
        return false;
    }

    auto winSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

    bg1 = Sprite::create("bg_scroll.jpg");
    bg1->setContentSize(Size(winSize.width, winSize.height));
    bg1->setPosition(Vec2(origin.x + winSize.width / 2, origin.y + winSize.height / 2));
    addChild(bg1);

    bg2 = Sprite::create("bg_scroll.jpg");
    bg2->setContentSize(Size(winSize.width, winSize.height));
    bg2->setPosition(
            Vec2(origin.x + winSize.width / 2, origin.y + winSize.height + winSize.height / 2));
    addChild(bg2);

    //滚动背景
    scheduleUpdate();

    ////////////返回按钮////////////
    auto labelMenu = Label::createWithTTF("Back", "fonts/arial.ttf", 20.0f);
    auto menu2 = Menu::create(
            MenuItemLabel::create(labelMenu, [](Ref *pSender) {
                Director::getInstance()->popScene(); //退出当前场景
                JNITools::changeActivityOrientation(1); //横屏
            }), NULL);
    menu2->setPosition(winSize.width - 20, 50);
    addChild(menu2);
    return true;
}

void BackgroundScroll::update(float dt) {
    float bg1Y = bg1->getPositionY();
    float bg2Y = bg2->getPositionY();

    bg1Y -= speedY;  //向下滚动 239 238 ... 0   等于0时 bg2Y 为屏幕的高度(480)
    bg2Y -= speedY;
    log("bg1Y-- %f,bg2-- %f", bg1Y, bg2Y);

    /* 当第1个地图完全离开屏幕时，第2个地图刚好完全出现在屏幕上，这时候就让第1个地图紧贴在
     第2个地图后面 */
    Size bgSize = bg1->getContentSize();
    if (bg1Y <= -bgSize.height / 2) { //第一张图片的y 超出屏幕高的一半 -height/2
        bg1Y = bgSize.height + bgSize.height / 2; // 锚点为中心点，屏幕高度+图片高度一半
    }
    /* 同理，当第2个地图完全离开屏幕时，第1个地图刚好完全出现在屏幕上，这时候就让第2
     个地图紧贴在第1个地图后面 */
    if (bg2Y <= -bgSize.height / 2) {
        bg2Y = bgSize.height + bgSize.height / 2;
    }

    bg1->setPositionY(bg1Y); //y坐标更新
    bg2->setPositionY(bg2Y);
}