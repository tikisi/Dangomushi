//
//  GameOver.cpp
//  Game
//
//  Created by Ryoma Usui on 2020/08/23.
//

#include "GameOver.hpp"

void GameOver::update()
{
    if (SimpleGUI::ButtonAt(U"Retart", Scene::Center().movedBy(0, 50))) {
        changeScene(State::Game);
    }
}

void GameOver::draw() const
{
    font50(U"GameOver").drawAt(Scene::Center());
}
