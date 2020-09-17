//
//  Stage.hpp
//  Game
//
//  Created by Ryoma Usui on 2020/09/17.
//

#ifndef Stage_h
#define Stage_h
#include <Siv3D.hpp>

struct Stage {
    RectF rect;
    
    double arg;
    double accArg;
    double r;
    double centerX;
    double centerY;
};

#endif /* Stage_h */
