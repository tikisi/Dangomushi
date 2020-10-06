# pragma once
# include "Common.hpp"

// タイトルシーン
class Title : public MyApp::Scene
{
private:
	const Texture backTexture;
    const Font font40;
	const Font font30;
	const Font font25;

	static inline constexpr uint32 btnWidth = 200;
	static inline constexpr uint32 btnHeight = 35;
	static inline constexpr uint32 btnMargin = 30;

	static inline constexpr Point windowSize = Point(640, 480);
	static inline constexpr Point btnSize2 = Point(150, 25);

	uint32 selecter1;
	uint32 selecter2;
	bool isWindow;	// 小窓が出ているか

public:

	Title(const InitData& init) : backTexture(U"Title.png") ,font40(40), font30(30), font25(25), IScene(init) {
		Scene::SetBackground(Palette::Black);
		LoadSaveData(getData());

		selecter1 = 0; 
		selecter2 = 1;
		isWindow = false;

		AudioAsset(U"Title").setLoop(true);
		AudioAsset(U"Title").play();
	}
	~Title() {
		AudioAsset(U"Title").stop();
		ClearPrint();
	}

    void update() override;

    void draw() const override;
};
