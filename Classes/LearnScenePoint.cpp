//
// Created by jun zhao on 2018/12/16.
//

#include "LearnScenePoint.h"

Scene *LearnScenePoint::createScene() {
    return LearnScenePoint::create();
}

bool LearnScenePoint::init() {
    // 1. super init first
    if (!Scene::init()) {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto rect = DrawNode::create();
    rect->setTag(1);
    rect->drawRect(Vec2(0, 0), Vec2(100, 100), Color4F(1.0, 0, 0, 1.0));
    rect->setContentSize(Size(100, 100)); //设置size后 设置锚点才会生效
    rect->setAnchorPoint(Vec2(0.5, 0.5));//矩形默认锚点为(0,0) 设置为(0.5,0.5)
    rect->setPosition(visibleSize.width / 2,
                      visibleSize.height / 2); //设置到屏幕中央
    addChild(rect);

    auto dot = DrawNode::create();
    dot->setTag(2);
    dot->drawDot(Vec2(0, 0), 10, Color4F(1.0, 1.0, 1.0, 1.0));
//    dot->setAnchorPoint(Vec2(0,0)); //设置size后 设置锚点才会生效
    dot->setPosition(20, 20);
    rect->addChild(dot); //添加到矩形里面

    //执行定时器
    this->getScheduler()->schedule(schedule_selector(LearnScenePoint::rotation), this, 0, false);
    return true;
}

//实现矩形旋转
void LearnScenePoint::rotation(float delay) {
    log("dddddd%f,delay");
    //获取正方形节点 并执行旋转
    auto rect = this->getChildByTag(1);
    rect->setRotation(rect->getRotation() + 1);  //旋转点跟锚点有关系 0.5,0.5 绕中心旋转

    auto dot = rect->getChildByTag(2); //圆点添加到矩形上，由矩形node获取
    Vec2 position = dot->getPosition();
    log("%f,%f", position.x, position.y); //圆点的本地坐标 (20，20) 不变
    Vec2 worldPos = dot->convertToWorldSpace(Vec2(0,0)); //圆点的世界坐标
    log("%f,%f", worldPos.x, worldPos.y);  //随着矩形旋转 会变化

}