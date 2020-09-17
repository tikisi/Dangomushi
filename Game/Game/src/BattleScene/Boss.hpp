#pragma once

struct Boss {
    int width = 50;     // 横幅
    int height = 30;    // 縦幅
    double speedX = 0.0;   // 横移動の速度
    double accX = 0.001;    // 横移動の加速度

    double PosX;    // 画面上での描画座標X


    bool onGround;     // 地面にいるかどうかのフラグ
    bool isRight;     // どっちに向いているのか（右なら1、左なら０）
    int HP;
    bool damageFlag;
};
