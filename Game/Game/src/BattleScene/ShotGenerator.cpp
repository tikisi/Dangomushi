#include "ShotGenerator.hpp"

void RasenGenerator::update() {
    if (counter++ % 1 == 0) {
        for (int i = 0; i < 8; i++) {
            shotAddr->add(new RasenShot(center + Circular(r, Math::QuarterPi - Math::QuarterPi * i), Math::Pi + Math::QuarterPi - i * Math::QuarterPi, r));
        }
    }
}

void SpiralGenerator::update() {
    if (counter++ % 15 == 0) {
        for (int i = 0; i < shotNum; i++) {
            shotAddr->add(new SpiralShot(center, Math::TwoPi / double(shotNum) * i, 0, 0.5, 0.01, 15));
        }
    }
}

bool SpiralGenerator::isFinish() const {
    return  counter > 15 * (layerNum - 1) ? true : false;
}