#pragma once
#include "Foot.hpp"

struct Player {
    int width = 50;     // 横幅
    int height = 30;    // 縦幅
    double speedX = 0.0;   // 横移動の速度
    double accX = 0.001;    // 横移動の加速度
    double speedY = 0.0;      // 縦移動の速度
    double accY = 0.4;    // 加速度Y
    double posY;    // 計算上の位置Y

    double drawPosX;    // 画面上での描画座標X
    double drawPosY;    // 画面上での描画座標Y


    bool isGround;     // 地面にいるかどうかのフラグ
    int jump = 0;
    bool isRight;     // どっちに向いているのか（右なら1、左なら０）
    int spinCount;  // 回転のアニメーション
    int HP;
    bool damageFlag;
    Foot::Type footType;


    /*角度を使った当たり判定*/
    /*double dirL;        // 角度L(不変値)
    double dirR;        // 角度R(不変値)
    bool intersects(Foot& foot) const {
        if (abs((posY + height / 2) - (foot.posY + FT_HEIGHT / 2)) < (height + FT_HEIGHT) / 2) {
            if (abs(((dirR + dirL) / 2) - ((foot.dirR + foot.dirL) / 2)) < ((dirL - dirR) + (foot.dirL - foot.dirR)) / 2) {
                return true;
            }
        }
        return false;
    }*/
};
