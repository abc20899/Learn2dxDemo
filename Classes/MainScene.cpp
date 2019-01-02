//
// Created by jun zhao on 2018/12/18.
//

#include "MainScene.h"

#define TABEL_LABEL_TAG 1024

Scene *MainScene::createScene() {
    return MainScene::create();
}

bool MainScene::init() {
    if (!Scene::init()) {
        return false;
    }
    visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();
//    for (int i = 0; i < 40; ++i) {
//        _childTestNames.push_back(__String::createWithFormat("string_%d", i)->getCString());
//    }

    _childTestNames.push_back("BasicScene");
    _childTestNames.push_back("BallSpriteScene");
    _childTestNames.push_back("LearnEventScene");
    _childTestNames.push_back("LearnSceneMath");
    _childTestNames.push_back("LearnUIScene");
    _childTestNames.push_back("LearnScenePoint");
    _childTestNames.push_back("JoyStickScene");
    _childTestNames.push_back("RollBallScene");
    _childTestNames.push_back("game2048");
    _childTestNames.push_back("gameSnake");
    _childTestNames.push_back("BackgroundScroll");
    _childTestNames.push_back("Puzzle");
    _childTestNames.push_back("ParticleScene");
    _childTestNames.push_back("FindPairScene");
    _childTestNames.push_back("Sprite3DScene");
    _childTestNames.push_back("LittleGame");
    _childTestNames.push_back("Box2dScene");
    _childTestNames.push_back("PhysicsScene");
    _childTestNames.push_back("blackwhiteblock");

    //添加TableView
    auto tableView = TableView::create(this, Size(400, visibleSize.height));
    tableView->setDirection(ScrollView::Direction::VERTICAL); //竖向滑动
    Size tableSize = tableView->getContentSize();
    tableView->setPosition(Vec2(visibleSize.width / 2 + origin.x - tableSize.width / 2,
                                origin.y));
    tableView->setDelegate(this); //设置代理对象
    tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN); // 填充顺序
    this->addChild(tableView); //添加tableview到当前node
    tableView->reloadData(); //加载tableview


    ////////////////////添加返回键监听////////////////////////
    auto backKeyListener = EventListenerKeyboard::create();
    backKeyListener->onKeyReleased = [](EventKeyboard::KeyCode code, Event *event) {
        if (code == EventKeyboard::KeyCode::KEY_BACK) {
//            auto scene = Director::getInstance()->getRunningScene();
//            typeid(MainScene) == typeid(scene)
            Director::getInstance()->end();
//                Director::getInstance()->popScene();
        }
    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(
            backKeyListener, this);

    return true;
}

// 当cell被点击时调用该方法 参数为当前的tableview对象与被点击的cell对象
void MainScene::tableCellTouched(TableView *table, TableViewCell *cell) {
    CCLOG("cell touched at index: %i", cell->getIdx());
    auto index = cell->getIdx();
    switch (index) {
        case 0:
            Director::getInstance()->pushScene(HelloWorld::createScene());
            break;
        case 1:
            Director::getInstance()->pushScene(BallSprite::createScene());
            break;
        case 2:
            Director::getInstance()->pushScene(LearnEvent::createScene());
            break;
        case 3:
            Director::getInstance()->pushScene(LearnSceneMath::createScene());
            break;
        case 4:
            Director::getInstance()->pushScene(LearnUI::createScene());
            break;
        case 5:
            Director::getInstance()->pushScene(LearnScenePoint::createScene());
            break;
        case 6:
            Director::getInstance()->pushScene(JoyStickScene::createScene());
            break;
        case 7:
            Director::getInstance()->pushScene(RollBallScene::createScene());
            break;
        case 8:
            JNITools::changeActivityOrientation(2); //竖屏
            //横竖屏切换时延时1秒可以正确获取宽高
            scheduleOnce(schedule_selector(MainScene::to2048), 0.5f);
            break;
        case 9:
            Director::getInstance()->pushScene(snake::MainScene::createScene());
            break;
        case 10:
            JNITools::changeActivityOrientation(2); //竖屏
            scheduleOnce(schedule_selector(MainScene::toScrollbg), 0.5f);
            break;
        case 11:
            Director::getInstance()->pushScene(Puzzle::createScene());
            break;
        case 12:
            Director::getInstance()->pushScene(ParticleScene::createScene());
            break;
        case 13:
            Director::getInstance()->pushScene(FindPairScene::createScene());
            break;
        case 14:
            Director::getInstance()->pushScene(Sprite3DScene::createScene());
            break;
        case 15:
            Director::getInstance()->pushScene(little::GameScene::createScene());
            break;
        case 16:
            Director::getInstance()->pushScene(Box2dScene::createScene());
            break;
        case 17:
            Director::getInstance()->pushScene(PhysicsScene::createScene());
            break;
        case 18:
            JNITools::changeActivityOrientation(2); //竖屏
            scheduleOnce(schedule_selector(MainScene::toBlackWhite), 0.5f);
            break;
        default:
            break;
    }
}

