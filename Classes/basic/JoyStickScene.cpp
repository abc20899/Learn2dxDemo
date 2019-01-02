#include "JoyStickScene.h"

#include "JoyStick.h"

Scene *JoyStickScene::createScene() {
    auto scene = Scene::create();
    auto layer = JoyStickScene::create();
    scene->addChild(layer);
    return scene;
}

bool JoyStickScene::init() {
    if (!Layer::init()) {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    rocker = JoyStick::create();
    rocker->setPosition(Vec2(0, 0)); //左下角 锚点默认0，0
    addChild(rocker);

    /*加载精灵帧播放图片*/
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("ButterFly.plist", "ButterFly.png");
    __Dictionary *dic = __Dictionary::createWithContentsOfFile("ButterFly.plist");
    __Dictionary *dic2 = dynamic_cast<__Dictionary *>(dic->objectForKey("frames"));
    Sprite *sp = Sprite::createWithSpriteFrameName("fish_001.png"); //获取第一帧 设置位置
    sp->setFlippedX(true); //镜像
    sp->setTag(159);
    sp->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    addChild(sp);

    Vector<SpriteFrame *> allFrame;
    for (int i = 1; i <= dic2->count(); i++) {
        SpriteFrame *sf = SpriteFrameCache::getInstance()->getSpriteFrameByName(
                StringUtils::format("fish_0%02d.png", i));
        allFrame.pushBack(sf);
    }

    Animation *animtaion = Animation::createWithSpriteFrames(allFrame, 0.1);
    Animate *animte = Animate::create(animtaion);
    sp->runAction(RepeatForever::create(animte));

    /*开启检查调度*/
    schedule(CC_CALLBACK_1(JoyStickScene::schedulePos, this), "POS");


    ////////////返回按钮////////////
    auto labelMenu = Label::createWithTTF("Back", "fonts/arial.ttf", 20.0f);
    auto menu2 = Menu::create(
            MenuItemLabel::create(labelMenu, [](Ref *pSender) {
                Director::getInstance()->popScene(); //退出当前场景
            }), NULL);
//    menu2->setAnchorPoint(Vec2(0.5, 0.5)); 锚点默认为0，0 不能设置锚点
    menu2->setPosition(visibleSize.width - 50, 50);
    addChild(menu2);
    return true;
}

/*让我们的精灵按照摇杆的力度移动距离*/
void JoyStickScene::schedulePos(float dt) {
    /*获取摇杆到圆点的位置*/
    auto dis = rocker->getRocker()->getPosition().distance(rocker->getRockerBg()->getPosition());
    dis /= 20.0;
    log("%f", dis);
    auto hero = (Sprite *) getChildByTag(159);
    float angle = rocker->getAngle();

    switch (rocker->getDir()) {
        case RDIRECTION::UP:
            hero->setFlippedY(true);
            hero->setPositionY(hero->getPositionY() + dis);
            break;
        case RDIRECTION::DOWN:
            log("xia");
            hero->setFlippedY(false);
            hero->setPositionY(hero->getPositionY() - dis);
            break;
        case RDIRECTION::LEFT:
            hero->setFlippedX(false);
            hero->setPositionX(hero->getPositionX() - dis);
            break;
        case RDIRECTION::RIGHT:
            hero->setFlippedX(true);
            hero->setPositionX(hero->getPositionX() + dis);
            break;
        case RDIRECTION::L_UP:
            hero->setPosition(hero->getPosition() + Vec2(dis * cos(angle), dis * sin(angle)));
            break;
        case RDIRECTION::R_UP:
            hero->setPosition(hero->getPosition() + Vec2(dis * cos(angle), dis * sin(angle)));
            break;
        case RDIRECTION::L_DOWN:
            hero->setPosition(hero->getPosition() + Vec2(dis * cos(angle), -dis * sin(angle)));
            break;
        case RDIRECTION::R_DOWN:
            hero->setPosition(hero->getPosition() + Vec2(dis * cos(angle), -dis * sin(angle)));
            break;
        default:
            break;
    }
}