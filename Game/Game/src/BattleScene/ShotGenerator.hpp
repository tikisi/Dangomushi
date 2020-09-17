#pragma once
#include <Siv3D.hpp>
#include "Shot.hpp"
#include "ShotManager.hpp"

class ShotGenerator {
public:
    ShotAddr* shotAddr;
    virtual void update() = 0;
    virtual bool isfinish() const = 0;
    ShotGenerator(ShotAddr* shotAddr) : shotAddr(shotAddr) {}
    virtual ~ShotGenerator() {};
};

class RasenGenerator : public ShotGenerator {
public:
    Vec2 center;
    uint32 counter;
    RasenGenerator(ShotAddr* shotAddr, Vec2 center) : ShotGenerator(shotAddr), center(center), counter(0) {}
    virtual ~RasenGenerator() {};

    inline static constexpr double r = 250;
    void update() override {
        if (counter++ % 1 == 0) {
            for (int i = 0; i < 8; i++) {
                shotAddr->add(new Shot(center + Circular(r, Math::QuarterPi - Math::QuarterPi * i), Math::Pi + Math::QuarterPi - i * Math::QuarterPi, r));
            }
        }
    };
    bool isfinish() const override {
        return counter > 15 ? true : false;
    };
};
