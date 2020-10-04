
# include "Title.hpp"

void Title::update()
{
	backTexture.draw(0, 0);
	if(SimpleGUI::ButtonAt(U"Start", Scene::Center().movedBy(0, 50))) {
		getData().SelectNum = 1; // ダンゴムシに設定
		changeScene(State::Game);
	}
	if (SimpleGUI::ButtonAt(U"CharaSelect", Scene::Center().movedBy(0, 100))) {
		changeScene(State::CharaSelect);
	}
}

void Title::draw() const
{
    font50(U"High Score:  " + Format(getData().highscore) + U" cm").draw(10, 10);
}

