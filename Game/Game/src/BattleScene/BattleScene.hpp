#pragma once
#include "../Common.hpp"
#include "Player.hpp"
#include "Boss.hpp"
#include "Stage.hpp"
#include "ShotManager.hpp"

#define STAGE_NUM 3
class BattleScene : public MyApp::Scene
{
private:
    Stage stage[STAGE_NUM];
    Battle::Player player;
    ShotManager shotManager;

    Texture dango1;
    Texture dango2;
    Texture dango3;
    Texture dango4;
    Texture dango5;
    Texture dango;

    Boss boss;
    
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

    void shotInit();
    void shotUpdate();
    void shotDraw() const;

    void bossInit();
    void bossUpdate();
    void bossDraw() const;
    void bossIntersects();

    void bossDownStop();
    void bossDownMove();
    void bossDownToUp1();
    void bossDownToUp2();
    void bossUpStop();
    void bossUptoDown1();
    void bossUptoDown2();
};
