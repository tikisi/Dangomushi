#pragma once
#include <Siv3D.hpp>

enum class BossState : uint16 {
// 画面下にいるとき
    DownStop,       // 停止中
    DownMove,       // 移動中
    DownToUp1,      // 攻撃された後画面外へ
    UptoDown2,      // 画面内へ

// 画面上にいるとき
    DownToUp2,      // 攻撃された後画面内へ
    UptoDown1,      // 画面外へ
    UpStop,         // 上で停止中 
};



struct Boss {
    RectF rect;
    double speedX;
    double accX;
    bool isLeft;    // 左を向いているかどうか
    int HP;

    BossState state;
    BossState nState;

    int animCount;
    Stopwatch stopWatch1;
    Stopwatch stopWatch2;
};
