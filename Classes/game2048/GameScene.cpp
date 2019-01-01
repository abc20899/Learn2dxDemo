//
// Created by jun zhao on 2018/12/19.
/**
 * 游戏网格原理很简单，
就是两个LayerColor层的堆叠，
先在原来游戏界面添加一个大的LayerColor层，
然后在这个LayerColor层，添加16个小LayerColor层。
 * */

#include "GameScene.h"

namespace game2048 {

    Scene *GameScene::createScene() {
        return GameScene::create();
    }

    bool GameScene::init() {
        if (!Scene::init()) {
            return false;
        }

        winSize = Director::getInstance()->getVisibleSize();
        Vec2 origin = Director::getInstance()->getVisibleOrigin();
        log("winSize %f,%f", winSize.width, winSize.height); //竖屏 width: 270  height: 480

        // 分数
        score = 0;
        TTFConfig config("fonts/HelloKitty.ttf", 32);
        auto labelScore = Label::createWithTTF(config, "Score  :  0  ");
        labelScore->setPosition(
                Vec2(winSize.width / 2, winSize.height - labelScore->getContentSize().height));
        this->addChild(labelScore);
        labelScore->setTag(105);

        //背景色、宽、高     两边的分界线也要算上 GAME_COLS + 1
        colorBlack = LayerColor::create(Color4B(170, 170, 170, 255),
                                        GAME_TILED_WIDTH * GAME_COLS +
                                        GAME_TILED_BOARD_WIDTH * (GAME_COLS + 1),
                                        GAME_TILED_HEIGHT * GAME_ROWS +
                                        GAME_TILED_BOARD_WIDTH * (GAME_ROWS + 1));
        log("colorBlack %f,%f", colorBlack->getContentSize().width,
            colorBlack->getContentSize().height);
        //锚点 0,0
        auto centerP = Vec2(winSize.width / 2 + origin.x - colorBlack->getContentSize().width / 2,
                            winSize.height / 2 + origin.y -
                            colorBlack->getContentSize().height / 2);
        colorBlack->setPosition(centerP);
        log("colorBlack %f,%f", centerP.x,
            centerP.y); //winSize.width / 2 + origin.x = 160,,winSize.height / 2 + origin.y=240
        addChild(colorBlack);


        // 初始化  逻辑网格数组
        for (int i = 0; i < GAME_ROWS; ++i) {
            for (int j = 0; j < GAME_COLS; ++j) {
                map[i][j] = 0;
            }
        }
        // 初始化每一个网格,锚点0,0左下角  从下往上一行一行画
        // 第1行 0=(2,2)  1=(64*1+2*2,2)  3=(64*2+2*3,2) 4=(64*3+2*4,2)
        // 第2行 0=(2,64+2*2)  1=(64*1+2*2,64+2*2)  3=(64*2+2*3,64+2*2) 4=(64*3+2*4,64+2*2)
        for (int row = 0; row < GAME_ROWS; ++row) {
            for (int col = 0; col < GAME_COLS; ++col) {
                auto layerTiled = LayerColor::create(Color4B(70, 70, 70, 80), GAME_TILED_WIDTH,
                                                     GAME_TILED_HEIGHT);
                layerTiled->setPosition(
                        Vec2(GAME_TILED_WIDTH * col + GAME_TILED_BOARD_WIDTH * (col + 1),
                             GAME_TILED_HEIGHT * row + GAME_TILED_BOARD_WIDTH * (row + 1)));
                colorBlack->addChild(layerTiled);
            }
        }


        ////////////返回按钮////////////
        auto labelMenu = Label::createWithTTF("Back", "fonts/arial.ttf", 20.0f);
        auto menu = Menu::create(
                MenuItemLabel::create(labelMenu, [](Ref *pSender) {
                    //返回到菜单页
                    auto scene = game2048::MainScene::createScene();
                    Director::getInstance()->replaceScene(TransitionFadeDown::create(0.5f, scene));
                }), NULL);
        menu->setPosition(winSize.width - 20, 20);
        addChild(menu);

        //产生一个随机数字块
        newNumberTiled();

        auto listener = EventListenerTouchOneByOne::create();
        //&引用当前对象 this
        listener->onTouchBegan = [&](Touch *touch, Event *event) {
            //记录触摸点位置
            m_x = touch->getLocation().x;
            m_y = touch->getLocation().y;
            m_startMove = true;
            return true;
        };
        //&引用当前对象 this
        listener->onTouchMoved = [&](Touch *touch, Event *event) {
            int x = touch->getLocation().x;
            int y = touch->getLocation().y;
            int distanceX = abs(m_x - x); //x轴移动距离
            int distanceY = abs(m_y - y);//y轴移动距离
            //x轴或者y轴移动距离大于10像素作为一次移动
            if (m_startMove && (distanceX > 10 || distanceY > 10)) {
                m_startMove = false;
                MOVE_DIR dir; //判断移动方向
                if (distanceX > distanceY) { //x轴移动
                    //判断左右
                    if (x > m_x) {
                        dir = MOVE_DIR::RIGHT;
                    } else {
                        dir = MOVE_DIR::LEFT;
                    }
                } else {
                    //判断上下
                    if (y > m_y) {
                        dir = MOVE_DIR::UP;
                    } else {
                        dir = MOVE_DIR::DOWN;
                    }
                }
                moveAllTiled(dir);
            }
        };
        Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(
                listener, this);

        return true;
    };

