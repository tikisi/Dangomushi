#pragma once
#include "../Common.hpp"
#include "Player.hpp"
#include "Boss.hpp"
#include "Stage.hpp"
#include "ShotManager.hpp"
#include "Bullet.hpp"

#define STAGE_NUM 4
class BattleScene : public MyApp::Scene
{
private:
    Stage stage[STAGE_NUM];
    Battle::Player player;
    Boss boss;
    ShotManager shotManager;

    Bullet bullets[30];

public:
    BattleScene(const InitData& init);

    void update() override;

    void draw() const override;

    void stageInit();
    void stageUpdate();
    void stageDraw() const;

    void playerInit();
    void playerUpdate();
    void playerDraw() const;

    void bossInit();
    void bossUpdate();
    void bossDraw() const;

    void shotInit();
    void shotUpdate();
    void shotDraw() const;


    void homing();

    void bulletInit(int num, double speed, double spiral);

};
