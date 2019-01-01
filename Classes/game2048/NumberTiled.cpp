//
// Created by jun zhao on 2018/12/19.
//

#include "NumberTiled.h"

bool NumberTiled::init() {
    if (!Node::init()) {
        return false;
    }

    // 背景层 数字块背景颜色层
    auto bk = LayerColor::create(Color4B(200, 200, 200, 255), GAME_TILED_WIDTH, GAME_TILED_HEIGHT);
    bk->setTag(101);
    this->addChild(bk);

    // 数字层——随机出一个数字，若数字等于7 则产生4否则产生2
    int n = rand() % 10;
    this->number = n == 7 ? 4 : 2;
    // 根据数字的值，赋予不同颜色
    switch (this->number) {
        case 2:
            bk->setColor(Color3B(230, 220, 210));
            break;
        case 4:
            bk->setColor(Color3B(230, 210, 190));
            break;
        default:
            break;
    }

    // 创建字体，并将本块的数字显现上去 数字显示层
    TTFConfig config("fonts/HelloKitty.ttf", 30);
    auto label = Label::createWithTTF(config, StringUtils::format("%d", this->number));
    label->setPosition(Vec2(GAME_TILED_WIDTH / 2, GAME_TILED_HEIGHT / 2));
    label->setColor(Color3B::BLACK);
    label->setTag(102);
    bk->addChild(label);

    return true;
}

void NumberTiled::moveTo(int r, int c) {
    this->num_row = r;
    this->num_col = c;
    Vec2 pos = Vec2(num_col * GAME_TILED_WIDTH + GAME_TILED_BOARD_WIDTH * (num_col + 1),
                    num_row * GAME_TILED_HEIGHT + GAME_TILED_BOARD_WIDTH * (num_row + 1));
    log("pos-- %d, %d, %f, %f", num_row, num_col, pos.x, pos.y);
    this->setPosition(pos);
}

void NumberTiled::doubleNumber() {
    // 将数字块的数字值翻倍
    this->number = this->number * 2;
    // 获取到背景层和数字层
    auto bk = this->getChildByTag(101);
    Label *label = (Label *) bk->getChildByTag(102);
    // 对数字层的数字，重新绘制
    label->setString(StringUtils::format("%d", number));
    //根据值得大小，对背景层重绘颜色
    switch (this->number) {
        case 2:
            bk->setColor(Color3B(230, 220, 210));
            break;
        case 4:
            bk->setColor(Color3B(230, 210, 190));
            break;
        case 8:
            bk->setColor(Color3B(230, 150, 100));
            label->setColor(Color3B(255, 255, 255));
            break;
        case 16:
            bk->setColor(Color3B(230, 120, 80));
            label->setColor(Color3B(255, 255, 255));
            break;
        case 32:
            bk->setColor(Color3B(230, 100, 90));
            label->setColor(Color3B(255, 255, 255));
            break;
        case 64:
            bk->setColor(Color3B(230, 70, 60));
            label->setColor(Color3B(255, 255, 255));
            break;
        case 128:
            label->setScale(0.7f);
            bk->setColor(Color3B(230, 190, 60));
            label->setColor(Color3B(255, 255, 255));
            break;
        case 256:
            label->setScale(0.7f);
            bk->setColor(Color3B(230, 190, 60));
            label->setColor(Color3B(255, 255, 255));
            break;
        case 512:
            label->setScale(0.7f);
            bk->setColor(Color3B(230, 190, 60));
            label->setColor(Color3B(255, 255, 255));
            break;
        case 1024:
        case 2048:
            label->setScale(0.5f);
            bk->setColor(Color3B(210, 180, 30));
            label->setColor(Color3B(255, 255, 255));
            break;
        default:
            break;
    }
}