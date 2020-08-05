#pragma once

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
};
