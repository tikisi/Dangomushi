#include "Game.hpp"

void Game::switchGenerateFoot(const int Lv) {
    switch (Lv) {
    case 1:
        generateFoot = std::bind(&Game::generateLv1, this);
        break;
    case 2:
        generateFoot = std::bind(&Game::generateLv2, this);
        break;
    case 3:
        generateFoot = std::bind(&Game::generateLv3, this);
        break;
    case 4:
        generateFoot = std::bind(&Game::generateLv4, this);
        break;
    case 5:
        generateFoot = std::bind(&Game::generateLv5, this);
        break;
    case 6:
        generateFoot = std::bind(&Game::generateLv6, this);
        break;
    }
}

void Game::generateInit(const int Lv) {
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
    case 6:
        generateLv6Init();
        break;
    }

    switchGenerateFoot(Lv);
}


void Game::generateLv1Init() {
    footWidth = 5.0;
    foots[0].type = Foot::Type::norm;
    foots[0].height = 30.0;
    foots[0].dirR = -Math::HalfPi - 0.2;
    foots[0].dirL = foots[0].dirR + (Math::Pi / footWidth);
    foots[0].posY = player.posY + 10;
    foots[0].time = 0.0;
    foots[0].withDraw = 0.0;

    for (int i = 1; i < FT_NUM; i++) {
        footWidth += 0.05;
        foots[i].type = Foot::Type::norm;
        foots[i].height = 30.0;

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
int Game::generateLv1() {
    if (((int)-player.posY + 2) > 5000) {
        enemyOn(0, 300);
    }

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
            foots[i].height = 30.0;

            return i;
        }
    }

    return -1;
}



void Game::generateLv2Init() {
    foots[0].dirL = 4.98;
    foots[0].dirR = foots[0].dirL - 1.2;
    foots[0].posY = player.posY + 10;
    foots[0].type = Foot::Type::ice;
    foots[0].height = 30;
    foots[0].time = 0.0;
    foots[0].withDraw = 0.0;

    for (int i = 1; i < FT_NUM; i++) {
        foots[i].type = Foot::Type::ice;
        foots[i].height = 30;

        if (RandomBool()) {
            foots[i].dirR = foots[i - 1].dirL + Math::Pi / 5 + Random<double>(Math::TwoPi / 3);
            foots[i].dirL = foots[i].dirR + 1.2;
        }
        else {
            foots[i].dirL = foots[i - 1].dirR - Math::Pi / 5 - Random<double>(Math::TwoPi / 3);
            foots[i].dirR = foots[i].dirL - 1.2;
        }
        foots[i].posY = foots[i - 1].posY - (3 * foots[i].height + Random<double>(20));

        foots[i].time = 0.0;
        foots[i].withDraw = 0.0;
    }
}

int Game::generateLv2() {
    // 敵の生成
    if ((int)-player.posY > (Lv - 1) * 10000 + 2000) {
        enemyOn(1, 300);
    }
    for (int i = 0; i < FT_NUM; i++) {
        if (foots[i].drawPosY > 1000) {

            foots[i].type = Foot::Type::ice;
            if (RandomBool()) {
                foots[i].dirR = foots[i != 0 ? i - 1 : FT_NUM - 1].dirL + Math::Pi / 6 + Random<double>(Math::Pi / 3);
                foots[i].dirL = foots[i].dirR + 1.2;
            }
            else {
                foots[i].dirL = foots[i != 0 ? i - 1 : FT_NUM - 1].dirR - Math::Pi / 6 - Random<double>(Math::Pi / 3);
                foots[i].dirR = foots[i].dirL - 1.2;
            }
            foots[i].posY = foots[i != 0 ? i - 1 : FT_NUM - 1].posY - (3 * foots[i].height + Random<double>(20));
            foots[i].height = 30;

            foots[i].time = 0.0;
            foots[i].withDraw = 0.0;
            return i;
        }
    }

    return -1;
}


