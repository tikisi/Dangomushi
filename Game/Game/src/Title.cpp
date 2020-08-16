
# include "Title.hpp"

void Title::update()
{
	if(SimpleGUI::ButtonAt(U"Start", Scene::Center().movedBy(0, 50))) {
		changeScene(State::Game);
	}
	if (SimpleGUI::ButtonAt(U"CharaSelect", Scene::Center().movedBy(0, 100))) {
		changeScene(State::CharaSelect);
	}
}

void Title::draw() const
{
    font50(U"Title").drawAt(Scene::Center());
}
