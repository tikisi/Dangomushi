#pragma once
#include"Common.hpp"

class CharaSelect : public MyApp::Scene
{
private:

    int SelectNUM = 1;
    int species;

    Texture model_player, model_sub, pickup_sub;
    Texture s1dango, s2dango, j1dango, j2dango, j3dango;
    Texture s1ebi, s2ebi, j1ebi, j2ebi, j3ebi, j4ebi;
    Texture s1yado, s2yado, j1yado, j2yado, j3yado, j4yado;
    Texture s1gdango, s2gdango, s3gdango, s4gdango, s5gdango, j1gdango, j2gdango, j3gdango, j4gdango, j5gdango;
    Texture s1kurowa, s2kurowa, j1kurowa, j2kurowa, j3kurowa, j4kurowa;

    int walkCount;
    int jumpCount;
    int spinCount;
    bool orLeft;
    double speedX;
    double posX;
    double speedY;
    double posY;

    Font font30;
    Font font60;
    Font font20;

    // Stage選択Window
    bool isWindow;  // ステージ選択Windowを表示するか
    uint32 stageSelecter;

public:

    CharaSelect(const InitData& init)
        : font30(30), font60(60), font20(20, Typeface::Bold), IScene(init)
    {
        //if(species=<4)
        //ボス倒したら
        //species++;
        //早くクリアしたら
        //species++;
        species = getData().releasedChara;


        // 一回だけ 
        s1dango = Texture(U"player/dangomushi/s1dangomushi.png");
        s2dango = Texture(U"player/dangomushi/s2dangomushi.png");
        j1dango = Texture(U"player/dangomushi/j1dangomushi.png");
        j2dango = Texture(U"player/dangomushi/j2dangomushi.png");
        j3dango = Texture(U"player/dangomushi/j3dangomushi.png");

        s1ebi = Texture(U"player/ebi/s1ebi.png");
        s2ebi = Texture(U"player/ebi/s2ebi.png");
        j1ebi = Texture(U"player/ebi/j1ebi.png");
        j2ebi = Texture(U"player/ebi/j2ebi.png");
        j3ebi = Texture(U"player/ebi/j3ebi.png");
        j4ebi = Texture(U"player/ebi/j4ebi.png");

        s1yado = Texture(U"player/yadokari/s1yadokari.png");
        s2yado = Texture(U"player/yadokari/s2yadokari.png");
        j1yado = Texture(U"player/yadokari/j1yadokari.png");
        j2yado = Texture(U"player/yadokari/j2yadokari.png");
        j3yado = Texture(U"player/yadokari/j3yadokari.png");
        j4yado = Texture(U"player/yadokari/j4yadokari.png");

        s1gdango = Texture(U"player/gdangomushi/s1gdangomushi.png");
        s2gdango = Texture(U"player/gdangomushi/s2gdangomushi.png");
        s3gdango = Texture(U"player/gdangomushi/s3gdangomushi.png");
        s4gdango = Texture(U"player/gdangomushi/s4gdangomushi.png");
        s5gdango = Texture(U"player/gdangomushi/s5gdangomushi.png");
        j1gdango = Texture(U"player/gdangomushi/j1gdangomushi.png");
        j2gdango = Texture(U"player/gdangomushi/j2gdangomushi.png");
        j3gdango = Texture(U"player/gdangomushi/j3gdangomushi.png");
        j4gdango = Texture(U"player/gdangomushi/j4gdangomushi.png");
        j5gdango = Texture(U"player/gdangomushi/j5gdangomushi.png");

        s1kurowa = Texture(U"player/kurowassan/s1kurowassan.png");
        s2kurowa = Texture(U"player/kurowassan/s2kurowassan.png");
        j1kurowa = Texture(U"player/kurowassan/j1kurowassan.png");
        j2kurowa = Texture(U"player/kurowassan/j2kurowassan.png");
        j3kurowa = Texture(U"player/kurowassan/j3kurowassan.png");
        j4kurowa = Texture(U"player/kurowassan/j4kurowassan.png");

        walkCount = 0;
        jumpCount = 0;
        spinCount = 0;
        orLeft = true;
        speedX = 0;
        speedY = 0;
        posX = 550;
        posY = 410;

        isWindow = false;
        stageSelecter = 1;
    }

    ~CharaSelect() {
        getData().selectedLv = stageSelecter;
    }

