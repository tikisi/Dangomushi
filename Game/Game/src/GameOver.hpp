#pragma once

#include <stdio.h>
#include "Common.hpp"

// タイトルシーン
class GameOver : public MyApp::Scene
{
private:
    const Texture gameOverTex;
    const Texture gameClearTex;
    const Font font50;

public:

    GameOver(const InitData& init) : gameOverTex(U"GameOverBack.png"), gameClearTex(U"StageClear.jpeg"), font50(50), IScene(init) {
        AudioAsset(U"GameOver_BGM").play();
    }

    void update() override;

    void draw() const override;
};

