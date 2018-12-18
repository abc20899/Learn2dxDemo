//
// Created by jun zhao on 2018/12/16.
//

#include "LearnSceneMath.h"

Scene *LearnSceneMath::createScene() {
    return LearnSceneMath::create();
}

bool LearnSceneMath::init() {
    // 1. super init first
    if (!Scene::init()) {
        return false;
    }

    visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto dot = DrawNode::create();
    dot->setTag(2);
    dot->drawDot(Vec2(0, 0), 10, Color4F(1.0, 1.0, 1.0, 1.0));
//    dot->setAnchorPoint(Vec2(0,0)); //设置size后 设置锚点才会生效
    this->addChild(dot); //添加到scene节点


    //小球运动轨迹
    direction = Vec2(random(-1, 1), random(-1, 1));
    this->getScheduler()->schedule(schedule_selector(LearnSceneMath::dotRun), this, 0,
                                   false);

    //lambda表达式 三角函数测试
    //    dot->setPosition(visibleSize.width / 2, visibleSize.height / 2);
    auto &tmp = visibleSize;//lambda捕获中要使用visibleSize成员的本地引用
    schedule([dot, this, &tmp, origin](float f) {
        //2、写这里代码之前，我们先在头文件中，创建一个成员变量float angle，用来记录角度
        //3、然后我们可以使用这个成员变量，因为需要变换角度或者位置，所以就用set...,这里先变换Y坐标的位置
        //4、初始化angle写到前面
        //5、为了能够发生变化，所以需要：
//        angle += 0.1;
//        dot->setPositionY(sin(angle) * 100 + origin.y +
//                          visibleSize.height / 2);//这里的sin里面的参数取值范围是[0,1];为了变化更明显，所以×100倍
//        dot->setPositionX(sin(angle) * 100 + origin.x + visibleSize.width / 2);

        //圆周运动
//        dot -> setPositionY(sin(angle)*100 + origin.y + visibleSize.height/2);//这里的sin里面的参数取值范围是[0,1];为了变化更明显，所以×100倍
//        dot -> setPositionX(cos(angle)*100 + origin.x + visibleSize.width/2);

        //椭圆运动
//        dot -> setPositionY(sin(angle)*100 + origin.y + visibleSize.height/2);//这里的sin里面的参数取值范围是[0,1];为了变化更明显，所以×100倍
//        dot -> setPositionX(cos(angle)*150 + origin.x + visibleSize.width/2);
    }, "dot");



    //基础数据类型 Value type int string float double map vector
    Value intVar(22);
    Value strVar("hehe");
    log("%d %s", intVar.asInt(), strVar.asString().c_str());
    log("%d", strVar.getType() == Value::Type::STRING); //Type enum类型

//    Vector<int> array;
//    for (int i = 0; i < 10; ++i) {
//        array.pushBack(i);
//    }
//    for (auto it = array.begin(); it != array.end(); it++) {
//        log("%d", it);
//    }

    Map<std::string, __String *> map;
    map.insert("w", __String::create("world"));
    map.insert("name", __String::create("junechiu"));
    log("name %s", map.at("name")->getCString());
    return true;
}

//小球运动 向量运动
void LearnSceneMath::dotRun(float delay) {
    auto dot = this->getChildByTag(2);
    Vec2 pos = dot->getPosition();
    if (pos.x < 0 || pos.x > visibleSize.width) {
        direction.x = direction.x * -1; //设置相反方向
    }
    if (pos.y < 0 || pos.y > visibleSize.height) {
        direction.y = direction.y * -1;//设置相反方向
    }
    //更新小球位置
    dot->setPosition(pos.x + direction.x * 10, pos.y + direction.y * 10);
}