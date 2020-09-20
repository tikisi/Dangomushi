﻿#pragma once

struct Item {
    int type;       // アイテムの種類
    double dir;         // 角度
    double drawPosY;    // 描画する座標Y
    double posY;    // 座標Y
    double posX;   // 描画座標X
    bool isFront;  // 後ろに回ったアイテムは消える

    bool isThere; // アイテムの存在

};
