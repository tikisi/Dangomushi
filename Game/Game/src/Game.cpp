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
    
    // アイテムの初期化
    itemInit();
    
}


void Game::update() {
    playerUpdate();
    collisionY();
    footUpdate();
    towerUpdate();
    itemUpdate();
    
}


void Game::draw() const {
    footDrawBefore();
    itemDrawBefore();
    towerDraw();
    footDraw();
    itemDraw();
    playerDraw();
}


void Game::towerUpdate() {
    // 塔の描画位置Yのずれを計算
    // ずれを二段分以下に抑える
    towerPosY = int(player.posY) % 80;
    towerDir = rotate(towerDir);
    
    // 描画する塔の種類を選択
    double a = towerDir;
    towerSelect = 0;
    while(a>0){
        if (towerSelect == 5) towerSelect = 0;
        else towerSelect += 1;
        a -= Math::TwoPi/72.0;
    }
   
    
    if(towerSelect == 0) {tower1 = tower[0]; tower2 = tower[3];
    }else if(towerSelect == 1) {tower1 = tower[1]; tower2 = tower[4];
    }else if(towerSelect == 2) {tower1 = tower[2]; tower2 = tower[5];
    }else if(towerSelect == 3) {tower1 = tower[3]; tower2 = tower[0];
    }else if(towerSelect == 4) {tower1 = tower[4]; tower2 = tower[1];
    }else if(towerSelect == 5) {tower1 = tower[5]; tower2 = tower[2];
    }
    
    
//    if (KeyRight.pressed()) towerSelect += 0.02;
//    if (KeyLeft.pressed()) towerSelect -= 0.02;
//
    
//    if (towerSelect < 0.0)towerSelect = 0.6;
//    if (towerSelect > 0.6)towerSelect = 0.0;
    
//    if (towerSelect > 0.5) { tower1 = tower[0]; tower2 = tower[3]; }
//    else if (towerSelect > 0.4) { tower1 = tower[1]; tower2 = tower[4]; }
//    else if (towerSelect > 0.3) { tower1 = tower[2]; tower2 = tower[5]; }
//    else if (towerSelect > 0.2) { tower1 = tower[3]; tower2 = tower[0]; }
//    else if (towerSelect > 0.1) { tower1 = tower[4]; tower2 = tower[1]; }
//    else { tower1 = tower[5]; tower2 = tower[2]; }
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
    player.speedX *= 0.99;
    if (player.isGround && !KeyRight.pressed() && !KeyLeft.pressed()) player.speedX *= 0.7;
    
    // ジャンプ
    if(KeySpace.down()) {
        if(player.isGround) {
            player.jump = 1;
            player.speedY += 8.0;
        }
    }
    if(!player.isGround && player.jump != 0) {
        if(KeySpace.pressed()) {
            player.speedY += 0.7;
        } else {
            player.jump = 0;
        }
        if(player.jump++ > 8) {
            player.jump = 0;
        }
    }

    /*if(KeySpace.up() || player.jump > 10) {
        player.speedY = player.jump;
        player.jump = 0;
    }
    
    if(KeySpace.down() && player.isGround) player.speedY = 12;
    */
    
    // 左右の加速
    if(KeyRight.pressed()) player.speedX += player.accX;
    if(KeyLeft.pressed()) player.speedX -= player.accX;
    
    
    
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
        if (foots[i].isFrontL && foots[i].isFrontR && foots[i].withDraw < 30) {
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
    Print << foots[1].time;
    Print << towerSelect;
    Print << U"towerDir:" << towerDir;
    
}

void Game::footInit() {
    // 足場初期化
    for (int i = 0; i < FT_TEX_NUM; i++) {
        footTextures[i] = Texture(Image(U"Tower" + Format(i + 1) + U".png").scale(FT_TEX_WIDTH, FT_TEX_HEIGHT));
    }
    
    for(int i = 0; i < FT_NUM; i++) {
        foots[i].time = 0;
        foots[i].type = RandomBool(0.2);
        foots[i].dirR = 0.0;
        foots[i].dirL = 0.0;
        foots[i].withDraw = 0.0;
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
        foots[i].posXL = calcPos(foots[i].dirL, FT_R - foots[i].withDraw);
        foots[i].posXR = calcPos(foots[i].dirR, FT_R - foots[i].withDraw);
        foots[i].isFrontR = isFront(foots[i].dirR);
        foots[i].isFrontL = isFront(foots[i].dirL);
        foots[i].drawPosY = foots[i].posY + (player.drawPosY - player.posY);
        
        // 再出現
        if(foots[i].drawPosY > 800){
            foots[i].posY -= 100 * FT_NUM;
            foots[i].type = RandomBool(0.2);
            foots[i].withDraw = 0.0;
            
            // 足場の位置のズレと大きさを制限
            if(i == FT_NUM - 1) foots[i].dirL = foots[0].dirL + Random<double>(-1.5, 1.5);
            else foots[i].dirL = foots[i+1].dirL + Random<double>(-1.5, 1.5);
            foots[i].dirR = foots[i].dirL - Random<double>(0.6, 1.0);
            
            // アイテムの再出現
            
            if(foots[i].dirR < foots[i].dirL){
                items[i].dir = Random(foots[i].dirR, foots[i].dirL);
            }else{
                items[i].dir = Random(foots[i].dirR, foots[i].dirL + Math::TwoPi);
                if (items[i].dir > Math::TwoPi) items[i].dir -= Math::TwoPi;
            }
            
            items[i].posY = foots[i].posY - 30;
            items[i].isThere = RandomBool(0.2);
        }
        

        foots[i].time += 0.02;
        if (foots[i].time > Math::TwoPi) foots[i].time -= Math::TwoPi;
        
        if(foots[i].type == 1) foots[i].withDraw = cos(foots[i].time) * 50;
        
        if(foots[i].type == 0 && foots[i].posY > player.posY + 10) foots[i].withDraw += 0.0;
        
        if(foots[i].withDraw > FT_R - FT_ROOT_R + 5) foots[i].withDraw = FT_R - FT_ROOT_R + 5;
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
            drawBox(TW_CENTER_X - FT_R + foots[i].withDraw, foots[i].drawPosY, foots[i].posXL, FT_HEIGHT).draw(Palette::Orange);
        }
        else if (foots[i].isFrontR && !foots[i].isFrontL) {
            drawBox(TW_CENTER_X + FT_R - foots[i].withDraw, foots[i].drawPosY, foots[i].posXR, FT_HEIGHT).draw(Palette::Orange);
        }
    }
}


void Game::itemInit() {
    // アイテム初期化
    for(int i = 0; i < FT_NUM; i++) {
        items[i].type = RandomBool(0.2);
        
        if(foots[i].dirR < foots[i].dirL){
            items[i].dir = Random(foots[i].dirR, foots[i].dirL);
        }else{
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











double Game::rotate(double arg) {
    arg -= player.speedX;
    
//    if (KeyRight.pressed()) arg -= 0.05;
//    if (KeyLeft.pressed()) arg += 0.05;
    
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
