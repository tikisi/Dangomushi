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
    double lowest; // 一番低い足場
    Foot::Type footType;


    /*角度を使った当たり判定*/
    double dirL;        // 角度L
    double dirR;        // 角度R

    bool intersects(const Foot& foot) const {
        // TwoPiを超えて -= TwoPiされたものを戻す
        double fdirL = foot.dirL > foot.dirR ? foot.dirL : foot.dirL + Math::TwoPi;
        double fdirR = foot.dirR;

        if (abs(posY - (foot.posY + foot.height / 2)) < (height + foot.height) / 2) {
            if (abs(((this->dirR + this->dirL) / 2) - ((fdirR + fdirL) / 2)) < ((this->dirL - this->dirR) + (fdirL - fdirR)) / 2) {
                return true;
            }
        }
        return false;
    }

    // 幅を更新
    void updateWidth(const int width, const int TW_CENTER_X) {
        this->width = width;
        dirR = Math::TwoPi - acos(-(double)(width / 2) / (double)FT_R);
        dirL = Math::TwoPi - acos((double)(width / 2) / (double)FT_R);
    }
};
