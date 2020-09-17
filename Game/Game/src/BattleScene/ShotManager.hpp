#pragma once
#include <Siv3D.hpp>
#include "Shot.hpp"

class ShotGenerator;

class ShotAddr {
public:
    virtual void add(Shot* s) = 0;
};

class ShotManager : public  ShotAddr {
public:
    Array<Shot*> shots;
    Array<ShotGenerator*> shotGenerators;
    void add(Shot* s) { shots.push_back(s); }

    void genRasen(Vec2 center);
    void update();
    void draw() const;
};
