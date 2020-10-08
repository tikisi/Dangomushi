# include "Game.hpp"


Game::Game(const InitData& init) : font30(30), nextEnemy(false), IScene(init) {
    // 背景読み込み
    ground = Texture(U"ground.png");
    sunset = Texture(U"pixelsunset.png");
    earth = Texture(U"earthh.png");
    white = Texture(U"pixelwhite.png");

    // 塔読み込み
    for (int i = 0; i < TW_NUM; i++) {
        tower[i] = Texture(U"tower" + Format(i + 1) + U".png");
    }

    // 敵読み込み
    crow1 = Texture(U"crow1.png");
    crow2 = Texture(U"crow2.png");
    crowcharge1 = Texture(U"crowcharge1.png");
    crowcharge2 = Texture(U"crowcharge2.png");

    cubicRed = Texture(U"boxRed.png");
    cubicBlue = Texture(U"boxBlue.png");
    cubic = cubicBlue;

    AudioAsset(U"Main_BGM").setLoop(true);
    AudioAsset(U"Main_BGM").play();

    // プレイヤー初期化
    playerInit();

    // 足場の初期化
    footInit();

    // アイテムの初期化
    itemInit();

    // 敵の初期化
    //    enemyInit(0);
}


void Game::update() {
#ifdef DEBUG
    ClearPrint();
#endif

    playerUpdate();
    collisionY();
    towerUpdate();
    footUpdate();
    collisionX();
    itemUpdate();
    enemyUpdate();
    backUpdate();
}


void Game::draw() const {
    backDraw();
    footDrawBefore();
    itemDrawBefore();
    towerDraw();
    footDraw();
    itemDraw();
    playerDraw();
    enemyDraw();
}


void Game::backUpdate() {
    back.Pos1 = -player.posY / 100 - 200;
    back.alpha = 1.0 + player.posY / 20000.0;
    if (back.alpha < -1) {
        texture1 = earth;
        texture2 = white;
        back.alpha += 2;
        back.Pos1 -= 400;
    }
    else if (back.alpha < 0) {
        texture1 = sunset;
        texture2 = earth;
        back.alpha++;
        back.Pos1 -= 200;
    }
    else {
        texture1 = ground;
        texture2 = sunset;
    }
}

void Game::backDraw() const {
    texture2.resized(1000, 1000).draw(-150, back.Pos1 - 200);
    texture1.resized(1000, 1000).draw(-150, back.Pos1, ColorF(1.0, back.alpha));

    // 到達バー背景
    Rect(700, 0, 100, 600).draw(ColorF(0, 0, 0, 0.7));

    // 到達バーの区切り表示
    for (int i = 1; i <= 5; i++) {
        Rect(700, 600 - i * 100, 100, 5).draw(Palette::Green);
    }
    // 到達バー
    Rect(705, 600 + 600.0 / 60000.0 * player.posY, 90, 5).draw(Palette::Red);
    
    if(getData().dataLv < 5) Line(700, 100, 800, 100).draw(3, Palette::Lime);
    else Line(700, 100, 800, 100).draw(3, Palette::Green);
    if(getData().dataLv < 4) Line(700, 200, 800, 200).draw(3, Palette::Lime);
    else Line(700, 200, 800, 200).draw(3, Palette::Green);
    if(getData().dataLv < 3) Line(700, 300, 800, 300).draw(3, Palette::Lime);
    else Line(700, 300, 800, 300).draw(3, Palette::Green);
    if(getData().dataLv < 2) Line(700, 400, 800, 400).draw(3, Palette::Lime);
    else Line(700, 400, 800, 400).draw(3, Palette::Green);
    if(getData().dataLv < 1) Line(700, 500, 800, 500).draw(3, Palette::Lime);
    else Line(700, 500, 800, 500).draw(3, Palette::Green);
    
#ifdef DEBUG
    Print << back.alpha;
#endif
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
    dango = walking1;

    player.drawPosX = TW_CENTER_X;  // 塔の中心
    player.drawPosY = 400;
    player.posY = 0;
    player.HP = 500;
    player.damageFlag = 0;
    player.updateWidth(player.width, TW_CENTER_X);
}



