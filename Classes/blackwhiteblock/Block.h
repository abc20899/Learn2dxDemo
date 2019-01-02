//
// Created by jun zhao on 2019/1/2.
//

#ifndef PROJ_ANDROID_BLOCK_H
#define PROJ_ANDROID_BLOCK_H

#include "cocos2d.h"
#include <iostream>

USING_NS_CC;

class Block : public Sprite {

public:
//    static Vector<Block *> blockes;
    //static成员变量需要在类定义体外进行初始化与定义，
    // 因为static数据成员独立该类的任意对象存在，它是与类关联的对象，不与类对象关联。
    int lineIndex; //行号
public:
    //大小、颜色、内容、字体大小、字体颜色
    static Block *
    createBlock(Size size, Color3B color3B, std::string label, int fontSize, Color4B color4B);

    virtual bool init(Size size, Color3B color3B, std::string label, int fontSize, Color4B color4B);

    void moveDown(std::function<void()> func); //向下移动 //std::function<void()> &func

    void removeBlock();
};

#endif //PROJ_ANDROID_BLOCK_H
