#include "GameClear.hpp"

void GameClear::update()
{
    gameClearTex.draw(0, 0);
    //gameClearTex
    if (/*SimpleGUI::ButtonAt(U"[Enter] タイトルへ", Scene::Center().movedBy(-100, 200)) || */KeyEnter.down()) {
        AudioAsset(U"GameOver_BGM").stop();
        changeScene(State::Title);
    }
//    if (SimpleGUI::ButtonAt(U"つづきから", Scene::Center().movedBy(0, 250))) {
//        AudioAsset(U"GameOver_BGM").stop();
//        changeScene(State::Game);
//    }
}

void GameClear::draw() const
{
    font50(U"High Score:  " + Format(getData().highscore) + U" cm").draw(10, 10);
    RoundRect(190, 490, 220, 45, 10).draw(Palette::White).drawFrame(2, 0, Palette::Black);
    font20(U"[Enter] タイトルへ").draw(210, 496, Palette::Black);
}
