#include "GameOver.hpp"

void GameOver::update()
{
    gameOverTex.draw(0, 0);
    //gameClearTex
    if (SimpleGUI::ButtonAt(U"タイトルへ", Scene::Center().movedBy(0, 200)) && KeyEnter.down()) {
        AudioAsset(U"GameOver_BGM").stop();
        changeScene(State::Title);
    }
    
}

void GameOver::draw() const
{
    font50(U"High Score:  " + Format(getData().highscore) + U" cm").draw(10, 10);
}
