//
//  GameOver.cpp
//  Game
//
//  Created by Ryoma Usui on 2020/08/23.
//

#include "GameOver.hpp"

void GameOver::update()
{
    if (SimpleGUI::ButtonAt(U"タイトルへ", Scene::Center().movedBy(0, 50))) {
        changeScene(State::Title);
    }
    if (SimpleGUI::ButtonAt(U"つづきから", Scene::Center().movedBy(0, 50))) {
        changeScene(State::Game);
    }
}

void GameOver::draw() const
{
    font50(U"GameOver").drawAt(Scene::Center());
    font50(U"High Score:  " + Format(getData().highscore) + U" cm").draw(10, 10);
}
