//
//  GameOver.hpp
//  Game
//
//  Created by Ryoma Usui on 2020/08/23.
//

#ifndef GameOver_hpp
#define GameOver_hpp

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


#endif /* GameOver_hpp */
