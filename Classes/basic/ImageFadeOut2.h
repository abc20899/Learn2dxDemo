//
// Created by jun zhao on 2018/12/30.
//

#ifndef PROJ_ANDROID_IMAGEFADEOUT_H
#define PROJ_ANDROID_IMAGEFADEOUT_H

#include "cocos2d.h"

USING_NS_CC;

class ImageFadeOut2 : public Node {

protected:
    ClippingNode *displayImage;
    DrawNode *displayClipping;
    Image *imageRef;
    int pointA;
    int pointB;

public:
    ImageFadeOut2();

    ~ImageFadeOut2();

    static ImageFadeOut2 *create(std::string image);

    bool initWithImage(std::string image);

    virtual void update(float dt);

};

#endif //PROJ_ANDROID_IMAGEFADEOUT_H
