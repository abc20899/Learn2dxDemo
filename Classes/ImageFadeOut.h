//
//  ImageFadeOut.h
//  Particle
//
//  Created by JasonWu on 12/20/14.
//
//

#ifndef __Particle__ImageFadeOut__
#define __Particle__ImageFadeOut__

#include <stdio.h>
#include "cocos2d.h"

USING_NS_CC;

class ImageFadeOut:public Node
{
protected:
    ClippingNode* _displayImage;
    DrawNode* _displayClipping;
    
    Image* _image;
    
    //两个运动的点
    int _pointA;
    int _pointB;
    
public:
    ImageFadeOut();
    virtual ~ImageFadeOut();
    static ImageFadeOut* create(std::string image);
    bool initWithImage(std::string image);
    
    virtual void update(float d);
};

#endif /* defined(__Particle__ImageFadeOut__) */