    void update() override
    {
        if (isWindow == false) {
            // キャラ選択完了
            if (SelectNUM <= species){
                RoundRect(450, 495,220,45,10).draw(Palette::White);
                font20(U"[Enter] GameStart").draw(460, 500, Palette::Black);

                if (KeyEnter.down()) {
                    RoundRect(450, 495, 220, 45, 10).drawFrame(3, 3, Palette::Yellow);
                    getData().SelectNum = SelectNUM;
                    isWindow = true;
                }
            }

            // キャラ切り替え
            if (KeyUp.down()) SelectNUM--;
            if (KeyDown.down()) SelectNUM++;

            if (SelectNUM < 1) SelectNUM = 5;
            if (5 < SelectNUM) SelectNUM = 1;

            // 左右の向き
            if (KeyLeft.pressed() && !KeyRight.pressed()) orLeft = true;
            else if (!KeyLeft.pressed() && KeyRight.pressed()) orLeft = false;

            // 歩くアニメーション
            if ((KeyLeft.pressed() && !KeyRight.pressed()) || (!KeyLeft.pressed() && KeyRight.pressed())) {
                walkCount++;

                if (orLeft && speedX == 0) speedX = -0.8;
                if (!orLeft && speedX == 0) speedX = 0.8;

                if (orLeft) speedX -= 0.1;
                else speedX += 0.1;
            }
            else {
                speedX = 0;
            }
            posX += speedX;

            if (10 < walkCount) walkCount = 0;

            if (posX < 435) {
                posX = 435;
                speedX = 0;
            }
            if (665 < posX) {
                posX = 665;
                speedX = 0;
            }

            // 跳ぶアニメーション
            if (posY == 410 && KeySpace.down()) {
                speedY += 10.0 * 1.2;
                jumpCount = 1;
                spinCount = 1;
            }
            if (1 <= jumpCount) {
                jumpCount++;
                spinCount++;

                if (KeySpace.pressed() && jumpCount <= 9) {
                    speedY += 0.7 * 1.2;
                }
                speedY -= 0.4;
                speedY *= 0.98;
                posY -= speedY;
            }
            if (410 < posY) {
                jumpCount = 0;
                spinCount = 0;
                speedY = 0;
                posY = 410;
            }


            if (SelectNUM == 1) {
                pickup_sub = s1dango;

                if (16 < spinCount) spinCount = 6;

                if (11 <= spinCount) model_player = j3dango;
                else if (6 <= spinCount) model_player = j2dango;
                else if (1 <= spinCount) model_player = j1dango;
                else if (walkCount <= 5) model_player = s1dango;
                else if (walkCount <= 10) model_player = s2dango;
            }
            if (SelectNUM == 2) {
                pickup_sub = s1ebi;

                if (21 < spinCount) spinCount = 1;

                if (16 <= spinCount) model_player = j4ebi;
                else if (11 <= spinCount) model_player = j3ebi;
                else if (6 <= spinCount) model_player = j2ebi;
                else if (1 <= spinCount) model_player = j1ebi;
                else if (walkCount <= 5) model_player = s1ebi;
                else if (walkCount <= 10) model_player = s2ebi;
            }
            if (SelectNUM == 3) {
                pickup_sub = s1yado;

                if (21 < spinCount) spinCount = 1;

                if (16 <= spinCount) model_player = j4yado;
                else if (11 <= spinCount) model_player = j3yado;
                else if (6 <= spinCount) model_player = j2yado;
                else if (1 <= spinCount) model_player = j1yado;
                else if (walkCount <= 5) model_player = s1yado;
                else if (walkCount <= 10) model_player = s2yado;
            }
            if (SelectNUM == 4) {
                pickup_sub = s1gdango;

                if (26 < spinCount) spinCount = 1;

                if (21 <= spinCount) model_player = j1gdango;
                else if (16 <= spinCount) model_player = j2gdango;
                else if (11 <= spinCount) model_player = j3gdango;
                else if (6 <= spinCount) model_player = j4gdango;
                else if (1 <= spinCount) model_player = j5gdango;
                else if (walkCount <= 2) model_player = s1gdango;
                else if (walkCount <= 4) model_player = s2gdango;
                else if (walkCount <= 6) model_player = s3gdango;
                else if (walkCount <= 8) model_player = s4gdango;
                else if (walkCount <= 10) model_player = s5gdango;
            }
            if (SelectNUM == 5) {
                pickup_sub = s1kurowa;

                if (21 < spinCount) spinCount = 1;

                if (16 <= spinCount) model_player = j4kurowa;
                else if (11 <= spinCount) model_player = j3kurowa;
                else if (6 <= spinCount) model_player = j2kurowa;
                else if (1 <= spinCount) model_player = j1kurowa;
                else if (walkCount <= 5) model_player = s1kurowa;
                else if (walkCount <= 10) model_player = s2kurowa;
            }
        }
        else {
            if ((KeyEscape | KeyBackspace).down()) isWindow = false;
            if (KeyUp.down() && stageSelecter != 1) stageSelecter--;
            if (KeyDown.down() && stageSelecter != getData().dataLv) stageSelecter++;

            if (KeyEnter.down()) {
                if(stageSelecter != 7) changeScene(State::Game);
                else changeScene(State::BattleScene);
            }
        }

#ifdef DEBUG
        ClearPrint();
        Print << U"SelectNUM" << SelectNUM;
        Print << U"species" << species;
        //Print << U"posY" << posY;
        //Print << U"jumpCount" << jumpCount;
        //Print << U"spinCount" << spinCount;
#endif	
    }

