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
    bossUpdate();
    shotUpdate();
}

void BattleScene::draw() const
{
    stageDraw();
    bossDraw();
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
    boss.rect = RectF(Scene::Width() - 200, Scene::Height() - 125, 200, 100);
    boss.speedX = 0.0;
    boss.accX = 0.7;

    boss.state = BossState::Stop;
    boss.HP = 5;
    boss.onRight = true;
}

void BattleScene::bossUpdate() {
    static Stopwatch stopWatch1(true);
    static Stopwatch stopWatch2(true);

    switch (boss.state)
    {
    case BossState::Stop:
        // 弾を発射
        if (stopWatch2.sF() >= 8.0) {
            //shotManager.genSpiral(boss.rect.pos + boss.rect.size / 2, 5, 4);
            shotManager.genRasen(boss.rect.pos + boss.rect.size / 2);
            stopWatch2.restart();
        }

        // Moveへ
        if (stopWatch1.sF() >= 24.0) {
            stopWatch1.restart();
            boss.speedX = 0;
            boss.state = BossState::Move;
        }
        break;
    case BossState::Move:
        if(stopWatch1.sF() <= 2.0) {
            if(boss.onRight) boss.speedX -= boss.accX;
            else boss.speedX += boss.accX;
        }

        boss.speedX *= 0.9;
        boss.rect.x += boss.speedX;
        
        // Stopへ
        if(boss.rect.x < 0) {
            boss.rect.x = 0; 
            boss.onRight = false;
            stopWatch1.restart();
            stopWatch2.restart();
            boss.state = BossState::Stop;
        }
        if(boss.rect.x > Scene::Width() - boss.rect.w) {
            boss.rect.x = Scene::Width() - boss.rect.w;
            boss.onRight = true;
            stopWatch1.restart();
            stopWatch2.restart();
            boss.state = BossState::Stop;
        }
        break;

    default:
        break;
    }

    ClearPrint();
    Print << U"onRight: " << boss.onRight;
    Print << U"BossState: " << int(boss.state);
    Print << U"StopWatch1: " << stopWatch1.sF();
}

void BattleScene::bossDraw() const {
    boss.rect.draw(Palette::Blueviolet);
}

void BattleScene::playerInit() {
    player = Player();
    player.rect.x = 100;
    player.rect.y = 520;
    player.rect.w = 30;
    player.rect.h = 30;

    player.speedX = 0.0;   // 横移動の速度
    player.accX = 0.5;    // 横移動の加速度
    player.speedY = 0.0;      // 縦移動の速度
    player.accY = 0.4;    // 加速度Y

    player.HP = 5;
    player.protectedCounter = 0;

    int selectNum = getData().SelectNum;
    dango1 = TextureAsset(U"player" + Format(selectNum) + Format(1));
    dango2 = TextureAsset(U"player" + Format(selectNum) + Format(2));
    dango3 = TextureAsset(U"player" + Format(selectNum) + Format(3));
    dango4 = TextureAsset(U"player" + Format(selectNum) + Format(4));
    dango5 = TextureAsset(U"player" + Format(selectNum) + Format(5));

    TextureAsset::Register(U"heart", U"pixelheart.png");
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

    // 座標の更新
    player.speedX *= 0.9;
    player.rect.x += player.speedX;
    player.speedY += player.accY;
    player.rect.y += player.speedY;
    if (player.rect.x <= 0) player.rect.x = 0;
    if (player.rect.x + player.rect.w >= Scene::Width()) player.rect.x = Scene::Width() - player.rect.w;


    // ブロックとの当たり判定
    player.isGround = false;
    for (int i = 0; i < STAGE_NUM; i++) {

        if (player.rect.intersects(stage[i].rect) && player.speedY > 0 && stage[i].rect.y - 0.1 < player.rect.y + player.rect.h) {
            player.rect.y = stage[i].rect.y - player.rect.h + 0.1;
            player.isGround = 1;
            if (cos(stage[i].arg) > 0) player.speedY = stage[i].r * cos(stage[i].arg) * stage[i].accArg;
            else player.speedY = 0;
        }
    }

    // 無敵状態の更新
    if (player.protectedCounter != 0) {
        if (player.protectedCounter++ >= 120) {
            player.protectedCounter = 0;
        }
    }

    // アニメーション
    if (player.isGround) {
        // 歩行中のアニメーション
        static int animCounter = 0;
        if (animCounter < 15) dango = dango1;
        else dango = dango2;

        if ((KeyRight | KeyLeft).pressed()) {
            if (animCounter++ == 30) animCounter = 0;
        }

        if (KeyRight.pressed()) player.isRight = true;
        else if (KeyLeft.pressed()) player.isRight = false;
    }
    else {
        // ジャンプ中のアニメーション
        player.spinCount++;
        if (player.spinCount > 15)player.spinCount = 6;
        if (player.jump) dango = dango3;
        else if (player.spinCount <= 10)dango = dango4;
        else dango = dango5;
    }
}

void BattleScene::playerDraw() const {
    // 無敵状態の時は点滅する
    if (player.protectedCounter == 0 || Periodic::Square0_1(0.5s)) {
        player.rect.draw(Palette::Gray);
        if (player.isRight) dango.mirrored().drawAt(player.rect.pos + player.rect.size / 2.0);
        else dango.drawAt(player.rect.pos + player.rect.size / 2.0);
    }

    // ライフを表示
    for (int i = 1; i <= player.HP; i++) {
        TextureAsset(U"heart").resized(30, 30).draw(Scene::Width() - i * (10 + 30), 10);
    }
}

void BattleScene::shotInit() {

}

void BattleScene::shotUpdate() {
    shotManager.update();

    // 当たり判定
    if (player.protectedCounter == 0) {
        Array<Shot*>& shots = shotManager.getShots();
        for (auto it = shots.begin(); it != shots.end(); it++) {
            if ((*it)->getCircle().intersects(player.rect)) {
                // if (--player.HP == 0) changeScene(State::GameOver);
                player.protectedCounter = 1;
                delete* it;
                shots.erase(it);
                break;
            }
        }
    }

    // 生成
    if (KeyZ.down()) shotManager.genRasen(Vec2(400, 50));
    if (KeyS.down())  shotManager.genSpiral(Vec2(700, 500), 10, 3);
}

void BattleScene::shotDraw() const {
    shotManager.draw();
}
