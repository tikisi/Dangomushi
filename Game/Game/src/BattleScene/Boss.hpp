#pragma once
#include <Siv3D.hpp>

enum class BossState {
    DownStop,       // 停止中
    UpStop,         // 上で停止中 
    UptoDown1,      // 画面外へ
    UptoDown2,      // 画面内へ
    DownMove,       // 移動中
    DownToUp1,      // 攻撃された後画面外へ
    DownToUp2,      // 攻撃された後画面内へ
};


struct Boss {
    RectF rect;
    double speedX;
    double accX;
    bool onRight;
    int HP;

    BossState state;
    BossState nState;

    int animCount;
    Stopwatch stopWatch1;
    Stopwatch stopWatch2;
};
