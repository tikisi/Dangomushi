#include "Game.hpp"

void Game::generate() {
    // Lvに変更があったとき
    if (nLv != Lv) {
        Lv = nLv;
        footWidth = 7.0;
    }

    switch (Lv) {
    case 1:
        generateLv1();
        break;
    case 2:
        generateLv2();
        break;
    case 3:
        generateLv3();
        break;
    case 4:
        generateLv4();
        break;
    case 5:
        generateLv5();
        break;
    }
}

void Game::generateInit() {
    switch (Lv) {
    case 1:
        generateLv1Init();
        break;
    case 2:
        generateLv2Init();
        break;
    case 3:
        generateLv3Init();
        break;
    case 4:
        generateLv4Init();
        break;
    case 5:
        generateLv5Init();
        break;
    }
}


void Game::generateLv1Init() {
    footWidth = 5.0;
    foots[0].type = Foot::Type::norm;
    foots[0].height = 30;
    foots[0].dirR = -Math::HalfPi - 0.2;
    foots[0].dirL = foots[0].dirR + (Math::Pi / footWidth);
    foots[0].posY = player.posY + 10;
    foots[0].time = 0.0;
    foots[0].withDraw = 0.0;

    for (int i = 1; i < FT_NUM; i++) {
        footWidth += 0.05;
        foots[i].type = Foot::Type::norm;
        foots[i].height = 30;

        if (RandomBool()) {
            foots[i].dirR = foots[i - 1].dirL + Math::Pi / 5 + Random<double>(Math::Pi / 7);
            foots[i].dirL = foots[i].dirR + (Math::Pi / footWidth);
        }
        else {
            foots[i].dirL = foots[i - 1].dirR - Math::Pi / 5 + Random<double>(Math::Pi / 7);
            foots[i].dirR = foots[i].dirL - (Math::Pi / footWidth);
        }

        foots[i].posY = foots[i - 1].posY - (3 * foots[i].height + Random<double>(60));
        foots[i].time = 0.0;
        foots[i].withDraw = 0.0;
    }
}

// ビームが出るのは途中からにしたい
void Game::generateLv1() {
    for (int i = 0; i < FT_NUM; i++) {
        if (foots[i].drawPosY > 1000) {
            // 足場の幅更新        
            if (footWidth > 9.0) footWidth = 9.0;
            else footWidth += 0.05;

            foots[i].type = Foot::Type::norm;
            if (RandomBool()) {
                foots[i].dirR = foots[i != 0 ? i - 1 : FT_NUM - 1].dirL + Math::Pi / 5 + Random<double>(Math::Pi / 7);
                foots[i].dirL = foots[i].dirR + (Math::Pi / footWidth);
            }
            else {
                foots[i].dirL = foots[i != 0 ? i - 1 : FT_NUM - 1].dirR - Math::Pi / 5 + Random<double>(Math::Pi / 7);
                foots[i].dirR = foots[i].dirL - (Math::Pi / footWidth);
            }
            foots[i].posY = foots[i != 0 ? i - 1 : FT_NUM - 1].posY - (3 * foots[i].height + Random<double>(60));

            player.lowest = foots[i != FT_NUM - 1 ? i + 1 : 0].posY;
        }
    }
}

void Game::generateLv2Init() {
    foots[0].dirL = 4.98;
    foots[0].dirR = 4.53;
    foots[0].posY = player.posY + 20;
    foots[0].type = Foot::Type::ice;
    foots[0].time = 0.0;
    foots[0].withDraw = 0.0;

    for (int i = 1; i < FT_NUM; i++) {
        foots[i].height = 30;
        foots[i].type = Foot::Type::ice;
        if (RandomBool()) {
            foots[i].dirR = foots[i != 0 ? i - 1 : FT_NUM - 1].dirL + Math::Pi / 5 + Random<double>(Math::TwoPi / 3);
            foots[i].dirL = foots[i].dirR + (Math::Pi / 7);
        }
        else {
            foots[i].dirL = foots[i != 0 ? i - 1 : FT_NUM - 1].dirR - Math::Pi / 5 + Random<double>(Math::TwoPi / 3);
            foots[i].dirR = foots[i].dirL - (Math::Pi / 7);
        }
        foots[i].posY = foots[i != 0 ? i - 1 : FT_NUM - 1].posY - (1.5 * foots[i].height + Random<double>(10));

        foots[i].time = 0.0;
        foots[i].withDraw = 0.0;
    }
}