    void draw() const override
    {
        Scene::SetBackground(ColorF(Palette::Black));

        //モデルの動く枠
        Rect(400, 100, 300, 360).draw(Palette::Blue).drawFrame(5, 0, Palette::White);

        if (SelectNUM <= species) {
            if (orLeft) model_player.scaled(1.2).drawAt(posX, posY);
            else model_player.mirrored().scaled(1.2).drawAt(posX, posY);
        }
        else {
            if (orLeft) model_player.scaled(1.2).drawAt(posX, posY, Palette::Black);
            else model_player.mirrored().scaled(1.2).drawAt(posX, posY, Palette::Black);
        }

        Triangle(550, 110, 540, 115, 560, 115).draw(Palette::White);
        Triangle(550, 450, 540, 445, 560, 445).draw(Palette::White);

        //キャラ一覧部分
        for (int i = 1; i <= 5; i++) {
            Rect(Arg::center(750, 60 + 80 * i), 60, 60).draw(Palette::Skyblue);
        }
        Rect(Arg::center(750, 60 + 80 * SelectNUM), 80, 80).draw(Palette::Lemonchiffon); //.drawFrame(3, 0, Palette::Yellow);

        s1dango.scaled(0.7).drawAt(750, 140);

        s1ebi.scaled(0.7).drawAt(750, 220);

        s1yado.scaled(0.7).drawAt(750, 300);

        if (species < 4) {
            s1gdango.scaled(0.7).drawAt(750, 380, Palette::Black);
        }
        else {
            s1gdango.scaled(0.7).drawAt(750, 380);
        }

        if (species < 5) {
            s1kurowa.scaled(0.7).drawAt(750, 460, Palette::Black);
        }
        else {
            s1kurowa.scaled(0.7).drawAt(750, 460);
        }
        //選択中のキャラ
        if (SelectNUM <= species)
            pickup_sub.scaled(0.7 * 1.4).drawAt(750, 60 + 80 * SelectNUM);
        else
            pickup_sub.scaled(0.7 * 1.4).drawAt(750, 60 + 80 * SelectNUM, Palette::Black);

        //名前と説明
        if (SelectNUM == 1) {
            font60(U"ダンゴムシ").drawAt(200, 100, Palette::White);
            font30(U"txt1").draw(40, 150, Palette::White);
        }
        else if (SelectNUM == 2) {
            //font60(U"エビ").drawAt(200, 100, Palette::White);
            //font30(U"txt2").draw(40, 150, Palette::White);
        }
        else if (SelectNUM == 3) {
            font60(U"ヤドカリ").drawAt(200, 100, Palette::White);
            font30(U"txt3").draw(40, 150, Palette::White);
        }
        else if (SelectNUM == 4 && 4 <= species) {
            font60(U"虹ダンゴムシ").drawAt(200, 100, Palette::White);
            font30(U"txt4").draw(40, 150, Palette::White);
        }
        else if (SelectNUM == 5 && 5 <= species) {
            font60(U"クロワッサン").drawAt(200, 100, Palette::White);
            font30(U"txt5").draw(40, 150, Palette::White);
        }
        else font60(U"???").drawAt(200, 100, Palette::White);

        // ステージ選択画面
        if (isWindow) {
            StageSelect::DrawWindow(getData(), stageSelecter);
        }
    }
};