void Game::playerUpdate() {
    if(player.posY < -60000)changeScene(State::BattleScene);
        // デバッグ用
    if (KeyUp.pressed()) {
        player.speedY = 20;
    }

    // ジャンプ
    if (KeySpace.down()) {
        player.spinCount = 0;
        if (player.isGround) {
            player.jump = 1;
            player.speedY += 5.0;
            player.updateWidth(30, TW_CENTER_X);
            AudioAsset(U"kaiten").play();
        }
    }

    if (!player.isGround && player.jump != 0) {
        if (player.jump++ > 8) {
            player.jump = 0;
        }
        if (KeySpace.pressed()) {
            player.speedY += 1.5;
        }
        else {
            player.jump = 0;
        }

        if (player.isGround)player.width = 50;
        else player.width = 30;
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
    player.speedX *= 0.99;
    if (player.footType != Foot::Type::ice && player.isGround && !KeyRight.pressed() && !KeyLeft.pressed()) player.speedX *= 0.5;
    // yの加速
    player.speedY -= player.accY;
    player.speedY *= 0.98;
    //    if(KeyDown.pressed())player.speedY = 0;
    player.posY -= player.speedY;

    // アニメーション
    if (player.isGround) {
        // プレイヤーの歩くアニメーション
        double b = towerDir;
//        bool walkflag = 0;
//        while (b > 0) {
//            walkflag = !walkflag;
//            if (walkflag)dango = dango1;
//            else dango = dango2;
//            b -= Math::TwoPi / 144.0;
//        }
        
        int texChangeNum = 3;
        while (b > 0) {
            texChangeNum = texChangeNum > 3 ? texChangeNum == 0 : texChangeNum + 1;
            b -= Math::TwoPi / 72.0;
        }
        
        switch (texChangeNum) {
            case 1:
                dango=walking1;
                break;
            case 2:
                dango=walking2;
                break;
            case 3:
                dango=walking3;
                break;
            case 4:
                dango=walking4;
                break;
            default:
                break;
        }
    }
    else {
        player.spinCount++;
        if (player.spinCount > 20)player.spinCount = 1;
        
        //if (player.jump) dango = spinning1;
        if (player.spinCount <= 5)dango = spinning1;
        else if (player.spinCount <= 10)dango = spinning2;
        else if (player.spinCount <= 15)dango = spinning3;
        else dango = spinning4;
    }

    // 落ちたとき
    if (player.posY > player.lowest + 300) {
        //changeScene(State::GameOver);
        getData().death++;
        changeScene(State::BattleScene);
    }
}

void Game::collisionY() {
    bool beforeFlg = player.isGround;
    for (int i = 0; i < FT_NUM; i++) {
        if (foots[i].withDraw < 30) {
            if (player.intersects(foots[i])) {
#ifdef DEBUG
                Print << U"collision";
#endif
                if (player.speedY < 0.0) {   // 上からぶつかったとき

                    player.posY = foots[i].posY - player.height / 2 - 0.00001;
                    player.isGround = true;     // 地面にいるフラグを立てる
                    player.speedY = 0.0;

                    // 刺にあたった瞬間のダメージ
                    if (player.footType == Foot::Type::norm && foots[i].type == Foot::Type::spike) {
                        player.HP -= 50;
                    }
                    if (player.footType == Foot::Type::norm && foots[i].type == Foot::Type::bounce) {
                        player.speedY = 10;
                        if (KeySpace.pressed()) player.speedY += 2;
                        player.jump = 1;
                    }
                    player.footType = foots[i].type;
                    // ジャンプ中->地面
                    if (beforeFlg == false && player.footType != Foot::Type::ice) {
                        player.speedX *= 0.2;
                        player.updateWidth(50, TW_CENTER_X);
                        AudioAsset(U"kaiten").stop();
                        AudioAsset(U"chakuchi").play();
                    }
                    break;
                }
                else {    //  下からぶつかったとき
                    player.posY = foots[i].posY + foots[i].height + (player.height / 2) + 0.00001;
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
    if (player.isRight) dango.mirrored().drawAt(player.drawPosX, player.drawPosY);
    else dango.drawAt(player.drawPosX, player.drawPosY);
    //Rect(730, 550 - player.HP, 40, player.HP).draw(Palette::Lightgreen);

    // デバッグ用表示
#ifdef DEBUG
    Print << U"player.posY" << player.posY;
    Print << U"Lowest:" << player.lowest;
    Print << foots[1].time;
    Print << towerSelect;
    Print << U"towerDir:" << towerDir;
    Print << U"JUMP:" << player.jump;
    Print << U"GROUND" << player.isGround;
    Print << back.alpha;
    Print << U"Lv: " << Lv;
    Print << U"DataLv: " << getData().dataLv;
#endif
}

void Game::footInit() {
    // 画像読み込み
    for (int i = 0; i < FT_TEX_NUM; i++) {
        footTextures[i] = Texture(Image(U"Tower" + Format(i + 1) + U".png").scale(FT_TEX_WIDTH, FT_TEX_HEIGHT));
    }

    // 足場の初期化
    Lv = getData().selectedLv;

    player.lowest = -(Lv - 1) * 10000;
    player.posY = -(Lv - 1) * 10000;
    footWidth = 7.0;
    isReachEnemyPos = false;
    generateInit(Lv);
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
    int i = generateFoot(); // 追加された足場

    // 足場が追加されたとき
    if (i != -1) {
        player.lowest = foots[i != FT_NUM - 1 ? i + 1 : 0].posY;
        int nLv = 1 - (int)(foots[i].posY / 10000);

        // Lvに変更があったとき
        if (nLv != Lv) {
            Lv = std::max(nLv, Lv); // レベルが下がらないように
            if(Lv == 1) footWidth = 7.0;
            else if(Lv == 4) footWidth = 5.0;
            isReachEnemyPos = false;
            switchGenerateFoot(Lv);
        }
    }
}

void Game::footDrawBefore() const {
    for (int i = 0; i < FT_NUM; i++) {
        Color footcolor;

        switch (foots[i].type) {
        case Foot::norm:
            footcolor = Color(10, 50 + foots[i].withDraw * 1.5, 50 + foots[i].withDraw * 1.5);
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

        // 左右の壁の描画
        if (!foots[i].isFrontL && foots[i].dirL > Math::HalfPi) {
            drawBox(foots[i].posRootXL, foots[i].drawPosY, foots[i].posXL, foots[i].height).draw(footcolor).drawFrame(5, 0, Palette::Black);
        }
        if (!foots[i].isFrontR && foots[i].dirR < Math::HalfPi) {
            drawBox(foots[i].posRootXR, foots[i].drawPosY, foots[i].posXR, foots[i].height).draw(footcolor).drawFrame(5, 0, Palette::Black);
        }
    }
}

void Game::footDraw() const {
    for (int i = 0; i < FT_NUM; i++) {

        Color footcolor;

        switch (foots[i].type) {
        case Foot::norm:
            footcolor = Color(10, 50 + foots[i].withDraw * 1.5, 50 + foots[i].withDraw * 1.5);
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

        // 左右の壁の描画
        if (foots[i].isFrontL && foots[i].dirL < Math::HalfPi * 3) {
            drawBox(foots[i].posRootXL, foots[i].drawPosY, foots[i].posXL, foots[i].height).draw(footcolor).drawFrame(5, 0, Palette::Black);
        }
        if (foots[i].isFrontR && foots[i].dirR > Math::HalfPi * 3) {
            drawBox(foots[i].posRootXR, foots[i].drawPosY, foots[i].posXR, foots[i].height).draw(footcolor).drawFrame(5, 0, Palette::Black);
        }



        // 足場のまるい壁
        if (foots[i].isFrontL && foots[i].isFrontR) {
            drawBox(foots[i].posXR, foots[i].drawPosY, foots[i].posXL, foots[i].height).draw(footcolor).drawFrame(5, 0, Palette::Black);
        }
        else if (!foots[i].isFrontR && foots[i].isFrontL) {
            drawBox(TW_CENTER_X - FT_R + foots[i].withDraw, foots[i].drawPosY, foots[i].posXL, foots[i].height).draw(footcolor).drawFrame(5, 0, Palette::Black);
        }
        else if (foots[i].isFrontR && !foots[i].isFrontL) {
            drawBox(TW_CENTER_X + FT_R - foots[i].withDraw, foots[i].drawPosY, foots[i].posXR, foots[i].height).draw(footcolor).drawFrame(5, 0, Palette::Black);
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
    //    // 回転
    //    for (int i = 0; i < FT_NUM; i++) {
    //        items[i].dir = rotate(items[i].dir);
    //        items[i].posX = calcPos(items[i].dir, FT_R);
    //        items[i].posY = foots[i].posY - 30;
    //        items[i].isFront = isFront(items[i].dir);
    //        items[i].drawPosY = items[i].posY + (player.drawPosY - player.posY);
    //        RectF itemRect(Arg::center(items[i].posX, items[i].drawPosY), 30, 30);
    //        RectF playerRect(player.drawPosX, player.drawPosY, player.width, player.height);
    //        if (playerRect.intersects(itemRect) && items[i].isThere) {
    //            items[i].isThere = 0;
    //            player.HP += 100;
    //        }
    //    }
}

void Game::itemDrawBefore() const {
    //    for (int i = 0; i < FT_NUM; i++) {
    //        // 後ろのアイテム
    //        if (!items[i].isFront && items[i].isThere) {
    //            RectF(Arg::center(items[i].posX, items[i].drawPosY), 30, 30).draw(Palette::Aqua);
    //        }
    //    }
}

void Game::itemDraw() const {
    //    for (int i = 0; i < FT_NUM; i++) {
    //        // 前のアイテム
    //        if (items[i].isFront && items[i].isThere) {
    //            RectF(Arg::center(items[i].posX, items[i].drawPosY), 30, 30).draw(Palette::Aqua);
    //        }
    //    }
}


void Game::enemyInit(bool type) {
    enemy.isRight = RandomBool(0.5);
    enemy.type = type;
    enemy.posY = player.posY - 600;
    enemy.attack = -300;
    enemy.move = 0;
}

void Game::enemyUpdate() {
    texturetime++;
    if (texturetime > 10000)texturetime -= 10000;
    // 再出現
    if (enemy.drawPosY > 900 && !enemyWait) {
        enemyTime++;
    }
    
    if(enemyPeriod < enemyTime) {
        enemyInit(enemy.type);
        enemyTime = 0;
    }
    
    if (enemy.attack < 0)enemy.attack++;

    enemy.move = sin(texturetime / 10.0) * 10;

    if (-5 < player.posY - enemy.posY && player.posY - enemy.posY < 5 && enemy.attack == 0 && player.isGround)enemy.attack++;
    if (enemy.posY > player.posY - 500 && enemy.attack <= 0 && !enemyWait) {
        enemy.posY += (player.posY - enemy.posY) / 50.0;
    }
    if (enemy.attack > 0)enemy.attack++;
    if (enemy.attack > 100)enemy.attack = 100;

    enemy.drawPosY = enemy.posY - player.posY + player.drawPosY + enemy.move - 30;

    if (texturetime % 50 < 25) {
        crow = crow1;
        crowcharge = crowcharge1;
    }
    else {
        crow = crow2;
        crowcharge = crowcharge2;
    }
    if (texturetime % 8 < 4) cubiccharge = cubicBlue;
    else cubiccharge = cubicRed;


    if (50 < enemy.attack && enemy.type == 1) {
        enemyrect = RectF(600 - (enemy.attack - 50) * 14, enemy.drawPosY, 100, 60);
    }
    else {
        enemyrect = RectF(600, enemy.drawPosY, 100, 60);
    }

    Rect playerrect(335, 385, 30, 30);

    //カラスにあたると吹っ飛ぶ
    if (enemyrect.intersects(playerrect)) {
        player.speedX = -0.1;
        player.speedY = 2;
    }

    //レーザーでゲームオーバー
    Line lazer(0, enemy.drawPosY + 30, 650, enemy.drawPosY + 30);
    if (50 < enemy.attack && enemy.attack < 100 && lazer.intersects(playerrect) && enemy.type == 0){
        getData().death++;
        changeScene(State::GameOver);
    }}

void Game::enemyDraw() const {
    //    if (enemy.attack < 0 || 50 < enemy.attack)RectF(700, enemy.drawPosY, 80, 50).drawFrame(10, HSV(120 * enemy.type, 1.0, 0.8)).draw(Palette::White);
    //    else RectF(700, enemy.drawPosY, 80, 50).drawFrame(10, HSV(120 * enemy.type, 1.0, 0.8)).draw(Color(255, 255 - enemy.attack * 3, 255 - enemy.attack));
    switch (enemy.type) {
    case 0:
        if (0 < enemy.attack && enemy.attack <= 50)Line(0, enemy.drawPosY + 30, 650, enemy.drawPosY + 30).draw(LineStyle::RoundDot, 3, Palette::Purple);
        if (50 < enemy.attack && enemy.attack < 100)Line(0, enemy.drawPosY + 30, 650, enemy.drawPosY + 30).draw(LineStyle::RoundCap, enemy.attack / 5.0, Palette::Red);

        if (enemy.attack <= 0 || 50 < enemy.attack)enemyrect(cubic).draw();
        else enemyrect(cubiccharge).draw();
        break;
    case 1:
        if (enemy.attack <= 0)enemyrect(crow).draw();
        else enemyrect(crowcharge).draw();
        break;
    default:
        break;
    }
}

void Game::enemyOff(){
    enemyWait = 1;
}

void Game::enemyOn(bool type, int period){
    enemyWait = 0;
    enemyPeriod = period;
    enemy.type = type;
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
    walking1 = TextureAsset(U"player" + Format(selectNum) + Format(1));
    walking2 = TextureAsset(U"player" + Format(selectNum) + Format(2));
    walking3 = TextureAsset(U"player" + Format(selectNum) + Format(3));
    walking4 = TextureAsset(U"player" + Format(selectNum) + Format(4));
    
    spinning1 = TextureAsset(U"player" + Format(selectNum) + Format(5));
    spinning2 = TextureAsset(U"player" + Format(selectNum) + Format(6));
    spinning3 = TextureAsset(U"player" + Format(selectNum) + Format(7));
    spinning4 = TextureAsset(U"player" + Format(selectNum) + Format(8));
}