//设置编号为 idx 的cell的大小  此处都为100*100
Size MainScene::tableCellSizeForIndex(TableView *table, ssize_t idx) {
    return Size(400, 30);
}

//由于tableview是动态获取数据的，该方法在初始化时会被调用一次，之后在每个隐藏的cell显示出来的时候都会调用
TableViewCell *MainScene::tableCellAtIndex(TableView *table, ssize_t idx) {
//    auto string = __String::createWithFormat("%d", idx);
//    // 在重用队列中获取一个cell 然后判断cell是否为空 不为空则创建一个新的
//    auto cell = table->dequeueCell();
//    if (!cell) {
//        cell = TableViewCell::create(); //创建一个新的cell
////        cell->addChild(LayerColor::create(Color4B::ORANGE)); //
//        auto sprite = Sprite::create("Icon.png"); //创建一个图片精灵
//        sprite->setAnchorPoint(Vec2::ZERO); //设置精灵锚点为左下角
//        sprite->setPosition(Vec2(0, 0)); //设置精灵位置 相当于在cell中的相对位置
//        cell->addChild(sprite); //将精灵加入到cell中
//
//        auto label = Label::createWithSystemFont(string->getCString(), "Helvetica", 20.0); //创建一个标签
//        label->setPosition(Vec2::ZERO); //设置标签相对cell的位置
//        label->setAnchorPoint(Vec2::ZERO); //设置标签锚点为左下角
//        label->setTag(123); //为标签做一个标记,以便于在cell在重用队列中被取出来时，能够获取的该label并重置label信息
//        cell->addChild(label); //将标签加入到cell中
//    } else {
//        // 如果cell不为空,则根据tag获取到之前cell中存放的元素,并将元素信息重置
//        //获取当前cell中的label
//        auto label = (Label *) cell->getChildByTag(123);
//        //重置label的相关信息
//        label->setString(string->getCString());
//    }

    auto cell = table->dequeueCell();
    if (!cell) {
        cell = TableViewCell::create();
        auto label = Label::createWithTTF(_childTestNames[idx], "fonts/arial.ttf", 20.0f);
        label->setTag(TABEL_LABEL_TAG);
        label->setAnchorPoint(Vec2(0.5, 0.5));
        label->setPosition(200, 15);
        cell->addChild(label);
    } else {
        auto label = (Label *) cell->getChildByTag(TABEL_LABEL_TAG);
        label->setString(_childTestNames[idx]);
    }

    return cell;
}

//设置cell的个数 即一个tableview中包含了20个cell
ssize_t MainScene::numberOfCellsInTableView(TableView *table) {
    return _childTestNames.size();
}

void MainScene::to2048(float dt) {
//    Director::getInstance()->pushScene(
//            TransitionFadeDown::create(0.5f, game2048::HelloWorld::createScene()));
    Director::getInstance()->pushScene(
            TransitionFadeDown::create(0.5f, game2048::MainScene::createScene()));
}

void MainScene::toScrollbg(float dt) {
    Director::getInstance()->pushScene(
            TransitionFadeDown::create(0.5, BackgroundScroll::createScene()));
}

void MainScene::toBlackWhite(float dt) {
    Director::getInstance()->pushScene(
            TransitionFadeDown::create(0.5, blackwhite::GameScene::createScene()));
}


















