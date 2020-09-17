#include "BattleScene.hpp"
using namespace Battle;

BattleScene::BattleScene(const InitData& init)
    : IScene(init) {
    Scene::SetBackground(Palette::White);
    stageInit();
    shotInit();
    bossInit();
    playerInit();
}

void BattleScene::update()
{
    stageUpdate();
    playerUpdate();
    shotUpdate();
}

void BattleScene::draw() const
{
    stageDraw();
    playerDraw();
    shotDraw();
}

void BattleScene::stageInit() {
    stage[0].rect.w = 800;
    stage[0].rect.h = 50;
    stage[0].rect.x = 0;
    stage[0].centerY = 600;
    stage[0].arg = 0;
    stage[0].accArg = 0;
    stage[0].r = 0;
    stage[1].rect.w = 100;
    stage[1].rect.h = 50;
    stage[1].rect.x = 100;
    stage[1].centerY = 300;
    stage[1].arg = 0;
    stage[1].accArg = 0.01;
    stage[1].r = 200;
    stage[2].rect.w = 100;
    stage[2].rect.h = 50;
    stage[2].rect.x = 300;
    stage[2].centerY = 300;
    stage[2].arg = 0;
    stage[2].accArg = 0.015;
    stage[2].r = 200;
    stage[3].rect.w = 100;
    stage[3].rect.h = 50;
    stage[3].rect.x = 500;
    stage[3].centerY = 300;
    stage[3].arg = 0;
    stage[3].accArg = 0.005;
    stage[3].r = 200;
}

void BattleScene::stageUpdate() {
    for (int i = 0; i < STAGE_NUM; i++) {
        stage[i].rect.y = stage[i].centerY + stage[i].r * sin(stage[i].arg) - stage[i].rect.h / 2.0;
        stage[i].arg += stage[i].accArg;
        if (stage[i].arg > Math::TwoPi)stage[i].arg -= Math::TwoPi;
        if (stage[i].arg < 0)stage[i].arg += Math::TwoPi;
    }
}

void BattleScene::stageDraw() const {
    for (int i = 0; i < STAGE_NUM; i++) {
        stage[i].rect.draw(Palette::Brown);
    }
}

void BattleScene::bossInit() {

}

void BattleScene::playerInit() {
    player = Player();
    player.rect.x = 100;
    player.rect.y = 520;
    player.rect.w = 50;
    player.rect.h = 30;

    player.speedX = 0.0;   // 横移動の速度
    player.accX = 0.5;    // 横移動の加速度
    player.speedY = 0.0;      // 縦移動の速度
    player.accY = 0.4;    // 加速度Y
}

void BattleScene::playerUpdate() {
    if (KeyRight.pressed()) player.speedX += player.accX;
    if (KeyLeft.pressed()) player.speedX -= player.accX;

    if (KeySpace.down()) {
        player.spinCount = 0;
        if (player.isGround) {
            player.jump = 1;
            player.speedY -= 8.0;
            AudioAsset(U"kaiten").play();
        }
    }

    if (!player.isGround && player.jump != 0) {
        if (player.jump++ > 8) {
            player.jump = 0;
        }
        if (KeySpace.pressed()) {
            player.speedY -= 0.5;
        }
        else {
            player.jump = 0;
        }

    }

    player.speedX *= 0.9;
    player.rect.x += player.speedX;
    player.speedY += player.accY;
    player.rect.y += player.speedY;

    player.isGround = 0;
    for (int i = 0; i < STAGE_NUM; i++) {

        if (player.rect.intersects(stage[i].rect) && player.speedY > 0 && stage[i].rect.y - 0.1 < player.rect.y + player.rect.h) {
            player.rect.y = stage[i].rect.y - player.rect.h + 0.1;
            player.isGround = 1;
            if (cos(stage[i].arg) > 0) player.speedY = stage[i].r * cos(stage[i].arg) * stage[i].accArg;
            else player.speedY = 0;
        }
    }
}

void BattleScene::playerDraw() const {
    ClearPrint();
    Print << player.speedY;
    Print << U"isGround: " << player.isGround;
    player.rect.draw(Palette::Gray);
}

void BattleScene::shotInit() {

}

void BattleScene::shotUpdate() {
    shotManager.update();

    // 当たり判定
    Array<Shot*>& shots = shotManager.getShots();
    for (auto it = shots.begin(); it != shots.end(); ) {
        if ((*it)->getCircle().intersects(player.rect)) {
            delete* it;
            it = shots.erase(it);
        }
        else {
            ++it;
        }
    }

    // 生成
    if (KeyZ.down()) shotManager.genRasen(Vec2(400, 50));
    if (KeyS.down())  shotManager.genSpiral(Vec2(700, 500), 10, 3);
}

void BattleScene::shotDraw() const {
    shotManager.draw();
}
