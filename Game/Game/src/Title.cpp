# include "Title.hpp"

void Title::update()
{
    if (isWindow == false) {
        if (KeyUp.down()) selecter1 = 0;
        if (KeyDown.down()) selecter1 = 1;

        if ((KeyEnter | KeyZ).down()) {
            if (selecter1 == 0) isWindow = true;
            else changeScene(State::CharaSelect, 0);
        }
    }
    else {
        if ((KeyEscape | KeyBackspace).down()) isWindow = false;
        if (KeyUp.down() && selecter2 != 1) selecter2--;
        if (KeyDown.down() && selecter2 != getData().dataLv) selecter2++;

        if (KeyEnter.down()) {
            changeScene(State::Game, 0);
        }
    }

}

void Title::draw() const
{
    // 背景
    backTexture.draw(0, 0);

    // Startボタン
    RoundRect(Arg::center(Scene::Center().x, Scene::Center().y + 150),
        btnWidth, btnHeight, 10).draw(Color(224, 255, 255, 200))
        .drawFrame(3, 0, ColorF(0, 0, 0, 0.8));
    font25(U"Start").drawAt(Scene::Center().x, Scene::Center().y + 150, Palette::Black);

    // CharaSelectボタン
    RoundRect(Arg::center(Scene::Center().x, Scene::Center().y + 150 + btnHeight + btnMargin),
        btnWidth, btnHeight, 10).draw(Color(224, 255, 255, 200))
        .drawFrame(3, 0, ColorF(0, 0, 0, 0.8));
    font25(U"CharaSelect").drawAt(Scene::Center().x, Scene::Center().y + 150 + btnHeight + btnMargin, Palette::Black);

    // セレクト枠
    Rect(Arg::center(Scene::Center().x, Scene::Center().y + 150 + selecter1 * (btnHeight + btnMargin)),
        btnWidth, btnHeight).drawFrame(3, 0, Palette::Yellow);

    // 小窓が出ているとき
    if (isWindow) {
        StageSelect::DrawWindow(getData(), selecter2);
    }
}