#pragma once

#include <stdio.h>
#include "Common.hpp"

// タイトルシーン
class GameOver : public MyApp::Scene
{
private:
    const Texture backTexture;
    const Font font50;

public:

    GameOver(const InitData& init) : backTexture(U"GameOverBack.png"), font50(50), IScene(init) {
        AudioAsset(U"GameOver_BGM").play();
    }

    void update() override;

    void draw() const override;
};
