#include "Game.hpp"

void Game::generate() {
    switch(Lv) {
        case 1:
            generateLv1();
            break;
        case 2:
            generateLv2();
            break;
    }
}

void Game::generateInit() {
    switch(Lv) {
        case 1:
            generateLv1Init();
            break;
        case 2:
            generateLv2Init();
            break;
    }
}


void Game::generateLv1Init() {
    foots[0].dirR = Random<double>(Math::Pi, 10 * Math::QuarterPi);
    foots[0].dirL = foots[0].dirR + (Math::Pi / 7);
    foots[0].posY = 300;
    foots[0].drawPosY = foots[0].posY - player.posY;
    for (int i = 1; i < FT_NUM; i++) {
        if (RandomBool()) {
            foots[i].dirR = foots[i - 1].dirL + Math::Pi / 5 + Random<double>(Math::Pi / 7);
            foots[i].dirL = foots[i].dirR + (Math::Pi / 7);
        }
        else {
            foots[i].dirL = foots[i - 1].dirR - Math::Pi / 5 + Random<double>(Math::Pi / 7);
            foots[i].dirR = foots[i].dirL - (Math::Pi / 7);
        }
        foots[i].posY = foots[i - 1].posY - (3 * FT_HEIGHT + Random<double>(60));
    }
}

void Game::generateLv1() {
    for (int i = 0; i < FT_NUM; i++) {
        if (foots[i].drawPosY > 1000) {
            if (RandomBool()) {
                foots[i].dirR = foots[i != 0 ? i - 1 : FT_NUM - 1].dirL + Math::Pi / 5 + Random<double>(Math::Pi / 7);
                foots[i].dirL = foots[i].dirR + (Math::Pi / 7);
            }
            else {
                foots[i].dirL = foots[i != 0 ? i - 1 : FT_NUM - 1].dirR - Math::Pi / 5 + Random<double>(Math::Pi / 7);
                foots[i].dirR = foots[i].dirL - (Math::Pi / 7);
            }
            foots[i].posY = foots[i != 0 ? i - 1 : FT_NUM - 1].posY - (2 * FT_HEIGHT + Random<double>(100));
        }
    }
}