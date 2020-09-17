//
//  Bullet.hpp
//  Game
//
//  Created by Ryoma Usui on 2020/09/17.
//

#ifndef Bullet_h
#define Bullet_h
#include <Siv3D.hpp>

struct Bullet {
    double angle = -1;
    double r;
    double dist = -1;
    double speed;
    double spiral;
};

#endif /* Bullet_h */