    void GameScene::newNumberTiled() {
        // 创建一个 数字块的实例
        auto tiled = NumberTiled::create();
        //首先，获取有多少空位置
        int freeCount = 16 - allTiled.size();
        log("2048-- freeCount %d", freeCount);
        //随机产生一个数，小于空位置总数
        int num = 0;
        if (freeCount > 0) { //freeCount必须大于0
            num = rand() % freeCount; //产生一个随机数字 小于freeCount
        }
        log("2048-- num %d", num);
        int row = 0, col = 0, count = 0; //行、列、标记
        bool find = false; //

        /**
         * 从第一个位置到最后一个位置遍历，遇到空位置，count+1，若大于产生的随机数，就在该位置放置数字块。
         * */
        for (; row < GAME_ROWS; ++row) {
            for (col = 0; col < GAME_COLS; ++col) {
                if (map[row][col] == 0) {
                    // 记录空白区域的数量
                    ++count;
                    log("2048-- num--:%d,count--:%d", num, count);
                    if (count >= num) {
                        find = true;
                        break;
                    }
                }
            }
            if (find) {
                break;
            }
        }

        // 注意在colorBack中添加tiled
        colorBlack->addChild(tiled);
        tiled->moveTo(row, col);
        allTiled.pushBack(tiled);
        map[row][col] = allTiled.getIndex(tiled) + 1;
    }

    void GameScene::moveAllTiled(MOVE_DIR dir) {
        // 判断 并 移动所有块  消除
        judgeMove();

        sound_clear = false;
        log("2048-- %d,%d,%d,%d", (int) isMoveLeft, (int) isMoveRight, (int) isMoveUp,
            (int) isMoveUp);
        // 如果上下左右都不能移动，则游戏结束~
        if (!isMoveLeft && !isMoveRight && !isMoveUp && !isMoveUp) {
            auto scene = GameOver::create();
            Director::getInstance()->replaceScene(TransitionFadeDown::create(1.5f, scene));
        }

        // 根据具体方向进行，相应方向的移动
        switch (dir) {
            case MOVE_DIR::UP:
                moveUp();
                break;
            case MOVE_DIR::DOWN:
                moveDown();
                break;
            case MOVE_DIR::LEFT:
                moveLeft();
                break;
            case MOVE_DIR::RIGHT:
                moveRight();
                break;
            default:
                break;
        }
        if (sound_clear) {
            SimpleAudioEngine::getInstance()->playEffect("2048/move.wav");
        } else {
            SimpleAudioEngine::getInstance()->playEffect("2048/move1.wav");
        }
        auto labelScore = (Label *) this->getChildByTag(105);
        labelScore->setString(StringUtils::format(" Score : %d  ", score));

        // 移动完成，随机产生新块
        newNumberTiled();
    }

