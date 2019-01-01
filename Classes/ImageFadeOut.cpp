//
//  ImageFadeOut.cpp
//  Particle
//
//  Created by JasonWu on 12/20/14.
//
//

#include "ImageFadeOut.h"

ImageFadeOut::ImageFadeOut() : _pointA(0), _pointB(0) {

}

ImageFadeOut::~ImageFadeOut() {

}

ImageFadeOut *ImageFadeOut::create(std::string image) {
    auto imageFadeOut = new ImageFadeOut();
    if (imageFadeOut == nullptr || imageFadeOut->initWithImage(image) == false) {
        CC_SAFE_DELETE(imageFadeOut);
        return nullptr;
    }

    return imageFadeOut;
}

bool ImageFadeOut::initWithImage(std::string image) {
    if (Node::init() == false) {
        return false;
    }

    _image = new Image();
    _image->initWithImageFile(image);

    _displayClipping = DrawNode::create();
    auto display = Sprite::create(image);
    display->setAnchorPoint(Vec2(0, 0));

    this->setContentSize(display->getContentSize());

    Vec2 points[4];
    points[0] = Vec2(0, 0);
    points[1] = Vec2(0, _contentSize.height);
    points[2] = _contentSize;
    points[3] = Vec2(_contentSize.width, 0);

    _displayClipping->drawPolygon(points, 4, Color4F(1.0f, 1.0f, 1.0f, 1.0f), 0,
                                  Color4F(0, 0, 0, 0));
    _displayClipping->setAnchorPoint(Vec2(0, 0));
    _displayClipping->setContentSize(_contentSize);

    _displayImage = ClippingNode::create(_displayClipping);
    _displayImage->addChild(display);

    addChild(_displayImage);

    this->setAnchorPoint(Vec2(0.5, 0.5));

    _pointA = _pointB = _contentSize.width + _contentSize.height;

    this->scheduleUpdate();

    return true;
}

void ImageFadeOut::update(float d) {
    const int step = 10;
    _pointA -= step;
    _pointB -= step;
    if (_pointA < 0) {
        this->unscheduleUpdate();
        return;
    }

    //计算切割线段两个顶点的位置
    Vec2 pA(
            _pointA > _contentSize.width ? 0 : _contentSize.width - _pointA,
            _pointA > _contentSize.width ? _contentSize.height - (_pointA - _contentSize.width)
                                         : _contentSize.height
    );

    Vec2 pB(
            _pointB > _contentSize.height ? _contentSize.width - (_pointB - _contentSize.height)
                                          : _contentSize.width,
            _pointB > _contentSize.height ? 0 : _contentSize.height - _pointB
    );

    //计算切割模板的点
    Vec2 points[5];
    int pointCount = 0;
    if (_pointA > _contentSize.width) {
        points[pointCount++] = pA;
        points[pointCount++] = Vec2(0, _contentSize.height);
        points[pointCount++] = _contentSize;
    } else {
        points[pointCount++] = pA;
        points[pointCount++] = _contentSize;
    }
    if (_pointB > _contentSize.height) {
        points[pointCount++] = Vec2(_contentSize.width, 0);
        points[pointCount++] = pB;
    } else {
        points[pointCount++] = pB;
    }

    _displayClipping->clear();
    _displayClipping->drawPolygon(points, pointCount, Color4F(1.0f, 1.0f, 1.0f, 1.0f), 0,
                                  Color4F(0, 0, 0, 0));


    //遍历AB两点组成的线段上的像素 创建粒子特效
    int x = pA.x, y = pA.y;
    auto pixel = (unsigned int *) (_image->getData());
    while (x < pB.x && y > 0) {
        x += step;
        y -= step;

        auto colorCode = pixel + (static_cast<unsigned int>(_contentSize.height - y - 1) *
                                  _image->getWidth()) + x;

        //过滤透明像素
        if ((*colorCode >> 24 & 0xff) < 0xff) {
            continue;
        }

        Color4F color(
                (*colorCode & 0xff) / 255.0f,
                (*colorCode >> 8 & 0xff) / 255.0f,
                (*colorCode >> 16 & 0xff) / 255.0f,
                1.0f
        );

        auto p = ParticleSystemQuad::create("particle/fire.plist");
        p->setStartColor(color);
        p->setEndColor(color);
        p->setAutoRemoveOnFinish(true);
        p->setPosition(Vec2(x + 15, y + 15));

        addChild(p);
    }
}

