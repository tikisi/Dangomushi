#include "ShotManager.hpp"
#include "ShotGenerator.hpp"

void ShotManager::genRadial(const Vec2& center) { shotGenerators.push_back(new RadialGenerator(this, center)); }
void ShotManager::genRasen(const Vec2& center) { shotGenerators.push_back(new RasenGenerator(this, center)); }
void ShotManager::genSpiral(const Vec2& center, uint32 shotNum, uint32 layerNum) { shotGenerators.push_back(new SpiralGenerator(this, center, shotNum, layerNum)); }

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
