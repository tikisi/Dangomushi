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
    virtual ~ShotGenerator() = default;
};

class RadialGenerator : public ShotGenerator {
private:
    Vec2 center;
    uint32 counter;
    double accAbs;  // 加速度の絶対値
    double randomOffset;
    
public:
    RadialGenerator(ShotAddr * shotAddr, const Vec2& center, double accAbs) :
        ShotGenerator(shotAddr), center(center), counter(0), accAbs(accAbs) {
        randomOffset = Random<double>(Math::QuarterPi);
    }
    virtual ~RadialGenerator() {}

    void update() override;
    bool isFinish() const override {return counter > 60;}
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

class ShieldGenerator : public ShotGenerator {
private:
    Vec2 center;
    uint32 r;
    uint32 shotNum;

public:
    ShieldGenerator(ShotAddr* shotAddr, const Vec2& center, uint32 r, uint32 shotNum) 
        : ShotGenerator(shotAddr), center(center), r(r), shotNum(shotNum) {}

    void update() override;
    bool isFinish() const override {return true;}
};