void Game::generateLv2() {
    foots[0].height = 30;
    for (int i = 0; i < FT_NUM; i++) {
        if (foots[i].drawPosY > 1000) {
            foots[i].type = RandomBool(0.2) ? Foot::Type::spike : Foot::Type::ice;
            //foots[i].type = 
            foots[i].height = Random(30, 100);
            if (RandomBool()) {
                foots[i].dirR = foots[i != 0 ? i - 1 : FT_NUM - 1].dirL + (Math::Pi / 4 + Random<double>(Math::Pi / 4));
                foots[i].dirL = foots[i].dirR + Random(Math::Pi / 12, Math::Pi / 2);
            }
            else {
                foots[i].dirL = foots[i != 0 ? i - 1 : FT_NUM - 1].dirR - (Math::Pi / 4 + Random<double>(Math::Pi / 4));
                foots[i].dirR = foots[i].dirL - Random(Math::Pi / 12, Math::Pi / 2);
            }
            foots[i].posY = foots[i != 0 ? i - 1 : FT_NUM - 1].posY - (foots[i].height + Random<double>(10));

            player.lowest = foots[i != FT_NUM - 1 ? i + 1 : 0].posY;
        }
    }
}

void Game::generateLv3Init() {
    //    foots[0].dirR = -Math::HalfPi - 0.2;
    //    foots[0].dirL = foots[0].dirR + (Math::Pi / 7);
    foots[0].dirL = 4.98;
    foots[0].dirR = 4.53;
    foots[0].posY = player.posY + 20;
    foots[0].drawPosY = foots[0].posY - player.posY;
    for (int i = 1; i < FT_NUM; i++) {
        if (RandomBool()) {
            foots[i].dirR = foots[i - 1].dirL + Math::Pi / 6 + Random<double>(Math::Pi / 3);
            foots[i].dirL = foots[i].dirR + 1.2;
        }
        else {
            foots[i].dirL = foots[i - 1].dirR - Math::Pi / 6 - Random<double>(Math::Pi / 3);
            foots[i].dirR = foots[i].dirL - 1.2;
        }
        foots[i].posY = foots[i - 1].posY - (3 * foots[i].height + Random<double>(20));
        player.lowest = 0;
    }
}

void Game::generateLv3() {
    for (int i = 0; i < FT_NUM; i++) {
        foots[i].type = Foot::Type::ice;
        if (foots[i].drawPosY > 1000) {
            if (RandomBool()) {
                foots[i].dirR = foots[i != 0 ? i - 1 : FT_NUM - 1].dirL + Math::Pi / 6 + Random<double>(Math::Pi / 3);
                foots[i].dirL = foots[i].dirR + 1.2;
            }
            else {
                foots[i].dirL = foots[i != 0 ? i - 1 : FT_NUM - 1].dirR - Math::Pi / 6 - Random<double>(Math::Pi / 3);
                foots[i].dirR = foots[i].dirL - 1.2;
            }
            foots[i].posY = foots[i != 0 ? i - 1 : FT_NUM - 1].posY - (3 * foots[i].height + Random<double>(20));


            player.lowest = foots[i != FT_NUM - 1 ? i + 1 : 0].posY;
        }
    }
}

// Lv1の氷version (横の間隔を狭めて、縦の間隔を広げる)
// ToDo カラスのほうが良い(途中から
void Game::generateLv4Init() {
    footWidth = 5.0;
    foots[0].type = Foot::Type::ice;
    foots[0].height = 30;
    foots[0].dirR = -Math::HalfPi - 0.2;
    foots[0].dirL = foots[0].dirR + (Math::Pi / footWidth);
    foots[0].posY = player.posY + 10;
    foots[0].time = 0.0;
    foots[0].withDraw = 0.0;

    for (int i = 1; i < FT_NUM; i++) {
        footWidth += 0.05;
        foots[i].type = Foot::Type::ice;
        foots[i].height = 30;

        if (RandomBool()) {
            foots[i].dirR = foots[i - 1].dirL + Math::Pi / 5 + Random<double>(Math::Pi / 7.4);
            foots[i].dirL = foots[i].dirR + (Math::Pi / footWidth);
        }
        else {
            foots[i].dirL = foots[i - 1].dirR - Math::Pi / 5 + Random<double>(Math::Pi / 7.4);
            foots[i].dirR = foots[i].dirL - (Math::Pi / footWidth);
        }
        foots[i].posY = foots[i - 1].posY - (4.5 * foots[i].height + Random<double>(40));

        foots[i].time = 0.0;
        foots[i].withDraw = 0.0;
    }
}

