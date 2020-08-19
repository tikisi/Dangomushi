# include "Game.hpp"


Game::Game(const InitData& init) : font30(30), IScene(init) {
    // 塔読み込み
    for (int i = 0; i < TW_NUM; i++) {
        tower[i] = Texture(U"tower" + Format(i + 1) + U".png");
    }
    // プレイヤー初期化
    playerInit();

    // 足場の初期化
    footInit();

    // アイテムの初期化
    itemInit();

    // 敵の初期化
    enemyInit();
}


void Game::update() {
    playerUpdate();
    collisionY();
    towerUpdate();
    footUpdate();
    collisionX();
    itemUpdate();
    enemyUpdate();
}


void Game::draw() const {
    footDrawBefore();
    itemDrawBefore();
    towerDraw();
    footDraw();
    itemDraw();
    playerDraw();
    enemyDraw();
}


void Game::towerUpdate() {
    // 塔の描画位置Yのずれを計算
    // ずれを二段分以下に抑える
    towerPosY = int(player.posY) % 80;
    towerDir = rotate(towerDir);

    // 描画する塔の種類を選択
    double a = towerDir;
    towerSelect = 0;
    while (a > 0) {
        if (towerSelect == 5) towerSelect = 0;
        else towerSelect += 1;
        a -= Math::TwoPi / 72.0;
    }


    if (towerSelect == 0) {
        tower1 = tower[0]; tower2 = tower[3];
    }
    else if (towerSelect == 1) {
        tower1 = tower[1]; tower2 = tower[4];
    }
    else if (towerSelect == 2) {
        tower1 = tower[2]; tower2 = tower[5];
    }
    else if (towerSelect == 3) {
        tower1 = tower[3]; tower2 = tower[0];
    }
    else if (towerSelect == 4) {
        tower1 = tower[4]; tower2 = tower[1];
    }
    else if (towerSelect == 5) {
        tower1 = tower[5]; tower2 = tower[2];
    }

}


void Game::towerDraw() const {
    for (int i = 0; i < 18; i++) {
        tower1.resized(TW_WIDTH, TW_HEIGHT).drawAt(TW_CENTER_X, 2 * i * TW_HEIGHT - TW_HEIGHT - towerPosY);
        tower2.resized(TW_WIDTH, TW_HEIGHT).drawAt(TW_CENTER_X, 2 * (i - 1) * TW_HEIGHT - towerPosY);
    }
}


void Game::playerInit() {
    loadPlayer(getData().SelectNum);

    player.drawPosX = TW_CENTER_X - (player.width / 2);  // 塔の中心
    player.drawPosY = 400;
    player.posY = player.drawPosY;
    player.HP = 500;
    player.damageFlag = 0;

    player.dirR = Math::TwoPi - acos((player.drawPosX - TW_CENTER_X) / FT_R);
    player.dirL = Math::TwoPi - acos((player.drawPosX + player.width - TW_CENTER_X) / FT_R);
}



void Game::playerUpdate() {
    // デバッグ用
    if (KeyUp.pressed()) {
        player.speedY = 10;
    }

    // ジャンプ
    if (KeySpace.down()) {
        player.spinCount = 0;
        if (player.isGround) {
            player.jump = 1;
            player.speedY += 5.0;
            player.width = 30;
        }
    }

    if (!player.isGround && player.jump != 0) {
        if (player.jump++ > 8) {
            player.jump = 0;
            player.width = 50;
        }
        if (KeySpace.pressed()) {
            player.speedY += 1.5;
        }
        else {
            player.jump = 0;
            player.width = 50;
        }
    }

    // 左右の加速
    if (player.footType == Foot::Type::ice)player.accX = 0.0005;
    else player.accX = 0.001;

    if (KeyRight.pressed()) {
        player.speedX += player.accX;
        player.isRight = true;
    }

    if (KeyLeft.pressed()) {
        player.speedX -= player.accX;
        player.isRight = false;
    }
    player.speedX *= 0.98;
    if (player.footType != Foot::Type::ice && player.isGround && !KeyRight.pressed() && !KeyLeft.pressed()) player.speedX *= 0.5;
    // yの加速
    player.speedY -= player.accY;
    player.speedY *= 0.98;
    player.posY -= player.speedY;

    // アニメーション
    if (player.isGround) {
        // プレイヤーの歩くアニメーション
        double b = towerDir;
        bool walkflag = 0;
        while (b > 0) {
            walkflag = !walkflag;
            if (walkflag)dango = dango1;
            else dango = dango2;
            b -= Math::TwoPi / 72.0;
        }

        if (walkflag == player.damageFlag && player.footType == Foot::Type::spike) {
            player.HP -= 10;
            player.damageFlag = !player.damageFlag;
        }
    }
    else {
        player.spinCount++;
        if (player.spinCount > 15)player.spinCount = 6;


        if (player.jump) dango = dango3;
        else if (player.spinCount <= 10)dango = dango4;
        else dango = dango5;
    }


}

