#pragma once
#include <Siv3D.hpp>
#include "Shot.hpp"
#include "ShotManager.hpp"

class ShotGenerator {
public:
    ShotAddr* shotAddr;
    virtual void update() = 0;
    virtual bool isFinish() const = 0;
    ShotGenerator(ShotAddr* shotAddr) : shotAddr(shotAddr) {}
    virtual ~ShotGenerator() {};
};

class RadialGenerator : public ShotGenerator {
private:
    Vec2 center;
    uint32 counter;
    double randomOffset;
    
public:
    RadialGenerator(ShotAddr * shotAddr, const Vec2& center) : ShotGenerator(shotAddr), center(center), counter(0) {
        randomOffset = Random<double>(Math::QuarterPi);
    }
    virtual ~RadialGenerator() {}

    void update() override;
    bool isFinish() const override {return counter > 30;}
};  

class RasenGenerator : public ShotGenerator {
private:
    Vec2 center;
    uint32 counter;
    inline static constexpr double r = 250;

public:
    RasenGenerator(ShotAddr* shotAddr, const Vec2& center) : ShotGenerator(shotAddr), center(center), counter(0) {}
    virtual ~RasenGenerator() {};

    void update() override;
    bool isFinish() const override { return counter > 15; };
};

class SpiralGenerator : public ShotGenerator {
public:
    Vec2 center;
    uint32 layerNum;
    uint32 shotNum;
    uint32 counter;

    SpiralGenerator(ShotAddr* shotAddr, const Vec2& center, uint32 shotNum, uint32 layerNum)
        : ShotGenerator(shotAddr), center(center), shotNum(shotNum), layerNum(layerNum), counter(0) {}

    void update() override;
    bool isFinish() const override;
};
