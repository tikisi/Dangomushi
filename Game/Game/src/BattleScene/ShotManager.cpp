#include "ShotManager.hpp"
#include "ShotGenerator.hpp"

void ShotManager::genRasen(Vec2 center) { shotGenerators.push_back(new RasenGenerator(this, center)); }

void ShotManager::update() {
    // XV
    for (auto& i : shots) { i->update(); }
    for (auto& i : shotGenerators) { i->update(); }


    // íœ
    for (auto it = shots.begin(); it != shots.end(); ) {
        /*Circle c = (*it)->getCircle();
        if(c.x < 0 || c.x > Scene::Width() ||
            c.y < 0 || c.y > Scene::Height())*/
        if ((*it)->circular.r > 340) {
            delete* it;
            it = shots.erase(it);
        }
        else {
            ++it;
        }
    }
    for (auto it = shotGenerators.begin(); it != shotGenerators.end();) {
        if ((*it)->isfinish()) {
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