void Game::collisionY() {
    bool flg = player.isGround;
    for (int i = 0; i < FT_NUM; i++) {
        if (foots[i].withDraw < 30) {
            if (player.intersects(foots[i])) {
                Print << U"collision";
                if (player.speedY < 0.0) {   // 上からぶつかったとき

                    player.posY = foots[i].posY - player.height - 0.00001;
                    player.isGround = true;     // 地面にいるフラグを立てる
                    player.speedY = 0.0;

                    // 刺にあたった瞬間のダメージ
                    if (player.footType == Foot::Type::norm && foots[i].type == Foot::Type::spike) {
                        player.HP -= 50;
                    }
                    if (player.footType == Foot::Type::norm && foots[i].type == Foot::Type::bounce) {
                        player.speedY = 10;
                        player.jump = 1;
                    }
                    player.footType = foots[i].type;
                    if (flg == false && player.footType != Foot::Type::ice)player.speedX *= 0.2;
                    break;
                }
                else {    //  下からぶつかったとき
                    player.posY = foots[i].posY + FT_HEIGHT + 0.00001;
                }

                player.speedY = 0.0;
            }
            else player.isGround = false;
        }
    }
    if (!player.isGround)player.footType = Foot::Type::norm;
}

void Game::collisionX() {
    for (int i = 0; i < FT_NUM; i++) {
        // 当たり判定
        if (foots[i].withDraw < 30 && player.intersects(foots[i])) {
            double tmp = player.speedX; // 退避
            player.speedX *= -1.0 - 0.00001;

            for (int j = 0; j < FT_NUM; j++) {
                foots[j].dirR = rotate(foots[j].dirR);
                foots[j].dirL = rotate(foots[j].dirL);
                foots[j].posRootXL = calcPos(foots[j].dirL, FT_ROOT_R);
                foots[j].posRootXR = calcPos(foots[j].dirR, FT_ROOT_R);
                foots[j].posXL = calcPos(foots[j].dirL, FT_R - foots[j].withDraw);
                foots[j].posXR = calcPos(foots[j].dirR, FT_R - foots[j].withDraw);
                foots[j].isFrontR = isFront(foots[j].dirR);
                foots[j].isFrontL = isFront(foots[j].dirL);
            }

            player.speedX = tmp * -0.5;
        }
    }
}

void Game::playerDraw() const {
    if (player.isRight) dango.mirrored().draw(player.drawPosX, player.drawPosY);
    else dango.draw(player.drawPosX, player.drawPosY);

    Rect(730, 550 - player.HP, 40, player.HP).draw(Palette::Lightgreen);

    // デバッグ用表示
    ClearPrint();
    Print << U"player.posY" << player.posY;
    Print << foots[1].time;
    Print << towerSelect;
    Print << U"towerDir:" << towerDir;
    Print << U"JUMP:" << player.jump;
    Print << U"GROUND" << player.isGround;
}

