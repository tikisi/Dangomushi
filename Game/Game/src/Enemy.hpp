#pragma once

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
