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
        if ((KeyEscape | KeyBackspace).down()) isWindow = false;
        if(KeyUp.down() && selecter2 != 1) selecter2--; 
        if(KeyDown.down() && selecter2 != getData().dataLv) selecter2++;

        if(KeyEnter.down()) {
            changeScene(State::Game);
        }
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
    if (isWindow) {
        Point center = Scene::Center();
        // 背景
        Rect(Arg::center(center), windowSize).draw(ColorF(0, 0, 0, 0.85))
            .drawFrame(0, 3, Palette::Lightyellow);
        // ハイスコア
        font40(U"ハイスコア " + Format(getData().highscore)).drawAt(center - Point(0, windowSize.y / 2 - 30 - 20), Palette::White);

        // Line
        Point startPos = center - Point(0, windowSize.y / 2) + Point(0, 100);
        uint32 lineWidth = windowSize.x / 2 - 35;
        Line(startPos - Point(lineWidth, 0), startPos + Point(lineWidth, 0)).draw(LineStyle::SquareDot, 4, Palette::White);

        startPos += Point(0, 22);
        font25(U"開始するステージを選んでください").drawAt(startPos, Palette::White);

        // ステージ
        startPos += Point(0, 25 + 20);
        Point delta(0, 25 + 20);

        uint32 Lv = getData().dataLv;
        for (int i = 1; i <= Lv; i++) {
            if (i != 7)
                font25(U"Level " + Format(i)).drawAt(startPos + (i - 1) * delta, Palette::White);
            else
                font25(U"BossBattle").drawAt(startPos + (i - 1) * delta, Palette::White);
        }
        // カーソル
        Rect(Arg::center(startPos + (int)(selecter2 - 1) * delta), btnSize2).drawFrame(0, 2, Palette::Yellow);
    }
}

