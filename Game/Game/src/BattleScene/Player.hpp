#pragma once
#include <Siv3D.hpp>

namespace Battle {
    struct Player {
        RectF rect;
        double speedX;   // 横移動の速度
        double accX;    // 横移動の加速度
        double speedY;      // 縦移動の速度
        double accY;    // 加速度Y
        bool touch;  // 当たり判定用

        bool isGround;     // 地面にいるかどうかのフラグ
        int jump = 0;
        bool isRight;     // どっちに向いているのか（右なら1、左なら０）
        int spinCount;  // 回転のアニメーション

        int HP;         // ライフ
        uint32 protectedCounter; // 無敵状態かどうか
    };
}
