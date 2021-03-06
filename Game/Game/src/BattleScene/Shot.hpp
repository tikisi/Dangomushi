﻿#pragma once
#include <Siv3D.hpp>

class Shot {
public:
    virtual void update() = 0;
    virtual Circle getCircle() const = 0;
    virtual bool isFinish() const = 0;
    virtual ~Shot() {};
};

class RadialShot : public Shot {
public:
    Vec2 pos;
    Vec2 speed;
    Vec2 acc;
    static inline constexpr double r = 5.0;
    RadialShot(const Vec2& start, const Vec2& speed, const Vec2& acc) : 
        pos(start), speed(speed) ,acc(acc) {}

    void update() override { 
        speed += acc;
        pos += speed; 
    }
    Circle getCircle() const override { return Circle(pos, r); }
    bool isFinish() const override { return !(getCircle().intersects(Scene::Rect())); }
};

class RasenShot : public Shot {
private:
    Vec2 center;
    Circular circular;

    static inline constexpr double omega = 0.03;
    static inline constexpr double r = 5.0;

public:
    RasenShot(Vec2 center, double theta, double _r) : center(center), circular(_r, theta) {};

    void update() override {
        circular.theta -= omega;
        circular.r += 0.5;
    }
    Circle getCircle() const override { return Circle(center + circular, r); }
    bool isFinish() const override { return circular.r > 380; }
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

class ShieldShot : public Shot {
private:
    Vec2 center;
    Circular circular;
    Stopwatch stopwatch;

    static inline constexpr double omega = 0.03;

public:
    ShieldShot(Vec2& center, const double r, const double theta)
        : center(center), circular(Circular(r, theta)) {
        stopwatch.start();    
    }

    void update() override { circular.theta -= omega; }
    bool isFinish() const override { return stopwatch.sF() > 4.0; }
    Circle getCircle() const override { return Circle(center + circular, 5.0); }
};
