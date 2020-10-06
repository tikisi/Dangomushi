#pragma once

#include <stdio.h>
#include "Common.hpp"

// タイトルシーン
class GameClear : public MyApp::Scene
{
private:
    const Texture gameClearTex;
    const Font font50;

public:

    GameClear(const InitData& init) : gameClearTex(U"GameClear.jpg"), font50(50), IScene(init) {
        AudioAsset(U"GameOver_BGM").play();
    }

    void update() override;

    void draw() const override;
};
