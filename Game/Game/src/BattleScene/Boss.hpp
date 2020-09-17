#pragma once
#include <Siv3D.hpp>

enum class BossState {
    Stop,           // 停止中
    Move,           // 移動中
    Protected       // 攻撃された後
};

struct Boss {
    RectF rect;
    double speedX;
    double accX;

    BossState state;
    bool onRight;
    

    int HP;
};