    /**
     * 从最下面一行最左面到 上面倒数第二行最右面，挨个遍历，每个都要和自己上面一行相应列的数字块进行比较，
        ——如果本行的map值为0，则不管继续
        ——如果本行map值不为0，则从本行相应列一直遍历到倒数第二行的相应列
        ————如果上面那一行map值为0，则将本行与上面那一行互换（其实本行置0，上面那一行换成本行）
        ————否则，因为两行都不为0，判断两行数值是否相等
        ————————若相等，则上面那一行的数值翻倍，本行数字块移除，并对map内其他相应编号进行改变
        ————————若不等，则break
        逻辑块由map和Vector共同处理控制，
        map存储的是编号，就是这个块是本图内第几个产生的块，最先产生的块，map值为1，第二个为2，等等，
        而Vector是存储这个数字块的类，包括这个数字块的位置，和数字块数字的值。
        用这两个控制而不是仅仅单用Vector好处就是，我们不需要遇到判断，就要去Vector找，
        而是先通过map可以判断当前位置有没有数字块，
        而且在随机生成那里，也方便很多，程序效率会得到提高。
     * */
    void GameScene::moveUp() {
        // 向上移动所有的块
        for (int col = 0; col < GAME_COLS; ++col) {
            for (int row = GAME_ROWS - 1; row >= 0; --row) {
                if (map[row][col] > 0) {
                    for (int row1 = row; row1 < GAME_ROWS - 1; ++row1) {
                        // 上方是空的  才会移动
                        if (map[row1 + 1][col] == 0) { //如果上方格子编号为0
                            map[row1 + 1][col] = map[row1][col]; //将当前格子编号赋值给其上方的格子
                            map[row1][col] = 0; //将当前格子编号设置为0
                            //获取当前格子并进行移动到其上方的位置
                            allTiled.at(map[row1 + 1][col] - 1)->moveTo(row1 + 1, col);
                        } else {
                            // 获取上面那格子的数字  判断是否可以消除
                            int numObj = allTiled.at(map[row1 + 1][col] - 1)->number;
                            // 获取当前格子的数字
                            int numNow = allTiled.at(map[row1][col] - 1)->number;
                            // 两个格子数字相同
                            if (numNow == numObj) {
                                sound_clear = true;
                                score += numObj * 2;
                                // 上面那一行数字X2
                                allTiled.at(map[row1 + 1][col] - 1)->doubleNumber();
                                // 去除掉当前数字块
                                allTiled.at(map[row1][col] - 1)->removeFromParent();
                                // 获取当前数字块编号
                                int index = map[row1][col];
                                allTiled.erase(map[row1][col] - 1);
                                // 纠正所有大于index号码的编号大小
                                for (int r = 0; r < GAME_ROWS; ++r) {
                                    for (int c = 0; c < GAME_COLS; ++c) {
                                        if (map[r][c] > index) {
                                            --map[r][c];
                                        }
                                    }
                                }
                                // 将当前块编号设置为0
                                map[row1][col] = 0;
                            }
                            break;
                        }
                    }
                }
            }
        }
    }

    void GameScene::moveDown() {
        // 向下移动所有的块
        for (int col = 0; col < GAME_COLS; ++col) {
            for (int row = 0; row < GAME_ROWS; ++row) {
                if (map[row][col] > 0) {
                    for (int row1 = row; row1 > 0; --row1) {
                        if (map[row1 - 1][col] == 0) {
                            map[row1 - 1][col] = map[row1][col];
                            map[row1][col] = 0;
                            allTiled.at(map[row1 - 1][col] - 1)->moveTo(row1 - 1, col);
                        } else {
                            int numObj = allTiled.at(map[row1 - 1][col] - 1)->number;
                            int numNow = allTiled.at(map[row1][col] - 1)->number;
                            if (numNow == numObj) {
                                sound_clear = true;
                                score += numObj * 2;
                                allTiled.at(map[row1 - 1][col] - 1)->doubleNumber();
                                allTiled.at(map[row1][col] - 1)->removeFromParent();

                                int index = map[row1][col];
                                allTiled.erase(map[row1][col] - 1);

                                // 纠正块的编号
                                for (int r = 0; r < GAME_ROWS; ++r) {
                                    for (int c = 0; c < GAME_COLS; ++c) {
                                        if (map[r][c] > index) {
                                            --map[r][c];
                                        }
                                    }
                                }
                                map[row1][col] = 0;
                            }
                            break;
                        }
                    }
                }
            }
        }
    }

    void GameScene::moveLeft() {
        // 向左移动所有的块
        for (int row = 0; row < GAME_ROWS; ++row) {
            for (int col = 0; col < GAME_COLS; ++col) {
                if (map[row][col] > 0) {
                    for (int col1 = col; col1 > 0; --col1) {
                        if (map[row][col1 - 1] == 0) {
                            map[row][col1 - 1] = map[row][col1];
                            map[row][col1] = 0;

                            allTiled.at(map[row][col1 - 1] - 1)->moveTo(row, col1 - 1);
                        } else {
                            int numObj = allTiled.at(map[row][col1 - 1] - 1)->number;
                            int numNow = allTiled.at(map[row][col1] - 1)->number;
                            if (numNow == numObj) {
                                sound_clear = true;
                                score += numObj * 2;
                                allTiled.at(map[row][col1 - 1] - 1)->doubleNumber();
                                allTiled.at(map[row][col1] - 1)->removeFromParent();
                                int index = map[row][col1];
                                allTiled.erase(map[row][col1] - 1);
                                // 纠正块的编号
                                for (int r = 0; r < GAME_ROWS; ++r) {
                                    for (int c = 0; c < GAME_COLS; ++c) {
                                        if (map[r][c] > index) {
                                            --map[r][c];
                                        }
                                    }
                                }
                                map[row][col1] = 0;
                            }
                            break;
                        }
                    }
                }
            }
        }
    }

