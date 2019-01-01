//
// Created by jun zhao on 2019/1/1.
//

#include "GameScene.h"

namespace little {

    Scene *GameScene::createScene() {
        return GameScene::create();
    }

    bool GameScene::init() {
        if (!Scene::init()) {
            return false;
        }

        winSize = Director::getInstance()->getVisibleSize();
        auto origin = Director::getInstance()->getVisibleOrigin();

        auto colorBg = LayerColor::create(Color4B(246, 246, 246, 255));
        addChild(colorBg);

        //添加player
        player = Sprite::create("littlegame/player.jpeg");
        player->setPosition(Vec2(player->getContentSize().width / 2,
                                 winSize.height / 2 + player->getContentSize().height / 2));

        addChild(player);

        //添加触摸监听
        auto listener = EventListenerTouchOneByOne::create();
        listener->onTouchBegan = [this](Touch *touch, Event *event) {
            SimpleAudioEngine::getInstance()->playEffect("littlegame/pew-pew-lei.wav");
            //获取player坐标
            auto playerPos = player->getPosition();
            auto bullet = Sprite::create("littlegame/Projectile.jpeg");
            bullet->setPosition(playerPos);
            bulletes.pushBack(bullet); //添加进集合
            addChild(bullet);

            //获取点击坐标
            auto point = touch->getLocation();
            //用户点击位置与子弹的  横向距离和纵向距离  两个边长
            int offX = point.x - playerPos.x;
            int offY = point.y - playerPos.y;
            if (offX <= 0) {  //如果用户点击不合法
            }
            //计算子弹到达的最终点坐标
            int realX = winSize.width + (bullet->getContentSize().width / 2);  //在屏幕外的x坐标
            float ratio = (float) offY / (float) offX;                      //计算出角度  ∠A的对边比邻边
            int realY = (realX * ratio) + bullet->getPosition().y;          //在屏幕外的y坐标 x*∠A = y
            auto realDest = Vec2(realX, realY);  //创建目标移动的点

            //计算移动的时间
            int offRealX = realX - bullet->getPosition().x;
            int offRealY = realY - bullet->getPosition().y;
            float length = sqrtf((offRealX * offRealX) + (offRealY * offRealY)); //两点之间的距离
            float velocity = 480 / 1; // 480pixels/1sec  每秒480个像素 速度
            float realMoveDuration = length / velocity;  //移动时间 t = s/v

            //移动子弹
            auto movieTo = MoveTo::create(realMoveDuration, realDest);
            auto ratate = RotateTo::create(realMoveDuration * 10, 360.0f);
            auto callback = CallFunc::create(
                    CC_CALLBACK_0(GameScene::movieCallbak, this, bullet)); //移除bullet
            bullet->runAction(Sequence::create(movieTo,
                                               ratate,
                                               callback,
                                               NULL));

            return false;
        };
        Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(
                listener, this);


        SimpleAudioEngine::getInstance()->playBackgroundMusic(
                "littlegame/background-music-aac.wav", true);
        this->scheduleUpdate();
        schedule(schedule_selector(GameScene::addGhost), 1.0f);//一秒添加一个幽灵

        ////////////返回按钮////////////
        auto labelMenu = Label::createWithTTF("Back", "fonts/arial.ttf", 20.0f);
        auto menu2 = Menu::create(
                MenuItemLabel::create(labelMenu, [](Ref *pSender) {
                    SimpleAudioEngine::getInstance()->stopBackgroundMusic(true);
                    Director::getInstance()->popScene(); //退出当前场景
                }), NULL);
        menu2->setPosition(winSize.width - 20, 50);
        addChild(menu2);
        return true;
    }

    void GameScene::addGhost(float dt) {
        auto ghost = Sprite::create("littlegame/Target.jpeg");
        //计算可绘制范围 minY屏幕下面的坐标高度(以左下角为原点)  maxY为屏幕上方的坐标高度
        //只有在minY 和 maxY之间 坐标范围内 才能画完整的精灵
        int minY = ghost->getContentSize().height / 2;
        int maxY = winSize.height - ghost->getContentSize().height / 2;
        // 计算可随机 基数  最高点减去最低点  rangeY可画的y坐标点
        int rangeY = maxY - minY;
        // 随机出的基数*半个身高 = 最后坐标点
        int actualY = (rand() % rangeY) + minY;
        // winSize.width + (target->getContentSize().width/2)  屏幕的宽度+精灵宽度一半  也就是在屏幕外面
        ghost->setPosition(Vec2(winSize.width + (ghost->getContentSize().width / 2), actualY));
        ghost->setTag(1);
        addChild(ghost);
        ghostes.pushBack(ghost);

        // 移动速度 最慢4秒 最快2秒
        int minDuration = (int) 2.0;
        int maxDuration = (int) 4.0;
        int rangeDuration = maxDuration - minDuration; //随机的范围
        int actualDuration = (rand() % rangeDuration) + minDuration;//随机速度
        //创建动作 初始化耗时动作    参数: 移动的时间  坐标点(x,y) 0,y
        auto actionMove = MoveTo::create((float) actualDuration,
                                         Vec2(0 - ghost->getContentSize().width / 2,
                                              actualY));
        //精灵移动完 以后所做的动作  移动完以后 移除精灵
        auto actionMoveDone = CallFunc::create(
                CC_CALLBACK_0(GameScene::movieCallbak, this, ghost));
        //绑定动作
        ghost->runAction(Sequence::create(actionMove,
                                          actionMoveDone, NULL));
    }

    void GameScene::movieCallbak(Node *node) {
        this->removeChild(node);
        if (node->getTag() == 1) {
            ghostes.eraseObject((Sprite *) node);
        } else {
            bulletes.eraseObject((Sprite *) node);
        }
//        Sprite *sp;
//        for (auto it =  it != bulletes.end(); it++) {
//            sp = *it;
//            this->removeChild(sp, true);
//            bulletes.eraseObject(sp, true);
//        }
    }

    void GameScene::checkCollision() {
        for (int i = 0; i < bulletes.size(); i++) {
            for (int y = 0; y < ghostes.size(); y++) {
                auto bullet = bulletes.at(i);
                auto ghost = ghostes.at(y);
                if (ghost->getBoundingBox().containsPoint(bullet->getPosition())) {
                    log("checkCollisioncheckCollision...");
                    this->removeChild(ghost);
                    this->removeChild(bullet);
                    bulletes.erase(i);
                    ghostes.erase(y);
                }
            }
        }
    }

    void GameScene::update(float dt) {
        checkCollision();
    }
}