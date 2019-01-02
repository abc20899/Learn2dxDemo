//
// Created by jun zhao on 2019/1/1.
//

#include "Box2dScene.h"

Scene *Box2dScene::createScene() {
    return Box2dScene::create();
}

bool Box2dScene::init() {
    if (!Scene::init()) {
        return false;
    }

    world = new b2World(b2Vec2(0, -10)); //参数 重力加速度-10  y轴
    world->SetContactListener(this); //设置物体碰撞监听

    addRect(3, 5, b2_dynamicBody);
//    addRect(6, 5, b2_kinematicBody); //漂浮物体
    addGround();
    scheduleUpdate();


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

void Box2dScene::addRect(float x, float y, b2BodyType type) {
    //配置box2d  创建一个动态物体
    b2BodyDef def;
    def.position = b2Vec2(x, y);
    def.linearVelocity = b2Vec2(0, 6); //水平速度
    def.type = type; //类型： 动态受重力影响、静态、漂浮不受重力影响
    b2Body *body = world->CreateBody(&def);

    b2PolygonShape boxShape;
    boxShape.SetAsBox(0.5, 0.5); //半宽1/2  半高   1米*1米的箱子

    b2FixtureDef fixtureDef;
    fixtureDef.density = 1; //密度
    fixtureDef.friction = 0.3; //摩擦系数
    fixtureDef.shape = &boxShape;
    body->CreateFixture(&fixtureDef);

    //配置cocos shape
    auto s = Sprite::create();
    s->setTextureRect(Rect(0, 0, 0.5 * 2 * RATIO, 0.5 * 2 * RATIO)); //1米 * 1米
    addChild(s);

    //box2d 单位米 最多10米
//    s->setPosition(Vec2(def.position.x * RATIO, def.position.y * RATIO));
    //关联 精灵
    body->SetUserData(s);
}

void Box2dScene::addGround() {
    //配置box2d  创建一个静态物体
    b2BodyDef def;
    def.position = b2Vec2(240 / RATIO, 0);
    def.type = b2_staticBody; //类型： 动态、静态、漂浮
    groundBody = world->CreateBody(&def);

    b2PolygonShape groundShape;
    groundShape.SetAsBox(240 / RATIO, 0.5); //半宽480/2  半高   1米高

    //与其他物体产生作用
    b2FixtureDef fixtureDef;
    fixtureDef.density = 1; //密度
    fixtureDef.friction = 0.3; //摩擦系数
    fixtureDef.shape = &groundShape;
    groundBody->CreateFixture(&fixtureDef);
}

void Box2dScene::BeginContact(b2Contact *contact) {
    if (contact->GetFixtureA()->GetBody() == groundBody ||
        contact->GetFixtureB()->GetBody() == groundBody) {
        log("物体落在地上了");
    }
}

void Box2dScene::update(float dt) {
//    float32 timeStep 时间差,int32 velocityIterations速度迭代, int32 positionIterations位置迭代
    //模拟物理世界
    world->Step(dt, 8, 3);

    Sprite *sp;
    //迭代所有body
    for (b2Body *b = world->GetBodyList(); b; b = b->GetNext()) {
//        if (b->GetType() == b2_dynamicBody) {
//            log("%f", b->GetPosition().y); //
        if (b->GetUserData()) {
            sp = (Sprite *) b->GetUserData();
            //保持精灵运动
            sp->setPosition(Vec2(b->GetPosition().x * RATIO, b->GetPosition().y * RATIO));
        }
//        }
    }
}