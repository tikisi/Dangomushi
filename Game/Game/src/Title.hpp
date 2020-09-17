
# pragma once
# include "Common.hpp"

// タイトルシーン
class Title : public MyApp::Scene
{
private:
	const Texture backTexture;
    const Font font50;

public:

	Title(const InitData& init) : backTexture(U"Title.png") ,font50(50), IScene(init) {
		Scene::SetBackground(Palette::Black);
		ClearPrint();
        getData().dataLv = 1;
		AudioAsset(U"Title").setLoop(true);
		AudioAsset(U"Title").play();
	}

    void update() override;

    void draw() const override;
};
