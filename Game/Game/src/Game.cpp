# include "Game.hpp"

Game::Game(const InitData& init)
    : IScene(init) {
    // 塔読み込み
    for (int i = 0; i < TW_NUM; i++) {
        tower[i] = Texture(U"tower" + Format(i + 1) + U".png");
    }
    // プレイヤー初期化
    playerInit();

    // 足場の初期化
    footInit();
}


void Game::update() {
    playerUpdate();
    collisionY();
    towerUpdate();
    footUpdate();
}


void Game::draw() const {
    footDrawBefore();
    towerDraw();
    footDraw();
    playerDraw();
}


void Game::towerUpdate() {
    // 塔の描画位置Yのずれを計算
    // ずれを二段分以下に抑える
    towerPosY = int(player.posY) % 80;

    // 描画する当の種類を選択
    if (KeyRight.pressed()) towerSelect += 0.02;
    if (KeyLeft.pressed()) towerSelect -= 0.02;
    
    if (towerSelect < 0.0)towerSelect = 0.6;
    if (towerSelect > 0.6)towerSelect = 0.0;

    if (towerSelect > 0.5) { tower1 = tower[0]; tower2 = tower[3]; }
    else if (towerSelect > 0.4) { tower1 = tower[1]; tower2 = tower[4]; }
    else if (towerSelect > 0.3) { tower1 = tower[2]; tower2 = tower[5]; }
    else if (towerSelect > 0.2) { tower1 = tower[3]; tower2 = tower[0]; }
    else if (towerSelect > 0.1) { tower1 = tower[4]; tower2 = tower[1]; }
    else { tower1 = tower[5]; tower2 = tower[2]; }
}


void Game::towerDraw() const {
    for (int i = 0; i < 18; i++) {
        tower1.resized(TW_WIDTH, TW_HEIGHT).drawAt(TW_CENTER_X, 2 * i * TW_HEIGHT - TW_HEIGHT - towerPosY);
        tower2.resized(TW_WIDTH, TW_HEIGHT).drawAt(TW_CENTER_X, 2 * (i - 1) * TW_HEIGHT - towerPosY);
    }
}


void Game::playerInit() {
    player.drawPosX = TW_CENTER_X - (player.width / 2);  // 塔の中心
    player.drawPosY = 400;
    player.posY = player.drawPosY;
}


void Game::playerUpdate() {
    player.speedY -= player.accY;

    // ジャンプ
    if (KeySpace.down()) {
        player.speedY = 10;
    }
    
    // デバッグ用
    if (KeyUp.pressed()) {
        player.speedY = 10;
    }
    
    player.speedY *= 0.99;
    player.posY -= player.speedY;
    
    if(player.posY < -10000)changeScene(State::Battle);
}

void Game::collisionY() {
    RectF playerRect(player.drawPosX, player.posY, player.width, player.height);
    //playerRect.draw(Palette::Green);
    Print << player.posY;

    player.isGround = false;
    for (int i = 0; i < FT_NUM; i++) {
        if (foots[i].isFrontL && foots[i].isFrontR) {
            RectF footRect(foots[i].posXR, foots[i].posY, foots[i].posXL - foots[i].posXR, FT_HEIGHT);
            //footRect.draw(Palette::White);
             if (playerRect.intersects(footRect)) {
                Print << U"collision";
                if (player.speedY < 0.0) {   // 上からぶつかったとき
                    player.posY = foots[i].posY - player.height;
                    player.isGround = true;     // 地面にいるフラグを立てる
                }
                else {    //  下からぶつかったとき
                    player.posY = foots[i].posY + FT_HEIGHT;
                }

                player.speedY = 0.0;
            }
        }
    }

}


void Game::playerDraw() const {
    Rect(player.drawPosX, player.drawPosY, player.width, player.height).draw(Palette::Red);
    ClearPrint();
    Print << -round(player.posY);
}