void Game::footInit() {
    // 足場初期化
    for (int i = 0; i < FT_TEX_NUM; i++) {
        footTextures[i] = Texture(Image(U"Tower" + Format(i + 1) + U".png").scale(FT_TEX_WIDTH, FT_TEX_HEIGHT));
    }

    for (int i = 0; i < FT_NUM; i++) {
        foots[i].time = 0;
        //foots[i].type = (Foot::Type)Random<int>(4);
        foots[i].type = (Foot::Type)0;
        foots[i].dirR = 0.0;
        foots[i].dirL = 0.0;
        foots[i].withDraw = 0.0;
    }
    // 足場の生成
    Lv = 1;
    generateInit();
}

void Game::footUpdate() {
    // 回転
    for (int i = 0; i < FT_NUM; i++) {
        foots[i].dirR = rotate(foots[i].dirR);
        foots[i].dirL = rotate(foots[i].dirL);

        foots[i].posRootXL = calcPos(foots[i].dirL, FT_ROOT_R);
        foots[i].posRootXR = calcPos(foots[i].dirR, FT_ROOT_R);
        foots[i].posXL = calcPos(foots[i].dirL, FT_R - foots[i].withDraw);
        foots[i].posXR = calcPos(foots[i].dirR, FT_R - foots[i].withDraw);
        foots[i].isFrontR = isFront(foots[i].dirR);
        foots[i].isFrontL = isFront(foots[i].dirL);
        foots[i].drawPosY = foots[i].posY + (player.drawPosY - player.posY);
        foots[i].time += 0.02;
        if (foots[i].time > Math::TwoPi) foots[i].time -= Math::TwoPi;

        if (foots[i].type == 1) foots[i].withDraw = cos(foots[i].time) * 50;

        if (foots[i].type == 0 && foots[i].posY > player.posY + 10) foots[i].withDraw += 0.0;

        if (foots[i].withDraw > FT_R - FT_ROOT_R + 5) foots[i].withDraw = FT_R - FT_ROOT_R + 5;
    }

    // 再出現
    generate();
}

void Game::footDrawBefore() const {
    for (int i = 0; i < FT_NUM; i++) {
        // 左右の壁の描画
        if (!foots[i].isFrontL && foots[i].dirL > Math::HalfPi) {
            drawBox(foots[i].posRootXL, foots[i].drawPosY, foots[i].posXL, FT_HEIGHT).draw(Palette::Red);
        }
        if (!foots[i].isFrontR && foots[i].dirR < Math::HalfPi) {
            drawBox(foots[i].posRootXR, foots[i].drawPosY, foots[i].posXR, FT_HEIGHT).draw(Palette::Blue);
        }
    }
}

void Game::footDraw() const {
    for (int i = 0; i < FT_NUM; i++) {
        // 左右の壁の描画
        if (foots[i].isFrontL && foots[i].dirL < Math::HalfPi * 3) {
            drawBox(foots[i].posRootXL, foots[i].drawPosY, foots[i].posXL, FT_HEIGHT).draw(Palette::Red);
        }
        if (foots[i].isFrontR && foots[i].dirR > Math::HalfPi * 3) {
            drawBox(foots[i].posRootXR, foots[i].drawPosY, foots[i].posXR, FT_HEIGHT).draw(Palette::Blue);
        }

        Color footcolor;

        switch (foots[i].type) {
        case Foot::norm:
            footcolor = Color(170, 100 + foots[i].withDraw * 1.5, 100 + foots[i].withDraw * 1.5);
            break;
        case Foot::pull:
            footcolor = Color(170, 100 + foots[i].withDraw * 1.5, 100 + foots[i].withDraw * 1.5);
            break;
        case Foot::spike:
            footcolor = Color(0, 100 + foots[i].withDraw * 1.5, 100 + foots[i].withDraw * 1.5);
            break;
        case Foot::ice:
            footcolor = Color(140, 210, 255);
            break;
        case Foot::bounce:
            footcolor = Color(60, 60, 60);
            break;
        }


        // 足場のまるい壁
        if (foots[i].isFrontL && foots[i].isFrontR) {
            drawBox(foots[i].posXR, foots[i].drawPosY, foots[i].posXL, FT_HEIGHT).draw(footcolor).drawFrame(2, 0, Palette::Black);
            // Debug用
            font30(Format(i)).draw(foots[i].posXR, foots[i].drawPosY, Palette::Black);
            //font30(foots[i].type).draw(foots[i].posXR+5, foots[i].drawPosY+5);
        }
        else if (!foots[i].isFrontR && foots[i].isFrontL) {
            drawBox(TW_CENTER_X - FT_R + foots[i].withDraw, foots[i].drawPosY, foots[i].posXL, FT_HEIGHT).draw(footcolor).drawFrame(2, 0, Palette::Black);
        }
        else if (foots[i].isFrontR && !foots[i].isFrontL) {
            drawBox(TW_CENTER_X + FT_R - foots[i].withDraw, foots[i].drawPosY, foots[i].posXR, FT_HEIGHT).draw(footcolor).drawFrame(2, 0, Palette::Black);
        }
    }
}


