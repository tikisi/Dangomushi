#include "Game.hpp"

void Game::generate() {
    switch(Lv) {
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
    switch(Lv) {
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
    //foots[0].dirR = Random<double>(Math::Pi, 10 * Math::QuarterPi);
    
    foots[0].type = Foot::Type::norm;
    foots[0].height = 30;
    foots[0].dirR = -Math::HalfPi - 0.2;
    foots[0].dirL = foots[0].dirR + (Math::Pi / 7);
    foots[0].posY = player.posY+10;
    foots[0].drawPosY = foots[0].posY - player.posY;
    for (int i = 1; i < FT_NUM; i++) {
        foots[i].type = Foot::Type::norm;
        foots[i].height = 30;
        if (RandomBool()) {
            foots[i].dirR = foots[i - 1].dirL + Math::Pi / 5 + Random<double>(Math::Pi / 7);
            foots[i].dirL = foots[i].dirR + (Math::Pi / 7);
        }
        else {
            foots[i].dirL = foots[i - 1].dirR - Math::Pi / 5 + Random<double>(Math::Pi / 7);
            foots[i].dirR = foots[i].dirL - (Math::Pi / 7);
        }
        foots[i].posY = foots[i - 1].posY - (3 * foots[i].height + Random<double>(60));
    }
    player.lowest = 0;
}

void Game::generateLv1() {
    for (int i = 0; i < FT_NUM; i++) {
        if(KeyN.down())enemyInit(0);
        if(KeyM.down())enemyInit(1);
        
        if (foots[i].drawPosY > 1000) {
            if (RandomBool()) {
                foots[i].dirR = foots[i != 0 ? i - 1 : FT_NUM - 1].dirL + Math::Pi / 5 + Random<double>(Math::Pi / 7);
                foots[i].dirL = foots[i].dirR + (Math::Pi / 7);
            }
            else {
                foots[i].dirL = foots[i != 0 ? i - 1 : FT_NUM - 1].dirR - Math::Pi / 5 + Random<double>(Math::Pi / 7);
                foots[i].dirR = foots[i].dirL - (Math::Pi / 7);
            }
            foots[i].posY = foots[i != 0 ? i - 1 : FT_NUM - 1].posY - (2 * foots[i].height + Random<double>(100));
            
            player.lowest = foots[i != FT_NUM - 1 ? i + 1 : 0].posY;
        }
    }
}

void Game::generateLv2Init() {
    foots[0].dirL = 4.98;
    foots[0].dirR = 4.53;
    foots[0].posY = player.posY+20;
    foots[0].type = Foot::Type::ice;
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

        player.lowest = 0;
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
    foots[0].posY = player.posY+20;
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

void Game::generateLv4Init() {
    for (int i = 0; i < FT_NUM; i++) {
        
    }
}

void Game::generateLv4() {
    for (int i = 0; i < FT_NUM; i++) {
        
    }
}

void Game::generateLv5Init() {
    for (int i = 0; i < FT_NUM; i++) {
        
    }
}

void Game::generateLv5() {
    for (int i = 0; i < FT_NUM; i++) {
        
    }
}