void Game::footInit() {
    // 足場初期化
    for (int i = 0; i < FT_TEX_NUM; i++) {
        footTextures[i] = Texture(Image(U"Tower" + Format(i + 1) + U".png").scale(FT_TEX_WIDTH, FT_TEX_HEIGHT));
    }
    for (int i = 0; i < FT_NUM; i++) {
        // 足場の位置のズレを制限
        if(i == FT_NUM - 1) foots[i].dirL = foots[0].dirL + Random<double>(-1.5, 1.5);
        else foots[i].dirL = foots[i+1].dirL + Random<double>(-1.5, 1.5);
        foots[i].dirR = foots[i].dirL - 1;
        
        foots[i].posY = i * 100;
        foots[i].drawPosY = foots[i].posY - player.posY;
    }
}

void Game::footUpdate() {
    // 回転
    for (int i = 0; i < FT_NUM; i++) {
        foots[i].dirR = rotate(foots[i].dirR);
        foots[i].dirL = rotate(foots[i].dirL);

        foots[i].posRootXL = calcPos(foots[i].dirL, FT_ROOT_R);
        foots[i].posRootXR = calcPos(foots[i].dirR, FT_ROOT_R);
        foots[i].posXL = calcPos(foots[i].dirL, FT_R);
        foots[i].posXR = calcPos(foots[i].dirR, FT_R);
        foots[i].isFrontR = isFront(foots[i].dirR);
        foots[i].isFrontL = isFront(foots[i].dirL);
        foots[i].drawPosY = foots[i].posY + (player.drawPosY - player.posY);
        
        // 再出現
        if(foots[i].drawPosY > 800){
            foots[i].posY -= 100 * FT_NUM;
            
            // 足場の位置のズレを制限
            if(i == FT_NUM - 1) foots[i].dirL = foots[0].dirL + Random<double>(-1.5, 1.5);
            else foots[i].dirL = foots[i+1].dirL + Random<double>(-1.5, 1.5);
            foots[i].dirR = foots[i].dirL - Random<double>(0.6, 1.0);
        }
    }
}

void Game::footDrawBefore() const {
    for (int i = 0; i < FT_NUM; i++) {
        // 左右の壁の描画
        if (!foots[i].isFrontL) {
            drawBox(foots[i].posRootXL, foots[i].drawPosY, foots[i].posXL, FT_HEIGHT).draw(Palette::Red);
        }
        if (!foots[i].isFrontR) {
            drawBox(foots[i].posRootXR, foots[i].drawPosY, foots[i].posXR, FT_HEIGHT).draw(Palette::Blue);
        }
    }
}

void Game::footDraw() const {
    for (int i = 0; i < FT_NUM; i++) {
        // 左右の壁の描画
        if (foots[i].isFrontL) {
            drawBox(foots[i].posRootXL, foots[i].drawPosY, foots[i].posXL, FT_HEIGHT).draw(Palette::Red);
        }
        if (foots[i].isFrontR) {
            drawBox(foots[i].posRootXR, foots[i].drawPosY, foots[i].posXR, FT_HEIGHT).draw(Palette::Blue);
        }

        // 足場のまるい壁
        if (foots[i].isFrontL && foots[i].isFrontR) {
            drawBox(foots[i].posXR, foots[i].drawPosY, foots[i].posXL, FT_HEIGHT).draw(Palette::Orange);
        }
        else if (!foots[i].isFrontR && foots[i].isFrontL) {
            drawBox(TW_CENTER_X - FT_R, foots[i].drawPosY, foots[i].posXL, FT_HEIGHT).draw(Palette::Orange);
        }
        else if (foots[i].isFrontR && !foots[i].isFrontL) {
            drawBox(TW_CENTER_X + FT_R, foots[i].drawPosY, foots[i].posXR, FT_HEIGHT).draw(Palette::Orange);
        }
    }
}



double Game::rotate(double arg) {
    if (KeyRight.pressed()) arg -= 0.05;
    if (KeyLeft.pressed()) arg += 0.05;

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
