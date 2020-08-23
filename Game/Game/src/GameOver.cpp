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
    if (SimpleGUI::ButtonAt(U"Retart", Scene::Center().movedBy(0, WINDOW_HEIGHT / 2 - 50))) {
        AudioAsset(U"GameOver_BGM").stop();
        changeScene(State::Title);
    }
}

void GameOver::draw() const
{
}
