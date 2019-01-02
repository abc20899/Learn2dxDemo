//
// Created by jun zhao on 2018/12/30.
//

#include "ImageFadeOut2.h"

ImageFadeOut2::ImageFadeOut2() : pointA(0), pointB(0) {
}

ImageFadeOut2::~ImageFadeOut2() {
}

ImageFadeOut2 *ImageFadeOut2::create(std::string image) {
    auto imageFadeOut = new ImageFadeOut2();
    if (imageFadeOut == nullptr || !imageFadeOut->initWithImage(image)) {
        CC_SAFE_DELETE(imageFadeOut);
        return nullptr;
    }
    return imageFadeOut;
}

void ImageFadeOut2::update(float dt) {
    const int step = 10; //a,b两点每帧减10
    pointA -= step;
    pointB -= step;
    if (pointA < 0) {
        this->unscheduleUpdate();
        return;
    }

    //计算切割线段两个顶点的值
    Vec2 pA(
            pointA > _contentSize.width ? 0 : _contentSize.width - pointA,
            pointA > _contentSize.width ? _contentSize.height - (pointA - _contentSize.width)
                                        : _contentSize.height
    );

    Vec2 pB(
            pointB > _contentSize.height ? _contentSize.width - (pointB - _contentSize.height)
                                         : _contentSize.width,
            pointB > _contentSize.height ? 0 : _contentSize.height - pointB
    );

    //计算切割模板的点 5个点
    Vec2 points[5];
    int pointCount = 0;
    if (pointA > _contentSize.width) {
        points[pointCount++] = pA;
        points[pointCount++] = Vec2(0, _contentSize.height);
        points[pointCount++] = _contentSize;
    } else {
        points[pointCount++] = pA;
        points[pointCount++] = _contentSize;
    }
    if (pointB > _contentSize.height) {
        points[pointCount++] = Vec2(_contentSize.width, 0);
        points[pointCount++] = pB;
    } else {
        points[pointCount++] = pB;
    }

    displayClipping->clear();
    displayClipping->drawPolygon(points, pointCount, Color4F(1.0f, 1.0f, 1.0f, 1.0f), 0,
                                 Color4F(0, 0, 0, 0));

    //遍历AB两点组成的线段上的像素 创建粒子效果
    int x = pA.x, y = pA.y;
    auto pixel = (unsigned int *) (imageRef->getData()); //像素转换成无符号的int
    while (x < pB.x && y > 0) {
        x += step;
        y -= step;

        auto colorCode = pixel + (static_cast<unsigned int>(_contentSize.height - y - 1) *
                                  imageRef->getWidth()) + x;
        //过滤透明像素
        if ((*colorCode >> 24 & 0xff) < 0xff) { //0xff 255
            continue;
        }

        //浮点数计算 r,g,b,a
        Color4F color(
                (*colorCode & 0xff) / 255.0f,
                (*colorCode >> 8 & 0xff) / 255.0f,
                (*colorCode >> 16 & 0xff) / 255.0f,
                1.0f
        );

        //创建粒子
        auto p = ParticleSystemQuad::create("particle/fire.plist");
        p->setStartColor(color);
        p->setEndColor(color);
        p->setAutoRemoveOnFinish(true);
        p->setPosition(Vec2(x + 15, y + 15));
        addChild(p);
    }
}

bool ImageFadeOut2::initWithImage(std::string image) {
    if (!Node::init()) {
        return false;
    }

    //初始化image对象
    imageRef = new Image();
    imageRef->initWithImageFile(image);

    displayClipping = DrawNode::create();
    auto sp = Sprite::create(image);
    sp->setAnchorPoint(Vec2(0, 0));
    this->setContentSize(sp->getContentSize());//设置node的大小 _contentSize

    //矩形node对象的四个角的坐标
    Vec2 points[4];
    points[0] = Vec2(0, 0);
    points[1] = Vec2(0, _contentSize.height); //node的大小
    points[2] = _contentSize;
    points[3] = Vec2(_contentSize.width, 0);

    //const Vec2 *verts, int count, const Color4F &fillColor, float borderWidth, const Color4F &borderColor
    //画多边形
    displayClipping->drawPolygon(points, 4, Color4F(1.0f, 1.0f, 1.0f, 1.0f), 0,
                                 Color4F(0, 0, 0, 0));
    displayClipping->setAnchorPoint(Vec2(0, 0));
    displayClipping->setContentSize(_contentSize);

    //设置显示模板
    displayImage = ClippingNode::create(displayClipping);
    //设置显示图片
    displayImage->addChild(sp);

    //添加裁剪对象
    addChild(displayImage);
    this->setAnchorPoint(Vec2(0.5, 0.5));

    pointA = pointB = _contentSize.width + _contentSize.height;

    this->scheduleUpdate();

    return true;
}
