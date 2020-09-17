#pragma once
#include <Siv3D.hpp>

class Shot {
public:
    Vec2 center;
    Circular circular;

    static inline constexpr double omega = 0.03;
    static inline constexpr double r = 10.0;
    Shot(Vec2 center, double theta, double r) : center(center), circular(r, theta) {};

    void update() {
        circular.theta -= omega;
        circular.r += 0.5;
    }
    Circle getCircle() const { return Circle(center + circular, r); }
};