void Game::itemInit() {
    // アイテム初期化
    for (int i = 0; i < FT_NUM; i++) {
        items[i].type = RandomBool(0.2);

        if (foots[i].dirR < foots[i].dirL) {
            items[i].dir = Random(foots[i].dirR, foots[i].dirL);
        }
        else {
            items[i].dir = Random(foots[i].dirR, foots[i].dirL + Math::TwoPi);

            if (items[i].dir > Math::TwoPi) items[i].dir -= Math::TwoPi;
        }

        items[i].posY = foots[i].posY - 30;
        items[i].isThere = RandomBool(0.2);
    }
}

void Game::itemUpdate() {
    // 回転
    for (int i = 0; i < FT_NUM; i++) {
        items[i].dir = rotate(items[i].dir);
        items[i].posX = calcPos(items[i].dir, FT_R);
        items[i].posY = foots[i].posY - 30;
        items[i].isFront = isFront(items[i].dir);
        items[i].drawPosY = items[i].posY + (player.drawPosY - player.posY);
        RectF itemRect(Arg::center(items[i].posX, items[i].drawPosY), 30, 30);
        RectF playerRect(player.drawPosX, player.drawPosY, player.width, player.height);
        if (playerRect.intersects(itemRect) && items[i].isThere) {
            items[i].isThere = 0;
            player.HP += 100;
        }

    }
}

void Game::itemDrawBefore() const {
    for (int i = 0; i < FT_NUM; i++) {
        // 後ろのアイテム
        if (!items[i].isFront && items[i].isThere) {
            RectF(Arg::center(items[i].posX, items[i].drawPosY), 30, 30).draw(Palette::Aqua);
        }
    }
}

void Game::itemDraw() const {
    for (int i = 0; i < FT_NUM; i++) {
        // 前のアイテム
        if (items[i].isFront && items[i].isThere) {
            RectF(Arg::center(items[i].posX, items[i].drawPosY), 30, 30).draw(Palette::Aqua);
        }
    }
}


void Game::enemyInit() {
    enemy.isRight = RandomBool(0.5);
    enemy.type = RandomBool(0.5);
    enemy.posY = player.posY - 600;
    enemy.attack = -300;
    enemy.move = 0;
}

void Game::enemyUpdate() {
    // 再出現
    if (enemy.drawPosY > 900) {
        enemyInit();
    }


    if (enemy.attack < 0)enemy.attack++;
    if (enemy.type == 2 && enemy.attack <= 0)enemy.move = -150 + sin(foots[1].time) * 200;

    if (enemy.type == 2 && enemy.attack == 0 && player.isGround && player.speedX == 0)enemy.attack++;
    if (-5 < player.posY - enemy.posY && player.posY - enemy.posY < 5 && enemy.attack == 0 && player.isGround)enemy.attack++;
    if (enemy.posY > player.posY - 500 && enemy.attack <= 0) {
        enemy.posY += (player.posY - enemy.posY) / 50.0;
    }
    if (enemy.attack > 0)enemy.attack++;
    if (enemy.attack > 100)enemy.attack = 100;
    enemy.drawPosY = enemy.posY - player.posY + player.drawPosY + enemy.move;


}

