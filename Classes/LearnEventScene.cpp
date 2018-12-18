//
// Created by jun zhao on 2018/12/17.
//

#include "LearnEventScene.h"

Scene *LearnEvent::createScene() {
    return LearnEvent::create();
}

bool LearnEvent::init() {
    if (!Scene::init()) {
        return false;
    }
    winSize = Director::getInstance()->getVisibleSize();

    auto label = Label::create();
    label->setString("hello world");
    label->setPosition(winSize.width / 2, winSize.height / 2);
    addChild(label);

    /////////////////////////////////////事件回调机制///////////////////////////////////////////
    //触摸监听 EventListenerTouchOneByOne 单点触摸
    auto touchListener = EventListenerTouchOneByOne::create();
//    touchListener->onTouchBegan = CC_CALLBACK_2(LearnEvent::touchBeganHandler, this);//普通监听事件
    touchListener->onTouchBegan = [label](Touch *touch, Event *event) { //lambda 表达式
        log("touch begin %f,%f", touch->getLocation().x, touch->getLocation().y);
        Vec2 touchPos(touch->getLocation().x, touch->getLocation().y); //触摸点
        if (label->getBoundingBox().containsPoint(touchPos)) {
            log("touch 点击了label...");
        }
        //第二种判断label是否被点击
//        if (event->getCurrentTarget()->getBoundingBox().containsPoint(touch->getLocation())) {
//            log("touch 点击了label...");
//        }
        return true;  //返回true 继续执行 move end
    };
    touchListener->onTouchMoved = [label](Touch *touch, Event *event) {
        //label跟随手指移动
        log("touch move %f,%f", touch->getLocation().x, touch->getLocation().y);
        label->setPosition(touch->getLocation().x, touch->getLocation().y);
        return false;
    };
    //添加监听器
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(
            touchListener, label);


    /////////////////////////////////////自定义事件回调机制///////////////////////////////////////////
    EventCustom e("my event");
    e.setUserData((void *) "hello junechiu"); //void* 任意类型
    auto customEvent = EventListenerCustom::create("my event", [](EventCustom *e) {
        log("event excuted %s", (char *) e->getUserData());
    });
    //添加事件监听 优先级
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(customEvent,
                                                                                     1);
    Director::getInstance()->getEventDispatcher()->dispatchEvent(&e);//分发事件


    /////////////////////////////////////多点触摸///////////////////////////////////////////
    auto mutilTouchListener = EventListenerTouchAllAtOnce::create();
    mutilTouchListener->onTouchesMoved = [](const std::vector<Touch *> &touches, Event *event) {
        log("touches size %u", touches.size());
        Touch *t;
        for (auto it = touches.begin(); it != touches.end(); it++) {
            t = *it;
            log("touches x=%f,y=%f", t->getLocation().x, t->getLocation().y);
        }
    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(
            mutilTouchListener, this);


    /////////////////////////////////////加速度传感器///////////////////////////////////////////
    auto accListener = EventListenerAcceleration::create([](Acceleration *a, Event *event) {
        log("acc x=%f,y=%f,z=%f", a->x, a->y, a->z);
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(
            accListener, this);
    //开启设备加速度
    Device::setAccelerometerEnabled(true);


    /////////////////////////////////////按键事件监听///////////////////////////////////////////
    auto keyListener = EventListenerKeyboard::create();
    keyListener->onKeyPressed = [](EventKeyboard::KeyCode code, Event *event) {
        log("code %d", code);
        switch (code) {
            case EventKeyboard::KeyCode::KEY_BACK:
                log("code back");
                break;
            default:
                break;
        }
    };
    keyListener->onKeyReleased = [](EventKeyboard::KeyCode code, Event *event) {
        switch (code) {
            case EventKeyboard::KeyCode::KEY_BACK:
                log("code release back");
                Director::getInstance()->end(); //退出程序
                break;
            default:
                break;
        }
    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(
            keyListener, this);


    return true;
}

//触摸监听回调函数
bool LearnEvent::touchBeganHandler(Touch *touch, Event *event) {
    log("touch begin %f,%f", touch->getLocation().x, touch->getLocation().y);
    return false;
}
