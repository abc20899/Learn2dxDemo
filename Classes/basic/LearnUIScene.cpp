//
// Created by jun zhao on 2018/12/17.
//

#include "LearnUIScene.h"
#include <ui/cocosGUI.h>

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
//    auto listener = EventListenerTouchOneByOne::create();
//    listener->onTouchBegan = [tf](Touch *touch, Event *event) {
//        if (event->getCurrentTarget()->getBoundingBox().containsPoint(touch->getLocation())) {
//            tf->attachWithIME(); //开启键盘
//        } else {
//            tf->detachWithIME(); //关闭键盘
//        }
//        return false;
//    };
//    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener,
//    this);


    /**
     * 由于CCMenu的父类为CCLayer，所以锚点为（0,0），且无法设置锚点。CCMenu的默认原点坐标为屏幕正中心
     * （winSize.width/2, winSize.height/2）
     * CCMenuItem相对于CCMenu的偏移量默认为（0,0），且菜单项的锚点默认为（0.5,0.5）
     * */
    //menu typedef std::function<void(Ref*)> ccMenuCallback
    auto menu = Menu::create(
            MenuItemImage::create("start_btn.png", "start_btn.png", [](Ref *pSender) {
                log("game 游戏开始了");
            }), NULL);
    menu->setPosition(winSize.width / 2, winSize.height / 2);
    addChild(menu);

    //TableView 使用扩展库


    //VideoPlayer
    auto vp = cocos2d::experimental::ui::VideoPlayer::create();
    vp->setContentSize(Size(100, 100));
    vp->setPosition(Vec2(winSize.width / 2, winSize.height - 20));
    vp->setFileName("cocos2dx-xna.mp4");
    vp->play();
    addChild(vp);

    //webView
    auto webView = cocos2d::experimental::ui::WebView::create();
    webView->setContentSize(Size(100, 160));
    webView->setPosition(Vec2(60, winSize.height - 20));
    webView->loadURL("https://www.baidu.com");
    addChild(webView);

    //截屏功能
    auto listener2 = EventListenerTouchOneByOne::create();
    //this 作为捕获变量 表示scene 执行addSp  //error: 'this' cannot be implicitly captured in this context
    listener2->onTouchBegan = [this](Touch *touch, Event *event) {
        //const std::function<void(bool, const std::string&)>& afterCaptured, const std::string& filename
        utils::captureScreen([this](bool b, const std::string &filename) {
            if (b) {
                log("capture success %s,filename %s", b ? "true" : "false", filename.c_str());
                addSp(filename);
            } else {
                log("capture screen failed");
            }
        }, "cocos_cap.png");
        return false;
    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener2,
                                                                                          this);

    //sprite frame
    /***
     *  SpriteFrame     ：精灵帧。    它是相对动画而产生的，其实就是一张纹理图片。
        AnimationFrame  ：动画帧。    由精灵帧与间隔帧数组成，是动画Animation中的一帧。
        SpriteFrameCache：精灵帧缓冲。用于存放精灵帧CCSpriteFrame的缓冲池。
        AnimationCache  ：动画缓冲。  用于存放动画CCAnimation的缓冲池。
        delayPerUnit      ：单位帧间隔。连续两个动画帧之间的时间间隔。单位：秒。
        delayUnits        ：间隔帧数。  当前动画帧到下一个动画帧需要等待的单位帧间隔的个数。
        Vector<AnimationFrame*>&
        Animation：用于存储动画相关的信息。其中包含用于动画的所有动画帧信息，单位帧的时间间隔，总帧数，动画重复次数等等信息。
        Animate  ：用于创建动画的Action动作，需要Animation作为创建的参数。

        创建动画动作Animation/Animate的三种方式:
     */
    //1.直接使用图片资源
    auto sprite1 = Sprite::create("bird001.png");
    sprite1->setPosition(Vec2(30, 80));
    addChild(sprite1);
    auto animation1 = Animation::create();
    for (int i = 0; i < 3; ++i) {
        char str[50];
        sprintf(str, "bird00%d.png", i + 1); //文件名从1开始
        log("str--%s", str);
        animation1->addSpriteFrameWithFile(str);
    }
    //设置属性
    animation1->setRestoreOriginalFrame(true); //还原第一帧
    animation1->setDelayPerUnit(2.0 / 14.0);     //单位帧间隔
    animation1->setLoops(-1);                  //-1无限循环
    auto animate1 = Animate::create(animation1);
    sprite1->runAction(animate1);

    //2.使用精灵帧
    auto sprite2 = Sprite::create("bird001.png");
    sprite2->setPosition(Vec2(60, 80));
    addChild(sprite2);
    //将plist批处理的多张图片，添加到精灵帧缓冲池中
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("bird.plist");
    Vector<SpriteFrame *> arrayOfSpriteFrameNames;
    for (int i = 0; i < 3; ++i) {
        char str[50];
        sprintf(str, "bird00%d.png", i + 1); //文件名从1开始
        auto spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(str);
        arrayOfSpriteFrameNames.pushBack(spriteFrame);
    }
    //const Vector<SpriteFrame*>& arrayOfSpriteFrameNames, float delay = 0.0f, unsigned int loops = 1
    auto animation2 = Animation::createWithSpriteFrames(arrayOfSpriteFrameNames, 2.0 / 14.0, -1);
    animation2->setRestoreOriginalFrame(true); //还原第一帧
    auto animate2 = Animate::create(animation2);
    sprite2->runAction(animate2);

    //3.使用动画帧
    auto sprite3 = Sprite::create("bird001.png");
    sprite3->setPosition(Vec2(90, 80));
    addChild(sprite3);
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("bird.plist");
    Vector<AnimationFrame *> arrayOfAnimationFrameNames;
    for (int i = 0; i < 3; ++i) {
        char str[50];
        sprintf(str, "bird00%d.png", i + 1); //文件名从1开始
        auto spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(str);
        //SpriteFrame* spriteFrame, float delayUnits, const ValueMap& userInfo
        auto animationFrame = AnimationFrame::create(spriteFrame, i, ValueMap());
        arrayOfAnimationFrameNames.pushBack(animationFrame);
    }
    //const Vector<AnimationFrame*>& arrayOfAnimationFrameNames, float delayPerUnit, unsigned int loops
    auto animation3 = Animation::create(arrayOfAnimationFrameNames, 0.2f, -1);
    animation3->setRestoreOriginalFrame(true);
    auto animate3 = Animate::create(animation3);
    sprite3->runAction(animate3);



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

void LearnUI::addSp(const std::string &filename) {
    auto sp = Sprite::create(filename);
    sp->setContentSize(Size(480 / 3, 320 / 3));
    sp->setPosition(Vec2(winSize.width - 20, winSize.height - 20));
    this->addChild(sp);
}