void Game::generateLv3Init() {
    footWidth = 5.0;
    foots[0].type = Foot::Type::norm;
    foots[0].dirR = -Math::HalfPi - 0.2;
    foots[0].dirL = foots[0].dirR + (Math::Pi / footWidth);
    foots[0].height = 30.0;
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
        foots[i].height = 30.0;
        foots[i].posY = foots[i - 1].posY - (5 * foots[i].height + Random<double>(60));
        foots[i].time = 0.0;
        foots[i].withDraw = 0.0;
    }
}

int Game::generateLv3() {
    if (((int)-player.posY + 2) > (Lv - 1) * 10000 + 1000) {
        enemyOn(1, 300);
    }
    for (int i = 0; i < FT_NUM; i++) {
        if (foots[i].drawPosY > 1000) {
            // 足場の幅更新
            if (footWidth > 9.0) footWidth = 9.0;
            else footWidth += 0.05;

            foots[i].withDraw = 0.0;
            foots[i].height = 30;

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
            foots[i].posY = foots[i != 0 ? i - 1 : FT_NUM - 1].posY - (5 * foots[i].height + Random<double>(60));
            return i;
        }
    }

    return -1;
}

// Lv1の氷version (横の間隔を狭めて、縦の間隔を広げる)
// ToDo カラスのほうが良い(途中から
void Game::generateLv4Init() {
    footWidth = 5.0;
    foots[0].type = Foot::Type::ice;
    foots[0].dirR = -Math::HalfPi - 0.2;
    foots[0].dirL = foots[0].dirR + (Math::Pi / footWidth);
    foots[0].posY = player.posY + 10;
    foots[0].height = 30.0;
    foots[0].time = 0.0;
    foots[0].withDraw = 0.0;

    for (int i = 1; i < FT_NUM; i++) {
        footWidth += 0.05;
        foots[i].type = Foot::Type::ice;

        if (RandomBool()) {
            foots[i].dirR = foots[i - 1].dirL + Math::Pi / 5 + Random<double>(Math::Pi / 7.4);
            foots[i].dirL = foots[i].dirR + (Math::Pi / footWidth);
        }
        else {
            foots[i].dirL = foots[i - 1].dirR - Math::Pi / 5 + Random<double>(Math::Pi / 7.4);
            foots[i].dirR = foots[i].dirL - (Math::Pi / footWidth);
        }
        foots[i].height = 30.0;
        foots[i].posY = foots[i - 1].posY - (4.5 * foots[i].height + Random<double>(40));

        foots[i].time = 0.0;
        foots[i].withDraw = 0.0;
    }
}

int Game::generateLv4() {
    if ((int)-player.posY + 2 > (Lv - 1) * 10000 + 5000) {
        enemyOn(1, 300);
    }

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
            foots[i].height = 30.0;
            foots[i].posY = foots[i != 0 ? i - 1 : FT_NUM - 1].posY - (4.5 * foots[i].height + Random<double>(40));

            return i;
        }
    }

    return -1;
}

// LV1の２段に一つ引っ込むversion
// ToDo: カラスのほうがよさそう(途中から
void Game::generateLv5Init() {
    foots[0].type = Foot::Type::norm;
    foots[0].height = 30;
    foots[0].dirR = -Math::HalfPi - 0.2;
    foots[0].dirL = foots[0].dirR + (Math::Pi / footWidth);
    foots[0].posY = player.posY + 10;
    foots[0].time = 0.0;
    foots[0].withDraw = 0.0;

    for (int i = 1; i < FT_NUM; i++) {
        foots[i].type = Foot::Type::norm;
        foots[i].height = 30;
        foots[i].withDraw = 0;
        foots[i].time = 0;

        if (foots[i != 0 ? i - 1 : FT_NUM - 1].type == Foot::Type::pull) {

            if (foots[i >= 2 ? i - 2 : FT_NUM + i - 2].type == Foot::Type::pull) {

                if (foots[i >= 3 ? i - 3 : FT_NUM + i - 3].type == Foot::Type::pull) {
                    if (RandomBool(0.666)) foots[i].type = Foot::Type::bounce;
                    else foots[i].type = Foot::Type::norm;
                }
                else if (RandomBool(0.8)) foots[i].type = Foot::Type::pull;
            }
            else if (RandomBool(0.9)) foots[i].type = Foot::Type::pull;
        }
        else foots[i].type = Foot::Type::pull;

        if (RandomBool()) {
            foots[i].dirR = foots[i - 1].dirL + Math::Pi / 5 + Random<double>(Math::Pi / 7);
            foots[i].dirL = foots[i].dirR + (Math::Pi / 5.0);
        }
        else {
            foots[i].dirL = foots[i - 1].dirR - Math::Pi / 5 + Random<double>(Math::Pi / 7);
            foots[i].dirR = foots[i].dirL - (Math::Pi / 5.0);
        }

        foots[i].posY = foots[i - 1].posY - (3 * foots[i].height + Random<double>(60));
    }
}