void Game::enemyDraw() const {
    if (enemy.attack < 0 || 50 < enemy.attack)RectF(700, enemy.drawPosY, 80, 50).drawFrame(10, HSV(120 * enemy.type, 1.0, 0.8)).draw(Palette::White);
    else RectF(700, enemy.drawPosY, 80, 50).drawFrame(10, HSV(120 * enemy.type, 1.0, 0.8)).draw(Color(255, 255 - enemy.attack * 3, 255 - enemy.attack));

    switch (enemy.type) {
    case 0:
        if (0 < enemy.attack && enemy.attack <= 50)Line(0, enemy.drawPosY, 700, enemy.drawPosY).draw(LineStyle::RoundDot, 3, Palette::Purple);
        if (50 < enemy.attack && enemy.attack < 100)Line(0, enemy.drawPosY, 700, enemy.drawPosY).draw(LineStyle::RoundCap, enemy.attack / 5.0, Palette::Red);
        break;
    case 1:
        if (50 < enemy.attack && enemy.attack < 100) {
            Circle(700 - (enemy.attack - 50) * 14, enemy.drawPosY, 20).draw(Palette::Red);
        }
        break;
    case 2:
        if (0 < enemy.attack && enemy.attack <= 50) Line(700, enemy.drawPosY, player.drawPosX, player.drawPosY).draw(5, Palette::Purple);
        if (50 < enemy.attack && enemy.attack < 100)RectF(0, enemy.drawPosY, 700, 10 + enemy.attack / 10).draw(Palette::Red);

    default:
        break;
    }
}


double Game::rotate(double arg) {
    arg -= player.speedX;
    if (arg < 0) arg += Math::TwoPi;
    if (arg > Math::TwoPi) arg -= Math::TwoPi;

    return arg;
}

double Game::calcPos(double arg, double r) {
    return TW_CENTER_X + r * cos(arg);
}

bool Game::isFront(double arg) {
    if (Math::Pi <= arg && arg <= Math::TwoPi) return true;
    else return false;
}

void Game::loadPlayer(int selectNum) {
    const static String path = U"player/"; // ディレクトリのパス

    switch (selectNum) {
    case 1:
        dango1 = Texture(path + U"dangomushi/s1dangomushi.png");
        dango2 = Texture(path + U"dangomushi/s2dangomushi.png");
        dango3 = Texture(path + U"dangomushi/j1dangomushi.png");
        dango4 = Texture(path + U"dangomushi/j2dangomushi.png");
        dango5 = Texture(path + U"dangomushi/j3dangomushi.png");
        break;
    case 2:
        dango1 = Texture(path + U"ebi/s1ebi.png");
        dango2 = Texture(path + U"ebi/s2ebi.png");
        dango3 = Texture(path + U"ebi/j1ebi.png");
        dango4 = Texture(path + U"ebi/j2ebi.png");
        dango5 = Texture(path + U"ebi/j3ebi.png");
        break;
    case 3:
        dango1 = Texture(path + U"yadokari/s1yadokari.png");
        dango2 = Texture(path + U"yadokari/s2yadokari.png");
        dango3 = Texture(path + U"yadokari/j1yadokari.png");
        dango4 = Texture(path + U"yadokari/j2yadokari.png");
        dango5 = Texture(path + U"yadokari/j3yadokari.png");
        break;
    case 4:
        dango1 = Texture(path + U"gdangomushi/s1gdangomushi.png");
        dango2 = Texture(path + U"gdangomushi/s2gdangomushi.png");
        dango3 = Texture(path + U"gdangomushi/j1gdangomushi.png");
        dango4 = Texture(path + U"gdangomushi/j2gdangomushi.png");
        dango5 = Texture(path + U"gdangomushi/j3gdangomushi.png");
        break;
    case 5:
        dango1 = Texture(path + U"kurowassan/s1kurowassan.png");
        dango2 = Texture(path + U"kurowassan/s2kurowassan.png");
        dango3 = Texture(path + U"kurowassan/j1kurowassan.png");
        dango4 = Texture(path + U"kurowassan/j2kurowassan.png");
        dango5 = Texture(path + U"kurowassan/j3kurowassan.png");
        break;
    }
}
