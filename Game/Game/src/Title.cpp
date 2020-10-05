# include "Title.hpp"

void Title::update()
{
    backTexture.draw(0, 0);
    /*if(SimpleGUI::ButtonAt(U"Start", Scene::Center().movedBy(0, 50))) {
        getData().SelectNum = 1; // ダンゴムシに設定
        changeScene(State::Game);
    }
    if (SimpleGUI::ButtonAt(U"CharaSelect", Scene::Center().movedBy(0, 100))) {
        changeScene(State::CharaSelect);
    }*/

    if (isWindow == false) {
        if (KeyUp.down()) selecter1 = 0;
        if (KeyDown.down()) selecter1 = 1;

        if ((KeyEnter | KeyZ).down()) {
            if (selecter1 == 0) isWindow = true;
            else changeScene(State::CharaSelect);
        }
    }
    else {
        if((KeyEscape | KeyBackspace).down()) isWindow = false;
    }

}

void Title::draw() const
{
    //font50(U"High Score:  " + Format(getData().highscore) + U" cm").draw(10, 10);
    //Rect(Scene::Center, btnWidth, btnHeight).draw()

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
    if(isWindow) {
        Rect(Arg::center(Scene::Center()), windowSize).draw(ColorF(0, 0, 0, 0.85));
        uint32 Lv = getData().dataLv;
        for(int i = 0; i < Lv; i++) {
              
        }
    }
}