void Game::generateLv4() {
    for (int i = 0; i < FT_NUM; i++) {
        if (foots[i].drawPosY > 1000) {
            // 足場の幅更新        
            if (footWidth > 9.0) footWidth = 9.0;
            else footWidth += 0.05;

            foots[i].type = Foot::Type::ice;
            if (RandomBool()) {
                foots[i].dirR = foots[i != 0 ? i - 1 : FT_NUM - 1].dirL + Math::Pi / 5 + Random<double>(Math::Pi / 7.4);
                foots[i].dirL = foots[i].dirR + (Math::Pi / footWidth);
            }
            else {
                foots[i].dirL = foots[i != 0 ? i - 1 : FT_NUM - 1].dirR - Math::Pi / 5 + Random<double>(Math::Pi / 7.4);
                foots[i].dirR = foots[i].dirL - (Math::Pi / footWidth);
            }
            foots[i].posY = foots[i != 0 ? i - 1 : FT_NUM - 1].posY - (4.5 * foots[i].height + Random<double>(40));

            player.lowest = foots[i != FT_NUM - 1 ? i + 1 : 0].posY;
        }
    }
}

// LV1の２段に一つ引っ込むversion
// ToDo: カラスのほうがよさそう(途中から
void Game::generateLv5Init() {
    footWidth = 5.0;
    foots[0].type = Foot::Type::norm;
    foots[0].height = 30;
    foots[0].dirR = -Math::HalfPi - 0.2;
    foots[0].dirL = foots[0].dirR + (Math::Pi / footWidth);
    foots[0].posY = player.posY + 10;
    foots[0].time = 0.0;
    foots[0].withDraw = 0.0;

    for (int i = 1; i < FT_NUM; i++) {
        footWidth += 0.05;
        if (foots[i - 1].type == Foot::Type::norm) foots[i].type = Foot::Type::pull;
        else foots[i].type = Foot::Type::norm;
        foots[i].height = 30;

        if (RandomBool()) {
            foots[i].dirR = foots[i - 1].dirL + Math::Pi / 5 + Random<double>(Math::Pi / 7);
            foots[i].dirL = foots[i].dirR + (Math::Pi / footWidth);
        }
        else {
            foots[i].dirL = foots[i - 1].dirR - Math::Pi / 5 + Random<double>(Math::Pi / 7);
            foots[i].dirR = foots[i].dirL - (Math::Pi / footWidth);
        }

        foots[i].posY = foots[i - 1].posY - (3 * foots[i].height + Random<double>(60));
        foots[i].time = 0.0;
        foots[i].withDraw = 0.0;
    }
}

void Game::generateLv5() {
    for (int i = 0; i < FT_NUM; i++) {
        if (foots[i].drawPosY > 1000) {
            // 足場の幅更新        
            if (footWidth > 9.0) footWidth = 9.0;
            else footWidth += 0.05;

            if (foots[i != 0 ? i - 1 : FT_NUM - 1].type == Foot::Type::norm) foots[i].type = Foot::Type::pull;
            else foots[i].type = Foot::Type::norm;

            if (RandomBool()) {
                foots[i].dirR = foots[i != 0 ? i - 1 : FT_NUM - 1].dirL + Math::Pi / 5 + Random<double>(Math::Pi / 7);
                foots[i].dirL = foots[i].dirR + (Math::Pi / footWidth);
            }
            else {
                foots[i].dirL = foots[i != 0 ? i - 1 : FT_NUM - 1].dirR - Math::Pi / 5 + Random<double>(Math::Pi / 7);
                foots[i].dirR = foots[i].dirL - (Math::Pi / footWidth);
            }
            foots[i].posY = foots[i != 0 ? i - 1 : FT_NUM - 1].posY - (3 * foots[i].height + Random<double>(60));

            player.lowest = foots[i != FT_NUM - 1 ? i + 1 : 0].posY;
        }
    }
}
