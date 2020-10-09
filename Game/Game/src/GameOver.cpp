#include "GameOver.hpp"

void GameOver::update()
{
    gameOverTex.draw(0, 0);
    //gameClearTex
    if (/*SimpleGUI::ButtonAt(U"[Enter] タイトルへ", Scene::Center().movedBy(0, 200)) || */KeyEnter.down()) {
        AudioAsset(U"GameOver_BGM").stop();
        changeScene(State::Title);
    }
}

void GameOver::draw() const
{
    font50(U"High Score:  " + Format(getData().highscore) + U" cm").draw(10, 10);
    RoundRect(290, 500, 220, 45, 10).draw(Palette::White).drawFrame(2,0,Palette::Black);
    font20(U"[Enter] タイトルへ").draw(310, 506, Palette::Black);
}
