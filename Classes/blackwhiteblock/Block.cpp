//
// Created by jun zhao on 2019/1/2.
//
#include "Block.h"

Block *Block::createBlock(Size size, Color3B color3B, std::string label, int fontSize,
                          Color4B color4B) {
    auto block = new Block();
    block->init(size, color3B, label, fontSize, color4B);
    block->autorelease();
    return block;
}

bool Block::init(Size size, Color3B color3B, std::string label, int fontSize, Color4B color4B) {
    if (!Sprite::init()) {
        return false;
    }

    lineIndex = 0;
    setContentSize(size);
    setAnchorPoint(Vec2(0, 0));//锚点左下角
    setTextureRect(Rect(0, 0, size.width, size.height));
    setColor(color3B);
    //添加一个文本
    auto labelText = Label::create();
    labelText->setString(label);
    labelText->setTextColor(color4B);
    labelText->setSystemFontSize(fontSize);
    addChild(labelText);
    labelText->setPosition(size.width / 2, size.height / 2);
    return true;
}

void Block::removeBlock() {
    removeFromParent(); //从父级移除
}

void Block::moveDown(std::function<void()> func) {
    Size winSize = Director::getInstance()->getVisibleSize();
    this->lineIndex--; //行号减1
    //x轴不变 y轴减去block高度  高度-2 保持块上下间隙
    auto moveTo = MoveTo::create(0.1f,
                                 Vec2(getPositionX(),
                                      winSize.height / 4 * lineIndex));
    auto callback = CallFunc::create(func);
    auto sp = Sequence::create(moveTo, callback, NULL);
    this->runAction(sp);
}