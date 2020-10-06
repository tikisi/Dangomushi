﻿#include "Game.hpp"

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
        case 6:
            generateLv6();
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
        case 6:
            generateLv6Init();
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
    
    if(KeyZ.down()) enemyOn(0, 100);
    if(KeyX.down()) enemyOff();
    
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
    foots[0].posY = player.posY + 10;
    foots[0].type = Foot::Type::ice;
    foots[0].time = 0.0;
    foots[0].withDraw = 0.0;
    
    for (int i = 1; i < FT_NUM; i++) {
        foots[i].height = 60;
        foots[i].type = Foot::Type::ice;
        foots[i].dirR = foots[i != 0 ? i - 1 : FT_NUM - 1].dirL + Math::Pi / 5 + Random<double>(Math::TwoPi / 2);
        foots[i].dirL = foots[i].dirR + 0.5;
        foots[i].posY = foots[i != 0 ? i - 1 : FT_NUM - 1].posY - 80;
        
        foots[i].time = 0.0;
        foots[i].withDraw = 0.0;
        player.lowest = foots[i != FT_NUM - 1 ? i + 1 : 0].posY;
    }
}

void Game::generateLv2() {
    if (KeyN.down())enemyInit(0);
    if (KeyM.down())enemyInit(1);
    for (int i = 0; i < FT_NUM; i++) {
        if (foots[i].drawPosY > 1000) {
            foots[i].type = Foot::Type::ice;
            foots[i].height = 60;
            
            foots[i].dirR = foots[i != 0 ? i - 1 : FT_NUM - 1].dirL + Math::Pi / 5 + Random<double>(Math::TwoPi / 2);
            foots[i].dirL = foots[i].dirR + 0.5;
            
            foots[i].posY = foots[i != 0 ? i - 1 : FT_NUM - 1].posY - 50;
            player.lowest = foots[i != FT_NUM - 1 ? i + 1 : 0].posY;
        }
    }
}

void Game::generateLv3Init() {
    if (KeyN.down())enemyInit(0);
    if (KeyM.down())enemyInit(1);
    //    foots[0].dirR = -Math::HalfPi - 0.2;
    //    foots[0].dirL = foots[0].dirR + (Math::Pi / 7);
    foots[0].dirL = 4.98;
    foots[0].dirR = 4.53;
    foots[0].posY = player.posY + 10;
    foots[0].drawPosY = foots[0].posY - player.posY;
    for (int i = 1; i < FT_NUM; i++) {
        if (RandomBool()) {
            foots[i].dirR = foots[i - 1].dirL + Math::Pi / 5 + Random<double>(Math::TwoPi / 3);
            foots[i].dirL = foots[i].dirR + 1.2;
        }
        else {
            foots[i].dirL = foots[i - 1].dirR - Math::Pi / 5 - Random<double>(Math::TwoPi / 3);
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
    // footWidth = 5.0;
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

        
        if (RandomBool()) {
            foots[i].dirR = foots[i - 1].dirL + Math::Pi / 5 + Random<double>(Math::Pi / 7.4);
            foots[i].dirL = foots[i].dirR + (Math::Pi / footWidth);
        }
        else {
            foots[i].dirL = foots[i - 1].dirR - Math::Pi / 5 + Random<double>(Math::Pi / 7.4);
            foots[i].dirR = foots[i].dirL - (Math::Pi / footWidth);
        }
        foots[i].posY = foots[i - 1].posY - (3.25 * foots[i].height + Random<double>(25));
        
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
            foots[i].posY = foots[i != 0 ? i - 1 : FT_NUM - 1].posY - (3.25 * foots[i].height + Random<double>(25));
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
        
        foots[i].posY = foots[i - 1].posY - (3 * foots[i].height + 55);//Random<double>(60));
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
            foots[i].withDraw = 0.0;
            foots[i].height = 30;
            
            
            if (RandomBool()) {
                foots[i].dirR = foots[i != 0 ? i - 1 : FT_NUM - 1].dirL + Math::Pi / 5 + Random<double>(Math::Pi / 7);
                foots[i].dirL = foots[i].dirR + (Math::Pi / footWidth);
            }
            else {
                foots[i].dirL = foots[i != 0 ? i - 1 : FT_NUM - 1].dirR - Math::Pi / 5 + Random<double>(Math::Pi / 7);
                foots[i].dirR = foots[i].dirL - (Math::Pi / footWidth);
            }
            foots[i].posY = foots[i != 0 ? i - 1 : FT_NUM - 1].posY - (3 * foots[i].height + 55);// Random<double>(60));
            
            player.lowest = foots[i != FT_NUM - 1 ? i + 1 : 0].posY;
        }
    }
}

void Game::generateLv6Init() {
    
    footWidth = 5.0;
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

        if (foots[i - 1].type == Foot::Type::pull) {

            if (foots[i - 2].type == Foot::Type::pull) {

                if (foots[i - 3].type == Foot::Type::pull) {

                    if(RandomBool(0.5)) foots[i].type == Foot::Type::ice;
                    else foots[i].type == Foot::Type::norm;
                }
                else if (RandomBool(0.45)) foots[i].type = Foot::Type::pull;
            }
            else if (RandomBool(0.75)) foots[i].type = Foot::Type::pull;
        }
        else foots[i].type = Foot::Type::pull;
        
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

void Game::generateLv6() {
    enemyOn(0, 100);

    for (int i = 0; i < FT_NUM; i++) {
        if (foots[i].drawPosY > 850) {

            foots[i].type = Foot::Type::norm;
            foots[i].withDraw = 0;
            foots[i].height = 40;

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
