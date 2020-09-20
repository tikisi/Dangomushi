#include "GameOver.hpp"

void GameOver::update()
{
    backTexture.draw(0, 0);
    if (SimpleGUI::ButtonAt(U"タイトルへ", Scene::Center().movedBy(0, 200))) {
        AudioAsset(U"GameOver_BGM").stop();
        changeScene(State::Title);
    }
    if (SimpleGUI::ButtonAt(U"つづきから", Scene::Center().movedBy(0, 250))) {
        AudioAsset(U"GameOver_BGM").stop();
        changeScene(State::Game);
    }
}

void GameOver::draw() const
{
    font50(U"High Score:  " + Format(getData().highscore) + U" cm").draw(10, 10);
}
