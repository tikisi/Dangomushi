#pragma once

#include <stdio.h>
#include "Common.hpp"

// タイトルシーン
class GameClear : public MyApp::Scene
{
private:
    const Texture gameClearTex;
    const Font font50;
    const Font font20;

public:

    GameClear(const InitData& init) : gameClearTex(U"asset/GameClear.jpg"), font50(50), font20(20, Typeface::Bold), IScene(init) {
        AudioAsset(U"GameOver_BGM").play();
    }

    void update() override;

    void draw() const override;
};
