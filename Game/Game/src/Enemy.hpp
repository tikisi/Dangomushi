//
//  Enemy.hpp
//  Game
//
//  Created by Ryoma Usui on 2020/08/09.
//

#ifndef Enemy_h
#define Enemy_h

struct Enemy {
    int type;       // 敵の種類
    bool isRight;
    double drawPosY;    // 描画する座標Y
    double posY;    // 座標Y
    int attack;
    int move;
    int aimX;
    int aimY;
};

#endif /* Enemy_h */
