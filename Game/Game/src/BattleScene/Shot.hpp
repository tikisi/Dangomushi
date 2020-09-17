#pragma once
#include <Siv3D.hpp>

class Shot {
public:
    virtual void update() = 0;
    virtual Circle getCircle() const = 0;
    virtual bool isFinish() const = 0;
};

class RadialShot : public Shot {
public:
    Vec2 pos;
    Vec2 speed;
    static inline constexpr double r = 10.0;
    RadialShot(const Vec2& start, const Vec2& speed) : pos(start), speed(speed) {}

    void update() override { pos += speed; }
    Circle getCircle() const override {return Circle(pos, r);} 
    bool isFinish() const override { return !(getCircle().intersects(Scene::Rect())); }
};

class RasenShot : public Shot {
private:
    Vec2 center;
    Circular circular;

    static inline constexpr double omega = 0.03;
    static inline constexpr double r = 10.0;

public:
    RasenShot(Vec2 center, double theta, double r) : center(center), circular(r, theta) {};

    void update() override {
        circular.theta -= omega;
        circular.r += 0.5;
    }
    Circle getCircle() const override { return Circle(center + circular, r); }
    bool isFinish() const override { return circular.r > 340; }
};


class SpiralShot : public Shot {
public:
    double angle = -1;
    double r;
    double dist = -1;
    double speed;
    double spiral;
    Vec2 center;

    SpiralShot(Vec2 center, double angle, double dist, double speed, double spiral, double r)
        : center(center), angle(angle), dist(dist), speed(speed), spiral(spiral), r(r) {}

    void update() override {
        if (dist >= 0) {
            angle += spiral;
            dist += speed;
        }
    }

    Circle getCircle() const override { return Circle(center + Circular(dist, angle), r); }
    bool isFinish() const override { return dist > 800; }
};