    void GameScene::moveRight() {
        // 向右移动所有的块
        for (int row = 0; row < GAME_ROWS; ++row) {
            for (int col = GAME_COLS - 1; col >= 0; --col) {
                if (map[row][col] > 0) {
                    for (int col1 = col; col1 < GAME_COLS - 1; ++col1) {
                        if (map[row][col1 + 1] == 0) {
                            map[row][col1 + 1] = map[row][col1];
                            map[row][col1] = 0;

                            allTiled.at(map[row][col1 + 1] - 1)->moveTo(row, col1 + 1);
                        } else {
                            int numObj = allTiled.at(map[row][col1 + 1] - 1)->number;
                            int numNow = allTiled.at(map[row][col1] - 1)->number;
                            if (numNow == numObj) {
                                sound_clear = true;
                                score += numObj * 2;
                                allTiled.at(map[row][col1 + 1] - 1)->doubleNumber();
                                allTiled.at(map[row][col1] - 1)->removeFromParent();
                                int index = map[row][col1];
                                allTiled.erase(map[row][col1] - 1);

                                for (int r = 0; r < GAME_ROWS; ++r) {
                                    for (int c = 0; c < GAME_COLS; ++c) {
                                        if (map[r][c] > index) {
                                            --map[r][c];
                                        }
                                    }
                                }
                                map[row][col1] = 0;
                            }
                            break;
                        }
                    }
                }
            }
        }
    }

    /**
     * 能否向上移动来解析一下这个方法：从最下面一行第一列到倒数第二行最后一列，进行两层循环：
        ——首先判断同列的上面那一行，是否为0（即是否是空的格子，没有数字块）
        ————如果为空，判断这一行是否为空
        ——————不为空，则可以向上移动
        ——————为空，则不能移动
        ————如果不为空，判断本行相应列是否为空
        ——————为空，则不能移动
        ——————不为空，判断本行与上一行同列的是否相同
        ————————相同，则可以移动
        ————————不同，不能移动
        根据前面“——”长短，可以看出，判断等级。
     * */

    void GameScene::judgeMove() {
        int r, c;
        isMoveUp = false;
        isMoveDown = false;
        isMoveRight = false;
        isMoveLeft = false;

        // 向上能否移动
        for (r = 0; r < GAME_ROWS - 1; ++r) {
            for (c = 0; c < GAME_COLS; ++c) {
                if (map[r + 1][c] == 0) {
                    if (map[r][c] != 0) {
                        isMoveUp = true;
                        break;
                    }
                } else {
                    if (map[r][c] != 0) {
                        if (allTiled.at(map[r][c] - 1)->number ==
                            allTiled.at(map[r + 1][c] - 1)->number) {
                            isMoveUp = true;
                            break;
                        }
                    }
                }
            }
            if (isMoveUp == true) break;
        }

        // 向下是否能移动
        for (r = GAME_ROWS - 1; r > 0; --r) {
            for (c = 0; c < GAME_COLS; ++c) {
                if (map[r - 1][c] == 0) {
                    if (map[r][c] != 0) {
                        isMoveDown = true;
                        break;
                    }
                } else {
                    if (map[r][c] != 0) {
                        if (allTiled.at(map[r][c] - 1)->number ==
                            allTiled.at(map[r - 1][c] - 1)->number) {
                            isMoveDown = true;
                            break;
                        }
                    }
                }
            }
            if (isMoveDown == true) break;
        }

        // 向左是否能移动
        for (c = 0; c < GAME_COLS - 1; ++c) {
            for (r = 0; r < GAME_ROWS; ++r) {
                if (map[r][c + 1] == 0) {
                    if (map[r][c] != 0) {
                        isMoveRight = true;
                        break;
                    }
                } else {
                    if (map[r][c] != 0) {
                        if (allTiled.at(map[r][c] - 1)->number ==
                            allTiled.at(map[r][c + 1] - 1)->number) {
                            isMoveRight = true;
                            break;
                        }
                    }
                }
            }
            if (isMoveRight == true) break;
        }

        // 向右是否能移动
        for (c = GAME_COLS - 1; c > 0; --c) {
            for (r = 0; r < GAME_ROWS; ++r) {
                if (map[r][c - 1] == 0) {
                    if (map[r][c] != 0) {
                        isMoveLeft = true;
                        break;
                    }
                } else {
                    if (map[r][c] != 0) {
                        if (allTiled.at(map[r][c] - 1)->number ==
                            allTiled.at(map[r][c - 1] - 1)->number) {
                            isMoveLeft = true;
                            break;
                        }
                    }
                }
            }
            if (isMoveLeft == true) break;
        }
    }
}
