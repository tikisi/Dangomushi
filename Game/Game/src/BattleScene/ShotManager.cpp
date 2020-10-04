#include "ShotManager.hpp"
#include "ShotGenerator.hpp"

void ShotManager::genRadial(const Vec2& center) { shotGenerators.push_back(new RadialGenerator(this, center)); }
void ShotManager::genRasen(const Vec2& center) { shotGenerators.push_back(new RasenGenerator(this, center)); }
void ShotManager::genSpiral(const Vec2& center, uint32 shotNum, uint32 layerNum) { shotGenerators.push_back(new SpiralGenerator(this, center, shotNum, layerNum)); }
void ShotManager::getShield(const Vec2& center, uint32 r, uint32 shotNum) { shotGenerators.push_back(new ShieldGenerator(this, center, r, shotNum)); }

void ShotManager::update() {
    // 更新
    for (auto& i : shots) { i->update(); }
    for (auto& i : shotGenerators) { i->update(); }


    // 削除
    for (auto it = shots.begin(); it != shots.end(); ) {
        if ((*it)->isFinish()) {
            delete* it;
            it = shots.erase(it);
        }
        else {
            ++it;
        }
    }
    for (auto it = shotGenerators.begin(); it != shotGenerators.end();) {
        if ((*it)->isFinish()) {
            delete* it;
            it = shotGenerators.erase(it);
        }
        else {
            ++it;
        }
    }
}

void ShotManager::draw() const {
    for (auto& i : shots) {
        i->getCircle().draw(Palette::Red);
    }
}

void ShotManager::deleteAll() {
    for (auto it = shots.begin(); it != shots.end();) { it = shots.erase(it); }
    for (auto it = shotGenerators.begin(); it != shotGenerators.end();) { it = shotGenerators.erase(it); }
}

ShotManager::~ShotManager() {
    // ポインタの削除
    this->deleteAll();
}
