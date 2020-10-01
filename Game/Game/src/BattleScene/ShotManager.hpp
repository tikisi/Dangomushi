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
    
    ShotManager() = default;
    ~ShotManager();

    void add(Shot* s) { shots.push_back(s); }

    void update();
    void draw() const;
    Array<Shot*>& getShots() { return shots; }

    void genRadial(const Vec2& center);
    void genRasen(const Vec2& center);
    void genSpiral(const Vec2& center, uint32 shotNum, uint32 layerNum);
    void getShield(const Vec2& center, uint32 r, uint32 shotNum);
};
