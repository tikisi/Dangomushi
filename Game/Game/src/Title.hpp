
# pragma once
# include "Common.hpp"

// タイトルシーン
class Title : public MyApp::Scene
{
private:
	const Font font50;

public:

	Title(const InitData& init) : font50(50), IScene(init) {}

	void update() override;

	void draw() const override;
};
