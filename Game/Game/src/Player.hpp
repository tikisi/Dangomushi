﻿#pragma once

struct Player {
    int width = 50;     // 横幅
    int height = 30;    // 縦幅
    double speedX = 0.02;   // 横移動の速度
    double speedY = 0.0;      // 縦移動の速度
    double accY = 0.4;    // 加速度Y
    double posY;    // 計算上の位置Y

    double drawPosX;    // 画面上での描画座標X
    double drawPosY;    // 画面上での描画座標Y

    bool isGround;     // 地面にいるかどうかのフラグ
};