int Game::generateLv5() {
    for (int i = 0; i < FT_NUM; i++) {
        if (foots[i].drawPosY > 850) {
            foots[i].type = Foot::Type::norm;
            foots[i].withDraw = 0;
            foots[i].time = 0;

            if (foots[i != 0 ? i - 1 : FT_NUM - 1].type == Foot::Type::pull) {

                if (foots[i >= 2 ? i - 2 : FT_NUM + i - 2].type == Foot::Type::pull) {

                    if (foots[i >= 3 ? i - 3 : FT_NUM + i - 3].type == Foot::Type::pull) {
                        if (RandomBool(0.666)) foots[i].type = Foot::Type::bounce;
                        else foots[i].type = Foot::Type::norm;
                    }
                    else if (RandomBool(0.8)) foots[i].type = Foot::Type::pull;
                }
                else if (RandomBool(0.9)) foots[i].type = Foot::Type::pull;
            }
            else foots[i].type = Foot::Type::pull;

            if (RandomBool()) {
                foots[i].dirR = foots[i != 0 ? i - 1 : FT_NUM - 1].dirL + Math::Pi / 5 + Random<double>(Math::Pi / 7);
                foots[i].dirL = foots[i].dirR + (Math::Pi / 5.0);
            }
            else {
                foots[i].dirL = foots[i != 0 ? i - 1 : FT_NUM - 1].dirR - Math::Pi / 5 + Random<double>(Math::Pi / 7);
                foots[i].dirR = foots[i].dirL - (Math::Pi / 5.0);
            }

            foots[i].height = 30.0;
            foots[i].posY = foots[i != 0 ? i - 1 : FT_NUM - 1].posY - (3 * foots[i].height + Random<double>(60));

            return i;
        }
    }
    return -1;
}


void Game::generateLv6Init() {
    footWidth = 0.6;
    foots[0].type = Foot::Type::norm;
    foots[0].dirL = 5.28;
    foots[0].dirR = 4.23;
    foots[0].posY = player.posY + 10;
    foots[0].height = 60;
    foots[0].time = 0.0;
    foots[0].withDraw = 0.0;

    for (int i = 1; i < FT_NUM; i++) {
        footWidth -= 0.003;
        foots[i].height = 100;
        foots[i].type = Foot::Type::ice;
        foots[i].dirR = foots[i != 0 ? i - 1 : FT_NUM - 1].dirL + Math::Pi / 5 + Random<double>(Math::Pi / 2);
        //foots[i].dirL = foots[i].dirR + 0.2;
        foots[i].dirL = foots[i].dirR + footWidth;
        foots[i].posY = foots[i != 0 ? i - 1 : FT_NUM - 1].posY - 50;

        foots[i].time = 0.0;
        foots[i].withDraw = 0.0;
    }
}

int Game::generateLv6() {
    for (int i = 0; i < FT_NUM; i++) {
        if (foots[i].drawPosY > 1000) {
            footWidth -= 0.003;
            foots[i].type = Foot::Type::ice;
            foots[i].height = 100;

            foots[i].dirR = foots[i != 0 ? i - 1 : FT_NUM - 1].dirL + Math::Pi / 5 + Random<double>(Math::Pi / 2);
            //foots[i].dirL = foots[i].dirR + 0.2;
            foots[i].dirL = foots[i].dirR + footWidth;

            foots[i].posY = foots[i != 0 ? i - 1 : FT_NUM - 1].posY - 50;
            foots[i].time = 0.0;
            foots[i].withDraw = 0.0;
            return i;
        }
    }

    return -1;
}
