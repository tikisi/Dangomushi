//
//  GameOver.cpp
//  Game
//
//  Created by Ryoma Usui on 2020/08/23.
//

#include "GameOver.hpp"

void GameOver::update()
{
    backTexture.draw(0, 0);
    if (SimpleGUI::ButtonAt(U"タイトルへ", Scene::Center().movedBy(0, 50))) {
        AudioAsset(U"GameOver_BGM").stop();
        changeScene(State::Title);
    }
    if (SimpleGUI::ButtonAt(U"つづきから", Scene::Center().movedBy(0, 50))) {
        AudioAsset(U"GameOver_BGM").stop();
        changeScene(State::Game);
    }
}

void GameOver::draw() const
{
    font50(U"High Score:  " + Format(getData().highscore) + U" cm").draw(10, 10);
}
