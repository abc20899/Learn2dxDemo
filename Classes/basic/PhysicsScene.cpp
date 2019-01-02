//
// Created by jun zhao on 2019/1/1.
//

#include "PhysicsScene.h"

Scene *PhysicsScene::createScene() {
    auto scene = Scene::createWithPhysics();
    //开启调试
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    auto layer = PhysicsScene::create();
    scene->addChild(layer);
    return scene;
}

bool PhysicsScene::init() {
    if (!Layer::init()) {
        return false;
    }
    winSize = Director::getInstance()->getVisibleSize();

    addBall(winSize.width / 2, winSize.height / 2);
    addEdge();

    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = [this](Touch *touch, Event *event) {
//        addBall(touch->getLocation().x, touch->getLocation().y);

        addRect(touch->getLocation().x, touch->getLocation().y);
        return false;
    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener,
                                                                                          this);

    //物体碰撞监听
    auto listenerCon = EventListenerPhysicsContact::create();
    listenerCon->onContactBegin = [](PhysicsContact &contact) {
        switch (contact.getShapeA()->getBody()->getContactTestBitmask() |
                contact.getShapeB()->getBody()->getContactTestBitmask()) {
            case RED_MASK | GREEN_MASK:
                log("red green");
                break;
            case RED_MASK | BLUE_MASK:
                log("red blue");
                break;
            case RED_MASK | RED_MASK:
                log("red red");
                break;
            case RED_MASK | EDGE_MASK:
                log("red edge");
                break;
            case GREEN_MASK | EDGE_MASK:
                log("green edge");
                break;
            case BLUE_MASK | EDGE_MASK:
                log("blue edge");
                break;
            default:
                break;
        }
        return true;
    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(
            listenerCon,
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

void PhysicsScene::addEdge() {
    auto body = PhysicsBody::createEdgeBox(winSize, PHYSICSBODY_MATERIAL_DEFAULT, 1);
    auto edgeShape = Node::create();
    edgeShape->setPhysicsBody(body);
    edgeShape->setPosition(winSize.width / 2, winSize.height / 2 + 20);
    edgeShape->getPhysicsBody()->setContactTestBitmask(EDGE_MASK);
    addChild(edgeShape);
}

void PhysicsScene::addBall(float x, float y) {
    auto sp = Sprite::create("ball_phy.png");
    sp->setPhysicsBody(PhysicsBody::createBox(sp->getContentSize()));
    sp->setPosition(x, y);
    addChild(sp);
}

void PhysicsScene::addRect(float x, float y) {
    auto sp = Sprite::create();
    sp->setTextureRect(Rect(0, 0, 50, 50));
    sp->setPhysicsBody(PhysicsBody::createBox(sp->getContentSize()));
    sp->setPosition(x, y);
    switch (rand() % 3) {
        case 0:
            sp->setColor(Color3B(255, 0, 0));
            sp->getPhysicsBody()->setContactTestBitmask(RED_MASK);
            break;
        case 1:
            sp->setColor(Color3B(0, 255, 0));
            sp->getPhysicsBody()->setContactTestBitmask(GREEN_MASK);
            break;
        case 2:
            sp->setColor(Color3B(0, 0, 255));
            sp->getPhysicsBody()->setContactTestBitmask(BLUE_MASK);
            break;
        default:
            break;
    }
    addChild(sp);
}